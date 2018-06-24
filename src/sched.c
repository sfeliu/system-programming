/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"
#define LS_INLINE static __inline __attribute__((always_inline))


void inicializar_sched()
{
	indice_tarea = 0;
	jugador_actual = 0;

	jugador_A = (jugador_t*) mmu_prox_pag_fisica_libre_kernel();
	jugador_B = (jugador_t*) mmu_prox_pag_fisica_libre_kernel();

}
void inic_w_k(){
	w=0;
	k=0;
}

uint16_t sched_proximoIndice()
{
	//__asm __volatile("call fin_intr_pic1");
	print_hex(jugador_actual, 1, 0, w, 0xf);
	print_hex(indice_tarea, 1, 0, w+1, 0xf);

	if(jugador_actual == 0)
	{
		jugador_actual = 1;
		if(indice_tarea == 0)
		{
			tarea_t* saltadora = (*jugador_B).saltadora;
			print_hex(indice_tarea, 1, 0, w+2, 0xf);
			print_hex((uint32_t)(*saltadora).indice_tss, 1, 0, w+3, 0xf);
			w=w+5;
			return (*saltadora).indice_tss;
		}
		else
		{
			tarea_t siguienteTarea = proximaTarea(jugador_B);
			indice_tarea = siguienteTarea.indice;
			print_hex(indice_tarea, 1, 0, w+2, 0xf);
			print_hex((uint32_t)(siguienteTarea.indice_tss), 1, 0, w+3, 0xf);
			w=w+5;
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
			print_hex(indice_tarea, 1, 0, w+2, 0xf);
			print_hex((uint32_t)((*saltadora).indice_tss), 1, 0, w+3, 0xf);
			w=w+5;
			return (*saltadora).indice_tss;
		}
		else
		{
			tarea_t siguienteTarea = proximaTarea(jugador_A);

			indice_tarea = siguienteTarea.indice;
			print_hex(indice_tarea, 1, 0, w+2, 0xf);
			print_hex((uint32_t)siguienteTarea.indice_tss, 1, 0, w+3, 0xf);
			w=w+5;
			return siguienteTarea.indice_tss;
		}
	}
}

tarea_t proximaTarea(jugador_t* jugador)
{
	tarea_t* cazador_anterior = (*jugador).ultimo_cazador;
	(*jugador).ultimo_cazador = (*cazador_anterior).siguiente;

	/*tarea_t* tarea_actual = jugador.cazadores;
	
	while((*tarea_actual).indice != indice_anterior){
			tarea_actual = (*tarea_actual).siguiente;
		}
	tarea_actual = (*tarea_actual).siguiente;
	
	while((*tarea_actual).indice < indice_anterior)
		{
			tarea_actual = (*tarea_actual).siguiente;
		}*/

	return *((*cazador_anterior).siguiente);
}

