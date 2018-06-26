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

void murio_cazadora(uint8_t indice_tarea, uint8_t jugador){
    uint8_t character1 = 0x78;                           /* Caracter '0' */
    uint8_t attr = (C_BG_BLACK | C_FG_RED);           /* Fondo negro y caracter blanco */
    uint32_t offset_jugador_A = 0;
    uint32_t offset_jugador_B =37 ;
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
    indice_tarea = ((uint32_t)indice_tarea)*2;
    if(jugador == 1){
        p[46][15+(indice_tarea) + offset_jugador_B].c = character1;
        p[46][15+(indice_tarea) + offset_jugador_B].a = attr;

    }else{
        p[46][15+(indice_tarea) + offset_jugador_A].c = character1;
        p[46][15+(indice_tarea) + offset_jugador_A].a = attr;
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

void mapa_de_juego(){
    uint8_t character1 = 0x30;                           /* Caracter '0' */
    uint8_t character2 = 0x41;                           /* Caracter 'A' */
    uint8_t character3 = 0x76;                           /* Caracter 'v' */
    uint8_t character4 = 0x69;                           /* Caracter 'i' */
    uint8_t character5 = 0x64;                           /* Caracter 'd' */
    uint8_t character6 = 0x61;                           /* Caracter 'a' */
    uint8_t character7 = 0x73;                           /* Caracter 's' */
    uint8_t attr1 = (C_BG_BLACK | C_FG_BLACK);           /* Fondo negro y caracter negro */
    uint8_t attr2 = (C_BG_GREEN | C_FG_GREEN);           /* Fondo verde y caracter verde */
    uint8_t attr3 = (C_BG_BLACK | C_FG_WHITE);           /* Fondo negro y caracter blanco */
    uint8_t attr4 = (C_BG_RED | C_FG_RED);           /* Fondo negro y caracter blanco */    
    uint8_t attr5 = (C_BG_BLUE | C_FG_BLUE);           /* Fondo negro y caracter blanco */    
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) 0x0;
    uint8_t m = 0;
    uint8_t n = 0;
    for (int f = 0; f < VIDEO_FILS; f++) {
        for (int c = 0; c < VIDEO_COLS; c++) {
            if(5<=f && f<=36 && ((5<=c && c<=36) || (42<=c && c<=73)) ){
                p[f][c].c = character1;
                p[f][c].a = attr2;
            }else
            if((44<=f && f<=46) && (34<=c && c<=36)){
                p[f][c].c = character1;
                p[f][c].a = attr4;
            }else
            if((44<=f && f<=46) && (42<=c && c<=44)){
                p[f][c].c = character1;
                p[f][c].a = attr5;
            }else{
                p[f][c].c = character1;
                p[f][c].a = attr1;
            }
        }
    }
    for(int c=15; c<=24;c++){      //tareas
        if((c%2) == 1){
            p[44][c].c = character1 + m;
            p[44][c].a = attr3;
            p[44][c+37].c = character1 + m;
            p[44][c+37].a = attr3;
            m++;
        }else{
            p[44][c+1].c = character1;
            p[44][c+1].a = attr1;
            p[44][c+38].c = character1;
            p[44][c+38].a = attr1;
        }
    }
    m = 0;
    for (int f = 5; f < 37; f++) {
        if(f<=14 || (f>=21 && f<= 30)){
            p[f][3].c = character1 + m;
            p[f][3].a = attr3;
            p[f][40].c = character1 + m;
            p[f][40].a = attr3;
            m++;
            if(f == 14 || f == 30){m=0;}
        }else{
            p[f][3].c = character2 + m;
            p[f][3].a = attr3;
            p[f][40].c = character2 + m;
            p[f][40].a = attr3;
            m++;
            if(f == 20){m=0;}
        }
    }
    for (int c = 5; c < 37; c++) {
        if(c<=14 || (c>=21 && c<=30)){
            p[3][c].c = character1 + n;
            p[3][c].a = attr3;
            p[3][c+37].c = character1 + n;
            p[3][c+37].a = attr3;
            n++;
            if(c == 14 || c == 30){n=0;}
        }else{
            p[3][c].c = character2 + n;
            p[3][c].a = attr3;
            p[3][c+37].c = character2 + n;
            p[3][c+37].a = attr3;
            n++;
            if(c == 20){n=0;}
        } 
    }
    p[42][33].c = character3;
    p[42][33].a = attr3;
    p[42][33+8].c = character3;
    p[42][33+8].a = attr3;
    p[42][34].c = character4;
    p[42][34].a = attr3;
    p[42][34+8].c = character4;
    p[42][34+8].a = attr3;
    p[42][35].c = character5;
    p[42][35].a = attr3;
    p[42][35+8].c = character5;
    p[42][35+8].a = attr3;
    p[42][36].c = character6;
    p[42][36].a = attr3;
    p[42][36+8].c = character6;
    p[42][36+8].a = attr3;
    p[42][37].c = character7;
    p[42][37].a = attr3;
    p[42][37+8].c = character7;
    p[42][37+8].a = attr3;

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


