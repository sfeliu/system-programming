/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"


void game_inicializar() {
	tarea_t* saltadora_A = jugador_A.saltadora;
	uint32_t* dir_fisica_codigo = NULL; // DEfinir
	uint32_t indice_tarea = tss_nueva_tarea(0, dir_fisica_codigo);
	saltadora_A.indice_tss = indice_tarea;
	saltadora_A.base_codigo = dir_fisica_codigo;
	saltadora_A.indice = 0;

	tarea_t* cazadores_A = jugador_A.cazadores;
	for(int i = 1; i < 5; i++)
	{
		dir_fisica_codigo = NULL; // DEfinir
		indice_tarea = tss_nueva_tarea(1, dir_fisica_codigo);
		agregar_cazador(cazadores_A, indice_tarea, dir_fisica_codigo, i);
	}

	tarea_t* saltadora_B = jugador_B.saltadora;
	dir_fisica_codigo = NULL; // DEfinir
	indice_tarea = tss_nueva_tarea(2, dir_fisica_codigo);
	saltadora_B.indice_tss = indice_tarea;
	saltadora_B.base_codigo = dir_fisica_codigo;
	saltadora_B.indice = 0;

	tarea_t* cazadores_B = jugador_B.cazadores;
	for(int i = 1; i < 5; i++)
	{
		dir_fisica_codigo = NULL; // DEfinir
		indice_tarea = tss_nueva_tarea(3, dir_fisica_codigo);
		agregar_cazador(cazadores_B, indice_tarea, dir_fisica_codigo, i);
	}

}

uint32_t game_numero() {
    return 1;
}

uint32_t game_escribir(uint32_t direccion, uint32_t* dato) {
    return 1;
}

uint32_t game_leer(uint32_t direccion, uint32_t* dato) {
    return 1;
}


void agregar_cazador(tarea_t* primero, uint32_t indice_tarea, uint32_t* dir_fisica_codigo, uint32_t indice_cazador)
{	
	tarea_t nueva_tarea = (tarea_t){
		.indice_tss = indice_tarea;
		.base_codigo = (uint32_t) dir_fisica_codigo;
		.indice = indice_cazador;
	}
	if(indice == 1)
	{	
		(*primero) = nueva_tarea;
		(*primero).siguiente = primero;
		(*primero).anterior = primero;
	}
	else
	{

		uint32_t direccion_nueva_tarea = mmu_prox_pag_fisica_libre_kernel();
		uint8_t* guardarAca = (uint8_t*)direccion_nueva_tarea;
		
		tarea_t* cazador_previo = primero;
		while((*cazador_previo).indice < indice_cazador-1)
		{
			cazador_previo = (*cazador_previo).siguiente;
		}
		nueva_tarea.anterior = cazador_previo;
		nueva_tarea.siguiente = primero;

		for(int j = 0; j < 4096; j++)
		{
			guardarAca[j] = nueva_tarea[j];
		}
		(*cazador_previo).siguiente = (tarea_t*) guardarAca;
		(*primero).anterior = (tarea_t*) guardarAca;
	}
}


crear_cazador()