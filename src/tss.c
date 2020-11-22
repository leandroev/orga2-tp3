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
#include "i386.h"

tss_mrms tss_Mortymrms[10];
tss_mrms tss_Rickmrms[10];
tss_t tss_initial;
tss_t tss_idle;
tss_t tss_rick;
tss_t tss_morty;
tss_t tss_rick_MrMs0;
tss_t tss_rick_MrMs1;
tss_t tss_rick_MrMs2;
tss_t tss_rick_MrMs3;
tss_t tss_rick_MrMs4;
tss_t tss_rick_MrMs5;
tss_t tss_rick_MrMs6;
tss_t tss_rick_MrMs7;
tss_t tss_rick_MrMs8;
tss_t tss_rick_MrMs9;
tss_t tss_morty_MrMs0;
tss_t tss_morty_MrMs1;
tss_t tss_morty_MrMs2;
tss_t tss_morty_MrMs3;
tss_t tss_morty_MrMs4;
tss_t tss_morty_MrMs5;
tss_t tss_morty_MrMs6;
tss_t tss_morty_MrMs7;
tss_t tss_morty_MrMs8;
tss_t tss_morty_MrMs9;


void tss_init_gdt(void) {
	gdt[TSS_IDLE].base_15_0  = ((uint32_t)(&tss_idle) << 16) >> 16;
    gdt[TSS_IDLE].base_23_16 = ((uint32_t)(&tss_idle) << 8) >> 24;
    gdt[TSS_IDLE].base_31_24 = (uint32_t)(&tss_idle) >> 24;

    gdt[TSS_INITIAL].base_15_0  = ((uint32_t)&tss_initial << 16) >> 16;
    gdt[TSS_INITIAL].base_23_16 = ((uint32_t)&tss_initial << 8) >> 24;
    gdt[TSS_INITIAL].base_31_24 = (uint32_t)(&tss_initial) >> 24;

    gdt[TSS_RICK].base_15_0  = ((uint32_t)&tss_rick << 16) >> 16;
    gdt[TSS_RICK].base_23_16 = ((uint32_t)&tss_rick << 8) >> 24;
    gdt[TSS_RICK].base_31_24 = (uint32_t)(&tss_rick) >> 24;

    gdt[TSS_MORTY].base_15_0  = ((uint32_t)&tss_morty << 16) >> 16;
    gdt[TSS_MORTY].base_23_16 = ((uint32_t)&tss_morty << 8) >> 24;
    gdt[TSS_MORTY].base_31_24 = (uint32_t)(&tss_morty) >> 24;

    tss_Mortymrms[0].task_seg  = tss_morty_MrMs0;
    tss_Mortymrms[1].task_seg  = tss_morty_MrMs1;
    tss_Mortymrms[2].task_seg  = tss_morty_MrMs2;
    tss_Mortymrms[3].task_seg  = tss_morty_MrMs3;
    tss_Mortymrms[4].task_seg  = tss_morty_MrMs4;
    tss_Mortymrms[5].task_seg  = tss_morty_MrMs5;
    tss_Mortymrms[6].task_seg  = tss_morty_MrMs6;
    tss_Mortymrms[7].task_seg  = tss_morty_MrMs7;
    tss_Mortymrms[8].task_seg  = tss_morty_MrMs8;
    tss_Mortymrms[9].task_seg  = tss_morty_MrMs9;

    tss_Rickmrms[0].task_seg   = tss_rick_MrMs0;
    tss_Rickmrms[1].task_seg   = tss_rick_MrMs1;
    tss_Rickmrms[2].task_seg   = tss_rick_MrMs2;
    tss_Rickmrms[3].task_seg   = tss_rick_MrMs3;
    tss_Rickmrms[4].task_seg   = tss_rick_MrMs4;
    tss_Rickmrms[5].task_seg   = tss_rick_MrMs5;
    tss_Rickmrms[6].task_seg   = tss_rick_MrMs6;
    tss_Rickmrms[7].task_seg   = tss_rick_MrMs7;
    tss_Rickmrms[8].task_seg   = tss_rick_MrMs8;
    tss_Rickmrms[9].task_seg   = tss_rick_MrMs9;

    //Cargo las tss en los descriptores
    for (int i = 0; i < 10; ++i)
    {
        tss_Rickmrms[i].in_use = 0;
        gdt[i+19].base_15_0  = ((uint32_t)&tss_Rickmrms[i].task_seg << 16) >> 16;
        gdt[i+19].base_23_16 = ((uint32_t)&tss_Rickmrms[i].task_seg << 8) >> 24;
        gdt[i+19].base_31_24 = (uint32_t)(&tss_Rickmrms[i].task_seg) >> 24;
        
    }

    for (int i = 0; i < 10; ++i)
    {
        tss_Mortymrms[i].in_use = 0;
        gdt[i+29].base_15_0  = ((uint32_t)&tss_Mortymrms[i].task_seg << 16) >> 16;
        gdt[i+29].base_23_16 = ((uint32_t)&tss_Mortymrms[i].task_seg << 8) >> 24;
        gdt[i+29].base_31_24 = (uint32_t)(&tss_Mortymrms[i].task_seg) >> 24;
        
    }


    /*
    gdt[TSS_RICK_MrMs0].base_15_0  = ((uint32_t)&tss_rick_MrMs0 << 16) >> 16;
    gdt[TSS_RICK_MrMs0].base_23_16 = ((uint32_t)&tss_rick_MrMs0 << 8) >> 24;
    gdt[TSS_RICK_MrMs0].base_31_24 = (uint32_t)(&tss_rick_MrMs0) >> 24;

    gdt[TSS_RICK_MrMs1].base_15_0  = ((uint32_t)&tss_rick_MrMs1 << 16) >> 16;
    gdt[TSS_RICK_MrMs1].base_23_16 = ((uint32_t)&tss_rick_MrMs1 << 8) >> 24;
    gdt[TSS_RICK_MrMs1].base_31_24 = (uint32_t)(&tss_rick_MrMs1) >> 24;

    gdt[TSS_RICK_MrMs2].base_15_0  = ((uint32_t)&tss_rick_MrMs2 << 16) >> 16;
    gdt[TSS_RICK_MrMs2].base_23_16 = ((uint32_t)&tss_rick_MrMs2 << 8) >> 24;
    gdt[TSS_RICK_MrMs2].base_31_24 = (uint32_t)(&tss_rick_MrMs2) >> 24;

    gdt[TSS_RICK_MrMs3].base_15_0  = ((uint32_t)&tss_rick_MrMs3 << 16) >> 16;
    gdt[TSS_RICK_MrMs3].base_23_16 = ((uint32_t)&tss_rick_MrMs3 << 8) >> 24;
    gdt[TSS_RICK_MrMs3].base_31_24 = (uint32_t)(&tss_rick_MrMs3) >> 24;

    gdt[TSS_RICK_MrMs4].base_15_0  = ((uint32_t)&tss_rick_MrMs4 << 16) >> 16;
    gdt[TSS_RICK_MrMs4].base_23_16 = ((uint32_t)&tss_rick_MrMs4 << 8) >> 24;
    gdt[TSS_RICK_MrMs4].base_31_24 = (uint32_t)(&tss_rick_MrMs4) >> 24;

    gdt[TSS_RICK_MrMs5].base_15_0  = ((uint32_t)&tss_rick_MrMs5 << 16) >> 16;
    gdt[TSS_RICK_MrMs5].base_23_16 = ((uint32_t)&tss_rick_MrMs5 << 8) >> 24;
    gdt[TSS_RICK_MrMs5].base_31_24 = (uint32_t)(&tss_rick_MrMs5) >> 24;

    gdt[TSS_RICK_MrMs6].base_15_0  = ((uint32_t)&tss_rick_MrMs6 << 16) >> 16;
    gdt[TSS_RICK_MrMs6].base_23_16 = ((uint32_t)&tss_rick_MrMs6 << 8) >> 24;
    gdt[TSS_RICK_MrMs6].base_31_24 = (uint32_t)(&tss_rick_MrMs6) >> 24;

    gdt[TSS_RICK_MrMs7].base_15_0  = ((uint32_t)&tss_rick_MrMs7 << 16) >> 16;
    gdt[TSS_RICK_MrMs7].base_23_16 = ((uint32_t)&tss_rick_MrMs7 << 8) >> 24;
    gdt[TSS_RICK_MrMs7].base_31_24 = (uint32_t)(&tss_rick_MrMs7) >> 24;

    gdt[TSS_RICK_MrMs8].base_15_0  = ((uint32_t)&tss_rick_MrMs8 << 16) >> 16;
    gdt[TSS_RICK_MrMs8].base_23_16 = ((uint32_t)&tss_rick_MrMs8 << 8) >> 24;
    gdt[TSS_RICK_MrMs8].base_31_24 = (uint32_t)(&tss_rick_MrMs8) >> 24;

    gdt[TSS_RICK_MrMs9].base_15_0  = ((uint32_t)&tss_rick_MrMs9 << 16) >> 16;
    gdt[TSS_RICK_MrMs9].base_23_16 = ((uint32_t)&tss_rick_MrMs9 << 8) >> 24;
    gdt[TSS_RICK_MrMs9].base_31_24 = (uint32_t)(&tss_rick_MrMs9) >> 24;

    gdt[TSS_MORTY_MrMs0].base_15_0  = ((uint32_t)&tss_morty_MrMs0 << 16) >> 16;
    gdt[TSS_MORTY_MrMs0].base_23_16 = ((uint32_t)&tss_morty_MrMs0 << 8) >> 24;
    gdt[TSS_MORTY_MrMs0].base_31_24 = (uint32_t)(&tss_morty_MrMs0) >> 24;

    gdt[TSS_MORTY_MrMs1].base_15_0  = ((uint32_t)&tss_morty_MrMs1 << 16) >> 16;
    gdt[TSS_MORTY_MrMs1].base_23_16 = ((uint32_t)&tss_morty_MrMs1 << 8) >> 24;
    gdt[TSS_MORTY_MrMs1].base_31_24 = (uint32_t)(&tss_morty_MrMs1) >> 24;

    gdt[TSS_MORTY_MrMs2].base_15_0  = ((uint32_t)&tss_morty_MrMs2 << 16) >> 16;
    gdt[TSS_MORTY_MrMs2].base_23_16 = ((uint32_t)&tss_morty_MrMs2 << 8) >> 24;
    gdt[TSS_MORTY_MrMs2].base_31_24 = (uint32_t)(&tss_morty_MrMs2) >> 24;

    gdt[TSS_MORTY_MrMs3].base_15_0  = ((uint32_t)&tss_morty_MrMs3 << 16) >> 16;
    gdt[TSS_MORTY_MrMs3].base_23_16 = ((uint32_t)&tss_morty_MrMs3 << 8) >> 24;
    gdt[TSS_MORTY_MrMs3].base_31_24 = (uint32_t)(&tss_morty_MrMs3) >> 24;

    gdt[TSS_MORTY_MrMs4].base_15_0  = ((uint32_t)&tss_morty_MrMs4 << 16) >> 16;
    gdt[TSS_MORTY_MrMs4].base_23_16 = ((uint32_t)&tss_morty_MrMs4 << 8) >> 24;
    gdt[TSS_MORTY_MrMs4].base_31_24 = (uint32_t)(&tss_morty_MrMs4) >> 24;

    gdt[TSS_MORTY_MrMs5].base_15_0  = ((uint32_t)&tss_morty_MrMs5 << 16) >> 16;
    gdt[TSS_MORTY_MrMs5].base_23_16 = ((uint32_t)&tss_morty_MrMs5 << 8) >> 24;
    gdt[TSS_MORTY_MrMs5].base_31_24 = (uint32_t)(&tss_morty_MrMs5) >> 24;

    gdt[TSS_MORTY_MrMs6].base_15_0  = ((uint32_t)&tss_morty_MrMs6 << 16) >> 16;
    gdt[TSS_MORTY_MrMs6].base_23_16 = ((uint32_t)&tss_morty_MrMs6 << 8) >> 24;
    gdt[TSS_MORTY_MrMs6].base_31_24 = (uint32_t)(&tss_morty_MrMs6) >> 24;

    gdt[TSS_MORTY_MrMs7].base_15_0  = ((uint32_t)&tss_morty_MrMs7 << 16) >> 16;
    gdt[TSS_MORTY_MrMs7].base_23_16 = ((uint32_t)&tss_morty_MrMs7 << 8) >> 24;
    gdt[TSS_MORTY_MrMs7].base_31_24 = (uint32_t)(&tss_morty_MrMs7) >> 24;

    gdt[TSS_MORTY_MrMs8].base_15_0  = ((uint32_t)&tss_morty_MrMs8 << 16) >> 16;
    gdt[TSS_MORTY_MrMs8].base_23_16 = ((uint32_t)&tss_morty_MrMs8 << 8) >> 24;
    gdt[TSS_MORTY_MrMs8].base_31_24 = (uint32_t)(&tss_morty_MrMs8) >> 24;

    gdt[TSS_MORTY_MrMs9].base_15_0  = ((uint32_t)&tss_morty_MrMs9 << 16) >> 16;
    gdt[TSS_MORTY_MrMs9].base_23_16 = ((uint32_t)&tss_morty_MrMs9 << 8) >> 24;
    gdt[TSS_MORTY_MrMs9].base_31_24 = (uint32_t)(&tss_morty_MrMs9) >> 24;
    */
}


void tss_init_idle(void){
    tss_initial = (tss_t){0};
    tss_idle =(tss_t){
        .ptl = 0,
        .unused0 = 0,
        .esp0 = KERNEL_STACK,
        .ss0 = GDT_DATA_0 << 3,
        .unused1 = 0,
        .esp1 = 0,
        .ss1 = 0, 
        .unused2 = 0,
        .esp2 = 0,
        .ss2 = 0,
        .unused3 = 0,
        .cr3 = KERNEL_PAGE_DIR,
        .eip = IDLE_CODE,
        .eflags = 0x202,
        .eax = 0,
        .ecx = 0,
        .edx = 0,
        .ebx = 0,
        .esp = KERNEL_STACK,     
        .ebp = KERNEL_STACK,     
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

}

void tss_init(void) {

    task_init(&tss_rick,RICK_CODE_PHY,TASK_CODE_VIRTUAL,RICK_CODE,TASK_PAGES,0);
    task_init(&tss_morty,MORTY_CODE_PHY,TASK_CODE_VIRTUAL,MORTY_CODE,TASK_PAGES,0);
}

void task_init(tss_t* new_tss, paddr_t phy_task, vaddr_t virt_task, paddr_t task_code, size_t pages,uint32_t pila_0)
{
    *new_tss = (tss_t) {0};
    new_tss->eip = virt_task;
    new_tss->cr3 = mmu_init_task_dir(phy_task,virt_task,task_code,pages);
    new_tss->esp = virt_task + pages*PAGE_SIZE;
    new_tss->ebp = virt_task + pages*PAGE_SIZE;
    new_tss->ss0 = GDT_DATA_0 << 3;
    new_tss->cs = (GDT_CODE_3 << 3) + 3;
    new_tss->ds = (GDT_DATA_3 << 3) + 3;
    new_tss->eflags = 0x202;
    new_tss->ss = (GDT_DATA_3 << 3) + 3;
    new_tss->es = (GDT_DATA_3 << 3) + 3;
    new_tss->ds = (GDT_DATA_3 << 3) + 3;
    new_tss->fs = (GDT_DATA_3 << 3) + 3;
    new_tss->gs = (GDT_DATA_3 << 3) + 3;
    new_tss->iomap = 0xFFFF;
    
    if (pila_0 == 0){
        new_tss->esp0 = mmu_next_free_kernel_page() + PAGE_SIZE;
    }else{
        new_tss->esp0 = pila_0;

    }
}

