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

/* Indices en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_COUNT 30

#define GDT_IDX_NULL_DESC           0
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
