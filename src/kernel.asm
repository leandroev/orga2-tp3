; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "print.mac"
;; DEFINE

;; EXTERN
extern GDT_DESC

;; GLOBAL

global start


BITS 16
;; Saltear seccion de datos
jmp start

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
start_rm_msg db     'Iniciando kernel en Modo Real'
start_rm_len equ    $ - start_rm_msg

start_pm_msg db     'Iniciando kernel en Modo Protegido'
start_pm_len equ    $ - start_pm_msg

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

;; Punto de entrada del kernel.
BITS 16
start:
    ; Deshabilitar interrupciones
    cli

    ; Cambiar modo de video a 80 X 50
    mov ax, 0003h
    int 10h ; set mode 03h
    xor bx, bx
    mov ax, 1112h
    int 10h ; load 8x8 font

    ; Imprimir mensaje de bienvenida
    print_text_rm start_rm_msg, start_rm_len, 0x07, 0, 0


    ; Habilitar A20
    call A20_check
    call A20_enable
    xchg bx, bx
    ; Cargar la GDT
    lgdt [GDT_DESC]

    ; Setear el bit PE del registro CR0
    mov eax, CR0
    or eax, 1
    mov cr0, eax
    
    ; Saltar a modo protegido
    jmp (10 << 3) : modo_protegido

BITS 32
modo_protegido:
    ; Establecer selectores de segmentos
    xor eax, eax
    mov ax, (11 << 3)                   ; selector de segmento de datos de nivel 0
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov gs, ax
    mov fs, ax

    ; Establecer la base de la pila
    mov ebp, 0x25000
    mov esp, 0x25000

    ; Imprimir mensaje de bienvenida

    ; Inicializar pantalla
    
    ; Inicializar el manejador de memoria
 
    ; Inicializar el directorio de paginas
    
    ; Cargar directorio de paginas

    ; Habilitar paginacion
    
    ; Inicializar tss

    ; Inicializar tss de la tarea Idle

    ; Inicializar el scheduler

    ; Inicializar la IDT
    
    ; Cargar IDT
 
    ; Configurar controlador de interrupciones

    ; Cargar tarea inicial

    ; Habilitar interrupciones

    ; Saltar a la primera tarea: Idle

    ; Ciclar infinitamente (por si algo sale mal...)
    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"