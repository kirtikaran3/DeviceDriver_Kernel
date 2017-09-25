#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aamulya Sehgal");

int param=0;

module_param(param, int, S_IRUSR | S_IWUSR);

void display(void)
{
	printk(KERN_ALERT "The value is %d.\n", param);
}

static int hello_init(void)
{
	printk(KERN_ALERT "Hello Linux!\n");
	display();
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "Bye Linux!\n");
}
module_init(hello_init);
module_exit(hello_exit);
