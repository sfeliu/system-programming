/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCHED_H__
#define __SCHED_H__

#include "stdint.h"
#include "screen.h"
#include "mmu.h"
#include "tss.h"

typedef struct str_tarea {
	uint16_t indice_tss;
	uint32_t base_codigo;
	uint8_t indice;
	struct str_tarea* siguiente;
	struct str_tarea* anterior;
}__attribute__((__packed__)) tarea_t;

typedef struct str_jugador {
    tarea_t* cazadores;		//tarea_t tareas[5];
    tarea_t* saltadora;
	tarea_t* ultimo_cazador;
	uint8_t cant_vidas;
} __attribute__((__packed__)) jugador_t;

tarea_t* tss_tarea_init;
tarea_t* tss_tarea_idle;

uint8_t indice_tarea;
uint8_t jugador_actual;

jugador_t* jugador_A;
jugador_t* jugador_B;

int w;
int k;

void inic_w_k();

void inicializar_sched();
uint16_t sched_proximoIndice();
tarea_t proximaTarea(jugador_t*);

#endif	/* !__SCHED_H__ */
