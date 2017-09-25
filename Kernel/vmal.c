#include<linux/init.h>
#include<linux/module.h>
#include<linux/vmalloc.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<linux/kernel.h>
#include<asm/uaccess.h>

#define DEVICE_NAME "devchar"
#define CLASS_NAME "dev"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aamulya Sehgal");

static int majorNumber;
static short size_of_ptr=0;
static struct class* devcharClass=NULL;
static struct device* devcharDevice=NULL;

static int dev_open(struct inode*, struct file*);
static int dev_release(struct inode*, struct file*);
static ssize_t dev_read(struct file*, char *, size_t, loff_t *);
static ssize_t dev_write(struct file*, const char *, size_t, loff_t *);

static struct file_operations fops=
{
	.open=dev_open,
	.read=dev_read,
	.write=dev_write,
	.release=dev_release,
};
void *ptr;
size_t size=256;

static int vmal_init(void)
{
	printk(KERN_INFO "devchar: initialising the devchar\n");
	
	majorNumber=register_chrdev(0, DEVICE_NAME, &fops);
	if(majorNumber<0)
	{
		printk(KERN_ALERT "devchar: failed to register a major number.\n");
		return majorNumber;
	}
	printk(KERN_INFO "devchar: registered correctly with major number %d\n",majorNumber);
	devcharClass=class_create(THIS_MODULE, CLASS_NAME);
	if(IS_ERR(devcharClass))
	{
		unregister_chrdev(majorNumber, DEVICE_NAME);
		printk(KERN_ALERT "Failed to register device class\n");
		return PTR_ERR(devcharClass);
	}
	printk(KERN_INFO "devchar: device class registerd correcctly\n");
	devcharDevice=device_create(devcharClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
	if(IS_ERR(devcharDevice))
	{
		class_destroy(devcharClass);
		unregister_chrdev(majorNumber, DEVICE_NAME);
		printk(KERN_ALERT "Failed to create the device\n");
		return PTR_ERR(devcharDevice);
	}
	printk(KERN_INFO "devchar: device class created correctly\n");
	ptr=vmalloc(size);
	if(ptr==(void *) 0)
	{
		printk(KERN_ALERT "Memory allocation faile.\n");
		return 0;
	}
	printk(KERN_INFO "Memory allocated successfully.\n");
	return 0;
}

static void vmal_exit(void)
{
	device_destroy(devcharClass, MKDEV(majorNumber, 0));
	class_unregister(devcharClass);
	class_destroy(devcharClass);
	unregister_chrdev(majorNumber, DEVICE_NAME);
	printk(KERN_INFO "devchar: Goodbye\n");
}

static int dev_open(struct inode *inodep, struct file *filep) 
{
	printk(KERN_INFO "devchar: Device successfully opened\n");
	return 0;
}

static int dev_release(struct inode *inodep, struct file *filep)
{
	printk(KERN_INFO "devchar: Device successfully closed\n");
	return 0;
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset)
{
	int err=0;
	size_of_ptr=strlen(ptr);
	err=copy_to_user(buffer, ptr, size_of_ptr);
	if(err==0)
	{
		printk(KERN_INFO "devchar: Sent %d characters to the user\n", size_of_ptr);
		return(size_of_ptr=0);
	}
	else
	{
		printk(KERN_INFO "devchar: Failed to send %d characters to the user\n", err);
	return -EFAULT;
	}
}

static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset)
{
	int err=0;
	err=copy_from_user(ptr, buffer, 256);
	if(err==0)
	{
		printk(KERN_INFO "devchar: Received %zu characters from the user\n", len);
		return(len);
	}
	else
	{
		printk(KERN_INFO "devchar: Failed to receive %d characters from the user\n", err);
	return -EFAULT;
	}
}

module_init(vmal_init);
module_exit(vmal_exit);
	
