#ifndef _HANOI_JOGADA_H_
#define _HANOI_JOGADA_H_

class Jogada{
private:
    int pinoOrigem,pinoDestino;
public:

    Jogada();

    int getPinoOrigem() const;

    void setPinoOrigem(int pinoOrigem);

    int getPinoDestino() const;

    void setPinoDestino(int pinoDestino);
};

#endif //_HANOI_JOGADA_H_

Jogada::Jogada(){
    this->pinoOrigem = 0;
    this->pinoDestino = 0;
}

int Jogada::getPinoOrigem() const {
    return pinoOrigem;
}

void Jogada::setPinoOrigem(int pinoOrigem) {
    this->pinoOrigem = pinoOrigem;
}

int Jogada::getPinoDestino() const {
    return pinoDestino;
}

void Jogada::setPinoDestino(int pinoDestino) {
    this->pinoDestino = pinoDestino;
}
