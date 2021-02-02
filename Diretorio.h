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
    Diretorio(int tamanhoBalde, int profundidadeGlobal);
    ~Diretorio();
    void inserir(string str);
    void buscar();
    void dividir();
    void duplicarDiretorio();
    void setTamanhoBalde(int tamanhoBalde);

};