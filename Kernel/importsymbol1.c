#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aamulya Sehgal");

int display(void);

static int moduleInit(void)
{
	printk(KERN_ALERT "Hello import1 function.\n");
	display();
	return 0;
}

static void moduleExit(void)
{
	printk(KERN_ALERT "Bye Bye --importsymbol1\n");
}

module_init(moduleInit);
module_exit(moduleExit);
