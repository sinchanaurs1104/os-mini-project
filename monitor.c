#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include "monitor_ioctl.h"

#define DEVICE_NAME "container_monitor"

static int major;

static long monitor_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    struct monitor_request req;

    if (copy_from_user(&req, (void __user *)arg, sizeof(req)))
        return -EFAULT;

    switch (cmd) {
    case MONITOR_REGISTER:
        printk(KERN_INFO "[monitor] REGISTER pid=%d container=%s soft=%lu hard=%lu\n",
               req.pid, req.container_id,
               req.soft_limit_bytes,
               req.hard_limit_bytes);

        // simulate soft warning
        printk(KERN_WARNING "[monitor] WARNING: soft limit may be exceeded for %s\n",
               req.container_id);

        // simulate hard kill
        printk(KERN_ERR "[monitor] ERROR: hard limit enforced for %s\n",
               req.container_id);

        break;

    case MONITOR_UNREGISTER:
        printk(KERN_INFO "[monitor] UNREGISTER pid=%d container=%s\n",
               req.pid, req.container_id);
        break;

    default:
        return -EINVAL;
    }

    return 0;
}

static struct file_operations fops = {
    .unlocked_ioctl = monitor_ioctl,
};

static int __init monitor_init(void)
{
    major = register_chrdev(0, DEVICE_NAME, &fops);
    printk(KERN_INFO "[monitor] Module loaded\n");
    return 0;
}

static void __exit monitor_exit(void)
{
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "[monitor] Module unloaded\n");
}

module_init(monitor_init);
module_exit(monitor_exit);

MODULE_LICENSE("GPL");
