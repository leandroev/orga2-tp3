/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

  Declaracion de funciones del manejador de memoria
*/

#ifndef __MMU_H__
#define __MMU_H__

#include "types.h"


void mmu_init(void);

paddr_t mmu_next_free_kernel_page(void);

void mmu_map_page(uint32_t cr3, vaddr_t virt, paddr_t phy, uint32_t attrs);

void mmu_unmap_page(uint32_t cr3, vaddr_t virt);

paddr_t mmu_init_kernel_dir(void);

paddr_t mmu_init_task_dir(paddr_t phy_start, vaddr_t virt_star, paddr_t code_start, size_t pages);

/* Struct de una entrada de la PDE */
typedef struct str_pd_entry {
    uint32_t present:1;
    uint32_t r_w:1;
    uint32_t u_s:1;
    uint32_t pwt:1;
    uint32_t pcd:1;
    uint32_t a:1;
    uint32_t ignored:1;
    uint32_t ps:1;
    uint32_t g:1;
    uint32_t disponible:3;
    uint32_t dir_base:20;
} __attribute__((__packed__, aligned (4))) pd_entry;


/* Struct de una entrada de la PTE */
typedef struct str_pt_entry {
    uint32_t present:1;
    uint32_t r_w:1;
    uint32_t u_s:1;
    uint32_t pwt:1;
    uint32_t pcd:1;
    uint32_t a:1;
    uint32_t d:1;
    uint32_t pat:1;
    uint32_t g:1;
    uint32_t disponible:3;
    uint32_t dir_base:20;
} __attribute__((__packed__, aligned (4))) pt_entry;







#endif //  __MMU_H__
