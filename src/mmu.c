/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

  Definicion de funciones del manejador de memoria
*/

#include "mmu.h"
#include "i386.h"

#include "kassert.h"

void mmu_init(void) {}

paddr_t mmu_next_free_kernel_page(void) {
  return 0;
}

paddr_t mmu_init_kernel_dir(void) {
    pd_entry* pd = (pd_entry*) KERNEL_PAGE_DIR;
	
	for (int i = 1; i < 1024; ++i)
	{
		pd[i] = (pd_entry) {0};
	}
	
	/* Inicializamos la primer entrada de la Kernel Page Directory */
	pd[0].dir_base = (KERNEL_PAGE_TABLE_0>>12);
    pd[0].disponible = 0;
    pd[0].g = 0;
    pd[0].ps = 0;
    pd[0].ignored = 0;
    pd[0].a = 0;
    pd[0].pcd = 0;
    pd[0].pwt = 0;
    pd[0].u_s = 0;
    pd[0].r_w = 1;
    pd[0].present = PAG_P;

    /* Inicializamos la Kernel Page table */
    pt_entry* pt = (pt_entry*) KERNEL_PAGE_TABLE_0;

    for (int i = 0; i < 1024; ++i)
    {
    	pt[i].dir_base = i;
    	pt[i].disponible = 0;
    	pt[i].g = 0;
    	pt[i].pat = 0;
    	pt[i].d = 0;
    	pt[i].a = 0;
    	pt[i].pcd = 0;
    	pt[i].pwt = 0;
    	pt[i].u_s = 0;
    	pt[i].r_w = 1;
    	pt[i].present = PAG_P;
    }
    return KERNEL_PAGE_DIR;
}
// void mmu_map_page(uint32_t cr3, vaddr_t virt, paddr_t phy, uint32_t attrs) {}
// paddr_t mmu_unmap_page(uint32_t cr3, vaddr_t virt) {}
// paddr_t mmu_init_task_dir(paddr_t phy_start, paddr_t code_start, size_t
// pages) {}

