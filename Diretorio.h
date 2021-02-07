#include <string>
#include <vector>
#include "Balde.h"

using namespace std;

class Diretorio {

    private:
    int profundidadeGlobal;
    int tamanhoBalde;
    vector<Balde*> baldes;

    public:
    Diretorio(int tamanhoBalde);
    ~Diretorio();
    void inserir(string pseudoChave);
    bool buscar(string str);
    void dividir();
    void duplicarDiretorio();
    int binarioParaInteiro(int bits, string str);

};