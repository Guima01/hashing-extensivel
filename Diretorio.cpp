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
    }
}

Diretorio::~Diretorio() {}

//transformação de número binario para inteiro
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

//transformação de um número inteiro para binário
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

//retorna certo balde através de um índice
Balde Diretorio::getBalde(int indice)
{
    return *this->baldes[indice];
}

//retorna o tamanho do diretório
int Diretorio::TamanhoDiretorio()
{
    return this->baldes.size();
}

//inserção das pseudoChaves
void Diretorio::inserir(string str)
{
    int pos = binarioParaInteiro(profundidadeGlobal, str);
    if (baldes[pos]->getPosicoesUsadas() == tamanhoBalde)
    {
        if (this->profundidadeGlobal > baldes[pos]->getProfundidadeLocal()) //divide o balde
        {
            dividir(baldes[pos], str);
            inserir(str);
        }
        else if (this->profundidadeGlobal == baldes[pos]->getProfundidadeLocal() && this->profundidadeGlobal < this->bitsMax) //duplica o diretório
        {
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

//faz a busca de certa pseudoChave no diretório
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

//divide o balde entre 2 novos baldes, realocando as pseudochaves 

void Diretorio::dividir(Balde *balde, string pos)
{
    balde->setProfundidadeLocal();
    Balde *novoBalde = new Balde(tamanhoBalde);
    Balde *novoBalde2 = new Balde(tamanhoBalde);
    novoBalde->recebeProfundidade(balde->getProfundidadeLocal());
    novoBalde2->recebeProfundidade(balde->getProfundidadeLocal());
    novoBalde->setPosition(balde->getPosition());
    novoBalde2->setPosition(balde->getPosition());

    
    string auxiliar = balde->getPseudoChave(0);
    novoBalde->setPseudoChave(auxiliar);
    novoBalde->setPosicoesUsadas();
    auxiliar = auxiliar.substr(0, novoBalde->getProfundidadeLocal());
    for (int i = 1; i < balde->getPosicoesUsadas(); i++)               //separa as chaves entre os baldes 
    {
        if (auxiliar == balde->getPseudoChave(i).substr(0, balde->getProfundidadeLocal()))
        {
            novoBalde->setPseudoChave(balde->getPseudoChave(i));
            novoBalde->setPosicoesUsadas();
        }
        else
        {
            novoBalde2->setPseudoChave(balde->getPseudoChave(i));
            novoBalde2->setPosicoesUsadas();
        }
    }

    delete balde;

    string bits1 = novoBalde->getPseudoChave(0).substr(0, novoBalde->getProfundidadeLocal());        //pega uma substring para alocar corretamente o balde
    string bits2 = "";
    if (novoBalde2->getPosicoesUsadas() > 0)                                                          
    {
        bits2 = novoBalde2->getPseudoChave(0).substr(0, novoBalde2->getProfundidadeLocal());
    }

    for (int i = 0; i < baldes.size(); i++)                                           //percorre todo o diretório e verifica em quais posições os novos baldes devem estar
    {
        string str = inteiroParaBinario(profundidadeGlobal, i);
        str = str.substr(0, novoBalde->getProfundidadeLocal());
        if (str == bits1)
        {
            baldes[i] = novoBalde;
            string position = inteiroParaBinario(profundidadeGlobal, i);
            baldes[i]->setPosition(position.substr(0, baldes[i]->getProfundidadeLocal()));              //armazena uma posição em binário no balde, e utilizando essa posição o balde será alocado corretamente no diretório
        }
        else if (str == bits2)
        {
            baldes[i] = novoBalde2;
            string position = inteiroParaBinario(profundidadeGlobal, i);
            baldes[i]->setPosition(position.substr(0, baldes[i]->getProfundidadeLocal()));
        }
    }
    for (int i = 0; i < baldes.size(); i++)                                     //trata o caso em que um dos novosbaldes é vazio 
    {
        if (baldes[i] == balde)
        {
            baldes[i] = novoBalde2;
            string position = inteiroParaBinario(profundidadeGlobal, i);
            baldes[i]->setPosition(position.substr(0, baldes[i]->getProfundidadeLocal()));
        }
    }
}


//duplica o diretório o balde e ajusta todos os baldes
void Diretorio::duplicarDiretorio(Balde *balde, string pos)
{
    this->profundidadeGlobal = profundidadeGlobal + 1;

    balde->setProfundidadeLocal();
    Balde *novoBalde = new Balde(tamanhoBalde);
    Balde *novoBalde2 = new Balde(tamanhoBalde);
    novoBalde->recebeProfundidade(balde->getProfundidadeLocal());
    novoBalde2->recebeProfundidade(balde->getProfundidadeLocal());
    novoBalde->setPosition(balde->getPosition());
    novoBalde2->setPosition(balde->getPosition());

    string auxiliar = balde->getPseudoChave(0);
    string auxiliar2;
    novoBalde->setPseudoChave(auxiliar);
    novoBalde->setPosicoesUsadas();
    auxiliar = auxiliar.substr(0, balde->getProfundidadeLocal());
    novoBalde->setPosition(auxiliar);   
    if (auxiliar[auxiliar.size() - 1] == '0')                       //armazena uma posição em binário no balde, e utilizando essa posição o balde será alocado corretamente no diretório
    {
        auxiliar2 = auxiliar;
        auxiliar2[auxiliar2.size() - 1] = '1';
        novoBalde2->setPosition(auxiliar2);
    }
    else
    {
        auxiliar2 = auxiliar;
        auxiliar2[auxiliar2.size() - 1] = '0';
        novoBalde2->setPosition(auxiliar2);
    }

    for (int i = 1; i < balde->getPosicoesUsadas(); i++)               //separa as chaves entre os baldes 
    {
        if (auxiliar == balde->getPseudoChave(i).substr(0, balde->getProfundidadeLocal()))
        {
            novoBalde->setPseudoChave(balde->getPseudoChave(i));
            novoBalde->setPosicoesUsadas();
        }
        else
        {
            novoBalde2->setPseudoChave(balde->getPseudoChave(i));
            novoBalde2->setPosicoesUsadas();
        }
    }

    vector<Balde *> vectorBaldeAux;
    vectorBaldeAux.push_back(novoBalde);
    vectorBaldeAux.push_back(novoBalde2);

    std::vector<Balde *>::iterator it;
    delete balde;

    for (int i = 0; i < baldes.size(); i++)             //utiliza de um vetor auxiliar para armazenar todos os diferentes baldes existentes para que haja uma futura realocação
    {
        it = find(vectorBaldeAux.begin(), vectorBaldeAux.end(), baldes[i]);
        if ((baldes[i] != balde) && (it == vectorBaldeAux.end()))
        {
            vectorBaldeAux.push_back(baldes[i]);
        }
    }

    for (int i = 0; i < 1 << (profundidadeGlobal - 1); i++)            //duplica o tamanho do diretório
    {
        this->baldes.push_back(nullptr);
    }

    for (int i = 0; i < vectorBaldeAux.size(); i++)                 //ajusta todos os baldes para novas posições
    {
        for (int j = 0; j < baldes.size(); j++)
        {
            string str = inteiroParaBinario(profundidadeGlobal, j);
            str = str.substr(0, vectorBaldeAux[i]->getProfundidadeLocal());
            if (str == vectorBaldeAux[i]->getPosition())
            {
                baldes[j] = vectorBaldeAux[i];
            }
        }
    }
}
