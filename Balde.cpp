#include <iostream>
#include <iostream>
#include <string>
#include "Balde.h"
#include <vector>

using namespace std;

Balde::Balde(int tamanhoBalde)
{
    this->tamanhoBalde = tamanhoBalde;
    this->profundidadeLocal = 0;
    this->posicoesUsadas = 0;
}

Balde::~Balde() {}

string Balde::getPseudoChave(int indice)
{
    return this->pseudoChaves[indice];
}

void Balde::setPseudoChave(string pseudoChave)
{
    this->pseudoChaves.push_back(pseudoChave);
}

void Balde::removePseudoChave(int pos)
{
    this->pseudoChaves.erase(pseudoChaves.begin() + pos);
}

void Balde::setProfundidadeLocal(int profundidade)
{
    this->profundidadeLocal = this->profundidadeLocal + 1;
}
int Balde::getProfundidadeLocal()
{
    return this->profundidadeLocal;
}

int Balde::getPosicoesUsadas()
{
    return this->posicoesUsadas;
}

void Balde::setPosicoesUsadas()
{
    this->posicoesUsadas += 1;
}

void Balde::removePosicoesUsadas()
{
    this->posicoesUsadas -= 1;
}
void Balde::esvaziaBalde()
{
    this->pseudoChaves.clear();
    this->posicoesUsadas = 0;
    cout<< pseudoChaves.size();
}
