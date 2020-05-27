#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
MODULE_AUTHOR("Serhii Popovych <serhii.popovych@globallogic.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");
static uint howmany = 1;
module_param(howmany, uint, S_IRUGO);
static int __init hello_init(void)
{
    int err = -EINVAL;
    uint i;
    if (howmany == 0 || (howmany >= 5 && howmany <= 10))
    {
            printk(KERN_EMERG " Warning! Suspicious number received!\n");
        }
        if (howmany > 10){
            printk(KERN_ERR "Error! Big value is introduced!\n");
            return err;
        }
        for (i = 0; i < howmany; i++){
        printk(KERN_INFO "Hello, world!\n");
    }
    return 0;
}
static void __exit hello_exit(void){
    printk("Goodbye! See your again!\n");
}
module_init(hello_init);
module_exit(hello_exit);
