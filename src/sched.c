/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

  Definicion de funciones del scheduler
*/

#include "sched.h"
#include "colors.h"
#include "screen.h"
#include "defines.h"


sched sched_task[3];
uint32_t current_task;

void iniciar_pantalla(){

	screen_draw_box(0, 0, CANT_FILAS, CANT_COLUMNAS, 1, 0x55); 	//Imicio pantalla CANT_COLUMNASxCANT_FILAS
	screen_draw_box(41, 0, 10, CANT_COLUMNAS, 1, 0x33);				//Inicio panel CANT_COLUMNASx09

	//screen_draw_box(42, 26, 7, 26, 1, 0x66); 
	for (int i = 0; i < 10; ++i)
	{
		if (i<3)
		{
			print("O",30+2*i,44,0x0F);
		}
		else
		{
			print("-",30+2*i,44,0x0F);
			print("-",30+2*i,46,0x0F);
		}

	}

	screen_draw_box(44,4,3,9,1,0x44); //Panel rick 
	print_dec(0,7,5,45,0x0F); //Puntaje Inicial

	screen_draw_box(44,67,3,9,1,0x11);//Panel morty
	print_dec(0,7,68,45,0x0F);//Puntaje Inicial
	
	//print("R",sched_task[RICKC137].pos_x,sched_task[RICKC137].pos_y,0x04);
	//print("R",sched_task[RICKD248].pos_x,sched_task[RICKD248].pos_y,0x01);
	//print("M",sched_task[MORTYC137].pos_x,sched_task[MORTYC137].pos_y,0x04);
	//print("M",sched_task[MORTYD248].pos_x,sched_task[MORTYD248].pos_y,0x01);
	//print("C",sched_task[CRONENBERG1].pos_x,sched_task[CRONENBERG1].pos_y,0x06);
	//print("C",sched_task[CRONENBERG2].pos_x,sched_task[CRONENBERG2].pos_y,0x06);
	//print("C",sched_task[CRONENBERG3].pos_x,sched_task[CRONENBERG3].pos_y,0x06);
		
}


void sched_init(void) {
	//Inicializamos el scheduler
	current_task = 0;
	for (uint8_t i = 0; i < 3 ; ++i)
	{
		sched_task[i].is_alive = 1;
		sched_task[i].tss_selector = ((i+16)<<3); //a partir de la 17 se encuentras los tss de cada tarea	
	}

	iniciar_pantalla();
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
