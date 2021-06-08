# C-minus-compiler

这是一个基于lex与yacc的C-minus的编译器，由.c代码生成.asm代码

## 编译方式

```shell
yacc -d cminus.y
lex cminus.lex
cc lex.yy.c y.tab.c emitcode.c symtable.c
./a.out << 'sourcecode'
```

即可生成x86汇编代码

## 运行方式

```shell
nasm -f elf -g -F stabs output.asm -l output.lst
gcc –m32 output.o –o output
```

仅可在Linux系统上运行

