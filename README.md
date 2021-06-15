# C-minus-compiler

这是一个基于lex与yacc的C-minus的编译器，由.c代码生成.asm汇编代码

## 构建方式

在构建之前，请先使用lex与yacc生成词法分析与文法分析文件

```shell
./cminus.sh
```

接着使用cmake进行构建

```shell
cd build
cmake ..
make
```

构建完毕，即在build文件夹中生成cminus文件，即为我们的C-minus语言编译器

## 运行方式

首先进行编译，以生成x86汇编代码与语法树，命令格式如下

```shell
cminus 'sourcefile' -o 'outputfile'
```

默认源文件为test/test.c，默认输出文件为output.asm

```shell
nasm -f elf output.asm 
#使用nasm -f elf -g -F stabs output.asm -l output.lst以获得调试信息
gcc –m32 'outputfile' –o 'outputexe'
```

仅可在Linux系统上运行，请确保已经安装 gcc-multlib

Ubuntu下使用

```shell
 sudo apt-get install gcc-multilib
```

进行安装
