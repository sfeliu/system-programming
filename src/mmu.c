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
	kernel_page_directory = (directory_entry_t*)0x27000;
	table_entry_t* page_table = (table_entry_t*) 0x28000;

	for(int i = 0; i < 1024; i++)
	{
		kernel_page_directory[i].p = 0;

		page_table[i] = (table_entry_t)
		{
			.p = 1,
			.r_w = 1,
			.us = 0,
			.pwt = 0,
			.psv = 0,
			.a = 0,
			.d = 0,
			.pat = 0,
			.g = 0,
			.ignored = 0,
			.dir_memory = i
		};
	}

	kernel_page_directory[0] = (directory_entry_t)
	{
		.p = 1,
		.r_w = 1,
		.us = 0,
		.pwt = 0,
		.pcd = 0,
		.a = 0,
		.ignored1 = 0,
		.ps = 0,
		.ignored4 = 0,
		.dir_page = 0x28
	};
}

// void mmu_inicializar_dir_tarea()
// {
// 	directory_entry_t* tarea_page_directory = (directory_entry_t*) FISICA0;
// 	table_entry_t* page_table = (table_entry_t*) FISICA1;
//
// 	for(int i = 0; i < 1024; i++)
// 	{
// 		tarea_page_directory[i].p = 0;
//
// 		page_table[i] =
// 		{
// 			.p = 1,
// 			.r_w = 1,
// 			.us = 0,
// 			.pwt = 0,
// 			.psv = 0,
// 			.a = 0,
// 			.d = 0,
// 			.pat = 0,
// 			.g = 0,
// 			.ignored = 0,
// 			.dir_memory = i
// 		};
// 	}
//
// 	tarea_page_directory[0] =
// 	{
// 		.p = 1,
// 		.r_w = 1,
// 		.us = 0,
// 		.pwt = 0,
// 		.pcd = 0,
// 		.a = 0,
// 		.ignored1 = 0,
// 		.ps = 0,
// 		.ignored4 = 0,
// 		.dir_page = FIS
// 	};
// }
