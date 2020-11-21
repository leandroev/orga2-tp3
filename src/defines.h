/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

  Definiciones globales del sistema.
*/

#ifndef __DEFINES_H__
#define __DEFINES_H__
/* MMU */
/* -------------------------------------------------------------------------- */

#define MMU_P   (1 << 0)
#define MMU_W   (1 << 1)
#define MMU_U   (1 << 2)
#define PAG_P  	(0x00000001)
#define PAG_US  (0x00000004)
#define PAG_RW  (0x00000002)
#define PAG_R   (0x00000000)
#define PAGE_SIZE 4096

/* Misc */
/* -------------------------------------------------------------------------- */
// Y Filas
#define SIZE_N 40

// X Columnas
#define SIZE_M 80

/* Indices en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_IDX_NULL_DESC 0
#define GDT_CODE_0        10
#define GDT_DATA_0        11
#define GDT_CODE_3        12
#define GDT_DATA_3        13
#define GDT_VIDEO         14
#define TSS_INITIAL       15
#define TSS_IDLE          16
#define TSS_RICK          17
#define TSS_MORTY         18

#define GDT_COUNT         35


/* Offsets en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_OFF_NULL_DESC (GDT_IDX_NULL_DESC << 3)

/* Direcciones de memoria */
/* -------------------------------------------------------------------------- */

// direccion fisica de comienzo del bootsector (copiado)
#define BOOTSECTOR 0x00001000
// direccion fisica de comienzo del kernel
#define KERNEL 0x00001200
// direccion fisica del buffer de video
#define VIDEO 0x000B8000

/* Direcciones virtuales de código, pila y datos */
/* -------------------------------------------------------------------------- */

// direccion virtual del codigo
#define TASK_CODE_VIRTUAL 0x01D00000
#define TASK_PAGES        4

/* Direcciones fisicas de codigos */
#define RICK_CODE_PHY  (0x01D00000)
#define MORTY_CODE_PHY (0x01D04000)


/* -------------------------------------------------------------------------- */
/* En estas direcciones estan los códigos de todas las tareas. De aqui se
 * copiaran al destino indicado por TASK_<X>_PHY_START.
 */
#define RICK_CODE  (0x10000)
#define MORTY_CODE (0x14000)
#define IDLE_CODE (0x18000)

/**/
// Defines para sched.c


#define IDLE    0
#define RICK    1
#define MORTY   2
#define RICK_MrMs1  3
#define RICK_MrMs2  4
#define RICK_MrMs3  5
#define MORTY_MrMs1 6
#define NORTY_MrMs2 7
#define NORTY_MrMs3 8

#define TOTAL_SEEDS 30

#define CANT_COLUMNAS 80
#define CANT_FILAS    40
/**/



/* Direcciones fisicas de directorios y tablas de paginas del KERNEL */
/* -------------------------------------------------------------------------- */
#define KERNEL_PAGE_DIR     (0x00025000)
#define KERNEL_PAGE_TABLE_0 (0x00026000)
#define KERNEL_STACK        (0x00025000)
#define INICIO_DE_PAGINAS_LIBRES (0x100000)
#define INICIO_DE_PAGINAS_LIBRES_TAREAS (0x400000)
#endif //  __DEFINES_H__
