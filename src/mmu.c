/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"

void mmu_inicializar()
{
	prox_pag_libre_kernel = AREA_LIBRE_KERNEL;
	prox_pag_libre_tarea = AREA_LIBRE_TAREAS;
}

void mmu_inicializar_dir_kernel()
{
	kernel_page_directory = (directory_entry_t*) 0x27000;
	table_entry_t* page_table = (table_entry_t*) 0x28000;

	int j = 0;

	for(int i = 0; i < 1024; i++)
	{
		kernel_page_directory[i].p = 0;

		page_table[i] = (table_entry_t)
		{
			.p = 1,
			.rw = 1,
			.us = 0,
			.pwt = 0,
			.psv = 0,
			.a = 0,
			.d = 0,
			.pat = 0,
			.g = 0,
			.ignored = 0,
			.dir_memory = i + 1024*j
		};
	}

	kernel_page_directory[j] = (directory_entry_t)
	{
		.p = 1,
		.rw = 1,
		.us = 0,
		.pwt = 0,
		.pcd = 0,
		.a = 0,
		.ignored1 = 0,
		.ps = 0,
		.ignored4 = 0,
		.dir_table = 0x28
	};
}

uint32_t mmu_inicializar_dir_tarea(uint8_t* codigo, uint32_t* dir_fisica_codigo)
{
	directory_entry_t* tarea_page_directory = (directory_entry_t*) mmu_prox_pag_fisica_libre_kernel();

	int j = 0;
	for(int i = 0; i < 1024; i++)
	{
		tarea_page_directory[i].p = 0;
	}

	tarea_page_directory[j] = (directory_entry_t)
	{
		.p = 1,
		.rw = 1,
		.us = 0,
		.pwt = 0,
		.pcd = 0,
		.a = 0,
		.ignored1 = 0,
		.ps = 0,
		.ignored4 = 0,
		.dir_table = 0x28 			//page table identity mapping kernel.
	};

	uint8_t rw = 1;
	uint8_t us = 1;
	uint32_t prox_pag_fisica = mmu_prox_pag_fisica_libre_kernel();
	mmu_mapearPagina((uint32_t)(0x8000000), (uint32_t)tarea_page_directory, prox_pag_fisica, rw, rw, us, us);

	if(codigo == 0) return (uint32_t)tarea_page_directory;

	uint8_t* guardarAca = (uint8_t*)prox_pag_fisica;
	for(int j = 0; j < 4096; j++)
	{
		guardarAca[j] = codigo[j];
	}
	*dir_fisica_codigo = prox_pag_fisica; // puntero a codigo modificado para poder tener la nueva base del codigo.	

	return (uint32_t)tarea_page_directory;
}

uint32_t mmu_prox_pag_fisica_libre_kernel()
{
	uint32_t temp = prox_pag_libre_kernel;
	prox_pag_libre_kernel += 4096;
	return temp;
}

uint32_t mmu_prox_pag_fisica_libre_tarea()
{
	uint32_t temp = prox_pag_libre_tarea;
	prox_pag_libre_tarea += 4096;
	return temp;
}

void mmu_mapearPagina(uint32_t virtual, uint32_t cr3, uint32_t fisica, uint8_t rw_d, uint8_t rw_tab, uint8_t us_d, uint8_t us_tab)
{
	uint32_t i_dir = virtual >> 22;
	uint32_t i_tab = (virtual << 10) >> 22;

    directory_entry_t* directory = (directory_entry_t*) cr3;
	if(directory[i_dir].p == 0)
	{
		directory[i_dir].p = 1;
		directory[i_dir].rw = rw_d;
		directory[i_dir].us = us_d;
		directory[i_dir].dir_table = mmu_prox_pag_fisica_libre_kernel() >> 12;
	}

	table_entry_t* table = (table_entry_t*) (directory[i_dir].dir_table << 12);
	table[i_tab].dir_memory = fisica >> 12;
	table[i_tab].p = 1;
	table[i_tab].rw = rw_tab;
	table[i_tab].us = us_tab;
}

void mmu_unmapearPagina(uint32_t virtual, uint32_t cr3)
{
	uint32_t i_dir = virtual >> 22;
	uint32_t i_tab = (virtual << 10) >> 22;

    directory_entry_t* directory = (directory_entry_t*) cr3;
	if(directory[i_dir].p == 0)
	{
		return;
	}

	table_entry_t* table = (table_entry_t*) (directory[i_dir].dir_table << 12);
	table[i_tab].p = 0;
}
