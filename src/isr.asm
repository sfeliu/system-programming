; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

%include "imprimir.mac"
extern print

BITS 32

sched_tarea_offset:     dd 0x00
sched_tarea_selector:   dw 0x00

msg_int_0: db       'Excepción 0: Error divición', 0
msg_int_1: db       'Excepción 1: Reservada', 0
msg_int_2: db       'Excepción 2: No enmascarable', 0
msg_int_3: db       'Excepción 3: Break Point', 0
msg_int_4: db       'Excepción 4: Overflow', 0
msg_int_5: db       'Excepción 5: BOUND range exceeded', 0
msg_int_6: db       'Excepción 6: Invalid opcode', 0
msg_int_7: db       'Excepción 7: Device not available', 0
msg_int_8: db       'Excepción 8: Double Fault', 0
msg_int_9: db       'Excepción 9: Coprocessor segment overrun', 0
msg_int_10: db      'Excepción 10: Invalid TSS', 0
msg_int_11: db      'Excepción 11: Segment not present', 0
msg_int_12: db      'Excepción 12: Stack segment fault', 0
msg_int_13: db      'Excepción 13: General protection', 0
msg_int_14: db      'Excepción 14: Page fault', 0
msg_int_15: db      'Excepción 15: Reservada', 0
msg_int_16: db      'Excepción 16: FPU Floating point error', 0
msg_int_17: db      'Excepción 17: Aligment check', 0
msg_int_18: db      'Excepción 18: Machine check', 0
msg_int_19: db      'Excepción 19: SIMD Floating point error', 0
msg_int_20: db      'Excepción 20: Reservada', 0
msg_int_21: db      'Excepción 21: Reservada', 0
msg_int_22: db      'Excepción 22: Reservada', 0
msg_int_23: db      'Excepción 23: Reservada', 0
msg_int_24: db      'Excepción 24: Reservada', 0
msg_int_25: db      'Excepción 25: Reservada', 0
msg_int_26: db      'Excepción 26: Reservada', 0
msg_int_27: db      'Excepción 27: Reservada', 0
msg_int_28: db      'Excepción 28: Reservada', 0
msg_int_29: db      'Excepción 29: Reservada', 0
msg_int_30: db      'Excepción 30: Reservada', 0
msg_int_31: db      'Excepción 31: Reservada', 0

;; PIC
extern fin_intr_pic1

;; Sched
extern sched_proximoIndice

;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;

%macro ISR 1
global _isr%1

_isr%1:
    mov eax, %1
    push 0xF
    push 0xF
    push 0xF
    push msg_int_%1
    call print
    jmp $

%endmacro

;;
;; Datos
;; -------------------------------------------------------------------------- ;;
; Scheduler
isrnumero:           dd 0x00000000
isrClock:            db '|/-\'

;;
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
ISR 20
ISR 21
ISR 22
ISR 23
ISR 24
ISR 25
ISR 26
ISR 27
ISR 28
ISR 29
ISR 30
ISR 31
;;
;; Rutina de atención del RELOJ
;; -------------------------------------------------------------------------- ;;

;;
;; Rutina de atención del TECLADO
;; -------------------------------------------------------------------------- ;;


;;
;; Rutinas de atención de las SYSCALLS
;; -------------------------------------------------------------------------- ;;

%define sysNumero   0x542
%define sysEscribir 0x824
%define sysLeer     0x7CA


;; Funciones Auxiliares
;; -------------------------------------------------------------------------- ;;
proximoReloj:
        pushad
        inc DWORD [isrnumero]
        mov ebx, [isrnumero]
        cmp ebx, 0x4
        jl .ok
                mov DWORD [isrnumero], 0x0
                mov ebx, 0
        .ok:
                add ebx, isrClock
                imprimir_texto_mp ebx, 1, 0x0f, 49, 79
                popad
        ret
        
        
