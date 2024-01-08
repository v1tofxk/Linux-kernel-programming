#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vitor");
MODULE_DESCRIPTION("A hello world LKM");

static int __init ModuleInit(void) {
    printk("Hello World!\n");
    return 0;
}

static void __exit ModuleExit(void) {
    printk("Bye-bye World!\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);

static int __init ModuleInit(void) {
        printk("Hello World!\n");
        return 0;
}

static void __exit ModuleExit(void) {
        printk("Bye-bye World!\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);
