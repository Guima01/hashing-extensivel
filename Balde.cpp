#include <iostream>
#include <iostream>
#include <string>
#include "Balde.h"
#include <vector>

using namespace std;

Balde::Balde(int tamanhoBalde){
    this->profundidadeLocal = 1;
    this->posicoesUsadas = 0;
    this->pseudoChaves;
}

Balde::~Balde(){}

string Balde::getPseudoChave(int indice){
    return this->pseudoChaves[indice];
}

void Balde::setPseudoChave(string pseudoChave){
    this->pseudoChaves.push_back(pseudoChave);
} 
void Balde::setProfundidadeLocal(int profundidade){
    this->profundidadeLocal = profundidade;
} 
int Balde::getProfundidadeLocal(){
    return this->profundidadeLocal;
}

int Balde::getPosicoesUsadas(){
    return this->posicoesUsadas;
}

void Balde::setPosicoesUsadas(){
    this->posicoesUsadas += 1;
}
