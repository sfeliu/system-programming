/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#ifndef __MMU_H__
#define __MMU_H__

#include "stdint.h"
#include "defines.h"
#include "i386.h"
#include "tss.h"
#include "game.h"

/* Struct de una entrada de la directory page */
typedef struct str_directory_entry_t {
	uint8_t p:1;
	uint8_t rw:1;
	uint8_t us:1;
	uint8_t pwt:1;
	uint8_t pcd:1;
	uint8_t a:1;
	uint8_t ignored1:1;
	uint8_t ps:1;
	uint8_t ignored4:4;
	uint32_t dir_table:20;
} __attribute__((__packed__)) directory_entry_t;

/* Struct de una entrada de la directory page */
typedef struct str_table_entry_t {
	uint8_t p:1;
	uint8_t rw:1;
	uint8_t us:1;
	uint8_t pwt:1;
	uint8_t psv:1;
	uint8_t a:1;
	uint8_t d:1;
	uint8_t pat:1;
	uint8_t g:1;
	uint8_t ignored:3;
	uint32_t dir_memory:20;
} __attribute__((__packed__)) table_entry_t;

directory_entry_t* kernel_page_directory;

uint32_t prox_pag_libre_kernel;
uint32_t prox_pag_libre_tarea;

void mmu_inicializar();

void mmu_inicializar_dir_kernel();
void mmu_inicializar_dir_tarea();

uint32_t mmu_prox_pag_fisica_libre_kernel();
uint32_t mmu_prox_pag_fisica_libre_tarea();


#endif	/* !__MMU_H__ */
