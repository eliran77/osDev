
global start
extern kmain

MODULEALIGN equ  1<<0
MEMINFO     equ  1<<1
FLAGS       equ  MODULEALIGN | MEMINFO
MAGIC       equ    0x1BADB002
CHECKSUM    equ -(MAGIC + FLAGS)


[BITS 32]                       ; All instructions should be 32-bit.
section .text

align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM
STACKSIZE equ 0x4000


start:
  mov  esp, stack + STACKSIZE
  push eax
  push ebx
  
  call kmain
  
  cli
  .hang:
        hlt
        jmp  .hang

section .bss
 
align 4
stack:
    resb STACKSIZE
