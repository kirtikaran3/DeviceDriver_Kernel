#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aamulya Sehgal");

static int maxsize=8;

static int a[8]={0,0,0,0,0,0,0,0};

module_param_array(a, int, &maxsize, S_IRUSR);

int exportFunction(void)
{
	int i;
	printk(KERN_ALERT "This function will export.\n");
	for(i=0;i<maxsize;i++)
		printk(KERN_ALERT "%d ",a[i]);
	printk(KERN_ALERT "\n");
	return 0;
}

EXPORT_SYMBOL(exportFunction);

static int moduleInit(void)
{
	printk(KERN_ALERT "Hello export function.\n");
	return 0;
}

static void moduleExit(void)
{
	printk(KERN_ALERT "Bye Bye --exportsymbol\n");
}

module_init(moduleInit);
module_exit(moduleExit);
