#include <iostream>
#include <string>
#include "Diretorio.h"

using namespace std;

Diretorio::Diretorio(int tamanhoBalde, int profundidade){
    this->tamanhoBalde = tamanhoBalde;
    this->profundidadeGlobal = profundidade;
    for(int i =0; i < 1<<profundidadeGlobal; i++){
        this->baldes.push_back(new Balde(tamanhoBalde,profundidade));
    }
}

Diretorio::~Diretorio(){}

void Diretorio::inserir(string str){}

void Diretorio::buscar(){}

void Diretorio::dividir(){}

void Diretorio::duplicarDiretorio(){}

void Diretorio::setTamanhoBalde(int tamanhoBalde){
    this->tamanhoBalde = tamanhoBalde;
}