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
	//print_hex(*dir_fisica_codigo, 8, 0, 0, 0xf);

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
	(*jugador_A).cant_vidas = 5;
	(*jugador_A).ultimo_cazador = cazadores_A; // Modificación: ultimo cazador es puntero a tarea.

	tarea_t* saltadora_B = inicializar_tarea_t();
	dir_fisica_codigo = NULL; // DEfinir
	indice_tarea = tss_nueva_tarea(2, dir_fisica_codigo);
	(*saltadora_B).indice_tss = (uint16_t)indice_tarea;
	(*saltadora_B).base_codigo = (uint32_t)dir_fisica_codigo;
	(*saltadora_B).indice = 0;
	(*jugador_B).saltadora = saltadora_B;

	tarea_t* cazadores_B = inicializar_tarea_t();
	for(int i = 1; i < 5; i++)
	{
		dir_fisica_codigo = NULL; // DEfinir
		indice_tarea = tss_nueva_tarea(3, dir_fisica_codigo);
		agregar_cazador(cazadores_B, indice_tarea, dir_fisica_codigo, i);
	}
	(*jugador_B).cazadores = cazadores_B; //cambio pablo
	(*jugador_B).cant_vidas = 5; //agrego pablo
	(*jugador_B).ultimo_cazador = cazadores_B; // Modificación: ultimo cazador es puntero a tarea.


}

uint32_t game_numero() {
	uint32_t temp = (uint32_t)indice_tarea;
    return temp;
}

uint32_t game_escribir(uint32_t direccion, uint32_t* dato) {
	//uint8_t attr1 = (C_BG_RED | C_FG_RED);           /* Fondo negro y caracter blanco */    
    //uint8_t attr2 = (C_BG_BLUE | C_FG_BLUE);           /* Fondo negro y caracter blanco */    
	//uint8_t character1 = 0x30;                           /* Caracter '0' */
	//uint32_t offset_A = 405;
    //uint32_t offset_B = 442;
   	//uint32_t offset_2 = (direccion/4)/32;

	if(jugador_actual == 0){
		//*((uint32_t*)(((*((*jugador_B).saltadora)).base_codigo)+direccion)) = *dato;
		//uint32_t fInit = offset_B+(direccion/4) + (47*offset_2);
	    //uint32_t cInit = offset_B+(direccion/4) + (47*offset_2);
	    //uint32_t fSize = offset_B+(direccion/4) + (47*offset_2);
	   	//uint32_t cSize = offset_B+(direccion/4) + (47*offset_2);
		//screen_drawBox(fInit, cInit, fSize, cSize, attr2, character1);
	}else{
		//*((uint32_t*)(((*((*jugador_A).saltadora)).base_codigo)+direccion)) = *dato;
		//uint32_t fInit = offset_A+(direccion/4) + (47*offset_2);
	    //uint32_t cInit = offset_A+(direccion/4) + (47*offset_2);
	    //uint32_t fSize = offset_A+(direccion/4) + (47*offset_2);
	   	//uint32_t cSize = offset_A+(direccion/4) + (47*offset_2);
		//screen_drawBox(fInit, cInit, fSize, cSize, attr1, character1);
	}
    return 1;
}

uint32_t game_leer(uint32_t direccion, uint32_t* dato) {
	//uint8_t character1 = 0x30;                           /* Caracter '0' */
	//uint8_t attr1 = (C_BG_RED | C_FG_RED);           /* Fondo negro y caracter blanco */    
    //uint8_t attr2 = (C_BG_BLUE | C_FG_BLUE);           /* Fondo negro y caracter blanco */    
    //uint32_t offset_A = 405;
    //uint32_t offset_B = 442;
    //uint32_t offset_2 = (direccion/4)/32;

	if(jugador_actual == 0){
		//*dato = *((uint32_t*)(((*((*jugador_B).saltadora)).base_codigo)+direccion));
		//uint32_t fInit = offset_B+(direccion/4) + (47*offset_2);
	    //uint32_t cInit = offset_B+(direccion/4) + (47*offset_2);
	    //uint32_t fSize = offset_B+(direccion/4) + (47*offset_2);
	   	//uint32_t cSize = offset_B+(direccion/4) + (47*offset_2);
		//screen_drawBox(fInit, cInit, fSize, cSize, attr2, character1);
	}else{
		//*dato = *((uint32_t*)(((*((*jugador_A).saltadora)).base_codigo)+direccion));
		//uint32_t fInit = offset_A+(direccion/4) + (47*offset_2);
	    //uint32_t cInit = offset_A+(direccion/4) + (47*offset_2);
	    //uint32_t fSize = offset_A+(direccion/4) + (47*offset_2);
	   	//uint32_t cSize = offset_A+(direccion/4) + (47*offset_2);
		//screen_drawBox(fInit, cInit, fSize, cSize, attr1, character1);
	}
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

		
		nueva_tarea.anterior = (*primero).anterior;
		nueva_tarea.siguiente = primero;

		(*guardarAca) = nueva_tarea;                                                         
		
		tarea_t* cazador_previo = (*primero).anterior;
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

void mantenimiento_scheduler(){
	if(jugador_actual == 0){
		if(indice_tarea == 0){
			if((*jugador_A).cant_vidas == 1){
				resetear_juego();
			}else{
				(*jugador_A).cant_vidas = ((*jugador_A).cant_vidas) - 1;
			}
		}else{
				tarea_t* tarea_actual = (*jugador_A).cazadores; // NO TIENE UN PRIMER NODO LA LISTA ???
				while((*tarea_actual).indice != indice_tarea)
				{
				tarea_actual = (*tarea_actual).siguiente;
				}
				indice_tarea = (*((*tarea_actual).anterior)).indice;
				tarea_t* tarea_anterior = (*tarea_actual).anterior;
				tarea_t* tarea_siguinte = (*tarea_actual).siguiente;
				(*tarea_anterior).siguiente = (tarea_siguinte);
				(*tarea_siguinte).anterior = (tarea_anterior);

				//mmu_unmapearPagina(uint32_t virtual, uint32_t cr3)
				//mmu_unmapearPagina((*tarea_actual).base_codigo);
				//(*jugador_A).ultimo_cazador = (*tarea_anterior).indice;
			
		}
	}else{
		if(indice_tarea == 0){
			if((*jugador_B).cant_vidas == 1){
				resetear_juego();
			}else{
				(*jugador_B).cant_vidas = ((*jugador_B).cant_vidas) - 1;
			}
		}else{
				tarea_t* tarea_actual = (*jugador_B).cazadores;
				while((*tarea_actual).indice != indice_tarea)
				{
				tarea_actual = (*tarea_actual).siguiente;
				}
				indice_tarea = (*((*tarea_actual).anterior)).indice;
				tarea_t* tarea_anterior = (*tarea_actual).anterior;
				tarea_t* tarea_siguinte = (*tarea_actual).siguiente;
				(*tarea_anterior).siguiente = (tarea_siguinte);
				(*tarea_siguinte).anterior = (tarea_anterior);

				//mmu_unmapearPagina(uint32_t virtual, uint32_t cr3)
				//mmu_unmapearPagina((*tarea_actual).base_codigo);
				//(*jugador_B).ultimo_cazador = (*tarea_anterior).indice;
				(*jugador_B).cant_vidas = ((*jugador_B).cant_vidas) - 1;
		}
	}
}

void resetear_juego(){
	mapa_de_juego();
	inicializar_sched();
	game_inicializar();
}
