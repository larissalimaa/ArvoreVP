#ifndef NOVP_CPP_INCLUDED
#define NOVP_CPP_INCLUDED
#include "noVp.h"



NoVP* NoVP::getPai(NoVP* n)
{
   //Pai definido como nulo para o nó raiz.
    return n == nullptr ? nullptr : n->pai;
}

NoVP* NoVP::GetAvo(NoVP* n)
{
    //retornar nullptr se for raiz ou filho da raiz
    return getPai(getPai(n));
}

NoVP* NoVP::GetIrmao(NoVP* n)
{
    NoVP* p = getPai(n);

    //Nenhum Pai significa nenhum irmão.
    if (p == nullptr)
    {
        return nullptr;
    }

    if (n == p->esq)
    {
        return p->dir;
    }
    else
    {
        return p->esq;
    }
}

NoVP* NoVP::GetTio(NoVP* n)
{
    NoVP* p = getPai(n);

   //Irmao do pai eh o tio
    return GetIrmao(p);
}



//Sets
void NoVP::setEsq(NoVP *p)
{
    esq = p;
}
void NoVP::setInfo(int val)
{
    info = val;
}
void NoVP::setDir(NoVP *p)
{
    dir = p;
}
void NoVP::setPai(NoVP *p)
{
    pai = p;
}
void NoVP::setCor(cor c)
{
    tipocor = c;
}

//Gets
NoVP* NoVP::getEsq()
{
    return esq;
}
int NoVP::getInfo()
{
    return info;
}
NoVP* NoVP::getDir()
{
    return dir;
}

/*
 * Retorna a cor do no
 essa funcao especificamente verifica o caso no noh folha (NIL)
 */
cor NoVP::noh_cor(NoVP* n)
{
    return n == nullptr ? PRETO : n->tipocor;
}



cor NoVP::getCor()
{
    return tipocor;
}





#endif // NOVP_CPP_INCLUDED
