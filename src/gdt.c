/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

  Definicion de la tabla de descriptores globales
*/

#include "gdt.h"

gdt_entry_t gdt[GDT_COUNT] = {
    /* Descriptor nulo*/
    /* Offset = 0x00 */
    [GDT_IDX_NULL_DESC] =
        {
            .limit_15_0 = 0x0000,   /* limit[0:15]  */
            .base_15_0 = 0x0000,    /* base[0:15]   */   
            .base_23_16 = 0x00,     /* base[23:16]  */   
            .type = 0x0,            /* type         */
            .s = 0x00,              /* s            */
            .dpl = 0x00,            /* dpl          */
            .p = 0x00,              /* p            */
            .limit_19_16 = 0x00,    /* limit[16:19] */
            .avl = 0x0,             /* avl          */
            .l = 0x0,               /* l            */
            .db = 0x0,              /* db           */
            .g = 0x00,              /* g            */
            .base_31_24 = 0x00,     /* base[31:24]  */
        },
    [GDT_CODE_0] =
      {
            .limit_15_0 = 0xC8FF,   /* limit[0:15]  */
            .base_15_0 = 0x0000,    /* base[0:15]   */
            .base_23_16 = 0x00,     /* base[23:16]  */
            .type = 0xA,            /* type         */
            .s = 0x01,              /* s            */
            .dpl = 0x00,            /* dpl          */
            .p = 0x01,              /* p            */
            .limit_19_16 = 0x00,    /* limit[16:19] */
            .avl = 0x0,             /* avl          */
            .l = 0x0,               /* l            */
            .db = 0x1,              /* db           */
            .g = 0x01,              /* g            */
            .base_31_24 = 0x00,     /* base[31:24]  */
      },
    [GDT_DATA_0] =
      {
            .limit_15_0 = 0xC8FF,   /* limit[0:15]  */
            .base_15_0 = 0x0000,    /* base[0:15]   */
            .base_23_16 = 0x00,     /* base[23:16]  */
            .type = 0x2,            /* type         */
            .s = 0x01,              /* s            */
            .dpl = 0x00,            /* dpl          */
            .p = 0x01,              /* p            */
            .limit_19_16 = 0x00,    /* limit[16:19] */
            .avl = 0x0,             /* avl          */
            .l = 0x0,               /* l            */
            .db = 0x1,              /* db           */
            .g = 0x01,              /* g            */
            .base_31_24 = 0x00,     /* base[31:24]  */
      },
    [GDT_CODE_3] =
      {
            .limit_15_0 = 0xC8FF,   /* limit[0:15]  */
            .base_15_0 = 0x0000,    /* base[0:15]   */
            .base_23_16 = 0x00,     /* base[23:16]  */
            .type = 0xA,            /* type         */
            .s = 0x01,              /* s            */
            .dpl = 0x03,            /* dpl          */
            .p = 0x01,              /* p            */
            .limit_19_16 = 0x00,    /* limit[16:19] */
            .avl = 0x0,             /* avl          */
            .l = 0x0,               /* l            */
            .db = 0x1,              /* db           */
            .g = 0x01,              /* g            */
            .base_31_24 = 0x00,     /* base[31:24]  */
      },
    [GDT_DATA_3] =
      {
            .limit_15_0 = 0xC8FF,   /* limit[0:15]  */
            .base_15_0 = 0x0000,    /* base[0:15]   */
            .base_23_16 = 0x00,     /* base[23:16]  */
            .type = 0x2,            /* type         */
            .s = 0x01,              /* s            */
            .dpl = 0x03,            /* dpl          */
            .p = 0x01,              /* p            */
            .limit_19_16 = 0x00,    /* limit[16:19] */
            .avl = 0x0,             /* avl          */
            .l = 0x0,               /* l            */
            .db = 0x1,              /* db           */
            .g = 0x01,              /* g            */
            .base_31_24 = 0x00,     /* base[31:24]  */
      },
    [GDT_VIDEO] =
        {
            .limit_15_0 = 0x7FFF,   /* limit[0:15]  */
            .base_15_0 = 0x8000,    /* base[0:15]   */   
            .base_23_16 = 0x0B,     /* base[23:16]  */   
            .type = 0x2,            /* type         */
            .s = 0x01,              /* s            */
            .dpl = 0x00,            /* dpl          */
            .p = 0x01,              /* p            */
            .limit_19_16 = 0x00,    /* limit[16:19] */
            .avl = 0x0,             /* avl          */
            .l = 0x0,               /* l            */
            .db = 0x1,              /* db           */
            .g = 0x00,              /* g            */
            .base_31_24 = 0x00,     /* base[31:24]  */
        }
};

gdt_descriptor_t GDT_DESC = {
  sizeof(gdt) - 1,
  (uint32_t)&gdt
};
