#include <iostream>
#include <string>
#include "Diretorio.h"

using namespace std;

Diretorio::Diretorio(int tamanhoBalde)
{
    this->tamanhoBalde = tamanhoBalde;
    this->profundidadeGlobal = 1;
    Balde *balde = new Balde(tamanhoBalde);
    for (int i = 0; i < 2; i++)
    {
        this->baldes.push_back(balde);
    }
}

Diretorio::~Diretorio() {}

int Diretorio::binarioParaInteiro(int bits, string str)
{
    string aux = (str.substr(0, bits));
    int num = atoi(aux.c_str());
    int decValue = 0;

    int base = 1;

    int temp = num;
    while (temp)
    {
        int lastDigit = temp % 10;
        temp = temp / 10;

        decValue += lastDigit * base;

        base = base * 2;
    }

    return decValue;
}

void Diretorio::inserir(string str)
{
    int pos = binarioParaInteiro(profundidadeGlobal, str);
    if(baldes[pos]->getPosicoesUsadas() == tamanhoBalde){
        cout<<"ta lotado"<<endl;
    }
    else{
    cout<<str<<endl;
    baldes[pos]->setPosicoesUsadas();
    baldes[pos]->setPseudoChave(str);
    }
}

bool Diretorio::buscar(string str)
{
    int pos = binarioParaInteiro(profundidadeGlobal, str);
    for(int i =0; i < tamanhoBalde; i++){
        cout<<baldes[pos]->getPseudoChave(i)<< " "<< str<<endl;
        if(baldes[pos]->getPseudoChave(i) == str){
            cout<< "pseudochave encontrada"<<endl;
            return true;
        }
    }
    cout<<"não tem a pseudochave";
    return false;
}

void Diretorio::dividir() {}

void Diretorio::duplicarDiretorio() {}
