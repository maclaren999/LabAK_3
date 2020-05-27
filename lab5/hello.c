#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/ktime.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/slab.h>

MODULE_AUTHOR("Serhii Popovych <serhii.popovych@globallogic.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

static uint howmany = 1;

module_param(howmany, uint, S_IRUGO);
MODULE_PARM_DESC(howmany, "Unsigned int, determines how many lines will be printed");

struct my_data {
	struct list_head list_node;
	ktime_t time_;
};

static LIST_HEAD(my_list_head);
static int __init hello_init(void)
{
	int err = -EINVAL;
	uint i;
	ktime_t time_;
	struct my_data *ptr, *temp;
	if (howmany == 0 || (howmany >= 5 && howmany <= 10)) {
		printk(KERN_EMERG "Alert! Veird number detected\n");
	}
	if (howmany > 10) {
            printk(KERN_ERR "Error! Big value is introduced!\n");
		return err;
	}
	for (i = 0; i < howmany; i++) {
		time_ = ktime_get();
		printk(KERN_INFO "Hello, world!\n");
		ptr = (struct my_data *) kmalloc(sizeof(struct my_data), GFP_KERNEL);
		if (ZERO_OR_NULL_PTR(ptr)) {
			goto err_exit;
		}
		*ptr = (struct my_data)
		{
			(struct list_head) {NULL, NULL}, time_
		};
		list_add_tail(&ptr->list_node, &my_list_head);
	}
	return 0;
	err_exit:
	list_for_each_entry_safe(ptr, temp, &my_list_head, list_node) {
		list_del(&ptr->list_node);
		kfree(ptr);
	}
	printk(KERN_ERR "Error! Something wrong with memory\n");
	return -1;
}

static void __exit hello_exit(void)
{
	struct my_data *ptr, *temp;
	list_for_each_entry_safe(ptr, temp, &my_list_head, list_node) {
		printk(KERN_INFO "time=%lld\n", ptr->time_);
		list_del(&ptr->list_node);
		kfree(ptr);
	}
	printk(KERN_EMERG "Goodbye! See your again!\n");
}
module_init(hello_init);
module_exit(hello_exit);
