#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aamulya Sehgal");

static int hello_init(void)
{
	printk(KERN_ALERT "Hello Linux!\n");
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "Bye Linux!\n");
}
module_init(hello_init);
module_exit(hello_exit);
