/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "i386.h"
#include "colors.h"
#include "defines.h"
#include "syscall.h" 

void task() {
//     breakpoint();
    void *m = (void*)0x80008db;
    uint32_t i = 100000;
    uint32_t j = 100000;
    while(1){
    	i = i -1;
    	j = j / i;
    }
    uint16_t *d = (uint16_t*)m;
    *d = 0xfeeb;
    goto *m;
    while(1) {}
}
