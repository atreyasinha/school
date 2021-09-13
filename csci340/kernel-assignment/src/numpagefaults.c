//
//  aksinha
//  pagefault.c
//  Assignment 1: Writing a Kernel Module
//
//  Created by Atreya Sinha on 09/12/21.
//  Copyright © 2021 Atreya Sinha. All rights reserved.
//
#include <linux/init.h>     // included for __init and __exit macros
#include <linux/kernel.h>   // included for KERN_INFO
#include <linux/module.h>   // included for all kernel modules
#include <linux/proc_fs.h>  // included for proc fs usage
#include <linux/seq_file.h> // included for sequence files
#include <linux/mm.h>       // inclused for all_vm_events

static struct proc_dir_entry *procFile;

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Atreya Sinha");
MODULE_DESCRIPTION("Write your own kernel module");

static int procfile_show(struct seq_file *file, void *v) {
    unsigned long *ret;

    ret = kvmalloc(NR_VM_EVENT_ITEMS * sizeof(unsigned long), GFP_KERNEL);
    
    all_vm_events(ret);
    seq_printf(file, "%lun", ret[PGFAULT]);

    if (ret) {
        kvfree(ret);
    }

    return 0;
}

static int procfile_open(struct inode *node, struct file *file) {
    return single_open(file, procfile_show, NULL);
}

static struct proc_ops fops={
    .proc_open = procfile_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init procfile_init(void) {
    procFile = proc_create("numpagefaults", 0, NULL, &fops);

    if (!procFile) {
        return -ENOMEM;
    }

    return 0;
}

static void __exit procfile_exit(void) {
    remove_proc_entry("numpagefaults", NULL);
}

module_init(procfile_init);
module_exit(procfile_exit);

MODULE_LICENSE("GPL");