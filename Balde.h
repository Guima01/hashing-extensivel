#ifndef BALDE_H
#define BALDE_H

#include <string>
#include <vector>

using namespace std;

class Balde {

    private:
    int profundidadeLocal;
    int posicoesUsadas;
    vector<string> pseudoChaves;
    
    public:
    Balde(int tamanhoBalde,int profundidade);
    ~Balde();
    string getPseudoChave(int indice);
    void setPseudoChave(string pseudoChave);
    void setProfundidadeLocal(int profundidade);
    int getProfundidadeLocal();
    void setTamanhoBalde(int tamanhoBalde);

};

#endif