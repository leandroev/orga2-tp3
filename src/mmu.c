/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

  Definicion de funciones del manejador de memoria
*/

#include "mmu.h"
#include "i386.h"

#include "kassert.h"

unsigned int proxima_pagina_libre;
void mmu_init(void) {
    proxima_pagina_libre = INICIO_DE_PAGINAS_LIBRES;
}

paddr_t mmu_next_free_kernel_page(void) { 
  paddr_t pagina_libre = proxima_pagina_libre;
  proxima_pagina_libre += PAGE_SIZE;
  return pagina_libre;
}

paddr_t mmu_init_kernel_dir(void) {  // Mapea los primeros 4MB de memoria con identity mapping
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

    for (uint32_t i = 0; i < 1024; ++i)
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

void mmu_map_page(uint32_t cr3, vaddr_t virt, paddr_t phy, uint32_t attrs) {
    pd_entry* pd = (pd_entry*) ((cr3>>12)<<12);
    uint32_t dirIdx = (virt>>22);
    uint32_t tableIdx = ((virt<<10)>>22);
    pt_entry* pt = (pt_entry*) (pd[dirIdx].dir_base<<12);


    if (pd[dirIdx].present != PAG_P)
    {
        uint32_t nueva_tabla = mmu_next_free_kernel_page(); //pido nueva memoria
        pt = (pt_entry*) nueva_tabla;


        for (int i = 0; i < 1024; ++i)
        {
            pt[i] = (pt_entry) {0};
        }
        //Actualizo la entrada del directorio
        pd[dirIdx].dir_base =(((uint32_t)pt) >>12);
        pd[dirIdx].disponible = 0;
        pd[dirIdx].g = 0;
        pd[dirIdx].ps = 0;
        pd[dirIdx].ignored = 0;
        pd[dirIdx].a = 0;
        pd[dirIdx].pcd = 0;
        pd[dirIdx].pwt = 0;
        pd[dirIdx].u_s = (attrs & PAG_US) >> 2;
        pd[dirIdx].r_w = (attrs & PAG_RW) >> 1;
        pd[dirIdx].present = PAG_P;
        
    }
    
    pt[tableIdx].present = PAG_P;
    pt[tableIdx].pwt = 0;
    pt[tableIdx].pcd = 0;
    pt[tableIdx].a = 0;
    pt[tableIdx].d = 0;
    pt[tableIdx].pat = 0;
    pt[tableIdx].g = 0;
    pt[tableIdx].disponible = 0;
    pt[tableIdx].u_s = (attrs & PAG_US) >> 2;
    pt[tableIdx].r_w = (attrs & PAG_RW) >> 1;
    pt[tableIdx].dir_base = (phy>>12);

    tlbflush();
}

void mmu_unmap_page(uint32_t cr3, vaddr_t virt) {
    
    pd_entry* pd = (pd_entry*) ((cr3>>12)<<12);
    uint32_t dirIdx = (virt>>22);
    uint32_t tableIdx = ((virt<<10)>>22);
    pt_entry* pt = (pt_entry*) (pd[dirIdx].dir_base<<12);
    pt[tableIdx].present = PAG_R;

    tlbflush();
}

paddr_t mmu_init_task_dir(paddr_t phy_start, vaddr_t virt_star, paddr_t code_start, uint32_t pages) {
    
    /****KERNEL****/

    //Pedimos memoria para el nuevo directorio del kernel
    paddr_t cr3 = mmu_next_free_kernel_page();
    uint32_t attrS = 0x00000007;

    //Mapeamos los primero 4MB con identity maping
    for (uint32_t i = 0; i < 1024; ++i) {
        mmu_map_page(cr3, i*PAGE_SIZE, i*PAGE_SIZE, attrS);
    }

    /****TAREA****/

    //Mapeo los 16kb  de la tarea 
    for (uint32_t i = 0; i < pages; ++i) {
        mmu_map_page(cr3,virt_star + i*PAGE_SIZE, phy_start + i*PAGE_SIZE,attrS); // mapeo 4kb
    }
    
    //Copio la tarea
    paddr_t cr3Actual = rcr3();
    
    //Mapeo los 16kb  de la tarea 
    for (uint32_t i = 0; i < pages; ++i) {
        mmu_map_page(cr3Actual,virt_star + i*PAGE_SIZE, phy_start + i*PAGE_SIZE,attrS); // mapeo 4kb
    }

    uint32_t* src = (uint32_t*) code_start; 
    uint32_t* dst = (uint32_t*) virt_star;
    
    for (uint32_t i = 0; i < 1024*pages; ++i) {
        dst[i] = src[i];
    }
    
    //Desmapeo
    //fbreakpoint();
    for (uint32_t i = 0; i < pages; ++i) {
        mmu_unmap_page(cr3Actual, virt_star + i*PAGE_SIZE); // desmapeo 4kb
    }
    
    tlbflush();
    return cr3;

}

