/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"
#include "screen.h"


void game_inicializar() {
	//tarea_t* saltadora_A = (*jugador_A).saltadora;
	tarea_t* saltadora_A = inicializar_tarea_t();
	uint32_t* dir_fisica_codigo = NULL; // DEfinir
	uint32_t indice_tarea = tss_nueva_tarea(0, dir_fisica_codigo);
	print_hex(*dir_fisica_codigo, 8, 0, 0, 0xf);

	(*saltadora_A).indice_tss = (uint16_t)indice_tarea;
	(*saltadora_A).base_codigo = *dir_fisica_codigo;
	(*saltadora_A).indice = 0;
	(*jugador_A).saltadora = saltadora_A;

	tarea_t* cazadores_A = inicializar_tarea_t();
	for(int i = 1; i < 5; i++)
	{
		dir_fisica_codigo = NULL; // DEfinir
		indice_tarea = tss_nueva_tarea(1, dir_fisica_codigo);
		agregar_cazador(cazadores_A, indice_tarea, dir_fisica_codigo, i);
	}
	(*jugador_A).cazadores = cazadores_A;

	tarea_t* saltadora_B = inicializar_tarea_t();
	dir_fisica_codigo = NULL; // DEfinir
	indice_tarea = tss_nueva_tarea(2, dir_fisica_codigo);
	(*saltadora_B).indice_tss = (uint16_t)indice_tarea;
	(*saltadora_B).base_codigo = *dir_fisica_codigo;
	(*saltadora_B).indice = 0;
	(*jugador_B).saltadora = saltadora_B;

	tarea_t* cazadores_B = (*jugador_B).cazadores;
	for(int i = 1; i < 5; i++)
	{
		dir_fisica_codigo = NULL; // DEfinir
		indice_tarea = tss_nueva_tarea(3, dir_fisica_codigo);
		agregar_cazador(cazadores_B, indice_tarea, dir_fisica_codigo, i);
	}
	(*jugador_A).cazadores = cazadores_A;

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
		.indice_tss = (uint16_t)indice_tarea,
		.base_codigo = *dir_fisica_codigo,
		.indice = (uint8_t)indice_cazador,
	};
	if(indice_cazador == 1)
	{
		(*primero) = nueva_tarea;
		(*primero).siguiente = primero;
		(*primero).anterior = primero;
	}
	else
	{

		uint32_t direccion_nueva_tarea = mmu_prox_pag_fisica_libre_kernel();
		tarea_t* guardarAca = (tarea_t*)direccion_nueva_tarea;

		tarea_t* cazador_previo = primero;
		while((*cazador_previo).indice < indice_cazador-1)
		{
			cazador_previo = (*cazador_previo).siguiente;
		}
		nueva_tarea.anterior = cazador_previo;
		nueva_tarea.siguiente = primero;


		(*cazador_previo).siguiente = (tarea_t*) guardarAca;
		(*primero).anterior = (tarea_t*) guardarAca ;
	}
}

tarea_t* inicializar_tarea_t()
{
	uint32_t direccion_nueva_tarea = mmu_prox_pag_fisica_libre_kernel();
	tarea_t* guardarAca = (tarea_t*)direccion_nueva_tarea;
	return guardarAca;
}