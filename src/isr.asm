; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
;
; Definicion de rutinas de atencion de interrupciones

%include "print.mac"

    ;;EXTERN
;--Rutina de interrupciones
extern rutina_de_interrupciones
;--PIC
extern pic_finish1
;--Sched
extern sched_next_task
;--check_end_game
extern check_end_game
;--killcurrent task
extern killcurrent_task
;--imprimir registros
extern imprimir_registros
;--int 100 look
extern int100_look
;--int 88
extern int88
;--int 89
extern use_portal_gun
;--int 123
extern int123_move

extern reset_screen

extern chequeo_error_code
extern virtual_valida
extern set_screen_debug
extern check_act_debug
extern set_modo_debug
extern check_screen_debug
extern reset_MrMsCel
;;GLOBAL
global _isr32
global _isr33
global _isr88
global _isr89
global _isr100
global _isr123
global jump_toIdle
BITS 32
;; Seccion de datos
sched_task_offset:      dd 0xFFFFFFFF
sched_task_selector:    dw 0xFFFF

;; memory
desp_x:             dd 0x0
desp_y:             dd 0x0 

;;Seccion de codigo


;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;
%macro ISR 1
global _isr%1

_isr%1:
    pushad  ; push registros prop. genereal
    mov eax, %1
    push eax
    call chequeo_error_code
    cmp eax, 1
    jne .sin_cod_error
    je .con_cod_error

.con_cod_error:
    add esp, 4
    jmp .push_parametros

.sin_cod_error:
    add esp, 4
    popad   ; pop registros prop. genereal
    push 0      ; cod error ficticio (0)
    pushad  ; push registros prop. genereal
    jmp .push_parametros

.push_parametros:
    sub esp, 4*4    ; 4 espacios para el backtrace
    mov edx, [esp+4*6]
    mov ecx, 0

.loop1:
    push ecx
    add edx, 4 ; retorno <- edx = ebp + 4
    push edx
    call virtual_valida
    pop edx
    pop ecx
    cmp eax, 1
    je .valida
.no_valida:
    cmp ecx,4
    je .fin_loop1
    mov DWORD [esp+ecx*4], 0
    inc ecx
    jmp .no_valida

.valida:    
    mov eax, [edx]
    mov [esp+ecx*4], eax
    inc ecx
    push ecx
    sub edx, 4 ; edx = ebp
    push edx
    call virtual_valida
    pop edx
    pop ecx
    cmp eax, 1
    jne .no_valida
    mov edx, [edx] ; viejo rbp
    cmp ecx,4
    jne .loop1

.fin_loop1:
    ; reservo 3 espacio para el stack
    sub esp, 3*4
    mov edx, [esp+4*19]; esp3
    mov ecx, 0

.loop2:
    push ecx
    push edx
    call virtual_valida
    pop edx
    pop ecx
    cmp eax, 1
    je .valida2

.no_valida2:
    mov DWORD [esp+4*ecx], 0
    inc ecx
    cmp ecx, 3
    je .fin_loop2
    jmp .no_valida2

.valida2:
    mov eax, [edx] ; [esp3]
    mov [esp+4*ecx], eax 
    add edx, 4 ; esp3 +4
    inc ecx
    cmp ecx, 3
    jne .loop2

.fin_loop2:    
    ;colocamos los valores de la tarea en la pila
    mov eax, [esp+4*17] ; CS3
    push eax

    ; push segmentos
    push ds
    push es
    push fs
    push gs
    
    ;push ss
    mov eax, [esp+4*25] ; SS3
    push eax

    mov eax, [esp+4*25] ; ESP3
    mov [esp+4*16], eax

    mov eax, [esp+4*24] ; EFLAGS
    push eax

    mov eax, [esp+4*23] ; eip
    push eax

    ; modo debug
    call check_act_debug
    cmp eax, 1
    jne .not_debug_mode
    call set_screen_debug
    call imprimir_registros
    mov eax, %1
    push eax
    call rutina_de_interrupciones
    .check_screen:
        call jump_toIdle
        call check_screen_debug
        cmp eax, 1
        je .check_screen

.not_debug_mode:
    call killcurrent_task ; matar tarea y saltar a la idle

%endmacro

;; Rutina de atención de las EXCEPCIONES
;; -------------------------------------------------------------------------- ;;
ISR 0
ISR 1
ISR 2
ISR 3
ISR 4
ISR 5
ISR 6
ISR 7
ISR 8
ISR 9
ISR 10
ISR 11
ISR 12
ISR 13
ISR 14
ISR 15
ISR 16
ISR 17
ISR 18
ISR 19

;; Rutina de atención del RELOJ
_isr32:
    pushad
    call pic_finish1 ; Indica que la interrupcion fue antendida
    call next_clock ; print el reloj del sistema
    call check_screen_debug ; chequeo pantalla debug 
    cmp eax, 1
    je .fin   
    call check_end_game ; chequeo juego finalizado
    cmp eax, 1
    je .fin    
    call reset_MrMsCel; set MrMs ticks
    call sched_next_task
    str cx
    cmp ax, cx
    je .fin
    mov [sched_task_selector],ax
    jmp far [sched_task_offset]
    
    .fin:
    popad
    iret
;; -------------------------------------------------------------------------- ;;
;; Rutina de atención del TECLADO
_isr33:
    pushad
    in al, 0x60 ; Captura una tecla
    cmp al, 0x15 ; verifico si toque la y
    jne .seguir
    ;activo modo debug
    call set_modo_debug
    .seguir:
    push eax
    call printScanCode ;Rutina para Imprimir el ScanCode
    add esp,4
    call pic_finish1
    popad
    iret

;;------------------------------------------------------------------------------;;
n_0 db     '0'
n0_len equ    $ - n_0

n_1 db     '1'
n1_len equ    $ - n_1

n_2 db     '2'
n2_len equ    $ - n_2

n_3 db     '3'
n3_len equ    $ - n_3

n_4 db     '4'
n4_len equ    $ - n_4

n_5 db     '5'
n5_len equ    $ - n_5

n_6 db     '6'
n6_len equ    $ - n_6

n_7 db     '7'
n7_len equ    $ - n_7

n_8 db     '8'
n8_len equ    $ - n_8

n_9 db     '9'
n9_len equ    $ - n_9


printScanCode:
    pushad
    mov eax, [esp + 36]
    cmp al, 0X0B
    je .print_0

    cmp al, 0X02
    je .print_1

    cmp al, 0X03
    je .print_2
    
    cmp al, 0X04
    je .print_3

    cmp al, 0X05
    je .print_4

    cmp al, 0X06
    je .print_5

    cmp al, 0X07
    je .print_6

    cmp al, 0X08
    je .print_7

    cmp al,0X09
    je .print_8

    cmp al, 0X0A
    je .print_9
    jmp .fin

    .print_0:
    print_text_pm n_0,n0_len,0x0F, 0, 79
    jmp .fin

    .print_1:
    print_text_pm n_1,n1_len,0x0F, 0, 79
    jmp .fin

    .print_2:
    print_text_pm n_2,n2_len,0x0F, 0, 79
    jmp .fin

    .print_3:
    print_text_pm n_3,n3_len,0x0F, 0, 79
    jmp .fin
    
    .print_4:
    print_text_pm n_4,n4_len,0x0F, 0, 79
    jmp .fin
    
    .print_5:
    print_text_pm n_5,n5_len,0x0F, 0, 79
    jmp .fin
    
    .print_6:
    print_text_pm n_6,n6_len,0x0F, 0, 79
    jmp .fin

    .print_7:
    print_text_pm n_7,n7_len,0x0F, 0, 79
    jmp .fin

    .print_8:
    print_text_pm n_8,n8_len,0x0F, 0, 79
    jmp .fin

    .print_9:
    print_text_pm n_9,n9_len,0x0F, 0, 79

    .fin:
    popad
    ret


;; Rutina de salto a la tarea idle
;;-----------------------------------------------------------------------------;;
jump_toIdle:
    pushad
    mov ax, 0x0080
    str cx
    cmp ax, cx
    je .fin
    jmp 0X0080:0
    .fin:
    popad 
    ret

 




;; -------------------------------------------------------------------------- ;;
;; Rutinas de atención de las SYSCALLS
%define TSS_IDLE        16

_isr88:
    pushad
    push ecx
    push ebx
    push eax
    call int88
    add esp, 12
    mov [esp+4*7], eax
    popad
    iret

_isr89:
    pushad
    call use_portal_gun
    popad
    iret

_isr100: ; y = esp - 1, x = esp
    pushad
    mov ebx, desp_y
    push ebx
    mov eax, desp_x
    push eax
    call int100_look
    add esp, 8
    popad
    mov ebx, [desp_y]
    mov eax, [desp_x]
    iret

_isr123:
    sub esp, 4
    pushad
    push ebx
    push eax
    call int123_move
    mov [esp+10*4],eax
    add esp, 8
    popad
    pop eax
    iret

;; -------------------------------------------------------------------------- ;;
;; Funciones Auxiliares
;; -------------------------------------------------------------------------- ;;
isrNumber:           dd 0x00000000
isrClock:            db '|/-\'
next_clock:
        pushad
        inc DWORD [isrNumber]
        mov ebx, [isrNumber]
        cmp ebx, 0x4
        jl .ok
                mov DWORD [isrNumber], 0x0
                mov ebx, 0
        .ok:
                add ebx, isrClock
                print_text_pm ebx, 1, 0x0f, 49, 79
                popad
        ret

isrNumber1:           dd 0x00000000
isrClock1:            db '|/-\'
isrNumber2:           dd 0x00000000
isrClock2:            db '|/-\'
isrNumber3:           dd 0x00000000
isrClock3:            db '|/-\'
isrNumber4:           dd 0x00000000
isrClock4:            db '|/-\'
isrNumber5:           dd 0x00000000
isrClock5:            db '|/-\'
isrNumber6:           dd 0x00000000
isrClock6:            db '|/-\'
isrNumber7:           dd 0x00000000
isrClock7:            db '|/-\'
isrNumber8:           dd 0x00000000
isrClock8:            db '|/-\'
isrNumber9:           dd 0x00000000
isrClock9:            db '|/-\'
isrNumber10:           dd 0x00000000
isrClock10:            db '|/-\'
isrNumber11:           dd 0x00000000
isrClock11:            db '|/-\'
isrNumber12:           dd 0x00000000
isrClock12:            db '|/-\'
isrNumber13:           dd 0x00000000
isrClock13:            db '|/-\'
isrNumber14:           dd 0x00000000
isrClock14:            db '|/-\'
isrNumber15:           dd 0x00000000
isrClock15:            db '|/-\'
isrNumber16:           dd 0x00000000
isrClock16:            db '|/-\'
isrNumber17:           dd 0x00000000
isrClock17:            db '|/-\'
isrNumber18:           dd 0x00000000
isrClock18:            db '|/-\'
isrNumber19:           dd 0x00000000
isrClock19:            db '|/-\'
isrNumber20:           dd 0x00000000
isrClock20:            db '|/-\'
isrNumber21:           dd 0x00000000
isrClock21:            db '|/-\'
isrNumber22:           dd 0x00000000
isrClock22:            db '|/-\'



%macro next_clock 3
global next_clock%3 ; macro para imprimir la rutina de interrupcion de reloj en diferentes posiciones del mapa

next_clock%3:
        mov edi, [esp + 4]
        mov esi, [esp + 8]
        pushad
        inc DWORD [isrNumber%3]
        mov ebx, [isrNumber%3]
        cmp ebx, 0x4
        jl .ok
                mov DWORD [isrNumber%3], 0x0
                mov ebx, 0
        .ok:
                add ebx, isrClock%3
                print_text_pm ebx, 1, 0x0f, edi, esi 
                popad
        ret
%endmacro

next_clock 40, 40, 1
next_clock 40, 40, 2
next_clock 40, 40, 3
next_clock 40, 40, 4
next_clock 40, 40, 5
next_clock 40, 40, 6
next_clock 40, 40, 7
next_clock 40, 40, 8
next_clock 40, 40, 9
next_clock 40, 40, 10
next_clock 40, 40, 11
next_clock 40, 40, 12
next_clock 40, 40, 13
next_clock 40, 40, 14
next_clock 40, 40, 15
next_clock 40, 40, 16
next_clock 40, 40, 17
next_clock 40, 40, 18
next_clock 40, 40, 19
next_clock 40, 40, 20
next_clock 40, 40, 21
next_clock 40, 40, 22
