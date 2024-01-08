# Tutorial: Creating a Kernel Module in Linux

## What is a kernel module?
Essentially, a kernel module is software that runs in the kernel space. In the kernel space, various operations can be performed, with one notable functionality being the ability to load and unload modules dynamically in the Linux kernel.

## Creating the Module in C

Open a text editor to create the module.c file:

```bash
$ nano modulo.c
```

```bash
#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("your_name_here");
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
```

Now, let's understand two functions. One is executed whenever the module is loaded into the kernel, and the other is executed when the module is removed from the kernel.

```bash
# Loaded into the kernel
static int __init ModuleInit(void) {
        printk("Hello World!\n");
        return 0;
}

# Removed from the kernel
static void __exit ModuleExit(void) {
        printk("Bye-bye World!\n");
}

module_init(ModuleInit); #module_init loads our function during initialization
module_exit(ModuleExit); #module_exit loads our function during exit
```
```bash
$ nano Makefile
```

```bash
# Indicates that the kernel module named "module" will be compiled and linked to the kernel
obj-m += module.o

# Default rule "all": performs the compilation of the kernel module.
all:
        make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

# Rule "clean": performs cleanup, removing temporary and generated binary files.
clean:
        make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

```
The module.ko file will be generated. To load it into the kernel, use the following command:

```bash
$ sudo insmod modulo.ko
```
With the lsmod command, we can see our kernel:

```bash
$ lsmod | grep modulo

```
Now, looking at the system logs, we can see our message:

```bash
$ dmesg | tail

```
## Well, it's quite a big "Hello World," isn't it! 😅 😅
