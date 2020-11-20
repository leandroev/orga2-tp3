/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

  Definicion de funciones del scheduler
*/

#include "sched.h"
#include "colors.h"
#include "screen.h"


#define IDLE    0
#define RICK    1
#define MORTY   2
#define RICK_MrMs1  3
#define RICK_MrMs2  4
#define RICK_MrMs3  5
#define MORTY_MrMs1 6
#define NORTY_MrMs2 7
#define NORTY_MrMs3 8


sched sched_task[3];
uint32_t current_task;



void sched_init(void) {
	//Inicializamos el scheduler
	current_task = 0;
	for (uint8_t i = 0; i < 3 ; ++i)
	{
		sched_task[i].is_alive = 1;
		sched_task[i].tss_selector = ((i+16)<<3); //a partir de la 17 se encuentras los tss de cada tarea	
	}

}

uint16_t sched_next_task() {
	current_task = (current_task + 1) % 3;
	while(sched_task[current_task].is_alive == 0){

		current_task = (current_task + 1) % 3;
	}
    return sched_task[current_task].tss_selector;
}










//funciones auxiliares
void imprimir_libretas(){
	print("Integrante 1: 218/16",10, 10, C_BG_RED | C_FG_WHITE);
	print("Integrante 2: 258/16",10, 12, C_BG_RED | C_FG_WHITE);
	print("Integrante 3: 951/12",10, 14, C_BG_RED | C_FG_WHITE);
}

void cambiar_fondo(){
	print(" ",0, 0, C_BG_RED | C_FG_WHITE);
}
