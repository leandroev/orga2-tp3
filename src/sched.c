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
#include "isr.h"

uint32_t screen_debug;
uint32_t act_debug;
uint32_t current_task;
uint32_t previous_task;
uint32_t score_rick;
uint32_t score_morty;
sched sched_task[23];

void sched_init(void) {
    //Inicializamos el scheduler
    screen_debug = 0;
    act_debug = 0;
    current_task = 0;
    previous_task = 0;
    for (uint8_t i = 0; i < 3; ++i) {
        sched_task[i].distCel = -1;
        sched_task[i].ticks = -1;
        sched_task[i].pos_x = -1;
        sched_task[i].pos_y = -1;
        sched_task[i].is_alive = TRUE;
        sched_task[i].tss_selector = ((i + 16) << 3); //a partir de la 16 se encuentras los tss de cada tarea
        sched_task[i].uses_of_gun = 0;
    }

    for (uint8_t i = 3; i < 23; ++i) {
        sched_task[i].ticks = -1;
        sched_task[i].distCel = -1;
        sched_task[i].pos_x = -1;
        sched_task[i].pos_y = -1;
        sched_task[i].is_alive = FALSE;
        sched_task[i].tss_selector = ((i + 16) << 3); //a partir de la 19 se encuentras los tss de cada tarea
        sched_task[i].uses_of_gun = TRUE;
    }
    screen_init();

    spread_megaSeeds();

    for (int i = 0; i < 20; ++i) {
        pilas_0[i] = 0;
    }
}

uint16_t sched_next_task() {
    uint32_t next_task;
    if(current_task == 0 && previous_task == 0){
        next_task = RICK;
    }
    if(previous_task == 0 && current_task == RICK){
        next_task = MORTY;
    }else{
        if(previous_task < 13 && previous_task != MORTY && previous_task != 0){
            if(previous_task == RICK){
                next_task = 3;
            }else{
                next_task = (previous_task + 1) % 13;
            }
            while(sched_task[next_task].is_alive == FALSE){
                next_task = (next_task + 1) % 13;
            }
            if(next_task < RICK){
                next_task = RICK;
            }
        }
        if(previous_task > 12 || previous_task == MORTY){
            if(previous_task == MORTY){
                next_task = 13;
            }else{
                next_task = (previous_task + 1) % 23;
            }
            while(sched_task[next_task].is_alive == FALSE){
                next_task = (next_task + 1) % 23;
            }
            if(next_task < MORTY){
                next_task = MORTY;
            }
        }
    }
    previous_task = current_task;
    current_task = next_task;
    
    print("R", 16, 42, C_FG_WHITE | C_BG_RED);
    print("M", 63, 42, C_FG_WHITE | C_BG_BLUE);


    if(sched_task[1].is_alive == TRUE){
        next_clock1(44, 16, 1);
    }else{
        print("X", 16, 44, C_FG_RED | C_BG_BLACK);
    }

    if(sched_task[2].is_alive == TRUE){
        next_clock2(44, 63, 2);
    }else{
        print("X", 63, 44, C_FG_BLUE | C_BG_BLACK);
    }

    if(sched_task[3].is_alive == TRUE){
        next_clock3(44, 21, 3);
    }else{
        print("X", 21, 44, C_FG_RED | C_BG_BLACK);
    }

    if(sched_task[4].is_alive == TRUE){
        next_clock4(44, 25, 4);
    }else{
        print("X", 25, 44, C_FG_RED | C_BG_BLACK);
    }

    if(sched_task[5].is_alive == TRUE){
        next_clock5(44, 29, 5);
    }else{
        print("X", 29, 44, C_FG_RED | C_BG_BLACK);
    }    

    if(sched_task[6].is_alive == TRUE){
        next_clock6(44, 33, 6);
    }else{
        print("X", 33, 44, C_FG_RED | C_BG_BLACK);
    }

    if(sched_task[7].is_alive == TRUE){
        next_clock7(44, 37, 7);
    }else{
        print("X", 37, 44, C_FG_RED | C_BG_BLACK);
    }

    if(sched_task[8].is_alive == TRUE){
        next_clock8(44, 41, 8);
    }else{
        print("X", 41, 44, C_FG_RED | C_BG_BLACK);
    }

    if(sched_task[9].is_alive == TRUE){
        next_clock9(44, 45, 9);
    }else{
        print("X", 45, 44, C_FG_RED | C_BG_BLACK);
    }

    if(sched_task[10].is_alive == TRUE){
        next_clock10(44, 49, 10);
    }else{
        print("X", 49, 44, C_FG_RED | C_BG_BLACK);
    }

    if(sched_task[11].is_alive == TRUE){
        next_clock11(44, 53, 11);
    }else{
        print("X", 53, 44, C_FG_RED | C_BG_BLACK);
    }

    if(sched_task[12].is_alive == TRUE){
        next_clock12(44, 57, 12);
    }else{
        print("X", 57, 44, C_FG_RED | C_BG_BLACK);
    }

    if(sched_task[13].is_alive == TRUE){
        next_clock13(47, 21, 13);
    }else{
        print("X", 21, 47, C_FG_BLUE | C_BG_BLACK);
    }

    if(sched_task[14].is_alive == TRUE){
        next_clock14(47, 25, 14);
    }else{
        print("X", 25, 47, C_FG_BLUE | C_BG_BLACK);
    }

    if(sched_task[15].is_alive == TRUE){
        next_clock15(47, 29, 15);
    }else{
        print("X", 29, 47, C_FG_BLUE | C_BG_BLACK);
    }
    
    if(sched_task[16].is_alive == TRUE){
        next_clock16(47, 33, 16);
    }else{
        print("X", 33, 47, C_FG_BLUE | C_BG_BLACK);
    }

    if(sched_task[17].is_alive == TRUE){
        next_clock17(47, 37, 17);
    }else{
        print("X", 37, 47, C_FG_BLUE | C_BG_BLACK);
    }
    
    if(sched_task[18].is_alive == TRUE){
        next_clock18(47, 41, 18);
    }else{
        print("X", 41, 47, C_FG_BLUE | C_BG_BLACK);
    }
    
    if(sched_task[19].is_alive == TRUE){
        next_clock19(47, 45, 19);
    }else{
        print("X", 45, 47, C_FG_BLUE | C_BG_BLACK);
    }

    if(sched_task[20].is_alive == TRUE){
        next_clock20(47, 49, 20);
    }else{
        print("X", 49, 47, C_FG_BLUE | C_BG_BLACK);
    }
    
    if(sched_task[21].is_alive == TRUE){
        next_clock21(47, 53, 21);
    }else{
        print("X", 53, 47, C_FG_BLUE | C_BG_BLACK);
    }

    if(sched_task[22].is_alive == TRUE){
        next_clock22(47, 57, 22);
    }else{
        print("X", 57, 47, C_FG_BLUE | C_BG_BLACK);
    }
    return sched_task[current_task].tss_selector;
}

void screen_init() {

    screen_draw_box(0, 0, CANT_FILAS, CANT_COLUMNAS, 1, 0x55);    //Imicio pantalla CANT_COLUMNASxCANT_FILAS
    screen_draw_box(41, 0, 10, CANT_COLUMNAS, 1, 0x33);                //Inicio panel CANT_COLUMNASx09


    screen_draw_box(44, 4, 3, 9, 1, 0x44); //Panel rick
    print_dec(score_rick, 7, 5, 45, 0x0F); //Puntaje Inicial

    screen_draw_box(44, 67, 3, 9, 1, 0x11);//Panel morty
    print_dec(score_morty, 7, 68, 45, 0x0F);//Puntaje Inicial

     for (uint32_t i = 0; i < 10; ++i)
    {   
        print_dec(i, 2, 21+(i*4), 43, C_FG_WHITE | C_BG_RED);
        print_dec(i, 2, 21+(i*4), 46, C_FG_WHITE | C_BG_BLUE);
    }
}

void killcurrent_task() {

    sched_task[current_task].is_alive = FALSE;
    sched_task[current_task].distCel  = -1;
    sched_task[current_task].ticks    = -1;
    if (current_task == RICK || current_task == MORTY) {

		if(sched_task[RICK].is_alive == TRUE) {
			print("RICK WINS", 34, 17, 0x0F);
		} else if (sched_task[MORTY].is_alive == TRUE) {
			print("MORTY WINS", 34, 17, 0x0F);
		}

		print("GAME OVER", 35, 15, 0x0F);

    } else {
        tss_t current_tss;
        uint32_t mrms_id;
        if (current_task < 13) {
            mrms_id = current_task-3;
            current_tss = tss_Rickmrms[mrms_id].task_seg;
            tss_Rickmrms[current_task - 3].in_use = FALSE;
        } else {
            mrms_id = current_task - 13;
            current_tss = tss_Mortymrms[current_task - 13].task_seg;
            tss_Mortymrms[mrms_id].in_use = FALSE;
        }
        paddr_t pila_0 = ((current_tss.esp0>>12)<<12);
        vaddr_t virt_task = TASK_CODE_MR_MEESEEKS + 2 * mrms_id * PAGE_SIZE;
        mmu_unmap_page(current_tss.cr3,virt_task);
        mmu_unmap_page(current_tss.cr3,virt_task+PAGE_SIZE);

        int i = 0;
        while (i < 20) {
            if (pilas_0[i] == 0) {

                pilas_0[i] = pila_0;
                i = 20;
            }
            i++;
        }
        reset_screen();
    }
    jump_toIdle();
}

uint32_t check_end_game(){
    // si alguno de los jugadores ya no esta vivo
    if(sched_task[RICK].is_alive == FALSE || sched_task[MORTY].is_alive == FALSE){
        return 1;
    }

    uint32_t assimilated = 0;
    for (int i = 0; i < TOTAL_SEEDS; i++) {
        if (seedsOnMap[i].assimilated == TRUE) {
            assimilated++;
        }
    }
    // si ya no quedan semillas
    if(assimilated == TOTAL_SEEDS){
        return 1;
    }
    // el juego sigue
    return 0; 
}

int next_tss(tss_mrms *tss_str) {
    for (int i = 0; i < 10; ++i) {
        if (tss_str[i].in_use != 1) {
            return i;
        }
    }
    return -1;
}

paddr_t next_esp0() {
    for (int i = 0; i < 20; ++i) {
        if (pilas_0[i] != 0) {
        	paddr_t tmp = pilas_0[i];
        	pilas_0[i] = 0;
            return tmp;
        }
    }
    return 0;
}

bool right_postition(uint32_t pos_x, uint32_t pos_y) {
    if (pos_x < CANT_COLUMNAS && pos_y < CANT_FILAS) {
        return TRUE;
    }
    return FALSE;
}


uint32_t int88(paddr_t code_phy, uint32_t pos_x, uint32_t pos_y) {
    if (current_task == RICK || current_task == MORTY) {
        /*Check if it's a valid position*/
        if (!right_postition(pos_x, pos_y)) {
            jump_toIdle();
            return 0;
        }

        /*if there'is a seed in posx,posy*/
		if (move_assimilated(pos_x,pos_y)){
            
        	int seed_pos = search_megaSeeds(pos_x, pos_y);
        	int index;
            if (current_task == RICK) {
                //verf slot
                index = next_tss(tss_Rickmrms);
                if (index == -1) {
                    jump_toIdle();
                    return 0;
                } else {
                    seedsOnMap[seed_pos].assimilated = TRUE;
                    score_rick = score_rick + 425;
                    reset_screen();
                    jump_toIdle();
                    return 0;
                }
            } else {//morty
                //verf slot
                index = next_tss(tss_Mortymrms);
                if (index == -1) {
                    jump_toIdle();
                    return 0;
                } else {
                    seedsOnMap[seed_pos].assimilated = TRUE;
                    score_morty = score_morty + 425;
                    reset_screen();
                    jump_toIdle();
                    return 0;
                }
            }
        }     

        if (current_task == RICK) {
            //verf slot
            int index = next_tss(tss_Rickmrms);
            if (index == -1) {
                return 0;
            } else {
                uint32_t cr3 = tss_rick.cr3;
                tss_Rickmrms[index].in_use = TRUE;
                vaddr_t virt_task = TASK_CODE_MR_MEESEEKS + 2 * index * PAGE_SIZE;
                paddr_t map_phy =
                        INICIO_DE_PAGINAS_LIBRES_TAREAS + (2 * PAGE_SIZE * pos_x) + (2 * PAGE_SIZE * CANT_COLUMNAS * pos_y);
                task_init_mr_meeseek(&tss_Rickmrms[index].task_seg, cr3, map_phy, virt_task, code_phy, next_esp0());
                sched_task[index + 3].is_alive = TRUE;
                sched_task[index + 3].pos_x = pos_x;
                sched_task[index + 3].pos_y = pos_y;
                sched_task[index + 3].distCel = 7;
                sched_task[index + 3].ticks = 2;

                reset_screen();
                jump_toIdle();
                return virt_task;
            } 

        } else {//morty
            //verif slot
            int index = next_tss(tss_Mortymrms);
            if (index == -1) {
                jump_toIdle();
                return 0;
            } else {
                uint32_t cr3 = tss_morty.cr3;
                tss_Mortymrms[index].in_use = TRUE;
                vaddr_t virt_task = TASK_CODE_MR_MEESEEKS + 2 * index * PAGE_SIZE;
                paddr_t map_phy =
                        INICIO_DE_PAGINAS_LIBRES_TAREAS + (2 * PAGE_SIZE * pos_x) + (2 * PAGE_SIZE * CANT_COLUMNAS * pos_y);
                task_init_mr_meeseek(&tss_Mortymrms[index].task_seg, cr3, map_phy, virt_task, code_phy, next_esp0());
                sched_task[index + 13].is_alive = TRUE;
                sched_task[index + 13].pos_x    = pos_x;
                sched_task[index + 13].pos_y    = pos_y;
                sched_task[index + 13].distCel  = 7;
                sched_task[index + 13].ticks    = 2;

                reset_screen();
                jump_toIdle();
                return virt_task;
            }
        }

    } else {//MrMeeseek

    	//sched_task[current_task].is_alive = FALSE;

        killcurrent_task();
        return 0;
    }
}

void use_portal_gun() {
    /* //rand() % 10;
    */
    breakpoint();
    uint32_t random_task = rand() % 10;        //tarea aleatoria del equipo contrario
    uint32_t position_x = rand() % CANT_COLUMNAS;
    uint32_t position_y = rand() % CANT_FILAS;
    uint32_t current_cr3;
    uint32_t old_cr3;
    vaddr_t virt_task;
    paddr_t new_phy;
    uint32_t attrs = 0x7;
    uint16_t n = 0;


    if(move_assimilated(position_x, position_y)) {

        int seed = search_megaSeeds(position_x, position_y);
        seedsOnMap[seed].assimilated = TRUE;
        
        if(current_task > 2 && current_task < 13) {
            score_rick+=425;
        }else if (current_task > 12 && current_task < 23) {
            score_morty+=425;
        }

        //killcurrent_task();

    } else {

        if (current_task > 2 && current_task < 13) {
            /*Tareas de Rick*/
            //Copiar el código de sched_task[current_task] a la nueva posición
            random_task += 13;

            for (uint16_t i = 13; i < 23; i++) {
                if(sched_task[i].is_alive == false) {
                    n++;
                }
            }

            if(n == 10){
                return;
            }

            while (sched_task[random_task].is_alive == FALSE) {
                random_task = rand() % 10;
                random_task += 13;
            }
            //Entonces sigue viva

            if(sched_task[current_task].uses_of_gun == FALSE) {
                return;
            }
            sched_task[current_task].uses_of_gun = FALSE;

            if(move_assimilated(position_x, position_y)) {
                int seed = search_megaSeeds(position_x, position_y);
                seedsOnMap[seed].assimilated = TRUE;
        
                if(current_task > 2 && current_task < 13) {
                    score_morty+=425;
                }else if (current_task > 12 && current_task < 23) {
                    score_rick+=425;
                }

                kill_task(random_task);
                //Hacer kill de la tarea random
                reset_screen();

                return;
            } 


            sched_task[random_task].pos_x = position_x;
            sched_task[random_task].pos_y = position_y;

            random_task -= 13;

            virt_task =  TASK_CODE_MR_MEESEEKS + random_task * PAGE_SIZE;
            new_phy = INICIO_DE_PAGINAS_LIBRES_TAREAS + (2 * PAGE_SIZE * position_x) + (2 * PAGE_SIZE * CANT_COLUMNAS * position_y);
            current_cr3 = tss_Mortymrms[random_task].task_seg.cr3;
            old_cr3 = rcr3();

            lcr3(current_cr3);

            mmu_map_page(current_cr3, new_phy, new_phy, attrs);
            mmu_map_page(current_cr3, new_phy + PAGE_SIZE, new_phy + PAGE_SIZE, attrs);

            uint32_t *src = (uint32_t *) virt_task;
            uint32_t *dst = (uint32_t *) new_phy;

            for (int i = 0; i < 2048; ++i) {
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
        
            for (uint16_t i = 3; i < 13; i++) {
                if(sched_task[i].is_alive == false) {
                    n++;
                }
            }

            if(n == 10){
                return;
            }

            while (sched_task[random_task].is_alive == FALSE) {
                random_task = rand() % 10;
                random_task += 3;
            }

            if(sched_task[current_task].uses_of_gun == FALSE) {
                return;
            }
            //sched_task[current_task].uses_of_gun = FALSE;

            if(move_assimilated(position_x, position_y)) {
                int seed = search_megaSeeds(position_x, position_y);
                seedsOnMap[seed].assimilated = TRUE;
        
                if(current_task > 2 && current_task < 13) {
                    score_rick+=425;
                }else if (current_task > 12 && current_task < 23) {
                    score_morty+=425;
                }

                kill_task(random_task);
                //Hacer kill de la tarea random

                return;
            } 

            // Sigue viva
            sched_task[random_task].pos_x = position_x;
            sched_task[random_task].pos_y = position_y;
            random_task -= 3;

            virt_task = TASK_CODE_MR_MEESEEKS + random_task * PAGE_SIZE;
            new_phy = INICIO_DE_PAGINAS_LIBRES_TAREAS + (2 * PAGE_SIZE * position_x) + (PAGE_SIZE * CANT_COLUMNAS * position_y);
            current_cr3 = tss_Rickmrms[random_task].task_seg.cr3;
            old_cr3 = rcr3();

            lcr3(current_cr3);

            mmu_map_page(current_cr3, new_phy, new_phy, attrs);
            mmu_map_page(current_cr3, new_phy + PAGE_SIZE, new_phy + PAGE_SIZE, attrs);

            uint32_t *src = (uint32_t *) virt_task;
            uint32_t *dst = (uint32_t *) new_phy;

            for (int i = 0; i < 2048; ++i) {
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
    }

    reset_screen();
}

void kill_task(uint32_t task){
    tss_t current_tss;
    uint32_t mrms_id;
    if (task < 13) {
        mrms_id = task-3;
        current_tss = tss_Rickmrms[mrms_id].task_seg;
        tss_Rickmrms[task - 3].in_use = FALSE;
        sched_task[task].is_alive = FALSE;
    } else {
        mrms_id = task - 13;
        current_tss = tss_Mortymrms[task - 13].task_seg;
        tss_Mortymrms[mrms_id].in_use = FALSE;
        sched_task[task].is_alive = FALSE;
    }
    paddr_t pila_0 = ((current_tss.esp0>>12)<<12);
    vaddr_t virt_task = TASK_CODE_MR_MEESEEKS + 2 * mrms_id * PAGE_SIZE;
    mmu_unmap_page(current_tss.cr3,virt_task);
    mmu_unmap_page(current_tss.cr3,virt_task+PAGE_SIZE);

    int i = 0;
    while (i < 20) {
        if (pilas_0[i] == 0) {
            pilas_0[i] = pila_0;
            i = 20;
        }
        i++;
    }
    reset_screen();
}


uint32_t int123_move(int desp_x, int desp_y) {
    
    if (current_task == RICK || current_task == MORTY) {
        killcurrent_task();
    }
    uint32_t max_move_allowed = (uint32_t)sched_task[current_task].distCel;
    if (distMan(desp_x, desp_y) > max_move_allowed){
        jump_toIdle();
    	return 0;
    }
    uint32_t curr_posx = sched_task[current_task].pos_x;
    uint32_t curr_posy = sched_task[current_task].pos_y;
    uint32_t newpos_x = modulo(curr_posx + desp_x, CANT_COLUMNAS);
    uint32_t newpos_y = modulo(curr_posy + desp_y, CANT_FILAS);

    if (move_assimilated(newpos_x, newpos_y)) {

        if(current_task > 2 && current_task < 13) {
            score_rick+=425;
        }else if (current_task > 12 && current_task < 23) {
            score_morty+=425;
        }

        //assimilated seed, kill current task and save the kernel stack
        int index = search_megaSeeds(newpos_x, newpos_y);
        seedsOnMap[index].assimilated = TRUE;
        killcurrent_task();
        return 0;
    } else {

        int index;
        vaddr_t virt_task;
        tss_t current_tss;
        if (current_task < 13) {
            index = current_task - 3;
            current_tss = tss_Rickmrms[index].task_seg;
            virt_task = TASK_CODE_MR_MEESEEKS + index *2* PAGE_SIZE;
        } else {
            index = current_task - 13;
            current_tss = tss_Mortymrms[index].task_seg;
            virt_task = TASK_CODE_MR_MEESEEKS + index* 2* PAGE_SIZE;//<--
        }        
        paddr_t new_phy = INICIO_DE_PAGINAS_LIBRES_TAREAS + (2 * PAGE_SIZE * newpos_x) + (2 * PAGE_SIZE * CANT_COLUMNAS * newpos_y);
        uint32_t attrS = 0x00000007;

        //temporal mapping wiht identity mapping
        uint32_t current_cr3 = rcr3();
        mmu_map_page(current_cr3, new_phy, new_phy, attrS); //4kb
        mmu_map_page(current_cr3, new_phy + PAGE_SIZE, new_phy + PAGE_SIZE, attrS); //4kb

        //code copy from the virtual address
        uint32_t *src = (uint32_t *) virt_task;
        uint32_t *dst = (uint32_t *) new_phy;
        for (int i = 0; i < 2048; ++i) {
            dst[i] = src[i];
        }

        //unmapping temporal
        mmu_unmap_page(current_cr3, new_phy);
        mmu_unmap_page(current_cr3, new_phy + PAGE_SIZE);

        //unmapping old virtual address
        current_cr3 = current_tss.cr3;//current task cr3
        mmu_unmap_page(current_cr3, virt_task);
        mmu_unmap_page(current_cr3, virt_task + PAGE_SIZE);

        //mapping new physical address
        mmu_map_page(current_cr3, virt_task, new_phy, attrS);
        mmu_map_page(current_cr3, virt_task + PAGE_SIZE, new_phy + PAGE_SIZE, attrS);

        //reset positicion
        sched_task[current_task].pos_x = newpos_x;
        sched_task[current_task].pos_y = newpos_y;

        reset_screen();
        jump_toIdle();
        return 1;
    }
}

void int100_look(int32_t *position_x, int32_t *position_y) {

    if (current_task == RICK || current_task == MORTY) {
        *position_x = -1;
        *position_y = -1;
        jump_toIdle();
    } else if (current_task > MORTY) {

        uint32_t tmp_x = abs(sched_task[current_task].pos_x - seedsOnMap[0].position_x);
        uint32_t tmp_y = abs(sched_task[current_task].pos_y - seedsOnMap[0].position_y);

        uint32_t steps = tmp_x + tmp_y;
        uint32_t mostNearSeed = 0;


        for (uint32_t i = 1; i < TOTAL_SEEDS; i++) {
            if(seedsOnMap[i].assimilated == FALSE) {
                tmp_x = abs(sched_task[current_task].pos_x - seedsOnMap[i].position_x);
                tmp_y = abs(sched_task[current_task].pos_y - seedsOnMap[i].position_y);
                
                if (steps > (tmp_x + tmp_y)) {
                    steps = tmp_x + tmp_y;
                    mostNearSeed = i;
                }
            }
        }
            
        *position_x = seedsOnMap[mostNearSeed].position_x - seedsOnMap[current_task].position_x;
        *position_y = seedsOnMap[mostNearSeed].position_y - seedsOnMap[current_task].position_y;

        print("$", seedsOnMap[mostNearSeed].position_x, seedsOnMap[mostNearSeed].position_y, C_FG_WHITE | C_BG_GREEN);
        jump_toIdle();
    }

}


void reset_screen() {
	//screeen init
    screen_draw_box(0, 0, CANT_FILAS, CANT_COLUMNAS, 1, 0x55);
    //Set scores

    print_dec(score_rick, 7, 5, 45, 0x0F);
    print_dec(score_morty, 7, 68, 45, 0x0F);
    //restore seeds
    uint32_t assimilated = 0;

    for (int i = 0; i < TOTAL_SEEDS; ++i) {
        if (seedsOnMap[i].assimilated == FALSE) {
            print("$", seedsOnMap[i].position_x, seedsOnMap[i].position_y, C_FG_WHITE | C_BG_BLACK);
        }else {
            assimilated++;
            print("R", seedsOnMap[i].position_x, seedsOnMap[i].position_y, 0x55);
        }
    }
    if(assimilated == TOTAL_SEEDS) {
        print("GAME OVER", 35, 15, 0x0F);

        if(score_rick > score_morty) {
			print("RICK WINS", 34, 17, 0x0F);
        } else if (score_morty > score_rick) {
            print("MORTY WINS", 34, 17, 0x0F);
        } else {
            print("TIE", 34, 17, 0x0F);
        }

        jump_toIdle();
    }

    //restore Mr Meeseeks RICK
    for (int i = 3; i < 13; ++i) {
        if (sched_task[i].is_alive == TRUE) {            
            print("R", sched_task[i].pos_x, sched_task[i].pos_y, C_FG_WHITE | C_BG_RED);
        }

    }
    //restore Mr Meeseeks MORTY
    for (int i = 13; i < 23; ++i) {

        if (sched_task[i].is_alive == TRUE) {
            print("M", sched_task[i].pos_x, sched_task[i].pos_y, C_FG_WHITE | C_BG_BLUE);
        }
    }
}


void spread_megaSeeds() {

    megaSeeds tmp;

    for (uint32_t i = 0; i < TOTAL_SEEDS; i++) {
        tmp.position_x = rand() % CANT_COLUMNAS;
        tmp.position_y = rand() % CANT_FILAS;
        seedsOnMap[i] = tmp;
        seedsOnMap[i].assimilated = FALSE;

        print("$", tmp.position_x, tmp.position_y, C_FG_WHITE | C_BG_BLACK);
    }

}

bool move_assimilated(uint32_t pos_x, uint32_t pos_y) {
    for (int i = 0; i < TOTAL_SEEDS; ++i) {

        if (seedsOnMap[i].assimilated == FALSE) {
            if (seedsOnMap[i].position_x == pos_x && seedsOnMap[i].position_y == pos_y) {
                return TRUE;
            }
        }
    }
    return FALSE;

}


int search_megaSeeds(uint32_t pos_x, uint32_t pos_y) {

    for (int i = 0; i < TOTAL_SEEDS; i++) {
        if (seedsOnMap[i].position_x == pos_x && seedsOnMap[i].position_y == pos_y) {
            return i;
        }
    }
    return -1;

}

uint32_t distMan(int desp_x, int desp_y) {
    return abs(desp_x) + abs(desp_y);
}

//funciones auxiliares

void imprimir_registros(uint32_t eip, uint32_t eflags,uint16_t ss,uint16_t gs,uint16_t fs,uint16_t es,uint16_t ds,
                        uint16_t cs, uint32_t stack1,uint32_t stack2,uint32_t stack3,uint32_t bcktrace1,
                        uint32_t bcktrace2,uint32_t bcktrace3,uint32_t bcktrace4, uint32_t edi,uint32_t esi,uint32_t ebp,uint32_t esp,uint32_t ebx,uint32_t edx,
                        uint32_t ecx, uint32_t eax,uint32_t err){

    screen_draw_box(0,24,40,1,1,0x00); //pinto linea izquierda
    screen_draw_box(0,53,40,1,1,0x00); //pinto linea derecha
    screen_draw_box(0,24,1,29,1,0x00); //pinto linea horizontal superior
    screen_draw_box(3,24,1,29,1,0x00); //pinto linea horizontal intermedia
    screen_draw_box(5,24,1,29,1,0x00); //pinto linea horizontal inferior
    screen_draw_box(1,25,2,28,1,0x44); //pinto linea roja intermedia
    screen_draw_box(4,25,1,28,0,0x10); //pinto linea azul intermedia
    screen_draw_box(6,25,34,28,0,0x70); //pinto fondo gris intermedia

    print("Tarea ",26,4,C_BG_BLUE | C_FG_WHITE);
    if(current_task == RICK){
        print("RICK",32,4,C_BG_BLUE | C_FG_WHITE);
    }else{
        if(current_task == MORTY){
          print("MORTY",32,4,C_BG_BLUE | C_FG_WHITE);  
        }else{
            uint32_t tarea;
            if(current_task < 13){
                tarea = current_task - 3;
                print("Meeseek    (RICK)",32,4,C_BG_BLUE | C_FG_WHITE);  
                print_dec(tarea,2,40,4,C_BG_BLUE | C_FG_WHITE);
            }else{
                tarea = current_task - 13;
                print("Meeseek    (MORTY)",32,4,C_BG_BLUE | C_FG_WHITE);  
                print_dec(tarea,2,40,4,C_BG_BLUE | C_FG_WHITE);
            }
        }
    }

    print("eax",26,7,0x7F);
    print_hex(eax,8,30,7,0x70);
    print("ebx",26,9,0x7F);
    print_hex(ebx,8,30,9,0x70);
    print("ecx",26,11,0x7F);
    print_hex(ecx,8,30,11,0x70);
    print("edx",26,13,0x7F);
    print_hex(edx,8,30,13,0x70);
    print("esi",26,15,0x7F);
    print_hex(esi,8,30,15,0x70);
    print("edi",26,17,0x7F);
    print_hex(edi,8,30,17,0x70);
    print("ebp",26,19,0x7F);
    print_hex(ebp,8,30,19,0x70);
    print("esp",26,21,0x7F);
    print_hex(esp,8,30,21,0x70);
    print("eip",26,23,0x7F);
    print_hex(eip,8,30,23,0x70);
    print("cs",27,25,0x7F);
    print_hex(cs,4,30,25,0x70);
    print("ds",27,27,0x7F);
    print_hex(ds,4,30,27,0x70);
    print("es",27,29,0x7F);
    print_hex(es,4,30,29,0x70);
    print("fs",27,31,0x7F);
    print_hex(fs,4,30,31,0x70);
    print("gs",27,33,0x7F);
    print_hex(gs,4,30,33,0x70);
    print("ss",27,35,0x7F);
    print_hex(ss,4,30,35,0x70);
    print("eflags",26,37,0x7F);
    print_hex(eflags,8,33,37,0x70);
    uint32_t cr0 = rcr0();
    print("cr0",40,8,0x7F);
    print_hex(cr0,8,44,8,0x70);
    uint32_t cr2 = rcr2();
    print("cr2",40,10,0x7F);
    print_hex(cr2,8,44,10,0x70);
    uint32_t cr3 = rcr3();
    print("cr3",40,12,0x7F);
    print_hex(cr3,8,44,12,0x70);
    uint32_t cr4 = rcr4();
    print("cr4",40,14,0x7F);
    print_hex(cr4,8,44,14,0x70);
    print("err",40,16,0x7F);
    print_hex(err,8,44,16,0x70);
    print("Stack",40,20,0x7F);
    print_hex(stack1,8,40,21,0x70);
    print_hex(stack2,8,40,22,0x70);
    print_hex(stack3,8,40,23,0x70);
    print("Backtrace",40,27,0x7F);
    print_hex(bcktrace1,8,40,28,0x70);
    print_hex(bcktrace2,8,40,29,0x70);
    print_hex(bcktrace3,8,40,30,0x70);
    print_hex(bcktrace4,8,40,31,0x70);

}

void set_screen_debug(){
    screen_debug = 1;
}

void set_modo_debug() {
    if (act_debug == 1) { // a la expera de una excepcion
        if(screen_debug == 1){ // ya hubo excepcion
            screen_debug = 0;
            reset_screen();
        }else{              // no hubo excepcion
            act_debug = 0;
            print("Debug Mode active",10,40,0x00);
        }
    }else{      // activar debug mode
        act_debug = 1;
        print("Debug Mode active",10,40,0x0F);
    }
}


uint32_t check_screen_debug() {
    return screen_debug;
}

uint32_t check_act_debug() {
    return act_debug;
}

uint32_t virtual_valida(uint32_t number){
  if (number % 4 == 0){
    // si es Rick o Morty
    if ( (number >= 0x1D00000) & (number < 0x1D04000) ){
      return 1;
    }
    // si es Messeek
    uint32_t begin_page = 2000 * (current_task-3); 
    uint32_t end_page = 2000 * (current_task-2); 
    if ( (number >= 0x08000000 + begin_page) & (number < 0x08000000 + end_page) ){
      return 1;
    }
  }
  return 0;
}

void imprimir_libretas() {
    print("Integrante 1: 218/16", 10, 10, C_BG_RED | C_FG_WHITE);
    print("Integrante 2: 258/16", 10, 12, C_BG_RED | C_FG_WHITE);
    print("Integrante 3: 951/12", 10, 14, C_BG_RED | C_FG_WHITE);
}

void cambiar_fondo() {
    print(" ", 0, 0, C_BG_RED | C_FG_WHITE);
}

int abs(int number) {
    if (number < 0)
        return -number;
    else
        return number;

}

int modulo(int numero, int base) {
    if (numero > 0) {
        return numero % base;
    } else {
        return (numero + base) % base;
    }
}

void reset_MrMsCel() {
    for (int i = 3; i < 23; ++i) {
        if (sched_task[i].distCel == 1) {
            sched_task[i].ticks = -1;
        }else{
        	if (sched_task[i].ticks == 0) {
        	    sched_task[i].ticks = 2;
        	    sched_task[i].distCel--;
        	}else{

        		if (sched_task[i].ticks > 0) {
        		    sched_task[i].ticks--;
        		}
        	}
        }
    }
}