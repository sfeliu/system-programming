/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "screen.h"

void print(const uint8_t* text, uint32_t x, uint32_t y, uint16_t attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO; // magia
    int32_t i;
    for (i = 0; text[i] != 0; i++) {
        p[y][x].c = (uint8_t) text[i];
        p[y][x].a = (uint8_t) attr;
        x++;
        if (x == VIDEO_COLS) {
            x = 0;
            y++;
        }
    }
}

void print_dec(uint32_t numero, uint32_t size, uint32_t x, uint32_t y, uint16_t attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO; // magia
    uint32_t i;
    uint8_t letras[16] = "0123456789";

    for(i = 0; i < size; i++) {
        uint32_t resto  = numero % 10;
        numero = numero / 10;
        p[y][x + size - i - 1].c = letras[resto];
        p[y][x + size - i - 1].a = attr;
    }
}

void print_hex(uint32_t numero, int32_t size, uint32_t x, uint32_t y, uint16_t attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO; // magia
    int32_t i;
    uint8_t hexa[8];
    uint8_t letras[16] = "0123456789ABCDEF";
    hexa[0] = letras[ ( numero & 0x0000000F ) >> 0  ];
    hexa[1] = letras[ ( numero & 0x000000F0 ) >> 4  ];
    hexa[2] = letras[ ( numero & 0x00000F00 ) >> 8  ];
    hexa[3] = letras[ ( numero & 0x0000F000 ) >> 12 ];
    hexa[4] = letras[ ( numero & 0x000F0000 ) >> 16 ];
    hexa[5] = letras[ ( numero & 0x00F00000 ) >> 20 ];
    hexa[6] = letras[ ( numero & 0x0F000000 ) >> 24 ];
    hexa[7] = letras[ ( numero & 0xF0000000 ) >> 28 ];
    for(i = 0; i < size; i++) {
        p[y][x + size - i - 1].c = hexa[i];
        p[y][x + size - i - 1].a = attr;
    }
}

void screen_drawBox(uint32_t fInit,
                    uint32_t cInit,
                    uint32_t fSize,
                    uint32_t cSize,
                    uint8_t character,
                    uint8_t attr ) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
    uint32_t f;
    uint32_t c;
    for (f = fInit; f < fInit+fSize; f++) {
    for (c = cInit; c < cInit+cSize; c++) {
          p[f][c].c = character;
          p[f][c].a = attr;
    }}
}


void black_out_screen(){
    uint8_t character = 0x30;                           /* Caracter '0' */
    uint8_t attr = (C_BG_BLACK | C_FG_BLACK);                /* Fondo negro y caracter negro */
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) 0x0;
    for (int f = 0; f < VIDEO_FILS; f++) {
    for (int c = 0; c < VIDEO_COLS; c++) {
        p[f][c].c = character;
        p[f][c].a = attr;
    }}
}

void imprimirTecla(uint8_t scanCode){
    uint16_t attr = 0x0F;
    if(scanCode == 0x2) print((uint8_t*) "1", 79, 0, attr);
    if(scanCode == 0x3) print((uint8_t*) "2", 79, 0, attr);
    if(scanCode == 0x4) print((uint8_t*) "3", 79, 0, attr);
    if(scanCode == 0x5) print((uint8_t*) "4", 79, 0, attr);
    if(scanCode == 0x6) print((uint8_t*) "5", 79, 0, attr);
    if(scanCode == 0x7) print((uint8_t*) "6", 79, 0, attr);
    if(scanCode == 0x8) print((uint8_t*) "7", 79, 0, attr);
    if(scanCode == 0x9) print((uint8_t*) "8", 79, 0, attr);
    if(scanCode == 0xA) print((uint8_t*) "9", 79, 0, attr);
    if(scanCode == 0xB) print((uint8_t*) "0", 79, 0, attr);
}


