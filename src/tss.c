/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"

tss tss_inicial;
tss tss_idle;

void tss_inicializar()
{
	uint32_t proxima_pag = mmu_prox_pag_fisica_libre_kernel(),
	tss_idle = (tss)
	{
		.esp0 = mmu_prox_pag_fisica_libre_kernel(),
		.ss0 = 0xb0,
		.cr3 = &kernel_page_directory,
		.eflags = 0x2,
		.esp = proxima_pag,
		.ebp = proxima_pag,
		.eip = 0x14000,
		.ss = 0xb0,
		.es = 0xb0,
		.cs = 0xa0,
		.ds = 0xb0,
		.fs = 0xb0,
		.gs = 0xb0
	};

	uint32_t proxima_pag = prox_pag_libre_tarea();
	tss_inicial = (tss)
	{
		.esp0 = mmu_prox_pag_fisica_libre_kernel(),
		.ss0 = 0xb0,
		.cr3 = mmu_inicializar_dir_tarea(0),
		.eflags = 0x2,
		.esp = mmu_mapearPagina(0x8000+4096, .cr3, proxima_pag, 1, 1, 0, 0),
		.ebp = .esp,
		.eip = 0x08000000,
		.ss = 0xb8,
		.es = 0xb8,
		.cs = 0xa8,
		.ds = 0xb8,
		.fs = 0xb8,
		.gs = 0xb8
	};
}

void tss_nueva_tarea()
{

}
