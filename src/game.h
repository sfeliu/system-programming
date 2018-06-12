/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#ifndef __GAME_H__
#define __GAME_H__

#include "stdint.h"
#include "defines.h"
#include "screen.h"
#include "mmu.h"
#include "sched.h"

void game_inicializar();

uint32_t game_numero();

uint32_t game_escribir(uint32_t direccion, uint32_t* dato);

uint32_t game_leer(uint32_t direccion, uint32_t* dato);

void agregar_cazador(tarea_t*, uint32_t, uint32_t*, uint32_t);

#endif  /* !__GAME_H__ */
