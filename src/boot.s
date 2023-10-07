#include "mm.h"

.section ".text.boot"


.globl _start
_start:
    mrs x0,mpidr_el1
    and x0,x0,#0XFF
    cbz x0,master
    b proc_hang

master:
    adr x0,bss_begin
    adr x1,bss_end
    sub x1,x1,x0
    bl memzero

proc_hang:
    wfe 
    b proc_hang