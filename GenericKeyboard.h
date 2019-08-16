#include <termios.h> // struct termios and macros
#include <unistd.h>   // tcgetattr(), tcsetattr()
#include <cstdio>     // getchar()

#define KBACKSPACE 0x0007F
#define KESC              0x0001B
#define KTAB               0x00009
#define KSPACE          0x00020
#define KENTER          0x0000A

#define KDELETE    0x4426F

#define KLEFT      0x44280
#define KUP        0x4427D
#define KRIGHT     0x4427F
#define KDOWN      0x4427E

#ifndef _HANOI_GENERICKEYBOARD_H_
#define _HANOI_GENERICKEYBOARD_H_

class GenericKeyboard{
public:
    int keyhit(bool special_key);
};

#endif //_HANOI_GENERICKEYBOARD_H_

/**
* @description Lê o caracter pressionada sem bloqueio
* @author Welverton Rodrigues
*/
int GenericKeyboard::keyhit(bool special_key) {

    termios oldt, newt; /// retorna imediatamente o código após uma tecla ser pressionada..
    int key;            /// se existir, ou -1 se nada foi pressionado (não há bloqueio)

    tcgetattr(STDIN_FILENO, &oldt); // salva as configurações atuais

    newt = oldt; // faz uma cópia das configurações antigas

    //newt.c_lflag &= ~ICANON;  // desabilita o modo canónico

    //TODO Desabilitando echo
    newt.c_lflag &= ~(ICANON | ECHO); // desabilita o modo canónico e o echo

    newt.c_cc[VTIME] = 0; // sem espera indefinida..
    newt.c_cc[VMIN] = 1;// que um byte seja lido

    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // habilita as novas configurações

    key = (int)getchar();

    if (special_key && key == KESC) { // pode ser uma sequência de escape!!!

        for (int k; (k = (int)getchar()) != -1; key = key*100 + k); // gera o código de escape

        if (key != KESC) { // eh sequência de escape!!!
            switch (key) {
                case 0x1A9F3DA: key = KDELETE; break;  // obs.: está incompleto!!!
                case 0x0043DCD: key = KUP;     break;  // falta verificar outras..
                case 0x0043DCE: key = KDOWN;   break;  // sequências de escape
                case 0x0043DCF: key = KRIGHT;  break;
                case 0x0043DD0: key = KLEFT;   break;
            }
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restaura as configuraçõeses antigas

    return key;
}
