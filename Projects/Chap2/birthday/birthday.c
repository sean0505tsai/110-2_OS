#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

MODULE_DESCRIPTION("list birthday");
MODULE_LICENSE("GPL");

struct Birthday {
	char* name;
	int year;
	int month;
	int day;
	struct list_head list;
};

static LIST_HEAD(birthday_list);

static int birthday_init(void){
	struct Birthday* birPtr;
	int i = 0;
	char* name[5] = {"Sandy", "Brynn", "Dorrina", "Grace", "Wei"};
	int year[5] = {1998, 1998, 1998, 1999, 1999};
	int month[5] = {10, 11, 9, 5, 6};
	int day[5] = {18, 9, 24, 30, 14};

	printk(KERN_INFO "Creating birthday list\n");
	while (i < 5){
		birPtr = kmalloc(sizeof(*birPtr), GFP_KERNEL);
		birPtr->name = name[i];
		birPtr->year = year[i];
		birPtr->month = month[i];
		birPtr->day = day[i];
		INIT_LIST_HEAD(&(birPtr->list));
		list_add_tail(&(birPtr->list), &birthday_list);
		i++;
	}

	list_for_each_entry(birPtr, &birthday_list, list) {
		printk(KERN_INFO "Adding %s's birthday which is %d/%d/%d\n",
			birPtr->name,
			birPtr->year,
			birPtr->month,
			birPtr->day);
	}
	
	return 0;
}

static void birthday_exit(void){
	struct Birthday *birPtr = NULL, *next = NULL;
	printk(KERN_INFO "Removing birthday list\n");

	list_for_each_entry_safe(birPtr, next, &birthday_list, list){
		printk(KERN_INFO "Removing %s's birthday which is %d/%d/%d\n",
			birPtr->name,
			birPtr->year,
			birPtr->month,
			birPtr->day);
		list_del(&(birPtr->list));
		kfree(birPtr);
	}
}

module_init(birthday_init);
module_exit(birthday_exit);
