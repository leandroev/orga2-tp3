/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

  Declaracion de funciones del scheduler.
*/

#ifndef __SCHED_H__
#define __SCHED_H__

#include "types.h"

void sched_init();
uint16_t sched_next_task();
void imprimir_libretas();
void cambiar_fondo();




typedef struct str_sched {
	uint8_t is_alive;
	uint16_t tss_selector;
}__attribute__((__packed__, aligned (8))) sched;

extern sched sched_task[3];

#endif //  __SCHED_H__
