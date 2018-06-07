/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"

tss tss_inicial;
tss tss_idle;

void tss_inicializar(uint32_t eip_inicial)
{
	uint32_t proxima_pag = mmu_prox_pag_fisica_libre_kernel();
	tss_idle = (tss)
	{
		.esp0 = mmu_prox_pag_fisica_libre_kernel(),
		.ss0 = 0xb0,
		.cr3 = (uint32_t) kernel_page_directory,
		.eflags = 0x202,
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

	gdt[GDT_IDX_IDLE_TASK].base_0_15 = (uint32_t) &tss_idle;
	gdt[GDT_IDX_IDLE_TASK].base_23_16 = (uint32_t) &tss_idle >> 16;
	gdt[GDT_IDX_IDLE_TASK].base_31_24 = (uint32_t) &tss_idle >> 24;
	gdt[GDT_IDX_IDLE_TASK].p = 1;
	
	//proxima_pag = mmu_prox_pag_fisica_libre_tarea();
	//uint32_t cr3_inicial = mmu_inicializar_dir_tarea(0);
	//mmu_mapearPagina(0x8000+4096, cr3_inicial, proxima_pag, 1, 1, 0, 0);
	tss_inicial = (tss)
	{
		.esp0 = mmu_prox_pag_fisica_libre_kernel(),
		.ss0 = 0xb0,
		.cr3 = (uint32_t) kernel_page_directory,
		.eflags = 0x2,
		.esp = eip_inicial,
		.ebp = eip_inicial,
		.eip = eip_inicial,
		.ss = 0xb8,
		.es = 0xb8,
		.cs = 0xa8,
		.ds = 0xb8,
		.fs = 0xb8,
		.gs = 0xb8
	};


	gdt[GDT_IDX_INITIAL_TASK].base_0_15 = (uint32_t) &tss_inicial;
	gdt[GDT_IDX_INITIAL_TASK].base_23_16 = (uint32_t) &tss_inicial >> 16;
	gdt[GDT_IDX_INITIAL_TASK].base_31_24 = (uint32_t) &tss_inicial >> 24;
	gdt[GDT_IDX_INITIAL_TASK].p = 1;

}

void tss_nueva_tarea()
{

}
