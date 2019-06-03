#include<linux/init.h>
#include<linux/module.h>
#include<linux/types.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/sched.h>
#include<asm/current.h>
#include<asm/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");

#denfine DRIVER_NAME "devonw"

static int devone_devs =1;
static int devone_major = 0;
module_param(devone_major , uint,0);
static struct cdev devonw_cdev;

struct devone_data{
	unsigned char val;
	rwlock_t lock;
};

ssize_t devone_write(struct file *filp,const char __user *buf,size_t count ,loff_t *f_pos)
{
	struct devone_data 8p =filp->private_data;
	unsigned char val;
	int retval= 0;

	printk("%s:count  %d pos %lld\n",__func__,count, *f_pos);

	if(count >=1){
		if(copy_from_user(&val, &buf[0],1)){
			retvail=-EFAULT;
			goto out;
		}
		
			write_lock(&p->lock);
			p->val=val;
			write_unlock(&p->lock);
			retval=count;
	}
out:
	return (retval);

}

