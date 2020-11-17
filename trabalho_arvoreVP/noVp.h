#ifndef NOVP_H_INCLUDED
#define NOVP_H_INCLUDED

//duas cores: V-> Vermelho, P-> Preto
enum cor { VERMELHO, PRETO };

class NoVP
{
  public:
    NoVP()               { };
    ~NoVP()              { };
    int info;	 // valor armazenado
    NoVP* esq;	 // ponteiro para o filho esquerdo
    NoVP* dir;	 // ponteiro para o filho direito
    NoVP* pai;	 // ponteiro p/ o pai
    enum cor tipocor;	 // cor do nó

    //Sets
    void setEsq(NoVP *p);
    void setInfo(int val);
    void setDir(NoVP *p);
    void setPai(NoVP *p);
    void setCor(cor c);

    //Gets
    NoVP* getEsq();
    int getInfo();
    NoVP* getDir();
    NoVP* getPai(NoVP* n);
    cor getCor();
    cor noh_cor(NoVP* n);

    //-----------//

    NoVP* GetAvo(NoVP* n);
    NoVP* GetIrmao(NoVP* n);
    NoVP* GetTio(NoVP* n);


};

#endif // NOVP_H_INCLUDED
