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
#include "tss.h"

int16_t sched_proximoIndice();

uint32_t* lista_prox_tarea_A;
uint32_t* info_tarea_A;
uint32_t* lista_prox_tarea_B;
uint32_t* info_tarea_B;

uint32_t* tss_tarea_init;
uint32_t* tss_tarea_idle;

#endif	/* !__SCHED_H__ */
