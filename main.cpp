#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include "Balde.h"
#include "Diretorio.h"

using namespace std;

string mod2(int bits)
{
    int bit;
    string pseudoChave = "";
    for (int i = 0; i < bits; i++)
    {
        bit = rand() % 100;
        bit = bit % 2;
        pseudoChave.append(to_string(bit));
    }
    return pseudoChave;
}

void menu(int bits, Diretorio diretorio)
{
    int seleciona;
    do
    {
        cout << "MENU" << endl;
        cout << "----" << endl;
        cout << "[1] Insercoes de N pseudo-chaves aleatorias" << endl;
        cout << "[2] Insercoes de N pseudo-chaves iniciadas com um mesmo padrao de bits" << endl;
        cin >> seleciona;
        if (seleciona == 0)
        {
            break;
        }
        else if (seleciona == 1)
        {
            vector<string> teste;
            for (int i = 0; i < 15; i++)
            {
                string str = mod2(bits);
                //cout<<"value: "<<str<<endl;
                teste.push_back(str);
            }
            for (int i = 0; i < 15; i++)
            {
                diretorio.inserir(teste[i]);
            }
            for (int i = 0; i < diretorio.baldes.size(); i++)
            {
                cout<<"profLocal: "<<diretorio.baldes[i]->getProfundidadeLocal()<<endl;
                if (diretorio.baldes[i] != nullptr)
                {
                    for (int j = 0; j < diretorio.baldes[i]->getPosicoesUsadas(); j++)
                    {
                        cout << "diretorio posicao: " << i << " pseudoChave:" << diretorio.baldes[i]->getPseudoChave(j) << endl;
                    }
                }
            }
        }
        else if (seleciona == 2)
        {
        }
    } while (seleciona != 0);
}

int main()
{
    int M;
    int B;
    srand(time(NULL));
    cout << "digita o tamanho do balde ai:";
    cin >> M;
    cout << "digita os bits ai:";
    cin >> B;
    Diretorio diretorio(M,B);
    menu(B, diretorio);
    return 0;
}