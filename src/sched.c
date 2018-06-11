/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"

void inicializar_sched()
{
	indice_tarea = 0;
	jugador_actual = 0;
}

uint16_t sched_proximoIndice()
{
	if(jugador_actual == 0)
	{
		jugador_actual = 1;
		if(indice_tarea == 0)
		{
			tarea_t* saltadora = (*jugador_B).saltadora;
			return (*saltadora).indice_tss;
		}
		else
		{
			tarea_t siguienteTarea = proximaTarea(*jugador_B);
			indice_tarea = siguienteTarea.indice;
			return siguienteTarea.indice_tss;
		}
	}
	else
	{
		jugador_actual = 0;
		if(indice_tarea != 0)
		{
			indice_tarea = 0;
			tarea_t* saltadora = (*jugador_A).saltadora;
			return (*saltadora).indice_tss;
		}
		else
		{
			tarea_t siguienteTarea = proximaTarea(*jugador_A);
			indice_tarea = siguienteTarea.indice;
			return siguienteTarea.indice_tss;
		}
	}
}

tarea_t proximaTarea(jugador_t jugador)
{
	uint8_t indice_anterior = jugador.ultimo_cazador;
	tarea_t* tarea_actual = jugador.cazadores;

	while((*tarea_actual).indice < indice_anterior)
	{
		tarea_actual = (*tarea_actual).siguiente;
	}

	return *tarea_actual;
}
