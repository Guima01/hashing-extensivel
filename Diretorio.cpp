#include <iostream>
#include <string>
#include <algorithm>
#include "Diretorio.h"

using namespace std;

Diretorio::Diretorio(int tamanhoBalde, int bits)
{
    this->bitsMax = bits;
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
            //cout << "realizando divisao do balde" << endl;
            dividir(baldes[pos], str);
            inserir(str);
        }
        else if (this->profundidadeGlobal == baldes[pos]->getProfundidadeLocal() && this->profundidadeGlobal < this->bitsMax)
        {
            //cout << "duplicando diretorio" << endl;
            duplicarDiretorio(baldes[pos], str);
            inserir(str);
        }
    }
    else
    {
        baldes[pos]->setPseudoChave(str);
        baldes[pos]->setPosicoesUsadas();
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

void Diretorio::dividir(Balde *balde, string pos)
{
    balde->setProfundidadeLocal();
    Balde *novoBalde = new Balde(tamanhoBalde);
    Balde *novoBalde2 = new Balde(tamanhoBalde);
    novoBalde->recebeProfundidade(balde->getProfundidadeLocal());
    novoBalde2->recebeProfundidade(balde->getProfundidadeLocal());
    string auxiliar = balde->getPseudoChave(0);
    novoBalde->setPseudoChave(auxiliar);
    novoBalde->setPosicoesUsadas();
    auxiliar = auxiliar.substr(0, novoBalde->getProfundidadeLocal());
    for (int i = 1; i < balde->getPosicoesUsadas(); i++)
    {
        if (auxiliar == balde->pseudoChaves[i].substr(0, balde->getProfundidadeLocal()))
        {
            //cout << auxiliar << " 1 " << balde->pseudoChaves[i].substr(0, balde->getProfundidadeLocal()) << endl;
            novoBalde->pseudoChaves.push_back(balde->pseudoChaves[i]);
            novoBalde->setPosicoesUsadas();
        }
        else
        {
            //cout << auxiliar << " 2 " << balde->pseudoChaves[i].substr(0, balde->getProfundidadeLocal()) << endl;
            novoBalde2->pseudoChaves.push_back(balde->pseudoChaves[i]);
            novoBalde2->setPosicoesUsadas();
        }
    }
    delete balde;
    string bits1 = novoBalde->pseudoChaves[0].substr(0, novoBalde->getProfundidadeLocal());
    string bits2 = "";
    if (novoBalde2->pseudoChaves.size() > 0)
    {
        bits2 = novoBalde2->pseudoChaves[0].substr(0, novoBalde2->getProfundidadeLocal());
    }
    for (int i = 0; i < baldes.size(); i++)
    {
        string str = inteiroParaBinario(profundidadeGlobal, i);
        str = str.substr(0, novoBalde->getProfundidadeLocal());
        if (str == bits1)
        {
            baldes[i] = novoBalde;
        }
        else if (str == bits2)
        {
            baldes[i] = novoBalde2;
        }
    }
    for (int i = 0; i < baldes.size(); i++)
    {
        if (baldes[i] == balde)
        {
            baldes[i] = novoBalde2;
        }
    }

    cout << "Balde" << endl;
    for (int i = 0; i < baldes.size(); i++)
    {
        cout << "profLocal: " << baldes[i]->getProfundidadeLocal() << endl;
        if (baldes[i] != nullptr)
        {
            for (int j = 0; j < baldes[i]->getPosicoesUsadas(); j++)
            {
                cout << "diretorio posicao: " << i << " pseudoChave:" << baldes[i]->getPseudoChave(j) << endl;
            }
        }
    }
    cout << endl;
    cout << endl;
    cout << endl;
}

void Diretorio::duplicarDiretorio(Balde *balde, string pos)
{
    this->profundidadeGlobal = profundidadeGlobal + 1;

    balde->setProfundidadeLocal();
    Balde *novoBalde = new Balde(tamanhoBalde);
    Balde *novoBalde2 = new Balde(tamanhoBalde);
    novoBalde->recebeProfundidade(balde->getProfundidadeLocal());
    novoBalde2->recebeProfundidade(balde->getProfundidadeLocal());

    string auxiliar = balde->getPseudoChave(0);
    novoBalde->setPseudoChave(auxiliar);
    novoBalde->setPosicoesUsadas();
    auxiliar = auxiliar.substr(0, balde->getProfundidadeLocal());

    for (int i = 1; i < balde->getPosicoesUsadas(); i++)
    {
        if (auxiliar == balde->pseudoChaves[i].substr(0, balde->getProfundidadeLocal()))
        {
            novoBalde->pseudoChaves.push_back(balde->pseudoChaves[i]);
            novoBalde->setPosicoesUsadas();
        }
        else
        {
            novoBalde2->pseudoChaves.push_back(balde->pseudoChaves[i]);
            novoBalde2->setPosicoesUsadas();
        }
    }

    vector<Balde *> vectorBaldeAux;
    vectorBaldeAux.push_back(novoBalde);
    vectorBaldeAux.push_back(novoBalde2);

    std::vector<Balde *>::iterator it;
    delete balde;

    for (int i = 0; i < baldes.size(); i++)
    {
        it = find(vectorBaldeAux.begin(), vectorBaldeAux.end(), baldes[i]);
        if ((baldes[i] != balde) && (it == vectorBaldeAux.end()) && (baldes[i]->pseudoChaves.size() > 0))
        {

            vectorBaldeAux.push_back(baldes[i]);
        }
    }

    for (int i = 0; i < 1 << (profundidadeGlobal - 1); i++)
    {
        Balde *aux = new Balde(tamanhoBalde);
        aux->recebeProfundidade(novoBalde2->getProfundidadeLocal());
        this->baldes.push_back(aux);
    }

    for (int i = 0; i < vectorBaldeAux.size(); i++)
    {
        if (vectorBaldeAux[i]->pseudoChaves.size() != 0)
        {
            string bits = vectorBaldeAux[i]->pseudoChaves[0].substr(0, vectorBaldeAux[i]->getProfundidadeLocal());
            for (int j = 0; j < baldes.size(); j++)
            {
                string str = inteiroParaBinario(profundidadeGlobal, j);
                str = str.substr(0, vectorBaldeAux[i]->getProfundidadeLocal());
                if (str == bits)
                {
                    vectorBaldeAux[i]->positions.push_back(j);
                    baldes[j] = vectorBaldeAux[i];
                }
            }
        }
    }

    cout << "Diretorio" << endl;
    for (int i = 0; i < baldes.size(); i++)
    {
        cout << "profLocal: " << baldes[i]->getProfundidadeLocal() << endl;
        if (baldes[i] != nullptr)
        {
            for (int j = 0; j < baldes[i]->getPosicoesUsadas(); j++)
            {
                cout << "diretorio posicao: " << i << " pseudoChave:" << baldes[i]->getPseudoChave(j) << endl;
            }
        }
    }
    cout << endl;
    cout << endl;
    cout << endl;
}
