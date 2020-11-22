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

extern set_modo_debug

extern check_screen_debug

extern check_act_debug
;--int 100 look
extern int100_look

;--int 88
extern int88

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
    sub esp, 5*4

    push edx
    push eax
    push es
    
    ;xchg bx, bx
    
    ;obtenemos SS3
    mov eax, [esp+4*12]
    mov es, ax
    ;obtenemos ESP3
    mov eax, [esp+4*11]

    ;no se por que esto funciona
    add eax, 8

    ;buscamos los 5 elementos del stack de nivel 3
    mov edx, [es:eax]
    mov [esp+4*7], edx
    add eax, 4
    
    mov edx, [es:eax] 
    mov [esp+4*6], edx
    add eax, 4

    mov edx, [es:eax] 
    mov [esp+4*5], edx
    add eax, 4

    mov edx, [es:eax] 
    mov [esp+4*4], edx
    add eax, 4

    mov edx, [es:eax] 
    mov [esp+4*3], edx

    pop es
    pop eax
    pop edx

    pushad
    ;colocamos los valores de la tarea en la pila
    ;xchg bx, bx
    mov eax, [esp+4*16] ;ESP3
    mov [esp+4*3], eax

    ;push cs
    mov eax, [esp+4*14] ; CS3
    push eax

    push ds
    push es
    push fs
    push gs

    ;push ss
    mov eax, [esp+4*22] ; SS3
    push eax

    ;pushfd
    mov eax, [esp+4*21] ;EFLAGS
    push eax

    mov eax, [esp+4*20]
    push eax
    pushad
    call imprimir_registros
    mov eax, %1
    push eax
    call rutina_de_interrupciones
    add esp, 4
    call killcurrent_task
    popad
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
    call next_clock ; Imprimir el reloj del sistema
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
    call check_screen_debug
    cmp eax, 1
    jne .seguir
    ;Imprimir registros
    call imprimir_registros
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
    mov eax, 0x59
    mov bx, (TSS_IDLE << 3)
    str cx
    cmp bx, cx
    jz .fin
    call jump_toIdle
    
    .fin:
    iret

_isr100: ; y = esp - 1, x = esp
    xchg bx, bx
    mov eax, 0x64
    mov bx, (TSS_IDLE << 3)
    str cx
    cmp bx, cx
    jz .fin
    call jump_toIdle
    ; pushad
    ; mov eax, x 
    ; push eax
    ; mov ebx, y
    ; push ebx
    ; call int100_look
    ; add esp, 8
    ; popad
    ; mov eax, [x]
    ; mov ebx, [y]
    .fin:
    iret

_isr123:
    mov eax, 0x7B
    mov bx, (TSS_IDLE << 3)
    str cx
    cmp bx, cx
    call jump_toIdle
    
    .fin:
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