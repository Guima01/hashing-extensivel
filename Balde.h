#ifndef BALDE_H
#define BALDE_H

#include <string>
#include <vector>

using namespace std;

class Balde {

    private:
    int tamanhoBalde;
    int profundidadeLocal;
    int posicoesUsadas;
    vector<string> pseudoChaves;
    
    public:
    vector<int> positions;
    Balde(int tamanhoBalde);
    ~Balde();
    string getPseudoChave(int indice);
    void setPseudoChave(string pseudoChave);
    void removePseudoChave(int pos);
    void setProfundidadeLocal(int profundidade);
    int getProfundidadeLocal();
    void setTamanhoBalde(int tamanhoBalde);
    int getPosicoesUsadas();
    void setPosicoesUsadas();
    void removePosicoesUsadas();

};

#endif