#ifndef AVP_H_INCLUDED
#define AVP_H_INCLUDED

#include "noVp.h"

class AVP{

    public:
    //Construtor
    AVP();
    //Destrutor
    ~AVP();
    //Ponteiro para raiz
    NoVP* raiz;

    //métodos

    //void insere(int val);

    //--------novos-------//
    void rotacao_esquerda(NoVP* n);
    void rotacao_direita(NoVP* n);
    NoVP* auxinsere(NoVP* raiz, NoVP* n);
    void insereCorrecao(NoVP* n);
    void insereRecursivo(NoVP* raiz, NoVP* n);
    void insereCaso4etapa2(NoVP* n);
    void insereCaso4(NoVP* n);
    void insereCaso3(NoVP* n);
    void insereCaso2(NoVP* n);
    void insereCaso1(NoVP* n);
    void insere(int val);

    //impressao
    void imprime_aux(NoVP* n, int indent);
    void imprime_AVP();
    //busca
    bool auxBusca(NoVP *p, int val);
    bool busca(int val);
    NoVP* busca_no(int val);
    NoVP* noMaximo(NoVP* n);


    void verifica_propriedades();
    void verifica_propriedade1(NoVP* n);
    void verifica_propriedade2(NoVP* raiz);
    void verifica_propriedade4(NoVP* n);
    void verifica_propriedade5(NoVP* raiz);
    void verifica_propriedade5_aux(NoVP* n, int contador, int* contador_caminho_negro);

    void deleta_caso1(NoVP* n);
    void deleta_caso2(NoVP* n);
    void deleta_caso3(NoVP* n);
    void deleta_caso4(NoVP* n);
    void deleta_caso5(NoVP* n);
    void deleta_caso6(NoVP* n);

    void substitui_no(NoVP* velho, NoVP* novo);
    void deleta(int val);


    void auxDestrutor(NoVP *p);

    //--------novos-------//

    NoVP* getRaiz()       { return raiz; };
    void setRaiz(NoVP* r)       { raiz= r; };


};

#endif // AVP_H_INCLUDED
