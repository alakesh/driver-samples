/* **************** LF331:1.6 s_15/lab2_maxvmalloc.c **************** */
/*
 * The code herein is: Copyright the Linux Foundation, 2011
 *
 * This Copyright is retained for the purpose of protecting free
 * redistribution of source.
 *
 *     URL:    http://training.linuxfoundation.org
 *     email:  trainingquestions@linuxfoundation.org
 *
 * The primary maintainer for this code is Jerry Cooperstein
 * The CONTRIBUTORS file (distributed with this
 * file) lists those known to have contributed to the source.
 *
 * This code is distributed under Version 2 of the GNU General Public
 * License, which you should have received with the source.
 *
 */
/*
 * Testing Maximum Memory Allocation (vmalloc)
 @*/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/vmalloc.h>

static int mem = 64;
module_param(mem, int, S_IRUGO);

#define MB (1024*1024)

static int __init my_init(void)
{
	static char *vm_buff;
	int size;

	/* try vmalloc */

	for (size = 4 * MB; size <= mem * MB; size += 4 * MB) {
		printk(KERN_INFO " pages=%6ld, size=%8d ", size / PAGE_SIZE,
		       size / MB);
		if (!(vm_buff = (char *)vmalloc(size))) {
			printk(KERN_ERR "... vmalloc failed\n");
			break;
		}
		printk(KERN_INFO "... vmalloc OK\n");
		vfree(vm_buff);
	}

	return 0;
}

static void __exit my_exit(void)
{
	printk(KERN_INFO "Module Unloading\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jerry Cooperstein");
MODULE_DESCRIPTION("LF331:1.6 s_15/lab2_maxvmalloc.c");
MODULE_LICENSE("GPL v2");
