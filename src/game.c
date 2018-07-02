/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"
#include "screen.h"

#define LS_INLINE static __inline __attribute__((always_inline))


// Inicializacion del juego, se inicializan las tareas y se les asigna a la estructura del scheduler.
void game_inicializar() {
	//tarea_t* saltadora_A = (*jugador_A).saltadora;
	//inic_w_k();
	
	// Inicializar tarea saltadora jugador A
	tarea_t* saltadora_A = inicializar_tarea_t();
	uint32_t* dir_fisica_codigo = NULL;
	uint32_t indice_tarea = tss_nueva_tarea(0, dir_fisica_codigo);
	//print_hex(*dir_fisica_codigo, 8, 0, 0, 0xf);

	(*saltadora_A).indice_tss = (uint16_t)indice_tarea;
	(*saltadora_A).base_codigo = *dir_fisica_codigo;
	(*saltadora_A).indice = 0;
	(*saltadora_A).indice_reloj = 0;
	(*jugador_A).saltadora = saltadora_A;
	//print_hex((uint32_t)(*jugador_A), 8, 0, w, 0xf);
	//print_hex((uint32_t)(*jugador_B), 8, 0, w+1, 0xf);

	// Inicializar Cazadores jugador A, cazadores_A es *tarea_t 
	tarea_t* cazadores_A = inicializar_tarea_t();
	for(int i = 1; i < 5; i++)
	{
		dir_fisica_codigo = NULL;
		indice_tarea = tss_nueva_tarea(1, dir_fisica_codigo);
		agregar_cazador(cazadores_A, indice_tarea, dir_fisica_codigo, i);
	}

	// Inicialización del resto del jugador A
	(*jugador_A).cazadores = cazadores_A;
	(*jugador_A).cant_vidas = 5;
	(*jugador_A).ultimo_cazador = cazadores_A;


	// Inicializar tarea saltadora jugador B
	tarea_t* saltadora_B = inicializar_tarea_t();
	dir_fisica_codigo = NULL;
	indice_tarea = tss_nueva_tarea(2, dir_fisica_codigo);
	(*saltadora_B).indice_tss = (uint16_t)indice_tarea;
	(*saltadora_B).base_codigo = (*dir_fisica_codigo);
	(*saltadora_B).indice = 0;
	(*saltadora_B).indice_reloj = 0;
	(*jugador_B).saltadora = saltadora_B;

	// Inicializar Cazadores jugador B, cazadores_B es *tarea_t 
	tarea_t* cazadores_B = inicializar_tarea_t();
	for(int i = 1; i < 5; i++)
	{
		dir_fisica_codigo = NULL;
		indice_tarea = tss_nueva_tarea(3, dir_fisica_codigo);
		agregar_cazador(cazadores_B, indice_tarea, dir_fisica_codigo, i);
	}
	// Inicialización del resto del jugador B
	(*jugador_B).cazadores = cazadores_B; //cambio pablo
	(*jugador_B).cant_vidas = 5; //agrego pablo
	(*jugador_B).ultimo_cazador = cazadores_B;

	// Inicializar contador de vidas en pantalla
	print_hex((*jugador_A).cant_vidas, 1, 35, 45, (C_BG_RED | C_FG_WHITE));
	print_hex((*jugador_B).cant_vidas, 1, 43, 45, (C_BG_BLUE | C_FG_WHITE));
}

// Como una especie de malloc para las tareas.
tarea_t* inicializar_tarea_t()
{
	uint32_t direccion_nueva_tarea = mmu_prox_pag_fisica_libre_kernel();
	tarea_t* guardarAca = (tarea_t*)direccion_nueva_tarea;
	return guardarAca;
}

// Inicializa un cazador nuevo con los parametros de entrada, y lo coloca al final de la lista
void agregar_cazador(tarea_t* primero, uint32_t indice_tarea, uint32_t* dir_fisica_codigo, uint32_t indice_cazador)
{
	tarea_t nueva_tarea = (tarea_t){
		.indice_tss = (uint16_t)indice_tarea,
		.base_codigo = *dir_fisica_codigo,
		.indice = (uint8_t)indice_cazador,
		.indice_reloj = 0,
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

// Devuelve indice de la tarea cazadora
uint32_t game_numero() {
	uint32_t temp = (uint32_t)indice_tarea;
	//print_hex(temp, 8, 2, k, 0xf);
	//k++;
    return temp;
}

// Escribe dato en el offset dado por dirección de la tarea saltadora
uint32_t game_escribir(uint32_t direccion, uint32_t* dato) {
	//print_hex(direccion, 8, 2, k, 0xf);
	//k++;
	if(direccion >= 0 && direccion < 0x1000)
	{
		direccion = (direccion <<20 )>>20;
		uint8_t character = 0x58;                           /* Caracter 'X' */
	   	uint8_t attr = 0x0;
	    uint32_t offset_dir_f = (direccion/4)/32;
	    uint32_t cInit = (direccion/4)-(offset_dir_f*32);
		uint32_t fInit = offset_dir_f + OFFSET_FILA;


	    uint32_t cr3_var = rcr3(); 
	   	cr3_var = (cr3_var >> 12)<<12;

	   	jugador_t* jugador = 0x0;
	
		if(jugador_actual == 0){
			jugador = jugador_B;
			attr = COLOR_A;
		    cInit = cInit + OFFSET_COLUMNA_B;
		}else{
			jugador = jugador_A;
			attr = COLOR_B;
			//*((uint32_t*)(dir_fisica+direccion)) = *dato;
			cInit = cInit + OFFSET_COLUMNA_A;
		}
		// Escritura
		uint32_t dir_fisica = (*((*jugador).saltadora)).base_codigo;
		mmu_mapearPagina(dir_fisica, cr3_var, dir_fisica, 1, 1, 1, 1);
		
		*((uint32_t*)(dir_fisica+direccion)) = *dato;
		mmu_unmapearPagina(dir_fisica, cr3_var);
		
		screen_drawBox(fInit, cInit, 1, 1, character, attr);
	}
	else
	{
		// Se pasa de límite. largo excepción.
		int i = 1;
		i = i/i-1;
	}
	return 1;
}

// Coloca lectura en dato encontrado en offset dado por dirección de la tarea saltadora
uint32_t game_leer(uint32_t direccion, uint32_t* dato) {
	//print_hex(direccion, 8, 2, k, 0xf);
	//k++;
	if(direccion >= 0 && direccion < 0x1000)
	{
		direccion = (direccion <<20 )>>20;
		uint8_t character = 0x0;                           /* Caracter '(space)' */
	   	uint8_t attr = 0x0;
	    uint32_t offset_dir_f = (direccion/4)/32;
	    uint32_t cInit = (direccion/4)-(offset_dir_f*32);
		uint32_t fInit = offset_dir_f + OFFSET_FILA;


	    uint32_t cr3_var = rcr3(); 
	   	cr3_var = (cr3_var >> 12)<<12;

	   	jugador_t* jugador = 0x0;
	
		if(jugador_actual == 0){
			jugador = jugador_B;
			attr = COLOR_A;
		    cInit = cInit + OFFSET_COLUMNA_B;
		}else{
			jugador = jugador_A;
			attr = COLOR_B;
			cInit = cInit + OFFSET_COLUMNA_A;
		}
		// Lectura
		uint32_t dir_fisica = (*((*jugador).saltadora)).base_codigo;
		mmu_mapearPagina(dir_fisica, cr3_var, dir_fisica, 1, 1, 1, 1);

		*dato = *((uint32_t*)(dir_fisica+direccion));
		mmu_unmapearPagina(dir_fisica, cr3_var);
		
		screen_drawBox(fInit, cInit, 1, 1, character, attr);
	}
	else
	{
		// Se pasa de límite. largo excepción.
		int i = 1;
		i = i/i-1;
	}
	return 1;
}

// Imprime en pantalla la última eip de la tarea saltadora, en el caso que sea el turno de la misma
void print_saltador(uint32_t eip_tarea){
	if(indice_tarea == 0)
	{
	 	if (eip_tarea >= 0x8000000 && eip_tarea < 0x8001000)
	 	{
			uint32_t offset = (eip_tarea << 20) >> 20;		

	    	uint32_t offset_f = (offset/4)/32;	
	   	 	uint32_t offset_c = (offset/4)-(offset_f*32);
	   	 	offset_f = offset_f + OFFSET_FILA;	
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
		else
		{
			// No debería estar nunca en este lugar, ya que al tratarse de la eip de la tarea, 
			// si no esta entre 0x8000000 y 0x800100 deberia haber page fault.
			int i = 1;
			i = i/i-1;
		}
	}
}

// Se encarga de hacer el mantenimiento en caso de excepcionas, ya sea desalojando una tarea cazadora o quitarle una vida a la saltadora
void mantenimiento_scheduler(){
	if(reestablecer_pausa == 1){
		reestablecer_pausa = 0;
		restaurar_pantalla();
		screen_drawBox(0, 0, 3, 12, 0x4F, (C_BG_BLACK | C_FG_BLACK));
	}
	if(jugador_actual == 0){
		if(indice_tarea == 0){
			if((*jugador_A).cant_vidas == 1){ //si no le quedan vidas
				(*jugador_A).cant_vidas = ((*jugador_A).cant_vidas) - 1;
				print_hex((*jugador_A).cant_vidas, 1, 35, 45, (C_BG_RED | C_FG_WHITE));

				finalizar_juego();
			}else{
				(*jugador_A).cant_vidas = ((*jugador_A).cant_vidas) - 1;
				print_hex((*jugador_A).cant_vidas, 1, 35, 45, (C_BG_RED | C_FG_WHITE));
				remap_saltadora(jugador_A);
			}
		}else{
				tarea_t* tarea_actual = (*jugador_A).ultimo_cazador;
				if( (*tarea_actual).indice == (*((*tarea_actual).anterior)).indice ){
					murio_cazadora((*tarea_actual).indice, jugador_actual);
					finalizar_juego();
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
				finalizar_juego();
			}else{
				(*jugador_B).cant_vidas = ((*jugador_B).cant_vidas) - 1;
				print_hex((*jugador_B).cant_vidas, 1, 43, 45, (C_BG_BLUE | C_FG_WHITE));
				remap_saltadora(jugador_B);
			}
		}else{
			tarea_t* tarea_actual = (*jugador_B).ultimo_cazador;
			if((*tarea_actual).indice == ((*(*tarea_actual).anterior)).indice ){ //si no hay mas cazadoras
				murio_cazadora((*tarea_actual).indice, jugador_actual);
				finalizar_juego();
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

// Restaura pantalla segun lo que estaba puesto en el puntero a ultima_pantalla del scheduller
void restaurar_pantalla(){
	for(int j = 0; j < VIDEO_FILS*VIDEO_COLS; j++)
	{
		((uint16_t*)VIDEO)[j] = ultima_pantalla[j];
	}
} 

// Restaura a la saltadora cuando la saltadora muere, basicamente la reinicia.
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

// Guardo la pantalla previo a imprimir datos pedidos al debuggear.
void debuggear(uint32_t pila){
	// Guardo último pantallaso
	paused = 1;
	for(int j = 0; j < VIDEO_FILS*VIDEO_COLS; j++)
	{
		ultima_pantalla[j] = ((uint16_t*)VIDEO)[j];
	}

	screen_drawBox(2, 25, 36, 30, 0x4F, (C_BG_BLACK | C_FG_BLACK));
	screen_drawBox(3, 26, 34, 28, 0x4F, (C_BG_LIGHT_GREY | C_FG_LIGHT_GREY));

	print((uint8_t*) "eax", 27, 4, (C_BG_LIGHT_GREY | C_FG_BLACK));
	print((uint8_t*) "ebx", 27, 6, (C_BG_LIGHT_GREY | C_FG_BLACK));
	print((uint8_t*) "ecx", 27, 8, (C_BG_LIGHT_GREY | C_FG_BLACK));
	print((uint8_t*) "edx", 27, 10, (C_BG_LIGHT_GREY | C_FG_BLACK));
	print((uint8_t*) "esi", 27, 12, (C_BG_LIGHT_GREY | C_FG_BLACK));
	print((uint8_t*) "edi", 27, 14, (C_BG_LIGHT_GREY | C_FG_BLACK));
	print((uint8_t*) "ebp", 27, 16, (C_BG_LIGHT_GREY | C_FG_BLACK));
	print((uint8_t*) "esp", 27, 18, (C_BG_LIGHT_GREY | C_FG_BLACK));
	print((uint8_t*) "eip", 27, 20, (C_BG_LIGHT_GREY | C_FG_BLACK));
	print((uint8_t*) " cs", 27, 22, (C_BG_LIGHT_GREY | C_FG_BLACK));
	print((uint8_t*) " ds", 27, 24, (C_BG_LIGHT_GREY | C_FG_BLACK));
	print((uint8_t*) " es", 27, 26, (C_BG_LIGHT_GREY | C_FG_BLACK));
	print((uint8_t*) " fs", 27, 28, (C_BG_LIGHT_GREY | C_FG_BLACK));
	print((uint8_t*) " gs", 27, 30, (C_BG_LIGHT_GREY | C_FG_BLACK));
	print((uint8_t*) " ss", 27, 32, (C_BG_LIGHT_GREY | C_FG_BLACK));
	print((uint8_t*) " eflags", 27, 35, (C_BG_LIGHT_GREY | C_FG_BLACK));
	print((uint8_t*) "cr0", 41, 5, (C_BG_LIGHT_GREY | C_FG_BLACK));
	print((uint8_t*) "cr2", 41, 7, (C_BG_LIGHT_GREY | C_FG_BLACK));
	print((uint8_t*) "cr3", 41, 9, (C_BG_LIGHT_GREY | C_FG_BLACK));
	print((uint8_t*) "cr4", 41, 11, (C_BG_LIGHT_GREY | C_FG_BLACK));
	print((uint8_t*) "stack", 41, 22, (C_BG_LIGHT_GREY | C_FG_BLACK));
	
	jugador_t* jugador = 0x0;
	if(jugador_actual == 0){
		jugador = jugador_A;
	}else{
		jugador = jugador_B;
	}
	tarea_t* tarea = 0x0;
	if(indice_tarea == 0){
		tarea = (*jugador).saltadora;
	}else{
		tarea = (*jugador).ultimo_cazador;
	}

	uint32_t indice_tarea = (*tarea).indice_tss;
	uint32_t base_0_15 = (uint32_t)gdt[indice_tarea].base_0_15; 
	uint32_t base_23_16 = (uint32_t)gdt[indice_tarea].base_23_16; 
	uint32_t base_31_24 = (uint32_t)gdt[indice_tarea].base_31_24; 
	// tss_tarea deberia ser la direccion a la tss de la tarea actual, hay q ver si funca.
	tss* tss_tarea = (tss*)((base_31_24<<24)|(base_23_16<<16)|(base_0_15));
	
	uint32_t size_push = 4;
	uint32_t eax = (*(uint32_t*)(pila + (7 * size_push)));
	print_hex(eax, 8, 31, 4, (C_BG_LIGHT_GREY | C_FG_WHITE));
	uint32_t ebx = (*(uint32_t*)(pila + (4 * size_push)));
	print_hex(ebx, 8, 31, 6, (C_BG_LIGHT_GREY | C_FG_WHITE));
	uint32_t ecx = (*(uint32_t*)(pila + (6 * size_push)));
	print_hex(ecx, 8, 31, 8, (C_BG_LIGHT_GREY | C_FG_WHITE));
	uint32_t edx = (*(uint32_t*)(pila + (5 * size_push)));
	print_hex(edx, 8, 31, 10, (C_BG_LIGHT_GREY | C_FG_WHITE));
	uint32_t esi = (*(uint32_t*)(pila + (1 * size_push)));
	print_hex(esi, 8, 31, 12, (C_BG_LIGHT_GREY | C_FG_WHITE));
	uint32_t edi = (*(uint32_t*)(pila + (0 * size_push)));
	print_hex(edi, 8, 31, 14, (C_BG_LIGHT_GREY | C_FG_WHITE));
	uint32_t ebp = (*(uint32_t*)(pila + (2 * size_push)));
	print_hex(ebp, 8, 31, 16, (C_BG_LIGHT_GREY | C_FG_WHITE));
	uint32_t esp = (*(uint32_t*)(pila + (12 * size_push)));
	print_hex(esp, 8, 31, 18, (C_BG_LIGHT_GREY | C_FG_WHITE));
	uint32_t eip = (*(uint32_t*)(pila + (9 * size_push)));
	print_hex(eip, 8, 31, 20, (C_BG_LIGHT_GREY | C_FG_WHITE));
	uint32_t cs = (*(uint32_t*)(pila + (10 * size_push)));
	print_hex(cs, 4, 31, 22, (C_BG_LIGHT_GREY | C_FG_WHITE));
	uint32_t ds = (uint32_t)(*tss_tarea).ds;
	print_hex(ds, 4, 31, 24, (C_BG_LIGHT_GREY | C_FG_WHITE));
	uint32_t es = (uint32_t)(*tss_tarea).es;
	print_hex(es, 4, 31, 26, (C_BG_LIGHT_GREY | C_FG_WHITE));
	uint32_t fs = (uint32_t)(*tss_tarea).fs;
	print_hex(fs, 4, 31, 28, (C_BG_LIGHT_GREY | C_FG_WHITE));
	uint32_t gs = (uint32_t)(*tss_tarea).gs;
	print_hex(gs, 4, 31, 30, (C_BG_LIGHT_GREY | C_FG_WHITE));
	uint32_t ss = (*(uint32_t*)(pila + (13 * size_push)));
	print_hex(ss, 4, 31, 32, (C_BG_LIGHT_GREY | C_FG_WHITE));
	uint32_t eflags = (*(uint32_t*)(pila + (11 * size_push)));
	print_hex(eflags, 8, 34, 35, (C_BG_LIGHT_GREY | C_FG_WHITE));
	uint32_t cr0 = rcr0();
	print_hex(cr0, 8, 45, 5, (C_BG_LIGHT_GREY | C_FG_WHITE));
	uint32_t cr2 = rcr2();
	print_hex(cr2, 8, 45, 7, (C_BG_LIGHT_GREY | C_FG_WHITE));
	uint32_t cr3 = (*tss_tarea).cr3;
	print_hex(cr3, 8, 45, 9, (C_BG_LIGHT_GREY | C_FG_WHITE));
	uint32_t cr4 = rcr4();
	print_hex(cr4, 8, 45, 11, (C_BG_LIGHT_GREY | C_FG_WHITE));

	// Casos borde, pila lvl 3.
	if(esp < 0x8001000 - 4)
		print_hex((*((uint32_t*)esp)), 8, 41, 25, (C_BG_LIGHT_GREY | C_FG_WHITE));
	if(esp < 0x8001000 - 8)
		print_hex((*((uint32_t*)(esp + 4))), 8, 41, 26, (C_BG_LIGHT_GREY | C_FG_WHITE));
	if(esp < 0x8001000 - 12)
		print_hex((*((uint32_t*)(esp + 8))), 8, 41, 27, (C_BG_LIGHT_GREY | C_FG_WHITE));
	if(esp < 0x8001000 - 16)	
		print_hex((*((uint32_t*)(esp + 12))), 8, 41, 28, (C_BG_LIGHT_GREY | C_FG_WHITE));

}

void resetear_juego(){
	__asm __volatile("cli");

	mapa_de_juego();
	inicializar_sched();
	game_inicializar();
	__asm __volatile("sti");

}

// Actualizo en pantalla el clock de la tarea actual, y en estructura de scheduller.
void actualizar_clock_tarea(){
	uint32_t offset_f = 46;
	uint32_t offset_c = 15;
	uint8_t attr = (C_BG_BLACK | C_FG_WHITE); 
	jugador_t* jugador = 0;
	uint8_t indice_reloj_tarea = 0;
	if(jugador_actual == 0){
		jugador = jugador_A;
	}else{
		jugador = jugador_B;
		offset_c = offset_c + 37;
	}
	if(indice_tarea == 0){
		indice_reloj_tarea = (*(*jugador).saltadora).indice_reloj;
		(*(*jugador).saltadora).indice_reloj = (indice_reloj_tarea + 1) % 4;
	}else{
		indice_reloj_tarea = (*(*jugador).ultimo_cazador).indice_reloj;
		(*(*jugador).ultimo_cazador).indice_reloj = (indice_reloj_tarea + 1) % 4;
		offset_c = offset_c + ((*(*jugador).ultimo_cazador).indice*2);
	}
	uint32_t text = caracteres_reloj[indice_reloj_tarea];
	screen_drawBox(offset_f, offset_c, 1, 1, text, attr);
}

// Imprime botón de MODO DEBUG, y actualiza la pausa si se cumplen la clausulas.
void actulizar_debugging(uint8_t scanCode){
	if(scanCode == 0x15){
		if(debugging == 0){
			debugging = 1;
			screen_drawBox(0, 0, 3, 12, 0x4F, (C_BG_LIGHT_GREY | C_FG_LIGHT_GREY));
			print((uint8_t*) " MODO DEBUG", 0, 1, (C_BG_LIGHT_GREY | C_FG_BLACK));
		}else{
			if(paused == 1){
				paused = 0;
				reestablecer_pausa = 1;
			}
			debugging = 0;
			screen_drawBox(0, 0, 3, 12, 0x4F, (C_BG_BLACK | C_FG_BLACK));
		}
	}
}

// Imprime un cartelito segun el ganador y entra en un loop infinito.
void finalizar_juego(){
	screen_drawBox(20, 31, 7, 16, 0x4F, (C_BG_BROWN | C_FG_BROWN));
	print((uint8_t*) " GAME OVER!", 33, 22, (C_BG_BROWN | C_FG_WHITE));
	if(jugador_actual == 0)
	{
		print((uint8_t*) " PLAYER 2 WON!", 32, 24, (C_BLINK | C_BG_BROWN | C_FG_BLUE));
	}
	else
	{
		print((uint8_t*) " PLAYER 1 WON!", 32, 24, (C_BLINK | C_BG_BROWN | C_FG_RED));
	}
	while(1){}
}