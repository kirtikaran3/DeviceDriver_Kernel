#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aamulya Sehgal");

int exportFunction(void);

int display(void)
{
	printk(KERN_ALERT "Displaying array.\n");
	exportFunction();
	printk(KERN_ALERT "Printed the array.\n");
	return 0;
}

EXPORT_SYMBOL(display);

static int moduleInit(void)
{
	printk(KERN_ALERT "Hello import function.\n");
	exportFunction();
	return 0;
}

static void moduleExit(void)
{
	printk(KERN_ALERT "Bye Bye --importsymbol\n");
}

module_init(moduleInit);
module_exit(moduleExit);
