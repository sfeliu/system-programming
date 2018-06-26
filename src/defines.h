/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

    Definiciones globales del sistema.
*/

#ifndef __DEFINES_H__
#define __DEFINES_H__

/* Bool */
/* -------------------------------------------------------------------------- */
#define TRUE                    0x00000001
#define FALSE                   0x00000000
#define ERROR                   1

/* Atributos paginas */
/* -------------------------------------------------------------------------- */
#define PAG_P                   0x00000001
#define PAG_R                   0x00000000
#define PAG_RW                  0x00000002
#define PAG_S                   0x00000000
#define PAG_US                  0x00000004

/* Misc */
/* -------------------------------------------------------------------------- */
#define MAX_VIDAS               5
#define NULL                    0x0

/* Indices en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_COUNT 30

#define GDT_IDX_NULL_DESC           0
#define GDT_IDX_INITIAL_TASK        1
#define GDT_IDX_IDLE_TASK           2
#define GDT_IDX_CODE_LVL_0          20
#define GDT_IDX_CODE_LVL_3          21
#define GDT_IDX_DATA_LVL_0          22
#define GDT_IDX_DATA_LVL_3          23
#define GDT_IDX_VIDEO_DATA          24

/* Offsets en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_OFF_NULL_DESC           (GDT_IDX_NULL_DESC      << 3)

/* Direcciones de memoria */
/* -------------------------------------------------------------------------- */
#define BOOTSECTOR              0x00001000 /* direccion fisica de comienzo del bootsector (copiado) */
#define KERNEL                  0x00001200 /* direccion fisica de comienzo del kernel */
#define VIDEO                   0x000B8000 /* direccion fisica del buffer de video */
#define AREA_LIBRE_KERNEL		0x00100000 /* direccion fisica del comienzo del area libre del kernel*/
#define AREA_LIBRE_TAREAS		0x00400000 /* direccion fisica del comienzo del area libre de tareas*/

/* Definiciones pantalla */
/* -------------------------------------------------------------------------- */
#define VIDEO_FILS 50
#define VIDEO_COLS 80
#define OFFSET_FILA		        5  /* Posición en la que arranca la fila de la pantalla de ambos jugadores */
#define OFFSET_COLUMNA_A        5  /* Posición en la que arranca la columna de la pantalla de jugador A */
#define OFFSET_COLUMNA_B        42 /* Posición en la que arranca la columna de la pantalla de jugador B */
#define COLOR_A					(C_BG_RED | C_FG_WHITE) /* Fondo negro y caracter blanco */    
#define COLOR_B		   			(C_BG_BLUE | C_FG_WHITE) /* Fondo negro y caracter blanco */ 

/* Colores de pantalla */
/* -------------------------------------------------------------------------- */
#define NEGRO              		0x0 /* Caracter | 4 << FONDO */
#define AZUL              		0x1 /* Caracter | 4 << FONDO */
#define VERDE              		0x2 /* Caracter | 4 << FONDO */
#define CYAN              		0x3 /* Caracter | 4 << FONDO */
#define ROJO              		0x4 /* Caracter | 4 << FONDO */
#define MAGENTA              	0x5 /* Caracter | 4 << FONDO */
#define MARRON            		0x6 /* Caracter | 4 << FONDO */
#define GRIS_CLARO             	0x7 /* Caracter | 4 << FONDO */
#define GRIS              		0x8 /* Caracter | 4 << FONDO */
#define CELESTE            		0x9 /* Caracter | 4 << FONDO */
#define VERDE_CLARO             0xA /* Caracter | 4 << FONDO */
#define CYAN_CLARO              0xB /* Caracter | 4 << FONDO */
#define ROJO_CLARO              0xC /* Caracter | 4 << FONDO */
#define MAGENTA_CLARO         	0xD /* Caracter | 4 << FONDO */
#define AMARILLO              	0xE /* Caracter | 4 << FONDO */
#define BLANCO               	0xF /* Caracter | 4 << FONDO */


#endif  /* !__DEFINES_H__ */
