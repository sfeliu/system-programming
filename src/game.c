/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"
#include "screen.h"

#define LS_INLINE static __inline __attribute__((always_inline))



void game_inicializar() {
	//tarea_t* saltadora_A = (*jugador_A).saltadora;
	inic_w_k();
	tarea_t* saltadora_A = inicializar_tarea_t();
	uint32_t* dir_fisica_codigo = NULL; // DEfinir
	uint32_t indice_tarea = tss_nueva_tarea(0, dir_fisica_codigo);
	//print_hex(*dir_fisica_codigo, 8, 0, 0, 0xf);

	(*saltadora_A).indice_tss = (uint16_t)indice_tarea;
	(*saltadora_A).base_codigo = *dir_fisica_codigo;
	(*saltadora_A).indice = 0;
	(*jugador_A).saltadora = saltadora_A;
	//print_hex((uint32_t)(*jugador_A), 8, 0, w, 0xf);
	//print_hex((uint32_t)(*jugador_B), 8, 0, w+1, 0xf);



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
	(*saltadora_B).base_codigo = (*dir_fisica_codigo);
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
	print_hex((*jugador_A).cant_vidas, 1, 35, 45, (C_BG_RED | C_FG_WHITE));
	print_hex((*jugador_B).cant_vidas, 1, 43, 45, (C_BG_BLUE | C_FG_WHITE));



}

uint32_t game_numero() {
	uint32_t temp = (uint32_t)indice_tarea;
	//print_hex(temp, 8, 2, k, 0xf);
	//k++;
    return temp;
}

uint32_t game_escribir(uint32_t direccion, uint32_t* dato) {
	//print_hex(direccion, 8, 2, k, 0xf);
	//k++;
	direccion = (direccion <<20 )>>20;
	uint8_t attr2 = (C_BG_RED | C_FG_WHITE);           /* Fondo negro y caracter blanco */    
    uint8_t attr1 = (C_BG_BLUE | C_FG_WHITE);           /* Fondo negro y caracter blanco */    
	uint8_t character1 = 0x58;                           /* Caracter 'X' */
    uint32_t offset_f = 5;
	uint32_t offset_c_A = 5;    
	uint32_t offset_c_B = 42;
    uint32_t offset_dir_f = (direccion/4)/32;
    uint32_t offset_dir_c = (direccion/4)-(offset_dir_f*32);

   	uint32_t cr3_var = rcr3(); 
   	cr3_var = (cr3_var >> 12)<<12;

	if(jugador_actual == 0){
		uint32_t dir_fisica = (*((*jugador_B).saltadora)).base_codigo;
		mmu_mapearPagina(dir_fisica, cr3_var, dir_fisica, 1, 1, 1, 1);

		*((uint32_t*)(dir_fisica+direccion)) = *dato;
		mmu_unmapearPagina(dir_fisica, cr3_var);
		uint32_t fInit = offset_f + offset_dir_f;
	    uint32_t cInit = offset_c_B + offset_dir_c;
	    uint32_t fSize = 1;
	   	uint32_t cSize = 1;
		screen_drawBox(fInit, cInit, fSize, cSize, character1, attr2);
	}else{
		uint32_t dir_fisica = (*((*jugador_A).saltadora)).base_codigo;
		mmu_mapearPagina(dir_fisica, cr3_var, dir_fisica, 1, 1, 1, 1);

		*((uint32_t*)(dir_fisica+direccion)) = *dato;
		mmu_unmapearPagina(dir_fisica, cr3_var);
		uint32_t fInit = offset_f + offset_dir_f;
	    uint32_t cInit = offset_c_A + offset_dir_c;
	    uint32_t fSize = 1;
	   	uint32_t cSize = 1;
		screen_drawBox(fInit, cInit, fSize, cSize, character1, attr1);
	}
    return 1;
}

uint32_t game_leer(uint32_t direccion, uint32_t* dato) {
	//print_hex(direccion, 8, 2, k, 0xf);
	//k++;
	direccion = (direccion <<20 )>>20;
	uint8_t character1 = 0x0;                           /* Caracter '(space)' */
	uint8_t attr2 = (C_BG_RED | C_FG_WHITE);           /* Fondo negro y caracter blanco */    
    uint8_t attr1 = (C_BG_BLUE | C_FG_WHITE);           /* Fondo negro y caracter blanco */    
    uint32_t offset_f = 5;
	uint32_t offset_c_A = 5;    
	uint32_t offset_c_B = 42;
    uint32_t offset_dir_f = (direccion/4)/32;
    uint32_t offset_dir_c = (direccion/4)-(offset_dir_f*32);

    uint32_t cr3_var = rcr3(); 
   	cr3_var = (cr3_var >> 12)<<12;

	if(jugador_actual == 0){
		uint32_t dir_fisica = (*((*jugador_B).saltadora)).base_codigo;
		mmu_mapearPagina(dir_fisica, cr3_var, dir_fisica, 1, 1, 1, 1);

		*dato = *((uint32_t*)(dir_fisica+direccion));
		mmu_unmapearPagina(dir_fisica, cr3_var);
		uint32_t fInit = offset_f + offset_dir_f;
	    uint32_t cInit = offset_c_B + offset_dir_c;
	    uint32_t fSize = 1;
	   	uint32_t cSize = 1;
		screen_drawBox(fInit, cInit, fSize, cSize, character1, attr2);
	}else{
		uint32_t dir_fisica = (*((*jugador_A).saltadora)).base_codigo;
		mmu_mapearPagina(dir_fisica, cr3_var, dir_fisica, 1, 1, 1, 1);

		*dato = *((uint32_t*)(dir_fisica+direccion));
		//*((uint32_t*)(dir_fisica+direccion)) = *dato;
		mmu_unmapearPagina(dir_fisica, cr3_var);
		uint32_t fInit = offset_f + offset_dir_f;
	    uint32_t cInit = offset_c_A + offset_dir_c;
	    uint32_t fSize = 1;
	   	uint32_t cSize = 1;
		screen_drawBox(fInit, cInit, fSize, cSize, character1, attr1);
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
			if((*jugador_A).cant_vidas == 1){ //si no le quedan vidas
				(*jugador_A).cant_vidas = ((*jugador_A).cant_vidas) - 1;
				print_hex((*jugador_A).cant_vidas, 1, 35, 45, (C_BG_RED | C_FG_WHITE));
				//resetear_juego();
			}else{
				(*jugador_A).cant_vidas = ((*jugador_A).cant_vidas) - 1;
				print_hex((*jugador_A).cant_vidas, 1, 35, 45, (C_BG_RED | C_FG_WHITE));
				remap_saltadora(jugador_A);
			}
		}else{
				tarea_t* tarea_actual = (*jugador_A).ultimo_cazador;
				if( (*tarea_actual).indice == (*((*tarea_actual).anterior)).indice ){
					murio_cazadora((*tarea_actual).indice, jugador_actual);
					//resetear_juego();
				}else{
					murio_cazadora((*tarea_actual).indice, jugador_actual);
					(*jugador_A).ultimo_cazador	= ((*tarea_actual).anterior);		
					indice_tarea = (*((*tarea_actual).anterior)).indice;
					tarea_t* tarea_anterior = (*tarea_actual).anterior;
					tarea_t* tarea_siguinte = (*tarea_actual).siguiente;
					(*tarea_anterior).siguiente = (tarea_siguinte);
					(*tarea_siguinte).anterior = (tarea_anterior);
				}			
		}
	}else{
		if(indice_tarea == 0){
			if((*jugador_B).cant_vidas == 1){
				//resetear_juego();
			}else{
				(*jugador_B).cant_vidas = ((*jugador_B).cant_vidas) - 1;
				print_hex((*jugador_B).cant_vidas, 1, 43, 45, (C_BG_BLUE | C_FG_WHITE));
				remap_saltadora(jugador_B);
			}
		}else{
			tarea_t* tarea_actual = (*jugador_B).ultimo_cazador;
			if((*tarea_actual).indice == ((*(*tarea_actual).anterior)).indice ){ //si no hay mas cazadoras
				murio_cazadora((*tarea_actual).indice, jugador_actual);
				//resetear_juego();
			}else{
				murio_cazadora((*tarea_actual).indice, jugador_actual);
				(*jugador_B).ultimo_cazador	= ((*tarea_actual).anterior);		
				indice_tarea = (*((*tarea_actual).anterior)).indice;
				tarea_t* tarea_anterior = (*tarea_actual).anterior;
				tarea_t* tarea_siguinte = (*tarea_actual).siguiente;
				(*tarea_anterior).siguiente = (tarea_siguinte);
				(*tarea_siguinte).anterior = (tarea_anterior);
			}
		}
	}
}

void remap_saltadora(jugador_t* jug){
	//copio el codigo de la saltadora de nuevo
	//print_hex(jugador_actual, 8, 35, 0, 0xf);

	uint32_t* guardarAca = (uint32_t*)0x8000000;
	for(int j = 0; j < 1024; j++)
	{
		guardarAca[j] = ((uint32_t*)0x10000)[j];
	}
	uint32_t dir = (uint32_t)rcr3();
	//creo nueva tss con nueva pila nivel 0
	uint32_t posicion_tss = mmu_prox_pag_fisica_libre_kernel();
	tss* tss_tarea = (tss*)posicion_tss;

	*tss_tarea = (tss)
	{
		.esp0 = mmu_prox_pag_fisica_libre_kernel() + 4096,
		.ss0 = 0xb0,
		.cr3 = dir,
		.eflags = 0x202,
		.esp = 0x8000000 + 4096,
		.ebp = 0x8000000 + 4096,
		.eip = 0x8000000,
		.ss = 0xbb,
		.es = 0xbb,
		.cs = 0xab,
		.ds = 0xbb,
		.fs = 0xbb,
		.gs = 0xbb,
		.iomap = 0xffff
	};

	uint32_t indice_tarea = (*((*jug).saltadora)).indice_tss;

	gdt[indice_tarea].base_0_15 = (uint32_t) tss_tarea;
	gdt[indice_tarea].base_23_16 = (uint32_t) tss_tarea >> 16;
	gdt[indice_tarea].base_31_24 = (uint32_t) tss_tarea >> 24;
	//gdt[indice_tarea].p = 1;
	//gdt[indice_tarea].limit_0_15 = 0x67;
	//gdt[indice_tarea].type = 0x9;
	//gdt[indice_tarea].dpl = 0x3;
	//gdt[indice_tarea].db = 0x1;
}

void resetear_juego(){
	__asm __volatile("cli");

	mapa_de_juego();
	inicializar_sched();
	game_inicializar();
	__asm __volatile("sti");

}

void print_saltador(uint32_t eip_tarea){
	if(indice_tarea == 0 && eip_tarea >= 0x8000000){
		uint32_t offset = (eip_tarea << 20) >> 20;

    	uint32_t offset_f = (offset/4)/32;
    	uint32_t offset_c = (offset/4)-(offset_f*32);
    	uint8_t attr = 0x0;
    	if(jugador_actual == 0)
    	{
    		offset_c = offset_c + OFFSET_COLUMNA_A;
    		attr = COLOR_A;
    	}
    	else
    	{
    		offset_c = offset_c + OFFSET_COLUMNA_B;
    		attr = COLOR_B;
    	}
    	uint8_t text = 0x4F;
//    	print((uint8_t*) &text, offset_f, offset_c, attr);
		screen_drawBox(offset_f, offset_c, 1, 1, text, attr);
	}
}