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
x:             dd 0x0
y:             dd 0x0 

;;Seccion de codigo


;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;
%macro ISR 1
global _isr%1

_isr%1:
    push eax
    mov eax, %1
    cmp eax, 8
    jb .sin_cod_error
    je .con_cod_error
    cmp eax, 17
    ja .sin_cod_error
    je .con_cod_error
    cmp eax, 9
    je .sin_cod_error
    cmp eax, 15
    jb .con_cod_error
    jae .sin_cod_error

.con_cod_error:
    pop eax
    jmp .push_parametros

.sin_cod_error:
    pop eax
    push 0      ; cod error ficticio 0
    jmp .push_parametros

.push_parametros:
    sub esp, 4*4
    ;push backtrace
    push eax
    push ecx
    push edx
    mov edx, ebp
    mov ecx, 3

.loop1:
    push edx
    call virtual_valida
    pop edx
    cmp eax, 1
    mov eax, 0  ; si es invalida pongo 0
    cmove eax, [edx+4]
    mov [esp+ecx*4], eax
    mov edx, [edx] ; viejo rbp
    inc ecx
    cmp ecx,7
    jne .loop1

    pop edx
    pop ecx
    pop eax

    ; reservo espacio para el stack
    sub esp, 3*4
    push eax
    push ecx
    push edx

    mov edx, [esp+4*14]; esp3
    mov ecx, 3

.loop2:
    push edx
    call virtual_valida
    pop edx
    cmp eax, 1
    mov eax, 0 ; si es invalida pongo 0
    cmove eax, [edx] ; [esp3]
    mov [esp+4*ecx], eax 
    add edx, 4 ; esp3 +4
    inc ecx
    cmp ecx, 6
    jne .loop2
    
    pop edx
    pop ecx
    pop eax

    ;push registros de proposito general
    pushad
    
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

    mov eax, [esp+4*25] ;ESP3
    mov [esp+4*9], eax

    mov eax, [esp+4*24] ;EFLAGS
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
    add esp, 4

.not_debug_mode:
    add esp, 8*4
    call killcurrent_task
    popad ; reestablezco registros de prop gral
    add esp, 8*4    ; eip <- esp0
    iret
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
    call next_clock ; prit el reloj del sistema
    call reset_MrMsCel; set MrMs ticks
    call sched_next_task
    str cx
    cmp ax, cx
    je .fin
    mov [sched_task_selector],ax
    jmp far [sched_task_offset]
    
    .fin:
    ;call reset_screen
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
    jmp 0X0080:0

 




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
    popad
    iret

_isr89:
    pushad
    call use_portal_gun
    popad
    iret

_isr100: ; y = esp - 1, x = esp
    pushad
    mov eax, x 
    push eax
    mov ebx, y
    push ebx
    call int100_look
    add esp, 8
    popad
    mov eax, [x]
    mov ebx, [y]
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