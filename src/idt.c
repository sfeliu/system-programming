/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de las rutinas de atencion de interrupciones
*/

#include "defines.h"
#include "idt.h"
#include "isr.h"
#include "tss.h"

idt_entry idt[255] = { };

idt_descriptor IDT_DESC = {
    sizeof(idt) - 1,
    (uint32_t) &idt
};

/*
    La siguiente es una macro de EJEMPLO para ayudar a armar entradas de
    interrupciones. Para usar, descomentar y completar CORRECTAMENTE los
    atributos y el registro de segmento. Invocarla desde idt_inicializar() de
    la siguiene manera:

    void idt_inicializar() {
        IDT_ENTRY(0);
        ...
        IDT_ENTRY(19);

        ...
    }
*/

// DPL 0 puerta de interrupcion.
#define IDT_ENTRY_HARDWARE(numero)                                                                 \
    idt[numero].offset_0_15 = (uint16_t) ((uint32_t)(&_isr ## numero) & (uint32_t) 0xFFFF);        \
    idt[numero].segsel = (uint16_t) 0xA0;                                                          \
    idt[numero].attr = (uint16_t) 0x8E00;                                                          \
    idt[numero].offset_16_31 = (uint16_t) ((uint32_t)(&_isr ## numero) >> 16 & (uint32_t) 0xFFFF);


// DPL 3 y puerta de excepcion.
#define IDT_ENTRY_SOFTWARE(numero)                                                                 \
    idt[numero].offset_0_15 = (uint16_t) ((uint32_t)(&_isr ## numero) & (uint32_t) 0xFFFF);        \
    idt[numero].segsel = (uint16_t) 0xA0;                                                          \
    idt[numero].attr = (uint16_t) 0xEE00;                                                          \
    idt[numero].offset_16_31 = (uint16_t) ((uint32_t)(&_isr ## numero) >> 16 & (uint32_t) 0xFFFF);



void idt_inicializar() {
    // Excepciones
    IDT_ENTRY_HARDWARE(0);
    IDT_ENTRY_HARDWARE(1);
    IDT_ENTRY_HARDWARE(2);
    IDT_ENTRY_HARDWARE(3);
    IDT_ENTRY_HARDWARE(4);
    IDT_ENTRY_HARDWARE(5);
    IDT_ENTRY_HARDWARE(6);
    IDT_ENTRY_HARDWARE(7);
    IDT_ENTRY_HARDWARE(8);
    IDT_ENTRY_HARDWARE(9);
    IDT_ENTRY_HARDWARE(10);
    IDT_ENTRY_HARDWARE(11);
    IDT_ENTRY_HARDWARE(12);
    IDT_ENTRY_HARDWARE(13);
    IDT_ENTRY_HARDWARE(14);
    IDT_ENTRY_HARDWARE(15);
    IDT_ENTRY_HARDWARE(16);
    IDT_ENTRY_HARDWARE(17);
    IDT_ENTRY_HARDWARE(18);
    IDT_ENTRY_HARDWARE(19);
    IDT_ENTRY_HARDWARE(20);
    IDT_ENTRY_HARDWARE(21);
    IDT_ENTRY_HARDWARE(22);
    IDT_ENTRY_HARDWARE(23);
    IDT_ENTRY_HARDWARE(24);
    IDT_ENTRY_HARDWARE(25);
    IDT_ENTRY_HARDWARE(26);
    IDT_ENTRY_HARDWARE(27);
    IDT_ENTRY_HARDWARE(28);
    IDT_ENTRY_HARDWARE(29);
    IDT_ENTRY_HARDWARE(30);
    IDT_ENTRY_HARDWARE(31);

    IDT_ENTRY_HARDWARE(32);
    IDT_ENTRY_HARDWARE(33);
    IDT_ENTRY_SOFTWARE(102);
}
