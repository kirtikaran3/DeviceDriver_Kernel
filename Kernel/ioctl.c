#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<linux/kernel.h>
#include<asm/uaccess.h>
#include<linux/string.h>
#include<linux/ioctl.h>

#define QUERY_SET_VALUE _IOR('q', 1, int *)
#define QUERY_CLEAR_VALUE _IO('q', 2) 
#define QUERY_GET_VALUE _IOW('q', 3, int *)

#define DEVICE_NAME "devchar"
#define CLASS_NAME "dev"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kirti Karan");
MODULE_DESCRIPTION("A simple linux char driver");
MODULE_VERSION("0.1");

static int majorNumber;
static char buf[256]={0};
static short size_of_buf=256;
static int a;
static struct class* devcharClass=NULL;
static struct device* devcharDevice=NULL;

static int dev_open(struct inode*, struct file*);
static int dev_release(struct inode*, struct file*);
static ssize_t dev_read(struct file*, char *, size_t, loff_t *);
static ssize_t dev_write(struct file*, const char *, size_t, loff_t *);
static long my_ioctl(struct file*, unsigned int, unsigned long);

static struct file_operations fops=
{
	.open=dev_open,
	.read=dev_read,
	.write=dev_write,
	.unlocked_ioctl=my_ioctl,
	.release=dev_release,
};

static long my_ioctl(struct file *f, unsigned int cmd, unsigned long arg)
{
	switch(cmd)
	{
		case QUERY_GET_VALUE:
			copy_to_user((int *) arg, &a, sizeof(int));
			break;
		case QUERY_SET_VALUE:
			copy_from_user(&a, (int *) arg, sizeof(int));
			break;
		case QUERY_CLEAR_VALUE:
			break;
	}
	return 0;
}		

static int __init devchar_init(void)
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
	return 0;
}

static void __exit devchar_exit(void)
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
	size_of_buf=strlen(buf);
	err=copy_to_user(buffer, buf, size_of_buf);
	if(err==0)
	{
		printk(KERN_INFO "devchar: Sent %d characters to the user\n", size_of_buf);
		return(size_of_buf=0);
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
	err=copy_from_user(buf, buffer, 256);
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

module_init(devchar_init);
module_exit(devchar_exit);
