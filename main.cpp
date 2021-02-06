#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
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
    cout << pseudoChave << endl;
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
            for (int i = 0; i < 10; i++)
            {
                string str = mod2(bits);
                diretorio.inserir(str);
            }
            diretorio.buscar();
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
    Diretorio diretorio(M);
    menu(B,diretorio);
    return 0;
}