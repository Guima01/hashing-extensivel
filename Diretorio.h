#include <string>
#include <vector>
#include "Balde.h"

using namespace std;

class Diretorio {

    private:
    int bitsMax;
    int profundidadeGlobal;
    int tamanhoBalde;

    public:
    vector<Balde*> baldes;
    Diretorio(int tamanhoBalde, int bits);
    ~Diretorio();
    void inserir(string pseudoChave);
    bool buscar(string str);
    void dividir(Balde *balde, string pos);
    void duplicarDiretorio(Balde *balde, string pos);
    int binarioParaInteiro(int bits, string str);
    string inteiroParaBinario(int bits,int n);

};