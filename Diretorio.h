#include <string>
#include <vector>
#include "Balde.h"

using namespace std;

class Diretorio {

    private:
    int profundidadeGlobal;
    int tamanhoBalde;

    public:
    vector<Balde*> baldes;
    Diretorio(int tamanhoBalde);
    ~Diretorio();
    void inserir(string pseudoChave);
    bool buscar(string str);
    void dividir(int pos, Balde *balde);
    void duplicarDiretorio();
    int binarioParaInteiro(int bits, string str);
    string inteiroParaBinario(int bits,int n);

};