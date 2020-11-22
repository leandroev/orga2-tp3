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

#define TRUE  1
#define FALSE 0

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

#define TSS_RICK_MrMs0    19
#define TSS_RICK_MrMs1    20
#define TSS_RICK_MrMs2    21
#define TSS_RICK_MrMs3    22
#define TSS_RICK_MrMs4    23
#define TSS_RICK_MrMs5    24
#define TSS_RICK_MrMs6    25
#define TSS_RICK_MrMs7    26
#define TSS_RICK_MrMs8    27
#define TSS_RICK_MrMs9    28

#define TSS_MORTY_MrMs0   29
#define TSS_MORTY_MrMs1   30
#define TSS_MORTY_MrMs2   31
#define TSS_MORTY_MrMs3   32
#define TSS_MORTY_MrMs4   33
#define TSS_MORTY_MrMs5   34
#define TSS_MORTY_MrMs6   35
#define TSS_MORTY_MrMs7   36
#define TSS_MORTY_MrMs8   37
#define TSS_MORTY_MrMs9   38

#define GDT_COUNT         39


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
#define RICK_MrMs0   3
#define RICK_MrMs1   4
#define RICK_MrMs2   5
#define RICK_MrMs3   6
#define RICK_MrMs4   7
#define RICK_MrMs5   8
#define RICK_MrMs6   9
#define RICK_MrMs7   10
#define RICK_MrMs8   11
#define RICK_MrMs9   12
#define MORTY_MrMs0  13
#define NORTY_MrMs1  14
#define NORTY_MrMs2  15
#define NORTY_MrMs3  16
#define NORTY_MrMs4  17
#define NORTY_MrMs5  18
#define NORTY_MrMs6  19
#define NORTY_MrMs7  20
#define NORTY_MrMs8  21
#define NORTY_MrMs9  22

#define TOTAL_SEEDS 40

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
