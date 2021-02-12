#ifndef BALDE_H
#define BALDE_H

#include <string>
#include <vector>

using namespace std;

class Balde
{

    private:
    int tamanhoBalde;
    int profundidadeLocal;
    int posicoesUsadas;
    string position;

    public:
    vector<string> pseudoChaves;
    Balde(int tamanhoBalde);
    ~Balde();
    string getPseudoChave(int indice);
    void setPseudoChave(string pseudoChave);
    void removePseudoChave(int pos);
    void setProfundidadeLocal();
    int getProfundidadeLocal();
    void recebeProfundidade(int profundidade);
    void setTamanhoBalde(int tamanhoBalde);
    int getPosicoesUsadas();
    void setPosicoesUsadas();
    void removePosicoesUsadas();
    void esvaziaBalde();
    string getPosition();
    void setPosition(string position);
};

#endif