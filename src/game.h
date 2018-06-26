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
void mantenimiento_scheduler();
void resetear_juego();


uint32_t game_numero();

uint32_t game_escribir(uint32_t direccion, uint32_t* dato);

void remap_saltadora(jugador_t* jug);

uint32_t game_leer(uint32_t direccion, uint32_t* dato);

void agregar_cazador(tarea_t*, uint32_t, uint32_t*, uint32_t);
tarea_t* inicializar_tarea_t();
void print_saltador(uint32_t);
void actualizar_clock_tarea();

#endif  /* !__GAME_H__ */
