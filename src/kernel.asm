; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "imprimir.mac"
extern black_out_screen
extern GDT_DESC
extern idt_inicializar
extern IDT_DESC
extern resetear_pic
extern habilitar_pic
extern mmu_inicializar
extern mmu_inicializar_dir_kernel
extern mmu_inicializar_dir_tarea
extern kernel_page_directory
extern tss_inicializar
extern tss_inicializar_idle
extern tss_nueva_tarea
extern inicializar_entrada_gdt
extern prox_entrada_libre_gdt
extern inicializar_sched
extern game_inicializar
extern mapa_de_juego

global start


;; Saltear seccion de datos
jmp start

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
iniciando_mr_msg db     'Iniciando kernel (Modo Real)...'
iniciando_mr_len equ    $ - iniciando_mr_msg

iniciando_mp_msg db     'Iniciando kernel (Modo Protegido)...'
iniciando_mp_len equ    $ - iniciando_mp_msg

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
    imprimir_texto_mr iniciando_mr_msg, iniciando_mr_len, 0x07, 0, 0

    ; Habilitar A20
    call habilitar_A20

    ; Cargar la GDT
    lgdt [GDT_DESC]

    ; Setear el bit PE del registro CR0
    mov eax, CR0
    or eax, 1
    mov CR0, eax

    ; Saltar a modo protegido
    jmp 0xA0:mp

BITS 32
    mp:
    ; Establecer selectores de segmentos
    mov ax, 0xb0           ; nivel 0 - datos tipo read/write
    mov ss, ax             ; ss: Pila,
    mov ds, ax             ; ds: Segmento de datos
    mov gs, ax             ; ss: Pila,
    mov fs, ax             ; ss: Pila,
    mov es, ax             ; es: Pantalla

    ; Establecer la base de la pila
    mov esp, 0x27000
    mov ebp, 0x27000

    ; Imprimir mensaje de bienvenida
    imprimir_texto_mp iniciando_mp_msg, iniciando_mp_len, 0x07, 0x02, 0

    ; Inicializar pantalla
    mov ax, 0xc0           ; nivel 0 - datos tipo read/write - base 0xB8000 - límite 0xFA0
    mov ds, ax             ; ds: Segmento de datos
    call mapa_de_juego
    mov ax, 0xb0           ; nivel 0 - datos tipo read/write
    mov ds, ax             ; ds: Segmento de datos ---- Restauro DS

    ; Inicialiar el manejador de memoria
	call mmu_inicializar

    ; Inicializar el directorio de paginas
	call mmu_inicializar_dir_kernel

    ; Cargar directorio de paginas
	mov eax, [kernel_page_directory]
	mov cr3, eax

    ; Habilitar paginacion
	mov eax, cr0
	or eax, 0x80000000
	mov cr0, eax

    ; Inicializar tss
	push proseguir
	call tss_inicializar

    ; Inicializar tss de la tarea Idle
	call tss_inicializar_idle

    ; Inicializar el scheduler
    call inicializar_entrada_gdt
	call inicializar_sched
    call game_inicializar

    ; Inicializar la IDT
	;xchg bx, bx
    call idt_inicializar

    ; Cargar IDT
    lidt [IDT_DESC]

    ; Descomentar para testear excepcion divición por cero
    ;mov bx, 0
    ;div bx

    ; Configurar controlador de interrupciones
    call resetear_pic
    call habilitar_pic

    ; Cargar tarea inicial
    mov ax, 0x8
    ltr ax

    ; Habilitar interrupciones
 	proseguir:
    sti

	; call game_inicializar

    ; Saltar a la primera tarea: Idle
    jmp 0x10:0

    ; Ciclar infinitamente (por si algo sale mal...)
    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"
