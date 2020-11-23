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
uint32_t score_rick;
uint32_t score_morty;
sched sched_task[23];

void sched_init(void) {
	//Inicializamos el scheduler
	screen_debug = 0;
	act_debug = 0;
	current_task = 0;
	for (uint8_t i = 0; i < 3 ; ++i)
	{	
		sched_task[i].distCel = -1;
		sched_task[i].ticks   = -1;
		sched_task[i].pos_x   = -1;
		sched_task[i].pos_y   = -1;
		sched_task[i].id = i;
		sched_task[i].is_alive = TRUE;
		sched_task[i].tss_selector = ((i+16)<<3); //a partir de la 16 se encuentras los tss de cada tarea	
	}

	for (uint8_t i = 3; i < 23 ; ++i)
	{
		sched_task[i].ticks   = -1;
		sched_task[i].distCel = -1;
		sched_task[i].pos_x   = -1;
		sched_task[i].pos_y   = -1;
		sched_task[i].id = i;
		sched_task[i].is_alive = FALSE;
		sched_task[i].tss_selector = ((i+16)<<3); //a partir de la 19 se encuentras los tss de cada tarea	
	}
	screen_init();

	spread_megaSeeds();

	for (int i = 0; i < 20; ++i)
	{
		pilas_0[i] = 0;
	}
}

uint16_t sched_next_task() {
	current_task = (current_task + 1) % 23;
	while(sched_task[current_task].is_alive == FALSE){

		current_task = (current_task + 1) % 23;
	}
    return sched_task[current_task].tss_selector;
}


void killcurrent_task(){
	sched_task[current_task].is_alive = FALSE;
	if ( current_task == RICK || current_task == MORTY)
	{	
		print("GAME OVER",35,15,0x0F);
		
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

paddr_t next_esp0(paddr_t* esp0_str) {
	for (int i = 0; i < 20; ++i)
	{
		if (esp0_str[i] != 0)
		{
			return esp0_str[i];
		}
	}
	return 0;
}

bool right_postition(uint32_t pos_x, uint32_t pos_y){
	if(pos_x < 80  && pos_y < 40 ){
		return TRUE;
	}
	return FALSE;
}


uint32_t int88(paddr_t code_phy,uint32_t pos_x, uint32_t pos_y){
	if (current_task == RICK || current_task == MORTY){
		/*verificar si es una posicion valida*/
		if (!right_postition(pos_x, pos_y))
		{
			killcurrent_task();
			return 0;
		}
		
		/*if en posx,posy hay una semilla*/
		for (uint32_t i = 0; i < TOTAL_SEEDS; i++) {
			if(seedsOnMap[i].position_x == pos_x && seedsOnMap[i].position_y == pos_y){
				int index;
				if (current_task == RICK){
					//verf slot
					index = next_tss(tss_Rickmrms);
					if (index == -1)
					{
						// jump_toIdle();
						return 0;
					}else{
						//semilla asimilada
						seedsOnMap[i].assimilated = TRUE;
						/*actualizar puntaje*/
						score_rick = score_rick + 425;
						/*Actualizar pantalla*/
						reset_screen();
						// jump_toIdle();
						return 0;
	
					}
				}else{//morty
					//verf slot
					index = next_tss(tss_Mortymrms);
					if (index == -1)
					{
						// jump_toIdle();
						return 0;
					}else{
						//semilla asimilada
						seedsOnMap[i].assimilated = TRUE;
						/*actualizar puntaje*/
						score_morty = score_morty + 425;
						/*Actualizar pantalla*/
						reset_screen();
						// jump_toIdle();
						return 0;
					}
				}				
			}
		}
		
		if (current_task == RICK)
		{	
			//verifico si hay slots disponibles
			int index = next_tss(tss_Rickmrms);
			if (index == -1)
			{
				// jump_toIdle();
				return 0;
			}else{

				tss_Rickmrms[index].in_use = TRUE;
				vaddr_t virt_task = 0x08000000+index*PAGE_SIZE;
				paddr_t map_phy = INICIO_DE_PAGINAS_LIBRES_TAREAS + (2*PAGE_SIZE*pos_x) +(2*PAGE_SIZE*80*pos_y);
				task_init(&tss_Rickmrms[index].task_seg,map_phy,virt_task,code_phy,2,next_esp0(pilas_0));
				sched_task[index + 3].is_alive = TRUE;
				sched_task[index + 3].pos_x = pos_x;
				sched_task[index + 3].pos_y = pos_y;
				sched_task[index + 3].distCel = 7;
				sched_task[index + 3].ticks = 2;


				//reseteo pantalla? verficar
				reset_screen();
				// jump_toIdle();
				return virt_task;
			}

		}else{//morty
			//verifico si hay slots disponibles
			int index = next_tss(tss_Mortymrms);
			if (index == -1)
			{
				return 0;
			}else{
				tss_Mortymrms[index].in_use = TRUE;
				vaddr_t virt_task = 0x08000000 + index*PAGE_SIZE;
				paddr_t map_phy = INICIO_DE_PAGINAS_LIBRES_TAREAS + (2*PAGE_SIZE*pos_x) +(2*PAGE_SIZE*80*pos_y);
				task_init(&tss_Mortymrms[index].task_seg,map_phy,virt_task,code_phy,2,next_esp0(pilas_0));
				sched_task[index + 13].is_alive = TRUE;
				sched_task[index + 13].pos_x = pos_x;
				sched_task[index + 13].pos_y = pos_y;
				sched_task[index + 13].distCel = 7;
				sched_task[index + 13].ticks = 2;


				//reseteo pantalla? verficar
				reset_screen();
				// jump_toIdle();
				return virt_task;
			}			
		}
	
	}else{

		killcurrent_task();
		return 0;
	}
}

void use_portal_gun() {
		/* //rand() % 10;
		*/

		uint32_t random_task = rand() % 10;		//tarea aleatoria del equipo contrario
		uint32_t position_x = rand() % CANT_FILAS;
		uint32_t position_y = rand() % CANT_COLUMNAS;
		uint32_t current_cr3;
		uint32_t old_cr3;
		vaddr_t virt_task;
		paddr_t new_phy;
		uint32_t attrs = 0x7;

		if(current_task > 2 && current_task < 13) {
			/*Tareas de Rick*/
			//Copiar el código de sched_task[current_task] a la nueva posición
			random_task += 13;
			if(sched_task[random_task].is_alive == FALSE) {
				return;
			}
			//Entonces sigue viva
			sched_task[random_task].pos_x = position_x;
			sched_task[random_task].pos_y = position_y;
			random_task -= 13;

			virt_task = 0x800A000 + random_task * PAGE_SIZE;
			new_phy = INICIO_DE_PAGINAS_LIBRES_TAREAS + (2*PAGE_SIZE*position_x) +(2*PAGE_SIZE*80*position_y);
			current_cr3 = tss_Mortymrms[random_task].task_seg.cr3;
			old_cr3 = rcr3();

			lcr3(current_cr3);

			mmu_map_page(current_cr3, new_phy, new_phy, attrs); 
			mmu_map_page(current_cr3, new_phy + PAGE_SIZE, new_phy + PAGE_SIZE, attrs); 

			uint32_t* src = (uint32_t*) virt_task;
			uint32_t* dst = (uint32_t*) new_phy;
			
			for (int i = 0; i < 2048; ++i)
			{
				dst[i] = src[i];
			}
			
			mmu_unmap_page(current_cr3, new_phy);
			mmu_unmap_page(current_cr3, new_phy + PAGE_SIZE);
			
			mmu_unmap_page(current_cr3, virt_task);
			mmu_unmap_page(current_cr3, virt_task + PAGE_SIZE);

			mmu_map_page(current_cr3, virt_task, new_phy, attrs); 
			mmu_map_page(current_cr3, virt_task + PAGE_SIZE, new_phy + PAGE_SIZE, attrs); 

			lcr3(old_cr3);
		} else if (current_task > 12 && current_task < 23) {
			/*Tareas de Morty*/
			random_task += 3; 
			if(sched_task[random_task].is_alive == FALSE) {
				return;
			}
			// Sigue viva
			sched_task[random_task].pos_x = position_x;
			sched_task[random_task].pos_y = position_y;
			random_task -= 3;

			virt_task = 0x8000000 + random_task * PAGE_SIZE;
			new_phy = INICIO_DE_PAGINAS_LIBRES_TAREAS + (2*PAGE_SIZE*position_x) +(PAGE_SIZE*80*position_y);
			current_cr3 = tss_Rickmrms[random_task].task_seg.cr3;
			old_cr3 = rcr3();

			lcr3(current_cr3);

			mmu_map_page(current_cr3, new_phy, new_phy, attrs); 
			mmu_map_page(current_cr3, new_phy + PAGE_SIZE, new_phy + PAGE_SIZE, attrs); 

			uint32_t* src = (uint32_t*) virt_task;
			uint32_t* dst = (uint32_t*) new_phy;
			
			for (int i = 0; i < 2048; ++i)
			{
				dst[i] = src[i];
			}
			
			mmu_unmap_page(current_cr3, new_phy);
			mmu_unmap_page(current_cr3, new_phy + PAGE_SIZE);
			
			mmu_unmap_page(current_cr3, virt_task);
			mmu_unmap_page(current_cr3, virt_task + PAGE_SIZE);

			mmu_map_page(current_cr3, virt_task, new_phy, attrs); 
			mmu_map_page(current_cr3, virt_task + PAGE_SIZE, new_phy + PAGE_SIZE, attrs); 

			lcr3(old_cr3);
		}
	reset_screen();
}

void screen_init(){

	screen_draw_box(0, 0, CANT_FILAS, CANT_COLUMNAS, 1, 0x55); 	//Imicio pantalla CANT_COLUMNASxCANT_FILAS
	screen_draw_box(41, 0, 10, CANT_COLUMNAS, 1, 0x33);				//Inicio panel CANT_COLUMNASx09


	screen_draw_box(44,4,3,9,1,0x44); //Panel rick 
	print_dec(score_rick,7,5,45,0x0F); //Puntaje Inicial

	screen_draw_box(44,67,3,9,1,0x11);//Panel morty
	print_dec(score_morty,7,68,45,0x0F);//Puntaje Inicial
	
	//screen_draw_box(42, 26, 7, 26, 1, 0x66); 
	for (int i = 0; i < 10; ++i){
		
		if (i<3){
			print("O",30+2*i,44,0x0F);
		}
		else{
			print("-",30+2*i,44,0x0F);
			print("-",30+2*i,46,0x0F);
		}

	}

	
		
}


void reset_screen(){
	//Imicio pantalla CANT_COLUMNASxCANT_FILAS
	screen_draw_box(0,0,CANT_FILAS,CANT_COLUMNAS,1,0x55);
	//restaturo semillas 
	for (int i = 0; i < TOTAL_SEEDS; ++i)
	{
		if (seedsOnMap[i].assimilated == FALSE)
		{
			print("$", seedsOnMap[i].position_x, seedsOnMap[i].position_y, C_FG_WHITE | C_BG_BLACK);			
		}
	}
	//Restauro Mr Meeseeks RICK
	for (int i = 3; i < 13; ++i)
	{
		if (sched_task[i].is_alive == TRUE)
		{
			print("R", sched_task[i].pos_x, sched_task[i].pos_y, C_FG_WHITE | C_BG_RED);
		}

	}
	//Restauro Mr Meeseeks MORTY
	for (int i = 13; i < 23; ++i)
	{
		
		if (sched_task[i].is_alive == TRUE)
		{
			print("M", sched_task[i].pos_x, sched_task[i].pos_y, C_FG_WHITE | C_BG_BLUE);
		}
	}

	//Seteo puntajes
	print_dec(score_rick,7,5,45,0x0F);
	print_dec(score_morty,7,68,45,0x0F);

}



void spread_megaSeeds(){

	megaSeeds tmp;

	for (uint32_t i = 0; i < TOTAL_SEEDS; i++){
		tmp.position_x = rand() % CANT_COLUMNAS;
		tmp.position_y = rand() % CANT_FILAS;
		seedsOnMap[i] = tmp;
		seedsOnMap[i].assimilated = FALSE;

		print("$", tmp.position_x, tmp.position_y, C_FG_WHITE | C_BG_BLACK);
	}

}

bool move_assimilated(uint32_t pos_x, uint32_t pos_y){
	for (int i = 0; i < TOTAL_SEEDS; ++i){

		if (seedsOnMap[i].assimilated == FALSE){
			if (seedsOnMap[i].position_x == pos_x && seedsOnMap[i].position_y == pos_y )
			{
				return TRUE;
			}
		}
	}
	return FALSE;

}
//always take a valid position
int search_megaSeeds(uint32_t pos_x, uint32_t pos_y){

	for (int i = 0; i < TOTAL_SEEDS; i++) {
		if(seedsOnMap[i].position_x == pos_x && seedsOnMap[i].position_y == pos_y){
			return i;	
		}
	}
	return -1;

}

uint32_t distMan(uint32_t curr_posx,uint32_t curr_posy,int desp_x,int desp_y){
	return abs(curr_posx-desp_x) + abs(curr_posy-desp_y);
}

uint32_t int123_move(int desp_x, int desp_y) {
	uint32_t curr_posx = sched_task[current_task].pos_x; 
	uint32_t curr_posy = sched_task[current_task].pos_y;
	uint32_t newpos_x	= make_positive((curr_posx + desp_x) % CANT_COLUMNAS, CANT_COLUMNAS);
	uint32_t newpos_y	= make_positive((curr_posy + desp_y) % CANT_FILAS, CANT_FILAS);
	
	if (current_task == RICK || current_task == MORTY){
		killcurrent_task();
	}
	// if (distMan(curr_posx,curr_posy,desp_x,desp_y) > 7){

	// 	return 0;
	// }

	if (move_assimilated(newpos_x,newpos_y)){

		//assimilated seed, kill current task and save the kernel stack
		int index = search_megaSeeds(newpos_x,newpos_y);
		seedsOnMap[index].assimilated = TRUE;
		sched_task[current_task].is_alive = FALSE;
		tss_t current_tss;
		if (current_task < 13){
			score_rick = score_rick + 425;
			current_tss = tss_Rickmrms[current_task-3].task_seg;
		}else{
			current_tss = tss_Mortymrms[current_task-13].task_seg;
			score_morty = score_morty + 425;

		}
		paddr_t pila_0 = current_tss.esp0;
		int i = 0;
		while( i < 20)
		{
			if (pilas_0[i] == 0){

				pilas_0[i] = pila_0;
				i = 20;
			}
			i++;
		}
		reset_screen();
		return 0;		
	}else{

		int index;
		vaddr_t virt_task;
		tss_t current_tss; 
		if (current_task < 13){
			current_tss = tss_Rickmrms[current_task-3].task_seg;
			index = current_task-3;
			virt_task = 0x08000000 + index*PAGE_SIZE;
		}else{
			index = current_task-13;
			virt_task = 0x0800A000 + index*PAGE_SIZE;
			current_tss = tss_Mortymrms[current_task-13].task_seg;
		}
		
		// uint32_t old_posx = sched_task[current_task].pos_x;
		// uint32_t old_posy = sched_task[current_task].pos_y;
		// paddr_t old_phy = INICIO_DE_PAGINAS_LIBRES_TAREAS + (2*PAGE_SIZE*old_posx) +(2*PAGE_SIZE*80*old_posy);
		paddr_t new_phy = INICIO_DE_PAGINAS_LIBRES_TAREAS + (2*PAGE_SIZE*newpos_x) +(2*PAGE_SIZE*80*newpos_y);
		uint32_t attrS = 0x00000007;
		

		//temporal mapping wiht identity mapping
		uint32_t current_cr3 = current_tss.cr3;
		mmu_map_page(current_cr3,new_phy,new_phy,attrS); //4kb
		mmu_map_page(current_cr3,new_phy+PAGE_SIZE,new_phy+PAGE_SIZE,attrS); //4kb
		
		//code copy from the virtual address
		uint32_t* src = (uint32_t*) virt_task;
		uint32_t* dst = (uint32_t*) new_phy;
		for (int i = 0; i < 2048; ++i)
		{
			dst[i] = src[i];
		}

		//unmapping temporal
		mmu_unmap_page(current_cr3,new_phy);
		mmu_unmap_page(current_cr3,new_phy+PAGE_SIZE);

		//unmapping old virtual address
		mmu_unmap_page(current_cr3,virt_task); 
		mmu_unmap_page(current_cr3,virt_task+PAGE_SIZE);

		//mapping new physical address
		mmu_map_page(current_cr3,virt_task,new_phy,attrS); 
		mmu_map_page(current_cr3,virt_task+PAGE_SIZE,new_phy+PAGE_SIZE,attrS);

		//reset positicion
		sched_task[current_task].pos_x = newpos_x;
		sched_task[current_task].pos_y = newpos_y;

		reset_screen(); 
		return 1;
	}
}

void int100_look(uint32_t* position_x, uint32_t* position_y) {

	if(current_task == RICK || current_task == MORTY){
		*position_x = -1;
		*position_y = -1;
	} else if (current_task > MORTY) { 
		
		uint32_t tmp_x = abs(sched_task[current_task].pos_x - seedsOnMap[0].position_x);
		uint32_t tmp_y = abs(sched_task[current_task].pos_y - seedsOnMap[0].position_y);

		uint32_t steps = tmp_x + tmp_y;
		uint32_t mostNearSeed = 0;


		for (uint32_t i = 1; i < TOTAL_SEEDS; i++) {
			tmp_x = abs(sched_task[current_task].pos_x - seedsOnMap[i].position_x);
			tmp_y = abs(sched_task[current_task].pos_y - seedsOnMap[i].position_y);

			if(steps > (tmp_x + tmp_y)) {
				steps = tmp_x + tmp_y;
				mostNearSeed = i;
			}
		}

		*position_x = seedsOnMap[mostNearSeed].position_x;
		*position_y = seedsOnMap[mostNearSeed].position_y;
		print("$",seedsOnMap[mostNearSeed].position_x, seedsOnMap[mostNearSeed].position_y, C_FG_WHITE | C_BG_GREEN);
	}

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

uint32_t make_positive(int x, int divisor){
	if(x<0){
		return x+divisor;
	} else {
		return x;
	}
}


void set_modo_debug()
{
	if (screen_debug == 1){
		act_debug = 1;
		screen_debug = 0;
		//reseteo pantalla
		reset_screen();
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

void reset_MrMsCel(){
	for (int i = 3; i < 23; ++i)
	{
		if (sched_task[i].distCel ==1)
		{
			sched_task[i].ticks = -1; 
		}	
		if (sched_task[i].ticks == 0)
		{
			sched_task[i].ticks = 2;
			sched_task[i].distCel--; 
		}
		if (sched_task[i].ticks > 0)
		{
			sched_task[i].ticks--;
		}	
	}
}