#ifndef cores_H
#define cores_H

#define white al_map_rgb(255,255,255) //branco
#define gray al_map_rgb(128,128,128)  //cinza
#define black al_map_rgb(0,0,0)       //preto

#define purple al_map_rgb(128,0,128)  //roxo
#define crimson al_map_rgb(220,20,60) //vermelho vibrante
#define deepskyblue al_map_rgb(0,191,255)    //azul claro
#define lightgreen al_map_rgb(30,235,35)
#define lightseagreen al_map_rgb(32,178,170) //verde claro
#define gold al_map_rgb(255,215,0)           // cor ouro | dourado

//paleta de cores 1

#define charlestongreen al_map_rgb(48, 41, 47)  //marrom
#define arsenic al_map_rgb(63, 64, 69) //cinza
#define outerspace al_map_rgb(65, 63, 84)    //azul acinzentado
#define lighttaupe al_map_rgb(175, 145, 100) // creme
#define linen al_map_rgb(247, 243, 227) //la

//paleta de cores para fontes

#define aeroblue al_map_rgb(208, 254, 245)  //azul clarinho
#define smokyblack al_map_rgb(7, 7, 7) //quase preto
#define darkscarlet al_map_rgb(74, 5, 28)    //vermelho escuro
#define smokyblackgreen al_map_rgb(12, 18, 12) // verde escuro
#define teagreen al_map_rgb(211, 249, 181) //verde claro

//paleta full
#define red al_map_rgb(255, 0, 0)  //vermelho
#define green al_map_rgb(0, 255, 0)
#define blue al_map_rgb(0, 0, 255)

// testes

#define cinzafundo al_map_rgb(83,84,89)

// outros defines

#define al_text(cor,x,y,texto) al_draw_text(serifa_light_m,cor,x,y,NULL,texto)

#endif //cores_H
