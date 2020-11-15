/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

  Definicion de estructuras para administrar tareas
*/

#include "tss.h"
#include "defines.h"
#include "kassert.h"
#include "mmu.h"

tss_t tss_initial = {0};
tss_t tss_idle = {
    .ptl = 0,
    .unused0 = 0,
    .esp0 = 0x24000,
    .ss0 = GDT_DATA_0 << 3,
    .unused1 = 0,
    .esp1 = 0,
    .ss1 = 0, 
    .unused2 = 0,
    .esp2 = 0,
    .ss2 = 0,
    .unused3 = 0,
    .cr3 = 0x25000,
    .eip = 0x18000,
    .eflags = 0x202,
    .eax = 0,
    .ecx = 0,
    .edx = 0,
    .ebx = 0,
    .esp = 0x24000,     
    .ebp = 0x24000,     
    .esi = 0,
    .edi = 0,
    .es = GDT_DATA_0 << 3,
    .unused4 = 0,
    .cs = GDT_CODE_0 << 3,
    .unused5 = 0,
    .ss = GDT_DATA_0 << 3,
    .unused6 = 0,
    .ds = GDT_DATA_0 << 3,
    .unused7 = 0,
    .fs = GDT_DATA_0 << 3,
    .unused8 = 0,
    .gs = GDT_DATA_0 << 3,
    .unused9 = 0,
    .ldt = 0,
    .unused10 = 0,
    .dtrap = 0,
    .iomap = 0,
};  


void tss_init(void) {
    gdt[TSS_IDLE].base_15_0 = ((uint32_t)(&tss_idle) << 16) >> 16;
    gdt[TSS_IDLE].base_23_16 = ((uint32_t)(&tss_idle) << 8) >> 24;
    gdt[TSS_IDLE].base_31_24 = (uint32_t)(&tss_idle) >> 24;

    gdt[TSS_INITIAL].base_15_0 = ((uint32_t)&tss_initial << 16) >> 16;
    gdt[TSS_INITIAL].base_23_16 = ((uint32_t)&tss_initial << 8) >> 24;
    gdt[TSS_INITIAL].base_31_24 = (uint32_t)(&tss_initial) >> 24;
}
/*
void task_init(uint32_t task_type, uint8_t task_index) {  // Por ahora estos parametros
  
}
*/