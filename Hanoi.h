//
// Created by Vinícius Montanheiro on 23/03/15.
//

#include "Stack.h"

#ifndef _HANOI_HANOI_H_
#define _HANOI_HANOI_H_

class Hanoi {
private:
    int topo;
    Stack<int> primeiroPino;
    Stack<int> segundoPino;
    Stack<int> terceiroPino;
    int movimentos;
    int discos;
public:
    Hanoi(int discos, int topo, int movimentos);

    string estilo[9];

    void setTopo(int topo);

    int getTopo() const;

    void setDiscos(int discos);

    int getDiscos() const;

    void setPrimeiroPino(Stack<int> primeiroPino);

    Stack<int> getPrimeiroPino() const;

    void setSegundoPino(Stack<int> segundoPino);

    Stack<int> getSegundoPino() const;

    void setTerceiroPino(Stack<int> terceiroPino);

    Stack<int> getTerceiroPino() const;

    void setMovimentos(int movimentos);

    int getMovimentos() const;
};

#endif //_HANOI_HANOI_H_

Hanoi::Hanoi(int discos, int topo,int movimentos) : discos(discos), topo(topo), movimentos(movimentos){
    this->topo = 0;
    this->estilo[0] = "       ||       ";
    this->estilo[1] = "      (##)      ";
    this->estilo[2] = "     (####)     ";
    this->estilo[3] = "    (######)    ";
    this->estilo[4] = "   (########)   ";
    this->estilo[5] = "  (##########)  ";
    this->estilo[6] = " (############) ";
    this->estilo[7] = "(##############)";
}

void Hanoi::setTopo(int topo) {
    this->topo = topo;
}

int Hanoi::getTopo() const {
    return this->topo;
}

void Hanoi::setDiscos(int discos) {
    this->discos = discos;
}

int Hanoi::getDiscos() const {
    return this->discos;
}

void Hanoi::setPrimeiroPino(Stack<int> primeiroPino) {
    this->primeiroPino = primeiroPino;
}

Stack<int> Hanoi::getPrimeiroPino() const {
    return this->primeiroPino;
}

void Hanoi::setSegundoPino(Stack<int> segundoPino) {
    this->segundoPino = segundoPino;
}

Stack<int> Hanoi::getSegundoPino() const {
    return this->segundoPino;
}

void Hanoi::setTerceiroPino(Stack<int> terceiroPino) {
    this->terceiroPino = terceiroPino;
}

Stack<int> Hanoi::getTerceiroPino() const {
    return this->terceiroPino;
}

void Hanoi::setMovimentos(int movimentos) {
    this->movimentos = movimentos;
}

int Hanoi::getMovimentos() const {
    return this->movimentos;
}





