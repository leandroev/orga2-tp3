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
    [GDT_IDX_NULL_DESC] =         {
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
    [GDT_CODE_0] = // 10
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
    [GDT_DATA_0] = //11
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
    [GDT_CODE_3] = //12
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
    [GDT_DATA_3] = //13
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
    [GDT_VIDEO] = //14
        {
            .limit_15_0 = 0x1F3F,   /* limit[0:15]  */
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
        },
    [TSS_INITIAL] = 
        {
              .limit_15_0 = 0X0067,   /* limit[0:15]  */
              .base_15_0 = 0x0000,    /* base[0:15]   */   
              .base_23_16 = 0x00,     /* base[23:16]  */   
              .type = 0x9,            /* type         */
              .s = 0x00,              /* s            */
              .dpl = 0x00,            /* dpl          */
              .p = 0x01,              /* p            */
              .limit_19_16 = 0x00,    /* limit[16:19] */
              .avl = 0x0,             /* avl          */
              .l = 0x0,               /* l            */
              .db = 0x0,              /* db           */
              .g = 0x00,              /* g            */
              .base_31_24 = 0x00,     /* base[31:24]  */
        }, 
    [TSS_IDLE] = //16
        {
              .limit_15_0 = 0X0067,   /* limit[0:15]  */
              .base_15_0 = 0x0000,    /* base[0:15]   */   
              .base_23_16 = 0X00,     /* base[23:16]  */   
              .type = 0x9,            /* type         */
              .s = 0x00,              /* s            */
              .dpl = 0x00,            /* dpl          */
              .p = 0x01,              /* p            */
              .limit_19_16 = 0x00,    /* limit[16:19] */
              .avl = 0x0,             /* avl          */
              .l = 0x0,               /* l            */
              .db = 0x0,              /* db           */
              .g = 0x00,              /* g            */
              .base_31_24 = 0x00,     /* base[31:24]  */
       },
    [TSS_RICK] = //17
        {
              .limit_15_0 = 0X0067,   /* limit[0:15]  */
              .base_15_0 = 0x0000,    /* base[0:15]   */   
              .base_23_16 = 0X00,     /* base[23:16]  */   
              .type = 0x9,            /* type         */
              .s = 0x00,              /* s            */
              .dpl = 0x00,            /* dpl          */
              .p = 0x01,              /* p            */
              .limit_19_16 = 0x00,    /* limit[16:19] */
              .avl = 0x0,             /* avl          */
              .l = 0x0,               /* l            */
              .db = 0x0,              /* db           */
              .g = 0x00,              /* g            */
              .base_31_24 = 0x00,     /* base[31:24]  */
       },
    [TSS_MORTY] = //18
        {
              .limit_15_0 = 0X0067,   /* limit[0:15]  */
              .base_15_0 = 0x0000,    /* base[0:15]   */   
              .base_23_16 = 0X00,     /* base[23:16]  */   
              .type = 0x9,            /* type         */
              .s = 0x00,              /* s            */
              .dpl = 0x00,            /* dpl          */
              .p = 0x01,              /* p            */
              .limit_19_16 = 0x00,    /* limit[16:19] */
              .avl = 0x0,             /* avl          */
              .l = 0x0,               /* l            */
              .db = 0x0,              /* db           */
              .g = 0x00,              /* g            */
              .base_31_24 = 0x00,     /* base[31:24]  */
       },
    [TSS_RICK_MrMs0] = //19
        {
              .limit_15_0 = 0X0067,   /* limit[0:15]  */
              .base_15_0 = 0x0000,    /* base[0:15]   */   
              .base_23_16 = 0X00,     /* base[23:16]  */   
              .type = 0x9,            /* type         */
              .s = 0x00,              /* s            */
              .dpl = 0x00,            /* dpl          */
              .p = 0x01,              /* p            */
              .limit_19_16 = 0x00,    /* limit[16:19] */
              .avl = 0x0,             /* avl          */
              .l = 0x0,               /* l            */
              .db = 0x0,              /* db           */
              .g = 0x00,              /* g            */
              .base_31_24 = 0x00,     /* base[31:24]  */
       },
    [TSS_RICK_MrMs1] = //20
        {
              .limit_15_0 = 0X0067,   /* limit[0:15]  */
              .base_15_0 = 0x0000,    /* base[0:15]   */   
              .base_23_16 = 0X00,     /* base[23:16]  */   
              .type = 0x9,            /* type         */
              .s = 0x00,              /* s            */
              .dpl = 0x00,            /* dpl          */
              .p = 0x01,              /* p            */
              .limit_19_16 = 0x00,    /* limit[16:19] */
              .avl = 0x0,             /* avl          */
              .l = 0x0,               /* l            */
              .db = 0x0,              /* db           */
              .g = 0x00,              /* g            */
              .base_31_24 = 0x00,     /* base[31:24]  */
       },
    [TSS_RICK_MrMs2] = //21
        {
              .limit_15_0 = 0X0067,   /* limit[0:15]  */
              .base_15_0 = 0x0000,    /* base[0:15]   */   
              .base_23_16 = 0X00,     /* base[23:16]  */   
              .type = 0x9,            /* type         */
              .s = 0x00,              /* s            */
              .dpl = 0x00,            /* dpl          */
              .p = 0x01,              /* p            */
              .limit_19_16 = 0x00,    /* limit[16:19] */
              .avl = 0x0,             /* avl          */
              .l = 0x0,               /* l            */
              .db = 0x0,              /* db           */
              .g = 0x00,              /* g            */
              .base_31_24 = 0x00,     /* base[31:24]  */
       },
    [TSS_RICK_MrMs3] = //22
        {
              .limit_15_0 = 0X0067,   /* limit[0:15]  */
              .base_15_0 = 0x0000,    /* base[0:15]   */   
              .base_23_16 = 0X00,     /* base[23:16]  */   
              .type = 0x9,            /* type         */
              .s = 0x00,              /* s            */
              .dpl = 0x00,            /* dpl          */
              .p = 0x01,              /* p            */
              .limit_19_16 = 0x00,    /* limit[16:19] */
              .avl = 0x0,             /* avl          */
              .l = 0x0,               /* l            */
              .db = 0x0,              /* db           */
              .g = 0x00,              /* g            */
              .base_31_24 = 0x00,     /* base[31:24]  */
       },
    [TSS_RICK_MrMs4] = //23
        {
              .limit_15_0 = 0X0067,   /* limit[0:15]  */
              .base_15_0 = 0x0000,    /* base[0:15]   */   
              .base_23_16 = 0X00,     /* base[23:16]  */   
              .type = 0x9,            /* type         */
              .s = 0x00,              /* s            */
              .dpl = 0x00,            /* dpl          */
              .p = 0x01,              /* p            */
              .limit_19_16 = 0x00,    /* limit[16:19] */
              .avl = 0x0,             /* avl          */
              .l = 0x0,               /* l            */
              .db = 0x0,              /* db           */
              .g = 0x00,              /* g            */
              .base_31_24 = 0x00,     /* base[31:24]  */
       },
    [TSS_RICK_MrMs5] = //24
        {
              .limit_15_0 = 0X0067,   /* limit[0:15]  */
              .base_15_0 = 0x0000,    /* base[0:15]   */   
              .base_23_16 = 0X00,     /* base[23:16]  */   
              .type = 0x9,            /* type         */
              .s = 0x00,              /* s            */
              .dpl = 0x00,            /* dpl          */
              .p = 0x01,              /* p            */
              .limit_19_16 = 0x00,    /* limit[16:19] */
              .avl = 0x0,             /* avl          */
              .l = 0x0,               /* l            */
              .db = 0x0,              /* db           */
              .g = 0x00,              /* g            */
              .base_31_24 = 0x00,     /* base[31:24]  */
       },
    [TSS_RICK_MrMs6] = //25
        {
              .limit_15_0 = 0X0067,   /* limit[0:15]  */
              .base_15_0 = 0x0000,    /* base[0:15]   */   
              .base_23_16 = 0X00,     /* base[23:16]  */   
              .type = 0x9,            /* type         */
              .s = 0x00,              /* s            */
              .dpl = 0x00,            /* dpl          */
              .p = 0x01,              /* p            */
              .limit_19_16 = 0x00,    /* limit[16:19] */
              .avl = 0x0,             /* avl          */
              .l = 0x0,               /* l            */
              .db = 0x0,              /* db           */
              .g = 0x00,              /* g            */
              .base_31_24 = 0x00,     /* base[31:24]  */
       },
    [TSS_RICK_MrMs7] = //26
        {
              .limit_15_0 = 0X0067,   /* limit[0:15]  */
              .base_15_0 = 0x0000,    /* base[0:15]   */   
              .base_23_16 = 0X00,     /* base[23:16]  */   
              .type = 0x9,            /* type         */
              .s = 0x00,              /* s            */
              .dpl = 0x00,            /* dpl          */
              .p = 0x01,              /* p            */
              .limit_19_16 = 0x00,    /* limit[16:19] */
              .avl = 0x0,             /* avl          */
              .l = 0x0,               /* l            */
              .db = 0x0,              /* db           */
              .g = 0x00,              /* g            */
              .base_31_24 = 0x00,     /* base[31:24]  */
       },
    [TSS_RICK_MrMs8] = //27
        {
              .limit_15_0 = 0X0067,   /* limit[0:15]  */
              .base_15_0 = 0x0000,    /* base[0:15]   */   
              .base_23_16 = 0X00,     /* base[23:16]  */   
              .type = 0x9,            /* type         */
              .s = 0x00,              /* s            */
              .dpl = 0x00,            /* dpl          */
              .p = 0x01,              /* p            */
              .limit_19_16 = 0x00,    /* limit[16:19] */
              .avl = 0x0,             /* avl          */
              .l = 0x0,               /* l            */
              .db = 0x0,              /* db           */
              .g = 0x00,              /* g            */
              .base_31_24 = 0x00,     /* base[31:24]  */
       },
    [TSS_RICK_MrMs9] = //28
        {
              .limit_15_0 = 0X0067,   /* limit[0:15]  */
              .base_15_0 = 0x0000,    /* base[0:15]   */   
              .base_23_16 = 0X00,     /* base[23:16]  */   
              .type = 0x9,            /* type         */
              .s = 0x00,              /* s            */
              .dpl = 0x00,            /* dpl          */
              .p = 0x01,              /* p            */
              .limit_19_16 = 0x00,    /* limit[16:19] */
              .avl = 0x0,             /* avl          */
              .l = 0x0,               /* l            */
              .db = 0x0,              /* db           */
              .g = 0x00,              /* g            */
              .base_31_24 = 0x00,     /* base[31:24]  */
       },
    [TSS_MORTY_MrMs0] = //29
        {
              .limit_15_0 = 0X0067,   /* limit[0:15]  */
              .base_15_0 = 0x0000,    /* base[0:15]   */   
              .base_23_16 = 0X00,     /* base[23:16]  */   
              .type = 0x9,            /* type         */
              .s = 0x00,              /* s            */
              .dpl = 0x00,            /* dpl          */
              .p = 0x01,              /* p            */
              .limit_19_16 = 0x00,    /* limit[16:19] */
              .avl = 0x0,             /* avl          */
              .l = 0x0,               /* l            */
              .db = 0x0,              /* db           */
              .g = 0x00,              /* g            */
              .base_31_24 = 0x00,     /* base[31:24]  */
       },
    [TSS_MORTY_MrMs1] = //30
        {
              .limit_15_0 = 0X0067,   /* limit[0:15]  */
              .base_15_0 = 0x0000,    /* base[0:15]   */   
              .base_23_16 = 0X00,     /* base[23:16]  */   
              .type = 0x9,            /* type         */
              .s = 0x00,              /* s            */
              .dpl = 0x00,            /* dpl          */
              .p = 0x01,              /* p            */
              .limit_19_16 = 0x00,    /* limit[16:19] */
              .avl = 0x0,             /* avl          */
              .l = 0x0,               /* l            */
              .db = 0x0,              /* db           */
              .g = 0x00,              /* g            */
              .base_31_24 = 0x00,     /* base[31:24]  */
       },
    [TSS_MORTY_MrMs2] = //31
        {
              .limit_15_0 = 0X0067,   /* limit[0:15]  */
              .base_15_0 = 0x0000,    /* base[0:15]   */   
              .base_23_16 = 0X00,     /* base[23:16]  */   
              .type = 0x9,            /* type         */
              .s = 0x00,              /* s            */
              .dpl = 0x00,            /* dpl          */
              .p = 0x01,              /* p            */
              .limit_19_16 = 0x00,    /* limit[16:19] */
              .avl = 0x0,             /* avl          */
              .l = 0x0,               /* l            */
              .db = 0x0,              /* db           */
              .g = 0x00,              /* g            */
              .base_31_24 = 0x00,     /* base[31:24]  */
       },
    [TSS_MORTY_MrMs3] = //32
        {
              .limit_15_0 = 0X0067,   /* limit[0:15]  */
              .base_15_0 = 0x0000,    /* base[0:15]   */   
              .base_23_16 = 0X00,     /* base[23:16]  */   
              .type = 0x9,            /* type         */
              .s = 0x00,              /* s            */
              .dpl = 0x00,            /* dpl          */
              .p = 0x01,              /* p            */
              .limit_19_16 = 0x00,    /* limit[16:19] */
              .avl = 0x0,             /* avl          */
              .l = 0x0,               /* l            */
              .db = 0x0,              /* db           */
              .g = 0x00,              /* g            */
              .base_31_24 = 0x00,     /* base[31:24]  */
       },
    [TSS_MORTY_MrMs4] = //33
        {
              .limit_15_0 = 0X0067,   /* limit[0:15]  */
              .base_15_0 = 0x0000,    /* base[0:15]   */   
              .base_23_16 = 0X00,     /* base[23:16]  */   
              .type = 0x9,            /* type         */
              .s = 0x00,              /* s            */
              .dpl = 0x00,            /* dpl          */
              .p = 0x01,              /* p            */
              .limit_19_16 = 0x00,    /* limit[16:19] */
              .avl = 0x0,             /* avl          */
              .l = 0x0,               /* l            */
              .db = 0x0,              /* db           */
              .g = 0x00,              /* g            */
              .base_31_24 = 0x00,     /* base[31:24]  */
       },
    [TSS_MORTY_MrMs5] = //34
        {
              .limit_15_0 = 0X0067,   /* limit[0:15]  */
              .base_15_0 = 0x0000,    /* base[0:15]   */   
              .base_23_16 = 0X00,     /* base[23:16]  */   
              .type = 0x9,            /* type         */
              .s = 0x00,              /* s            */
              .dpl = 0x00,            /* dpl          */
              .p = 0x01,              /* p            */
              .limit_19_16 = 0x00,    /* limit[16:19] */
              .avl = 0x0,             /* avl          */
              .l = 0x0,               /* l            */
              .db = 0x0,              /* db           */
              .g = 0x00,              /* g            */
              .base_31_24 = 0x00,     /* base[31:24]  */
       },
    [TSS_MORTY_MrMs6] = //35
        {
              .limit_15_0 = 0X0067,   /* limit[0:15]  */
              .base_15_0 = 0x0000,    /* base[0:15]   */   
              .base_23_16 = 0X00,     /* base[23:16]  */   
              .type = 0x9,            /* type         */
              .s = 0x00,              /* s            */
              .dpl = 0x00,            /* dpl          */
              .p = 0x01,              /* p            */
              .limit_19_16 = 0x00,    /* limit[16:19] */
              .avl = 0x0,             /* avl          */
              .l = 0x0,               /* l            */
              .db = 0x0,              /* db           */
              .g = 0x00,              /* g            */
              .base_31_24 = 0x00,     /* base[31:24]  */
       },
    [TSS_MORTY_MrMs7] = //36
        {
              .limit_15_0 = 0X0067,   /* limit[0:15]  */
              .base_15_0 = 0x0000,    /* base[0:15]   */   
              .base_23_16 = 0X00,     /* base[23:16]  */   
              .type = 0x9,            /* type         */
              .s = 0x00,              /* s            */
              .dpl = 0x00,            /* dpl          */
              .p = 0x01,              /* p            */
              .limit_19_16 = 0x00,    /* limit[16:19] */
              .avl = 0x0,             /* avl          */
              .l = 0x0,               /* l            */
              .db = 0x0,              /* db           */
              .g = 0x00,              /* g            */
              .base_31_24 = 0x00,     /* base[31:24]  */
       },
    [TSS_MORTY_MrMs8] = //37
        {
              .limit_15_0 = 0X0067,   /* limit[0:15]  */
              .base_15_0 = 0x0000,    /* base[0:15]   */   
              .base_23_16 = 0X00,     /* base[23:16]  */   
              .type = 0x9,            /* type         */
              .s = 0x00,              /* s            */
              .dpl = 0x00,            /* dpl          */
              .p = 0x01,              /* p            */
              .limit_19_16 = 0x00,    /* limit[16:19] */
              .avl = 0x0,             /* avl          */
              .l = 0x0,               /* l            */
              .db = 0x0,              /* db           */
              .g = 0x00,              /* g            */
              .base_31_24 = 0x00,     /* base[31:24]  */
       },
    [TSS_MORTY_MrMs9] = //38
        {
              .limit_15_0 = 0X0067,   /* limit[0:15]  */
              .base_15_0 = 0x0000,    /* base[0:15]   */   
              .base_23_16 = 0X00,     /* base[23:16]  */   
              .type = 0x9,            /* type         */
              .s = 0x00,              /* s            */
              .dpl = 0x00,            /* dpl          */
              .p = 0x01,              /* p            */
              .limit_19_16 = 0x00,    /* limit[16:19] */
              .avl = 0x0,             /* avl          */
              .l = 0x0,               /* l            */
              .db = 0x0,              /* db           */
              .g = 0x00,              /* g            */
              .base_31_24 = 0x00,     /* base[31:24]  */
       }

    
};

gdt_descriptor_t GDT_DESC = {sizeof(gdt) - 1, (uint32_t)&gdt};
