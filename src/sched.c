/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

  Definicion de funciones del scheduler
*/

#include "sched.h"
#include "colors.h"
#include "screen.h"
#include "prng.h"

uint32_t screen_debug;
uint32_t act_debug;
uint32_t current_task;

sched sched_task[3];

void sched_init(void) {
	//Inicializamos el scheduler
	screen_debug = 0;
	act_debug = 0;
	current_task = 0;
	for (uint8_t i = 0; i < 3 ; ++i)
	{
		sched_task[i].is_alive = 1;
		sched_task[i].tss_selector = ((i+16)<<3); //a partir de la 16 se encuentras los tss de cada tarea	
	}

	for (uint8_t i = 3; i < 23 ; ++i)
	{
		sched_task[i].is_alive = 0;
		sched_task[i].tss_selector = ((i+16)<<3); //a partir de la 17 se encuentras los tss de cada tarea	
	}
	iniciar_pantalla();

	spread_megaSeeds();

	//int100_look(13, 21);
	print("X", 13, 21, C_FG_DARK_GREY | C_BG_BLACK);
}

uint16_t sched_next_task() {
	current_task = (current_task + 1) % 3;
	while(sched_task[current_task].is_alive == 0){

		current_task = (current_task + 1) % 3;
	}
    return sched_task[current_task].tss_selector;
}


void killcurrent_task(){
	sched_task[current_task].is_alive = 0;
	if ( current_task == RICK || current_task == MORTY)
	{	
		print("GAME OVER",35,15,0x0F);
		// print("Universe-D248 Wins",30,17,0x09);
		
	}
	//jump_toIdle();

}


int next_tss(tss_mrms* tss_str) {
	for (int i = 0; i < 10; ++i)
	{
		if (tss_str[i].in_use != 1)
		{
			return i;
		}
	}
	return -1;
}

uint32_t int88(paddr_t code_phy,uint32_t pos_x, uint32_t pos_y){
	if (current_task == RICK || current_task == MORTY){
		/*if en posx,posy hay una semilla*/
		for (uint32_t i = 0; i < TOTAL_SEEDS; i++) {
			if(seedsOnMap[i].position_x == pos_x && seedsOnMap[i].position_y == pos_y){
				//hacer algo
				/*verificar si es una posicion valida*/

			}
		}
		
		if (current_task == RICK)
		{	
			//verifico si hay slots disponibles
			int index = next_tss(tss_Rickmrms);
			if (index == -1)
			{
				return 0;
			}else{
				tss_Rickmrms[index].in_use = 1;
				vaddr_t virt_task = 0x08000000+index*PAGE_SIZE;
				paddr_t map_phy = INICIO_DE_PAGINAS_LIBRES_TAREAS + (2*PAGE_SIZE*pos_x) +(2*PAGE_SIZE*80*pos_y);
				task_init(&tss_Rickmrms[index].task_seg,map_phy,virt_task,code_phy,2);
				sched_task[index + 3].is_alive = 1;
				return virt_task;

			}

		}else{
			//verifico si hay slots disponibles
			int index = next_tss(tss_Mortymrms);
			if (index == -1)
			{
				return 0;
			}else{
				tss_Mortymrms[index].in_use = 1;
				vaddr_t virt_task = 0x0800A000 + index*PAGE_SIZE;
				paddr_t map_phy = INICIO_DE_PAGINAS_LIBRES_TAREAS + (2*PAGE_SIZE*pos_x) +(2*PAGE_SIZE*80*pos_y);
				task_init(&tss_Mortymrms[index].task_seg,map_phy,virt_task,code_phy,2);
				sched_task[index + 13].is_alive = 1;
				return virt_task;

			}
			
		}
	
	}else{

		killcurrent_task();
		return 0;
	}



}

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


void spread_megaSeeds(){

	megaSeeds tmp;

	for (uint32_t i = 0; i < TOTAL_SEEDS; i++){
		tmp.position_x = rand() % CANT_COLUMNAS;
		tmp.position_y = rand() % CANT_FILAS;
		seedsOnMap[i] = tmp;

		print("$", tmp.position_x, tmp.position_y, C_FG_WHITE | C_BG_BROWN);
	}

}

uint32_t int123_move(int position_x, int position_y) {
	position_x = 0;
	position_y = 0;
	return position_x + position_y;
}

void int100_look(uint32_t* position_x, uint32_t* position_y) {

	/*
	if(current_task == RICK || current_task == MORTY){
		position_x = -1;
		position_y = -1;
	} else {
		
	}
	*/
	//falta una estructura que diga la posicion de un mr meeseek
	uint32_t tmp_x = abs(*position_x - seedsOnMap[0].position_x);
	uint32_t tmp_y = abs(*position_y - seedsOnMap[0].position_y);

	uint32_t steps = tmp_x + tmp_y;
	uint32_t mostNearSeed = 0;


	for (uint32_t i = 1; i < TOTAL_SEEDS; i++) {
		tmp_x = abs(*position_x - seedsOnMap[i].position_x);
		tmp_y = abs(*position_y - seedsOnMap[i].position_y);

		if(steps > (tmp_x + tmp_y)) {
			steps = tmp_x + tmp_y;
			mostNearSeed = i;
		}
	}
	
	print("(", 34, 40, C_FG_WHITE | C_BG_BROWN);
	print_dec(seedsOnMap[mostNearSeed].position_x, 2, 35, 40, C_FG_WHITE | C_BG_BROWN);
	print("-",37, 40, C_FG_WHITE | C_BG_BROWN);
	print_dec(seedsOnMap[mostNearSeed].position_y, 2, 38, 40, C_FG_WHITE | C_BG_BROWN);
	print(")",40, 40, C_FG_WHITE | C_BG_BROWN);

	*position_x = seedsOnMap[mostNearSeed].position_x;
	*position_y = seedsOnMap[mostNearSeed].position_y;
	print("$",seedsOnMap[mostNearSeed].position_x, seedsOnMap[mostNearSeed].position_y, C_FG_BLACK | C_BG_GREEN);
}



//funciones auxiliares

void imprimir_registros(uint32_t eip, uint32_t eflags,uint16_t ss,uint16_t gs,uint16_t fs,uint16_t es,uint16_t ds,
	uint16_t cs, uint32_t edi,uint32_t esi,uint32_t ebp,uint32_t esp,uint32_t ebx,uint32_t edx,uint32_t ecx, 
	uint32_t eax,uint32_t stack1,uint32_t stack2,uint32_t stack3,uint32_t stack4,uint32_t stack5 ){
	print("eax",26,7,0x0F);
	print_hex(eax,8,30,7,0x0F);
	print("ecx",26,9,0x0F);
	print_hex(ecx,8,30,9,0x0F);
	print("edx",26,11,0x0F);
	print_hex(edx,8,30,11,0x0F);
	print("ebx",26,13,0x0F);
	print_hex(ebx,8,30,13,0x0F);
	print("esp",26,15,0x0F);
	print_hex(esp,8,30,15,0x0F);
	print("ebp",26,17,0x0F);
	print_hex(ebp,8,30,17,0x0F);
	print("esi",26,19,0x0F);
	print_hex(esi,8,30,19,0x0F);
	print("edi",26,21,0x0F);
	print_hex(edi,8,30,21,0x0F);
	print("eip",26,23,0x0F);
	print_hex(eip,8,30,23,0x0F);
	print("cs",27,25,0x0F);
	print_hex(cs,4,30,25,0x0F);
	print("ds",27,27,0x0F);
	print_hex(ds,4,30,27,0x0F);
	print("es",27,29,0x0F);
	print_hex(es,4,30,29,0x0F);
	print("fs",27,31,0x0F);
	print_hex(fs,4,30,31,0x0F);
	print("gs",27,33,0x0F);
	print_hex(gs,4,30,33,0x0F);
	print("ss",27,35,0x0F);
	print_hex(ss,4,30,35,0x0F);
	print("eflags",26,37,0x0F);
	print_hex(eflags,8,33,37,0x0F);		
	uint32_t cr0 = rcr0();
	print("cr0",39,8,0x0F);
	print_hex(cr0,8,44,8,0x0F);
	uint32_t cr2 = rcr2();
	print("cr2",39,10,0x0F);
	print_hex(cr2,8,44,10,0x0F);
	uint32_t cr3 = rcr3();
	print("cr3",39,12,0x0F);
	print_hex(cr3,8,44,12,0x0F);
	uint32_t cr4 = rcr4();
	print("cr4",39,14,0x0F);
	print_hex(cr4,8,44,14,0x0F);
	print("Stack",40,27,0x0F);
	print_hex(stack1,8,40,28,0x0F);
	print_hex(stack2,8,40,29,0x0F);
	print_hex(stack3,8,40,30,0x0F);
	print_hex(stack4,8,40,31,0x0F);
	print_hex(stack5,8,40,32,0x0F);
	screen_draw_box(1,24,40,1,1,0x00); //pinto linea izquierda
	screen_draw_box(1,53,40,1,1,0x00); //pinto linea derecha
	screen_draw_box(1,24,1,29,1,0x00); //pinto linea horzontal superior
	screen_draw_box(3,24,1,29,1,0x00); //pinto linea horzontal inferior
	screen_draw_box(2,25,1,28,1,0x44); //pinto linea roja intermedia


}

void set_modo_debug()
{
	if (screen_debug == 1){
		act_debug = 1;
		screen_debug = 0;
		//reseteo pantalla
		iniciar_pantalla();
	}else{
		screen_debug = 1;
		act_debug = 0;
	}
}


uint32_t check_screen_debug(){
	return screen_debug;
}

uint32_t check_act_debug(){
	return act_debug;
}
void imprimir_libretas(){
	print("Integrante 1: 218/16",10, 10, C_BG_RED | C_FG_WHITE);
	print("Integrante 2: 258/16",10, 12, C_BG_RED | C_FG_WHITE);
	print("Integrante 3: 951/12",10, 14, C_BG_RED | C_FG_WHITE);
}

void cambiar_fondo(){
	print(" ",0, 0, C_BG_RED | C_FG_WHITE);
}

int abs(int number) {
	if(number < 0)
		return -number;
	else
		return number;
	
}

int modulo(int numero,int base){
	if(numero > 0){
		return numero % base;
	}else{
		return (numero + base) % base;
	}
}
