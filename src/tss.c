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
	gdt[GDT_IDX_INITIAL_TASK].base_0_15 = (uint32_t) &tss_inicial;
	gdt[GDT_IDX_INITIAL_TASK].base_23_16 = (uint32_t) &tss_inicial >> 16;
	gdt[GDT_IDX_INITIAL_TASK].base_31_24 = (uint32_t) &tss_inicial >> 24;
	gdt[GDT_IDX_INITIAL_TASK].p = 1;
}

void tss_inicializar_idle()
{
	uint32_t proxima_pag = mmu_prox_pag_fisica_libre_kernel();
	tss_idle = (tss)
	{
		.esp0 = mmu_prox_pag_fisica_libre_kernel() + 4096,
		.ss0 = 0xb0,
		.cr3 = (uint32_t)kernel_page_directory,
		.eflags = 0x202, //0x202
		.esp = proxima_pag + 4096,
		.ebp = proxima_pag + 4096,
		.eip = 0x14000,
		.ss = 0xb0,
		.es = 0xb0,
		.cs = 0xa0,
		.ds = 0xb0,
		.fs = 0xb0,
		.gs = 0xb0,
		.iomap = 0xffff
	};

	gdt[GDT_IDX_IDLE_TASK].base_0_15 = (uint32_t) &tss_idle;
	gdt[GDT_IDX_IDLE_TASK].base_23_16 = (uint32_t) &tss_idle >> 16;
	gdt[GDT_IDX_IDLE_TASK].base_31_24 = (uint32_t) &tss_idle >> 24;
	gdt[GDT_IDX_IDLE_TASK].p = 1;
}

uint32_t tss_nueva_tarea(uint32_t tipo, uint32_t* dir_fisica_codigo)
{
	uint32_t inicio_tarea;

	if(tipo == 0)
	{
		inicio_tarea = 0x10000;
	}
	if(tipo == 1)
	{
		inicio_tarea = 0x11000;
	}
	if(tipo == 2)
	{
		inicio_tarea = 0x12000;
	}
	if(tipo == 3)
	{
		inicio_tarea = 0x13000;
	}

	uint32_t dir = mmu_inicializar_dir_tarea((uint8_t*)inicio_tarea);
	dir_fisica_codigo = (uint32_t*) inicio_tarea; // inicio tarea es un puntero a la memoria fisica del nuevo codigo
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

	uint32_t indice_tarea = prox_entrada_libre_gdt();

	gdt[indice_tarea].base_0_15 = (uint32_t) &tss_tarea;
	gdt[indice_tarea].base_23_16 = (uint32_t) &tss_tarea >> 16;
	gdt[indice_tarea].base_31_24 = (uint32_t) &tss_tarea >> 24;
	gdt[indice_tarea].p = 1;
	gdt[indice_tarea].limit_0_15 = 0x67;
	gdt[indice_tarea].type = 0x9;
	gdt[indice_tarea].dpl = 0x3;
	gdt[indice_tarea].db = 0x1;
	return indice_tarea;
}
