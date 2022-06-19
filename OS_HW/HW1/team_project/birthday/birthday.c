#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

MODULE_DESCRIPTION("birthday");
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
	struct Birthday* birthPtr;
	int i = 0;
	char* name[5] = {"Sean", "Zoe", "Kenny", "Annie", "Bob"};
	int year[5] = {2000, 2000, 2001, 2001, 2001};
	int month[5] = {11, 3, 9, 10, 4};
	int day[5] = {18, 19, 2, 29, 6};

	printk(KERN_INFO "Create the list of birthday\n");
	while (i < 5){
		birthPtr = kmalloc(sizeof(*birthPtr), GFP_KERNEL);

		birthPtr->name=name[i];
		birthPtr->year=year[i];
		birthPtr->month=month[i];
		birthPtr->day=day[i];

		INIT_LIST_HEAD(&(birthPtr->list));
		list_add_tail(&(birthPtr->list), &birthday_list);
		i++;
	}

	list_for_each_entry(birthPtr, &birthday_list, list) {
		printk(KERN_INFO "Add %s's birthday which is %d/%d/%d\n",
			birthPtr->name,
			birthPtr->year,
			birthPtr->month,
			birthPtr->day);
	}

	return 0;
}

static void birthday_exit(void){
	struct Birthday *birthPtr = NULL, *next = NULL;
	printk(KERN_INFO "Remove the list of birthday\n");

	list_for_each_entry_safe(birthPtr, next, &birthday_list, list){
		printk(KERN_INFO "Remove %s's birthday which is %d/%d/%d\n",
			birthPtr->name,
			birthPtr->year,
			birthPtr->month,
			birthPtr->day);
		list_del(&(birthPtr->list));
		kfree(birthPtr);
	}
}

module_init(birthday_init);
module_exit(birthday_exit);
