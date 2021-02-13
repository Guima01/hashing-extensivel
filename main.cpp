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

void imprimeDiretorio(Diretorio diretorio)
{
    for (int i = 0; i < diretorio.TamanhoDiretorio(); i++)
    {
        if (diretorio.getBalde(i).getPosicoesUsadas() > 0)
        {
            cout << "balde com bits inicias: " << diretorio.getBalde(i).getPosition() << endl;
            cout << "profLocal: " << diretorio.getBalde(i).getProfundidadeLocal() << endl;
            for (int j = 0; j < diretorio.getBalde(i).getPosicoesUsadas(); j++)
            {
                cout << "diretorio posicao " << i << " : pseudoChave:" << diretorio.getBalde(i).getPseudoChave(j) << endl;
            }
            cout << endl;
        }
        else
        {
            cout << "essa posicao nao possui pseudoChaves" << endl;
            cout << endl;
        }
    }
}

void menu(int bits, Diretorio diretorio)
{
    int seleciona;
    do
    {
        cout << "MENU" << endl;
        cout << "----" << endl;
        cout << "[1] Insercoes de 20 pseudo-chaves aleatorias" << endl;
        cout << "[2] Insercoes de 20 pseudo-chaves iniciadas com um mesmo padrao de bits" << endl;
        cout << "[0] Sair" << endl;
        cin >> seleciona;
        if (seleciona == 0)
        {
            break;
        }
        else if (seleciona == 1)
        {
            for (int i = 0; i < 20; i++)
            {
                string str = mod2(bits);
                diretorio.inserir(str);
            }
            imprimeDiretorio(diretorio);
        }
        else if (seleciona == 2)
        {
            for (int i = 0; i < 20; i++)
            {
                string str = "0";
                str = str + mod2(bits - 1);
                diretorio.inserir(str);
            }
            imprimeDiretorio(diretorio);
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
    Diretorio diretorio(M, B);
    menu(B, diretorio);
    return 0;
}