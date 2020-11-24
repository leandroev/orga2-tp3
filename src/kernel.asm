; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "print.mac"

;; DEFINE
%define TSS_INITAIL     15
%define TSS_IDLE        16

;; GLOBAL
global start

;; EXTERN
extern GDT_DESC
extern IDT_DESC
extern idt_init
extern pic_reset
extern pic_enable
extern mmu_init
extern mmu_init_kernel_dir
extern imprimir_libretas
extern mmu_init_task_dir
extern cambiar_fond
extern tss_init
extern tss_init_gdt
extern tss_init_idle
extern sched_init
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
    
    ; Cargar la GDT
    LGDT [GDT_DESC]

    ; Setear el bit PE del registro CR0
    MOV eax,cr0
	OR eax,1
	MOV cr0,eax
    
    ; Saltar a modo protegido
    jmp (10<<3):modoprotegido

BITS 32
	modoprotegido:
        
    ; Establecer selectores de segmentos
    
    mov ax, (11<<3)
    mov es, ax
    mov ds, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Establecer la base de la pila
    mov esp, 0x25000
    mov ebp, 0x25000
    
    ; Imprimir mensaje de bienvenida

    ; Inicializar pantalla

    ; Inicializar el manejador de memoria
    call mmu_init
    ; Inicializar el directorio de paginas
    call mmu_init_kernel_dir
    ; Cargar directorio de paginas
    mov cr3, eax
    ; Habilitar paginacion
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax

    ;;Prueba Impresion de libretas
    ;call imprimir_libretas
    
    ; Inicializamos los descriptores de la tss
    call tss_init_gdt
    
    ; Inicializar tss
    call tss_init
    
    ; Inicializar tss de la tarea Idle
    call tss_init_idle

    ; Inicializar el scheduler
    call sched_init
    ; Inicializar la IDT
    call idt_init
    ; Cargar IDT
    lidt [IDT_DESC]

    ;;---Prueba idt
    ; mov eax,0
    ; div eax
    
    ; Configurar controlador de interrupciones
    call pic_reset
    call pic_enable

    ; Cargar tarea inicial
    mov ax, (TSS_INITAIL << 3)
    ltr ax

    ; Habilitar interrupciones
    sti
    
    ; Saltar a la primera tarea: Idle
    jmp (TSS_IDLE << 3):0
    
    ; Ciclar infinitamente (por si algo sale mal...)
    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"