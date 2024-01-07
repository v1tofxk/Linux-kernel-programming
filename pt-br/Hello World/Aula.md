# Tutorial: Criando um Módulo Kernel em Linux

## O que é um módulo kernel?

Basicamente, um módulo kernel é um software que roda no espaço do kernel. No espaço do kernel, você pode realizar diversas operações, e uma das funcionalidades notáveis é a capacidade de carregar e descarregar módulos dinamicamente no kernel Linux.

## Criando o Módulo em C

Abra um editor de texto para criar o arquivo `modulo.c`:

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

Agora, precisaremos carregar duas funções. Uma delas é executada sempre que o módulo está carregado no kernel, e a outra é executada se o módulo for removido do kernel.

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

module_init(ModuleInit); #module_init carrega a nossa função ao inicializar
module_exit(ModuleExit); #module_exit carrega a nossa função ao sair
```
```bash
$ nano Makefile
```

```bash
# Indica que o módulo do kernel chamado "mymodule" será compilado e vinculado ao kernel
obj-m += modulo.o

# Regra padrão "all": executa a compilação do módulo do kernel.
all:
        make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

# Regra "clean": executa a limpeza, removendo arquivos temporários e binários gerados.
clean:
        make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```
O arquivo module.ko será gerado. Para carregá-lo no kernel, use o seguinte comando:

```bash
$ sudo insmod modulo.ko
```
Com o comando lsmod, podemos ver nosso kernel:

```bash
$ lsmod | grep modulo

```
Agora, olhando para os logs do sistema, podemos ver nossa mensagem:

```bash
$ dmesg | tail

```
## Bom, é um hello world bem grande né! 😅
