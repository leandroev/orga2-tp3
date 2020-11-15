/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

  Definicion de funciones del manejador de memoria
*/

#include "mmu.h"
#include "i386.h"

#include "kassert.h"

paddr_t next_free_kernel_page;
paddr_t next_free_task_page;


void mmu_init(void) {
  next_free_kernel_page = INICIO_DE_PAGINA_LIBRE_KERNEL;
  next_free_task_page = INICIO_DE_PAGINA_LIRE_TAREA;
}

paddr_t mmu_next_free_kernel_page(void) {
  paddr_t free_page = next_free_kernel_page;
  free_page += PAGE_SIZE;
  return free_page;
} // mas adelante tenemos que definir el mismo pero para las tareas

paddr_t mmu_init_kernel_dir(void) {
    pd_entry* pd = (pd_entry*) KERNEL_PAGE_DIR;
	
	for (int i = 1; i < 1024; ++i) {
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
    pd[0].present = PAG_P;              // página presente

    /* Inicializamos la Kernel Page table */ 
    pt_entry* pt = (pt_entry*) KERNEL_PAGE_TABLE_0;

    //Como hay la PT tiene 1024 de 4k son 4MB
    for (int i = 0; i < 1024; ++i) { 
    	pt[i].dir_base = i;                   // esto pues, para que sea idd mapping
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



void mmu_map_page(uint32_t cr3, vaddr_t virt, paddr_t phy, uint32_t attrs) {
  uint32_t pd_index = virt >> 22;
  uint32_t pt_index = (virt >> 12) & 0x3FF;

  uint32_t dir_pt;
  pd_entry* pd = (pd_entry*) ((cr3 >> 12) << 12);

  if (!pd[pd_index].present) {  //Entra si la pagina no se encuentra presente
    dir_pt = mmu_next_free_kernel_page();
    pt_entry* pt = (pt_entry*) dir_pt;

    for (uint32_t i = 0; i < 1024; i++){
      pt[i].present = 0;
    }
    
    pd[pd_index].present = 0x1;         // La dejamos presente
    pd[pd_index].u_s = attrs & 0x2;
    pd[pd_index].r_w = attrs & 0x4;
    pd[pd_index].dir_base = dir_pt >> 12;
  }
    dir_pt = pd[pd_index].dir_base;
    pt_entry* pt = (pt_entry*) (dir_pt << 12);

    pt[pt_index].present = 0x1;
    pt[pt_index].u_s = attrs & 0x2;
    pt[pt_index].r_w = attrs & 0x4;
    pt[pt_index].dir_base = phy >> 12;

    tlbflush();
}

paddr_t mmu_unmap_page(uint32_t cr3, vaddr_t virt) {
	pd_entry* pd = (pd_entry*) ((cr3 >> 12) << 12);
	uint32_t pd_index = virt >> 22;
	uint32_t pt_index = (virt >> 12) & 0x3FF;
	pt_entry* pt = (pt_entry*) (pd[pd_index].dir_base << 12);

	pt[pt_index].present = 0;
	tlbflush();
  return 0;
}
// paddr_t mmu_init_task_dir(paddr_t phy_start, paddr_t code_start, size_t
// pages) {}

