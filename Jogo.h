//
// Created by Vinícius Montanheiro on 23/03/15.
//

#include "Hanoi.h"
#include "Jogada.h"

#ifndef _HANOI_JOGO_H_
#define _HANOI_JOGO_H_

class Jogo {
public:
    Hanoi hanoi;

    GenericKeyboard teclado;

    Stack<Jogada> jogadasADesfazer;

    Stack<Jogada> jogadasARefazer;

    Jogo();

    void lerDiscos();

    void iniciar();

    void limparTela();

    void sair();

    Stack<int> inserirDisco(Stack<int>, int disco);

    bool isCheio(Stack<int> pino);

    Stack<int> getPinoAtualizado(Stack<int> pino, bool pop);

    int getOrigemDestino(int destino, bool pop);

    void iniciarMovimento(int pinoOrigem, int pinoDestino);

    void emitirMensagem(string mensagem, bool continuar);

    bool validarPino(Stack<int> pino);

    void desfazerJogada();

    void refazerJogada();

    int continuarJogo();

    void mostrarPinos(Stack<int> primeiroPino, Stack<int> segundoPino, Stack<int> terceiroPino, bool continuar, string mensagem);

    bool validarTecla(int pino);

    void fazerJogada(int pinoOrigem, int pinoDestino);

    void incrementarMovimento();

    bool validarMovimento(int pinoOrigem, int pinoDestino);

    bool validarDiscos(int discoOrigem, int discoDestino);

};

#endif //_HANOI_JOGO_H_

Jogo::Jogo() : hanoi(0, 0, 0) {
    this->hanoi = Hanoi(0, 0, 0);
}

/**
* @description Faz a leitura e validações dos discos
*/
void Jogo::lerDiscos() {
    int discos = 0;
    cout << "\033[0;33m[?] - [INFORME QUANTIDADE DE DISCOS ENTRE (3 e 7) OU (ENTER) PARA SAIR]\033[0m" << endl;
    //cin >> discos;

    while (discos < 51 || discos > 55) {
        discos = teclado.keyhit(true);
        if (discos == 10) {
            this->limparTela();
            this->sair();
        }
    };
    hanoi.setDiscos(discos - 48);
    //TODO Remover após testes
    //Validação dos discos
//    if (discos < 3 || discos > 7) {
//        cerr << endl << "\033[0;33m [?] - [A QUANTIDADE DE DISCOS DEVE ESTAR ENTRE (3) E (7)]:\033[0m" << endl;
//        this->sair(1);
//    } else {

    // }
    this->limparTela();
}

/**
* @description Método que inicia o jogo
*/
void Jogo::iniciar() {
    Stack<int> primeiroPino, segundoPino, terceiroPino;
    this->limparTela();

    cout << "\033[0;33m******************************\033[0m" << endl;
    cout << "\033[0;33m* BEM VINDO A TORRE DE HANOI *\033[0m" << endl;
    cout << "\033[0;33m******************************\033[0m" << endl << endl;

    cout << "\t\033[0;36m  [INICIAR] \033[0m" << endl << endl;
    cout << "\033[0;33m******************************\033[0m" << endl;

    while (teclado.keyhit(true) != 10);
    this->limparTela();

    //Chamada para inserção dos discos
    this->lerDiscos();

    for (int discos = hanoi.getDiscos(); discos > 0; discos--) {
        primeiroPino.push(discos);
    }
    hanoi.setPrimeiroPino(primeiroPino);
    //Exibe os pinos pela primeira vez
    this->mostrarPinos(primeiroPino, segundoPino, terceiroPino, true, "");

}

/**
* @description Dispara chamada no sistema para limpar a tela
*/
void Jogo::limparTela() {
    cout << endl;
    system("clear");
}

/**
* @description Responsável por sair ou reiniciar o jogo após a verificação dos discos
* @params char R,r
*/
void Jogo::sair() {
    exit(system("exit"));
}

/**
* @description Faz contagem dos movimentos SEM decremento.
*/
void Jogo::incrementarMovimento() {
    int i = hanoi.getMovimentos();
    i++;
    hanoi.setMovimentos(i);
}

/**
* @description Insere discos no pino de destino
* @params Stack pinoDestino, int valor do disco origem
* @return Stack
*/
Stack<int> Jogo::inserirDisco(Stack<int> pino, int disco) {
    pino.push(disco);
    return pino;
}

/**
* @description Verifica se o pino está cheio
* @param Stack pinoAlvo
* @return bool
*/
bool Jogo::isCheio(Stack<int> pino) {
    Node<int> *pto;
    int size = 0;
    pto = pino.top;
    while (pto) {
        if (pto->item != 0) {
            size++;
        }
        pto = pto->next;
    }
    return size == hanoi.getDiscos();
}

/**
* @description Faz tratamento dos pinos durante as execuções das jogadas
* @params Stack, bool
* @return Stack
*/
Stack<int> Jogo::getPinoAtualizado(Stack<int> pino, bool pop) {
    int topo = 0;
    //Verifica se o pino é de origem ou destino
    if (pop) {
        this->validarPino(pino);
        pino.pop(&topo);
        hanoi.setTopo(topo);
    } else {
        hanoi.setTopo(pino.top ? pino.top->item : 0);
    }
    return pino;
}

/**
* @description Inicia e valida a execução dos movimentos entre as pilhas
* @params int pilha de origem, int pilha de destino
*/
void Jogo::iniciarMovimento(int pinoOrigem, int pinoDestino) {
    int discoOrigem;
    //Força o pino de origem a fazer o pop
    discoOrigem = this->getOrigemDestino(pinoOrigem, true);
    if (pinoDestino == 1) {
        hanoi.setPrimeiroPino(this->inserirDisco(hanoi.getPrimeiroPino(), discoOrigem));
    } else {
        if (pinoDestino == 2) {
            hanoi.setSegundoPino(this->inserirDisco(hanoi.getSegundoPino(), discoOrigem));
        } else {
            hanoi.setTerceiroPino(this->inserirDisco(hanoi.getTerceiroPino(), discoOrigem));
        }
    }


    //Verifica se todos os discos estão no terceiro pino.
    if (!this->isCheio(hanoi.getTerceiroPino())) {
        this->emitirMensagem("", true);
    } else {
        this->emitirMensagem("\033[0;32m [*** PARABÉNS!! VOCÊ CONCLUIU O JOGO COM [" + to_string(hanoi.getMovimentos()) + "] MOVIMENTOS **] \033[0m", false);
    }
}

bool Jogo::validarDiscos(int discoOrigem, int discoDestino) {
    if (((discoOrigem <= discoDestino || discoDestino == 0) && discoOrigem != discoDestino)) {
        return true;
    } else {
        this->emitirMensagem("[!] - [DISCO MAIOR QUE O DISCO DO PINO DE DESTINO]", true);
        return false;
    }
}

/**
*@description Faz a validação dos movimentos
* @params int pino de origem, int pino de origem
*/
bool Jogo::validarMovimento(int pinoOrigem, int pinoDestino) {
    if (pinoOrigem != pinoDestino) {
        Stack<int> pino;
        if (pinoOrigem == 1) {
            pino = hanoi.getPrimeiroPino();
        } else {
            if (pinoOrigem == 2) {
                pino = hanoi.getSegundoPino();
            } else {
                pino = hanoi.getTerceiroPino();
            }
        }

        if (pino.isEmpty()) {
            this->emitirMensagem("[!] - [PINO VAZIO! INFORME OUTRO PINO]", true);
            return false;
        } else {
            return true;
        }

    } else {
        this->emitirMensagem("[!] - [DISCO NÃO ENCONTRADO]", true);
        return false;
    }
}

/**
* @description Desfaz a jogada atual, recuperando os pinos da jogada anterior
*/
void Jogo::desfazerJogada() {
    this->incrementarMovimento();
    Jogada jogada = Jogada();
    this->jogadasADesfazer.pop(&jogada);
    this->jogadasARefazer.push(jogada);
    cout << endl << jogada.getPinoOrigem() << " - " << endl << jogada.getPinoDestino() << endl;
    this->iniciarMovimento(jogada.getPinoDestino(), jogada.getPinoOrigem());
}

/**
* @description Avança a jogada, somente após o primeiro desfazer.
*/
void Jogo::refazerJogada() {
    this->incrementarMovimento();
    Jogada jogada = Jogada();
    this->jogadasARefazer.pop(&jogada);
    this->jogadasADesfazer.push(jogada);
    this->iniciarMovimento(jogada.getPinoOrigem(), jogada.getPinoDestino());
}

/**
* @description Responsável por fazer a jogada padrão
* @description int pino de origem, int pino de destino
*/
void Jogo::fazerJogada(int pinoOrigem, int pinoDestino) {
    if (this->validarMovimento(pinoOrigem, pinoDestino)) {
        int discoOrigem, discoDestino;
        discoOrigem = this->getOrigemDestino(pinoOrigem, false);
        discoDestino = this->getOrigemDestino(pinoDestino, false);
        this->jogadasARefazer = Stack<Jogada>();
        this->incrementarMovimento();
        Jogada jogada = Jogada();

        if (this->validarDiscos(discoOrigem, discoDestino)) {
            jogada.setPinoDestino(pinoDestino);
            jogada.setPinoOrigem(pinoOrigem);
            this->jogadasADesfazer.push(jogada);
            this->iniciarMovimento(pinoOrigem, pinoDestino);
        }
    }
}

/**
* @description Define a mensagem de saída e se o game deve ou não continuar
* @params String mensagem de saída, bool flag continuar
*/
void Jogo::emitirMensagem(string mensagem, bool continuar) {
    this->mostrarPinos(hanoi.getPrimeiroPino(), hanoi.getSegundoPino(), hanoi.getTerceiroPino(), continuar, mensagem);
}

/**
* @description Verifica se o pino de origem está vazio
* @param Stack pino de origem
* @return bool
*/
bool Jogo::validarPino(Stack<int> pino) {
    Node<int> *pto;
    pto = pino.top;
    bool vazio = true;
    while (pto) {
        if (pto->item != 0) {
            vazio = false;
        }
        pto = pto->next;
    }
    //Se estiver vazio
    if (vazio) {
        this->emitirMensagem("[!] - [PINO VAZIO! SELECIONE OUTRO PINO]", true);
    }
    return vazio;
}

/**
* @description Recupera os discos da pilha de origem e destino.
* @params int id do pino
* @return int
*/
int Jogo::getOrigemDestino(int pino, bool pop) {
    int topo = 0;
    Stack<int> primeiroPino, segundoPino, terceiroPino;
    switch (pino) {
        case 1 :
            primeiroPino = this->getPinoAtualizado(hanoi.getPrimeiroPino(), pop);
            hanoi.setPrimeiroPino(primeiroPino);
            topo = hanoi.getTopo();
            break;
        case 2 :
            segundoPino = this->getPinoAtualizado(hanoi.getSegundoPino(), pop);
            hanoi.setSegundoPino(segundoPino);
            topo = hanoi.getTopo();
            break;
        case 3 :
            terceiroPino = this->getPinoAtualizado(hanoi.getTerceiroPino(), pop);
            hanoi.setTerceiroPino(terceiroPino);
            topo = hanoi.getTopo();
            break;
        default:
            break;
    }
    return topo;
}

/**
* @description Valida leitura dos pinos
* @params int código da tecla precionada, 1 = 49, 2 = 50 e 3 = 51
*/
bool Jogo::validarTecla(int tecla) {
    return tecla >= 49 && tecla <= 51;
}

/**
* @description Faz a leitura e validações dos pinos de origem e destino e dá continuidade ao game
*/
int Jogo::continuarJogo() {
    int pinoOrigem = 0;
    int pinoDestino = 0;

    cout << endl << endl << "\033[0;33m [MOVER DISCO]\033[0m \033[0;32m [(a) - Avançar | (d) - Desfazer] | (s) - Sair \033[0m\r" << endl;
    cout << "\r\t\033[0;33m[!] - [PINO DE ORIGEM  ENTRE (1 e 3)*]\033[0m ";
    //cin >> pinoOrigem;

    while (pinoOrigem != 97 && pinoOrigem != 100 && pinoOrigem != 115 && !validarTecla(pinoOrigem)) {
        pinoOrigem = teclado.keyhit(false);
    };

    if (pinoOrigem == 115) {
        this->limparTela();
        this->sair();
    } else {
        if (pinoOrigem == 97) {
            if (this->jogadasARefazer.isEmpty()) {
                this->emitirMensagem("[!] - [NÃO EXISTE JOGADAS A RE-FAZER]", true);
            } else {
                this->refazerJogada();
            }
            return 0;
        } else {
            if (pinoOrigem == 100) {
                if (this->jogadasADesfazer.isEmpty()) {
                    this->emitirMensagem("[!] - [NÃO EXISTE JOGADAS A DESFAZER]", true);
                } else {
                    this->desfazerJogada();
                }
                return 0;
            } else {

                cout << "\033[0;33m[" << (pinoOrigem - 48) << "]" << endl << "\r\t[!] - [PINO DE DESTINO ENTRE (1 e 3)*]\033[0m" << endl;
                //cin >> pinoDestino;

                while (!validarTecla(pinoDestino)) {
                    pinoDestino = teclado.keyhit(true);
                };
                this->fazerJogada(pinoOrigem - 48, pinoDestino - 48);
            }
        }
    }




    //TODO Remover após testes
//    if ((pinoOrigem == 'a' || pinoOrigem == 'A')) {
//        if (this->jogadasARefazer.isEmpty()) {
//            this->emitirMensagem("[!] - [NÃO EXISTE JOGADAS A RE-FAZER]", true);
//        } else {
//            this->refazerJogada();
//        }
//        return 0;
//    } else {
//        if (pinoOrigem == 'd' || pinoOrigem == 'D') {
//            if (this->jogadasADesfazer.isEmpty()) {
//                this->emitirMensagem("[!] - [NÃO EXISTE JOGADAS A DESFAZER]", true);
//            } else {
//                this->desfazerJogada();
//            }
//            return 0;
//        } else {
//
//            cout << "\t\033[0;33m[?] - [PINO DE DESTINO]:\033[0m";
//            cin >> pinoDestino;
//
//            if (validarTecla((int) pinoOrigem) && validarTecla((int) pinoDestino)) {
//                this->fazerJogada((int) pinoOrigem - 48, (int) pinoDestino - 48);
//            } else {
//                this->emitirMensagem("[!] - [O PINO INFORMADO NÃO EXISTE]", true);
//            }
//        }
//    }
    return 0;


}

/**
* @description Processa mensagem de saída para visualização
* @params Stack pino1,Stack pino2, Stack pino3, bool flag continuar, string mensagem de saída
*/
void Jogo::mostrarPinos(Stack<int> primeiroPino, Stack<int> segundoPino, Stack<int> terceiroPino, bool continuar, string mensagem) {
    Node<int> *primeiro, *segundo, *terceiro;
    primeiro = primeiroPino.top;
    segundo = segundoPino.top;
    terceiro = terceiroPino.top;
    this->limparTela();

    //Executa mensagens emitidas
    if (mensagem != "") {
        cerr << endl << endl << "\033[0;31m" << mensagem << "\033[0m" << endl;
        usleep(30); //Delay para resolver bug da visualização
    }

    cout << "\033[0;33m                [TORRE DE HANOI]\033[0m" << endl;
    cout << endl;
    cout << "\033[0;36m" << hanoi.estilo[0] << hanoi.estilo[0] << hanoi.estilo[0] << "\033[0m" << endl;

    //Varredura das pilhas para visualização
    for (int i = 0; i < hanoi.getDiscos(); i++) {
        if (primeiro) {
            cout << "\033[0;36m" << hanoi.estilo[primeiro->item] << "\033[0m";
            primeiro = primeiro->next;
        } else {
            cout << "\033[0;36m" << hanoi.estilo[0] << "\033[0m";
        }

        if (segundo) {
            cout << "\033[0;36m" << hanoi.estilo[segundo->item] << "\033[0m";
            segundo = segundo->next;
        } else {
            cout << "\033[0;36m" << hanoi.estilo[0] << "\033[0m";
        }

        if (terceiro) {
            cout << "\033[0;36m" << hanoi.estilo[terceiro->item] << "\033[0m";
            terceiro = terceiro->next;
        } else {
            cout << "\033[0;36m" << hanoi.estilo[0] << "\033[0m";
        }
        cout << endl;
    }
    cout << "\033[0;36m" << hanoi.estilo[0] << hanoi.estilo[0] << hanoi.estilo[0] << "\033[0m" << endl;
    cout << "\033[0;36m    Pino [1]    \033[0m";
    cout << "\033[0;36m    Pino [2]    \033[0m";
    cout << "\033[0;36m    Pino [3]    \033[0m" << endl;

    //Dá continuidade ao game
    if (continuar) {
        this->continuarJogo();
    }
    cout << endl;
}

