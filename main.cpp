#include <stdio.h>
#include <iostream>
#include <string>
#include "Balde.h"
#include "Diretorio.h"

using namespace std;

int main(){

    int M;
    int B;
    cout<<"digita o tamanho do balde ai:";
    cin>>M;
    cout<<"digita os bits ai:";
    cin>>B;
    Diretorio diretorio(M,B);

    return 0;
}