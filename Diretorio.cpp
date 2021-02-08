#include <iostream>
#include <string>
#include <algorithm>
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
        this->baldes[i]->positions.push_back(i);
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

string Diretorio::inteiroParaBinario(int bits, int n)
{
    string x;
    for (int i = 0; i < bits; i++)
    {
        if (n & 1)
        {
            x += '1';
        }
        else
        {
            x += '0';
        }
        n >>= 1;
    }
    reverse(x.begin(), x.end());
    return x;
}

void Diretorio::inserir(string str)
{
    int pos = binarioParaInteiro(profundidadeGlobal, str);
    if (baldes[pos]->getPosicoesUsadas() == tamanhoBalde)
    {
        if (this->profundidadeGlobal > baldes[pos]->getProfundidadeLocal())
        {
            cout << "realizando divisão do balde" << endl;
            dividir(pos, baldes[pos]);
            inserir(str);
        }
        else if (this->profundidadeGlobal == baldes[pos]->getProfundidadeLocal())
        {
        }
    }
    else
    {
        cout << "inserindo" << endl;
        baldes[pos]->setPosicoesUsadas();
        baldes[pos]->setPseudoChave(str);
    }
}

bool Diretorio::buscar(string str)
{
    int pos = binarioParaInteiro(profundidadeGlobal, str);
    for (int i = 0; i < tamanhoBalde; i++)
    {
        if (baldes[pos]->getPseudoChave(i) == str)
        {
            cout << "pseudochave encontrada" << endl;
            return true;
        }
    }
    cout << "não tem a pseudochave";
    return false;
}

void Diretorio::dividir(int pos, Balde *balde)
{
    vector<int> temp;
    balde->setProfundidadeLocal(balde->getProfundidadeLocal());
    Balde *novoBalde = new Balde(tamanhoBalde);
    Balde *novoBalde2 = new Balde(tamanhoBalde);
    *novoBalde = *balde;
    *novoBalde2 = *balde;
    novoBalde->positions.clear();
    novoBalde2->positions.clear();
    for (int i = 0; i < balde->positions.size(); i++)
    {
        if (i < balde->positions.size() / 2)
        {
            novoBalde->positions.push_back(balde->positions[i]);
        }
        else
        {
            novoBalde2->positions.push_back(balde->positions[i]);
        }
    }
    for (int i = 0; i < novoBalde->positions.size(); i++)
    {
        int pos = novoBalde->positions[i];
        int pos2 = novoBalde2->positions[i];
        baldes[pos] = novoBalde;
        baldes[pos2] = novoBalde2;
    }
    for (int i = 0; i < novoBalde->getPosicoesUsadas();)
    {
        string aux = (novoBalde->getPseudoChave(i).substr(0, novoBalde->getProfundidadeLocal()));
        string str = inteiroParaBinario(profundidadeGlobal, novoBalde->positions[0]);
        str = str.substr(0, novoBalde->getProfundidadeLocal());
        //cout << aux << " " << str << endl;
        if (aux != str)
        {
            //cout << novoBalde->getPseudoChave(i) << endl;
            novoBalde->removePseudoChave(i);
            novoBalde->removePosicoesUsadas();
        }
        else{
            i++;
        }
    }
    for (int i = 0; i < novoBalde2->getPosicoesUsadas();)
    {
        string aux = (novoBalde2->getPseudoChave(i).substr(0, novoBalde2->getProfundidadeLocal()));
        string str = inteiroParaBinario(profundidadeGlobal, novoBalde2->positions[0]);
        cout<<aux<<endl;
        str = str.substr(0, novoBalde2->getProfundidadeLocal());
        cout << aux << " " << str << endl;
        if (aux != str)
        {
            novoBalde2->removePseudoChave(i);
            novoBalde2->removePosicoesUsadas();
        }
        else
        {
            i++;
        }
    }
}

void Diretorio::duplicarDiretorio() {}
