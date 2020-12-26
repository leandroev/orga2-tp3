/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

  Declaracion de funciones del scheduler.
*/

#ifndef __SCHED_H__
#define __SCHED_H__

#include "types.h"
#include "i386.h"
#include "defines.h"
#include "tss.h"
#include "mmu.h"

//Functions
int abs(int number) ;
void int100_look(uint32_t* position_x, uint32_t* position_y);
uint32_t int123_move(int position_x, int position_y);
void spread_megaSeeds();
bool move_assimilated(uint32_t pos_x, uint32_t pos_y);
int search_megaSeeds(uint32_t pos_x, uint32_t pos_y);
int modulo(int numero, int base);


void sched_init();
uint16_t sched_next_task();
void imprimir_libretas();
void cambiar_fondo();
void imprimir_registros(uint32_t eip, uint32_t eflags,uint16_t ss,uint16_t gs,uint16_t fs,uint16_t es,uint16_t ds,
						uint16_t cs, uint32_t stack1,uint32_t stack2,uint32_t stack3,uint32_t bcktrace1,
						uint32_t bcktrace2,uint32_t bcktrace3,uint32_t bcktrace4, uint32_t edi,uint32_t esi,uint32_t ebp,uint32_t esp,uint32_t ebx,uint32_t edx,
						uint32_t ecx, uint32_t eax,uint32_t err);

void killcurrent_task();
uint32_t check_end_game();
void set_screen_debug();
void set_modo_debug();
uint32_t check_screen_debug();
uint32_t check_act_debug();
uint32_t virtual_valida(uint32_t number);
void screen_init();
uint32_t int88(paddr_t code_phy,uint32_t pos_x, uint32_t pos_y);
int next_tss(tss_mrms* tss_str);
paddr_t next_esp0(paddr_t* esp0_str);
bool right_postition(uint32_t pos_x, uint32_t pos_y);
void reset_screen();
uint32_t make_positive(int x, int divisor);
uint32_t distMan(int desp_x,int desp_y);

typedef struct str_sched {
	uint8_t is_alive;
	uint16_t tss_selector;
	uint8_t id;
	int pos_x;
	int pos_y;
	int distCel;
	int ticks;
	uint8_t uses_of_gun;
}__attribute__((__packed__, aligned (8))) sched;


typedef struct semillas {
	uint32_t position_x;
	uint32_t position_y;
	uint8_t assimilated;
}megaSeeds;

extern void reset_MrMsCel();
extern void jump_toIdle();
extern sched sched_task[23];
megaSeeds seedsOnMap[TOTAL_SEEDS];
paddr_t pilas_0[20];


#endif //  __SCHED_H__
