#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/version.h>
#include<linux/string.h>
#include<linux/fs.h>
#include<linux/reboot.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Joel Cecil");
MODULE_DESCRIPTION("Shutdown Program");
MODULE_VERSION("0.1");

static ssize_t readopt(struct file *,char *,size_t ,loff_t *);
static ssize_t shutdown(struct file *,const char *,size_t ,loff_t *);
static int open_dev(struct inode *,struct file *);
static int close_dev(struct inode *,struct file *);
int major;

int atoi(const char *str) {
    int res=0,i=0;
    for(i=0;str[i]!='\0';i++)
        res=res*10+str[i]-'0';
    return res;
}

static struct file_operations fops={
    .open=open_dev,
    .release=close_dev,
    .read=readopt,
    .write=shutdown,
};

static ssize_t readopt(struct file *filep,char *buff,size_t len,loff_t *f_ops) {
    char *b=kmalloc(40*sizeof(char),GFP_KERNEL);
    char msg[20] = "Incorrect option";
    sprintf(b,"%s",msg);
    copy_to_user(buff,b,strlen(b));
    printk("Reading option\n");
    return len;
}


ssize_t shutdown(struct file *filp,const char *buff,size_t len,loff_t *off) {
    char *b=kmalloc(30*sizeof(char),GFP_KERNEL);
    long int i;
    copy_from_user(b,buff,len);
    i=atoi(b);
    switch(i) {
	case 1: kernel_power_off(); break;
	case 2: kernel_restart(NULL); break;
    }
    return len;
}

static int open_dev(struct inode *a,struct file *filep) {
    printk(KERN_INFO "Shutdown device opened\n");
    return 0;
}

static int close_dev(struct inode *a,struct file *filep) {
    printk(KERN_INFO "Shutdown device closed\n");
    return 0;
}

static int __init shutdown_start(void) {
    if((major=(register_chrdev(0,"shutdown",&fops)))<0) {
        return -1;
    }
    printk(KERN_INFO "Shutdown device loaded%d\n",major);
    return 0;
}

static void __exit shutdown_end(void) {
    unregister_chrdev(major,"shutdown");
    printk(KERN_INFO "Shutdown device unloaded\n");
}

module_init(shutdown_start);
module_exit(shutdown_end);
