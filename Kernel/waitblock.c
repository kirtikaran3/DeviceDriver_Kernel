#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/delay.h>

#define DEVICE_NAME "devchar"
#define CLASS_NAME "dev"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aamulya Sehgal");
MODULE_DESCRIPTION("Waiting Process Demo");

static int majorNumber;
static int majorNumber;
static char buf[256]={0};
static short size_of_buf=256;
static struct class* devcharClass=NULL;
static struct device* devcharDevice=NULL;
static struct task_struct *sleep_task=current;
 

static int open(struct inode *inode, struct file *filp)
{
printk(KERN_INFO "Inside open \n" );
return 0;
}
 
static int release(struct inode *inode, struct file *filp)
{
printk (KERN_INFO "Inside close \n");
return 0;
}
 
static ssize_t read(struct file *filep, char *buffer, size_t len, loff_t *offset)
{
int err=0;
printk(KERN_INFO "Inside read\n");
printk(KERN_INFO "Scheduling out\n");
set_current_state(TASK_INTERRUPTIBLE);
schedule();
printk(KERN_INFO "Woken up\n");
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
 
static ssize_t write(struct file *filep, const char *buffer, size_t len, loff_t *offset)
{
int err=0;
printk(KERN_INFO "Inside Write\n");
wake_up_process(sleep_task);
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
 
static struct file_operations fops = {
.read = read,
.write = write,
.open = open,
.release = release
};
 
static int schd_init (void)
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
 
static void schd_cleanup(void)
{
device_destroy(devcharClass, MKDEV(majorNumber, 0));
	class_unregister(devcharClass);
	class_destroy(devcharClass);
	unregister_chrdev(majorNumber, DEVICE_NAME);
	printk(KERN_INFO "devchar: Goodbye\n");
}

module_init(schd_init);
module_exit(schd_cleanup);
