#include<linux/module.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<linux/kernel.h>
MODULE_LICENSE("Dual BSD/GPL");

static int hello_init(void)
{

	printk(KERN_INFO"Hello World!\n");
	printk("Process ID:%d\n",current->pid);
	//printk("Scheduling policy:= %d\n",);
	printk("over\n");
	return 0;	
}

static int hello_exit(void)
{
	printk(KERN_INFO  "driver unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);
