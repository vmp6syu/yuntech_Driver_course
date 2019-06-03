#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/semaphore.h>
#include <asm/uaccess.h>
#include <linux/uaccess.h>


//*1 Creat a structure for our test device

struct test_device {
	char data[100];
	struct semaphore sem;
} virtual_device;

//*2 To later register our device it needs a cdev object and some variables

struct cdev *mcdev;	//m stands 'my'
int major_number;	//store our major number
int ret;		//used to hold return values of functions

dev_t dev_num;		//hold major numbel that kernel give

#define DEVICE_NAME	"testdevice"	//name --> appeas in /proc/devices


//******************************************************************************************************
//*7 called on device_file open

int device_open(struct inode *inode, struct file *filp){
	
	//only allow one process to open this device by using a semaphore as mutual exclusve lock- mutex	
	if(down_interruptible(&virtual_device.sem) !=0){
		printk(KERN_ALERT "test: couldn't lock device during open");
		return -1;
	}	

	printk(KERN_INFO "test: open device");
	return 0;
}
//******************************************************************************************************


//******************************************************************************************************
//*8 called when user want to get information from the device

ssize_t device_read(struct file* filp, char* bufStoreData, size_t bufCount, loff_t* curOffset){
	//take data from kernel space(device) to user space(process)
	printk(KERN_INFO "test: reading from device");
	ret = copy_to_user(bufStoreData, virtual_device.data, bufCount);	
	return ret;
}

//******************************************************************************************************

//******************************************************************************************************
//*9 called when user want to send information to the device

ssize_t device_write(struct file* filp, const char* bufStoreData, size_t bufCount, loff_t* curOffset){
	//send data from user kernel
	printk(KERN_INFO "test: writing to device");
	ret=copy_from_user(virtual_device.data, bufStoreData, bufCount);
	return ret;
}

//******************************************************************************************************

//******************************************************************************************************
//*7 called upon user close

int device_close(struct inode *inode, struct file *filp){
	
	up(&virtual_device.sem);
	printk(KERN_INFO "test: close device");
	return 0;
}
//******************************************************************************************************



//******************************************************************************************************
//*6 tell the kernel which functions to call when user operates on our device file
struct file_operations fops = {
	.owner = THIS_MODULE,		//prevent unloadind of this module when operations are in use
	.open = device_open,		//points to the method to call when opening the device
	.release = device_close,	//points to the method to call when closing the device
	.write = device_write,		//points to the method to call when writing to the device
	.read = device_read		//points to the method to call when reading from the device
};
//******************************************************************************************************

//*3 register our device with the system: a teo process


static int driver_entry(void){

	//step 1 use dynamic allocation to assign our devicce

	ret = alloc_chrdev_region(&dev_num,0,1,DEVICE_NAME);
	if(ret<0){
		printk(KERN_ALERT "test: failed to allocate amajor number");
		return ret;	//propagate error
	}
	major_number = MAJOR(dev_num);	//extracts the major number and store our variable
	printk(KERN_INFO "test: major number is %d" ,major_number);
	printk(KERN_INFO "use \"mknod /dev/%s c %d 0\" for device file",DEVICE_NAME, major_number); //dmesg

	//step 2

	mcdev = cdev_alloc();	//cerat our cdev structure, initialized our cdev 
	mcdev->ops = &fops;
	mcdev->owner = THIS_MODULE;
	//that we creat cdev, we have to add it to kernel
	ret = cdev_add(mcdev, dev_num, 1);
	if(ret<0){	//check errors
		printk(KERN_ALERT "test: unable to add cdev to kernel");
		return ret;
	}
//*4 Initialize our semaphore

	sema_init(&virtual_device.sem,1);	//initial value of one		
	
	return 0;
}

static void driver_exit(void){
//*5 unregister everything in reverse order
	
	//a)
	cdev_del(mcdev);

	//b)
	unregister_chrdev_region(dev_num, 1);
	printk(KERN_ALERT "test: unloaded module");
}

//inform the kernel where to start and stop with our module/driver



module_init(driver_entry);
module_exit(driver_exit);