#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cstdlib>
#include <cassert>
#define INDENT_STEP  4

#include "AVP.h"

using namespace std;

AVP::AVP()
{
    raiz = NULL;

}

AVP::~AVP()
{
    auxDestrutor(this->raiz);
}

// Fun��o auxiliar do destrutor da �rvore VP
void AVP::auxDestrutor(NoVP *p)
{
    if(p != NULL)
    {
        auxDestrutor(p->getDir());
        auxDestrutor(p->getEsq());
        delete p;
    }
}



//Propriedades da arvore vermelho preta

/*
 * Funcao que verifica a propriedade 1 (todo no de uma arvore VP eh vermelho ou preta )
 * e desce recursivamente a arvore ate as folhas verificando cada noh
 */
void AVP::verifica_propriedade1(NoVP* n)
{
    assert(n->noh_cor(n) == VERMELHO || n->noh_cor(n) == PRETO);
    if (n == NULL)
        return;
    verifica_propriedade1(n->getEsq());
    verifica_propriedade1(n->getDir());
}



/*
 * Funcao que verifica a propriedade 2 (a raiuz da arvore VP eh sempre preta )
 */
void AVP::verifica_propriedade2(NoVP* raiz)
{
    assert(raiz->noh_cor(raiz) == PRETO);
}

/*
 * A propriedade 3 (todo folha (NIL) eh preto eh verificada no metodo "cor NoVP::noh_cor(NoVP* n)" em noVP.cppp
 */


/*
 * Funcao que verifica a propriedade 4 os filhos a direita e a esquerda de um noh vermelho sao sempre pretos
 */
void AVP::verifica_propriedade4(NoVP* n)
{
    if(n->noh_cor(n) == VERMELHO)
    {
        assert(n->getEsq()->noh_cor(n) == PRETO);
        assert(n->getDir()->noh_cor(n) == PRETO);
        assert(n->getPai(n)->noh_cor(n) == PRETO);
    }
    if (n == NULL)
        return;
    //percorre a arvore inteira recursivamente
    verifica_propriedade4(n->getEsq());
    verifica_propriedade4(n->getDir());
}
/*
 * Funcao que verifica a propriedade 5 da altura negra
 */
void AVP::verifica_propriedade5(NoVP* raiz)
{
    int contador_caminho_negro = -1;
    verifica_propriedade5_aux(raiz, 0, &contador_caminho_negro);
}

void AVP::verifica_propriedade5_aux(NoVP* n, int contador, int* contador_caminho_negro)
{
    if( n->noh_cor(n) == PRETO)
    {
        contador++;
    }
    if (n == NULL)
    {
        if (*contador_caminho_negro == -1)
        {
            *contador_caminho_negro = contador;
        }
        else
        {
            assert(contador == *contador_caminho_negro);
        }
        return;
    }
    verifica_propriedade5_aux(n->getEsq(),  contador, contador_caminho_negro);
    verifica_propriedade5_aux(n->getDir(), contador, contador_caminho_negro);
}






/*
 * Verifica propriedades da AVP
 */
void AVP::verifica_propriedades()
{
    verifica_propriedade1(raiz);
    verifica_propriedade2(raiz);
    verifica_propriedade4(raiz);
    verifica_propriedade5(raiz);
}


//busca e retorna o no
/*
NoVP* AVP::busca_no(NoVP *p, int val)
{

    if(p == NULL)
    {
        return NULL;
    }
    else if(p->getInfo() == val)
    {

        return p;
    }

    else if(val < p->getInfo())
    {

        auxBusca(p->getEsq(), val);
    }
    else
    {
        auxBusca(p->getDir(), val);
    }
    //return NULL;

}*/


NoVP* AVP::busca_no(int val)
{
    NoVP *p = this->raiz;
    while (p != NULL)
    {
        if (p->getInfo() == val)
        {
            return p;
        }
        else if (p->getInfo() < val)
        {
            p = p->getEsq();
        }
        else
        {
            assert(p->getInfo() > val);
            p = p->getDir();
        }
    }
    return p;
}

/*
 * Retorna o no maximo apartir de noh passado
 */
NoVP* AVP::noMaximo(NoVP* n)
{
    assert(n != NULL);
    while (n->getDir() != NULL)
    {
        n = n->getDir();
    }
    return n;
}

//deleta
/*
* Caso 1: N eh a nova raiz. Neste caso, terminamos.
Removemos um noh preto de cada caminho e a nova raiz eh preta, portanto, as propriedades s�o preservadas.
 */
void AVP::deleta_caso1(NoVP* n)
{
    if (n->getPai(n) == NULL)
        return;
    else
        deleta_caso2(n);
}

/*
 * Caso 2: O irm�o(I) � vermelho. Nesse caso, invertemos as cores do pai (P) e  do irmao (I) e, em seguida,
 giramos para a esquerda em P, transformando irm�o(I) no av� de N. Observe que P tem que ser
 preto porque teve um filho vermelho. A sub�rvore resultante tem um caminho curto um n�
 preto, ent�o n�o terminamos. Agora N tem um irm�o preto e um pai vermelho, ent�o podemos
 prosseguir para a etapa 4, 5 ou 6. (Seu novo irm�o � preto porque j� foi filho do (I) vermelho).
 Em casos posteriores, vamos renomear N novo irm�o como I.
 */
void AVP::deleta_caso2(NoVP* n)
{
    NoVP* irmao = n->GetIrmao(n);
    NoVP* pai = n->getPai(n);

    if (irmao->noh_cor(n) == VERMELHO)
    {
        pai->setCor(VERMELHO);

        irmao->setCor(PRETO);

        if (n == pai->getEsq())
            rotacao_esquerda(pai);
        else
            rotacao_direita(pai);

    }
    deleta_caso3(n);
}

/*
 Caso 3:  Pai (P), Irmao (I) e filhos de I s�o pretos. Neste caso, simplesmente repintamos I vermelho.
 O resultado eh que todos os caminhos que passam por I, que s�o precisamente aqueles caminhos que nao
 passam por N, tem um noh preto a menos. Como a exclusao do pai original de N fez com que
 todos os caminhos que passam por N tivessem um noh preto a menos, isso equilibra as coisas.
 No entanto, todos os caminhos atrav�s de P agora t�m um noh preto a menos do que os caminhos
 que n�o passam por P, entao a propriedade 5 (todos os caminhos de qualquer noh dado para
 seus nos folha cont�m o mesmo numero de nos pretos) ainda eh violada.
 Para corrigir isso, realizamos o procedimento de rebalanceamento em P, iniciando no caso 1.
 */
void AVP:: deleta_caso3(NoVP* n)
{
    NoVP* irmao = n->GetIrmao(n);
    NoVP* pai = n->getPai(n);

    if ( pai->noh_cor(n) == PRETO &&  irmao->noh_cor(n) == PRETO &&
            irmao->getEsq()->noh_cor(n) == PRETO && irmao->getDir()->noh_cor(n) == PRETO)
    {
        irmao->setCor(VERMELHO);
        deleta_caso1(pai);

    }
    else
        deleta_caso4(n);
}


/*
 * Caso4: Os filhos de I(Irmao) e o I s�o pretos, mas Pai (P) � vermelho. Neste caso, simplesmente trocamos as cores de I e P.
 Isso nao afeta o numero de n�s pretos nos caminhos que passam por I, mas adiciona um ao numero de nohs pretos
 nos caminhos que passam por N, compensando o noh preto excluido nesses caminhos.
 */
void AVP::deleta_caso4(NoVP* n)
{

    NoVP* irmao = n->GetIrmao(n);
    NoVP* pai = n->getPai(n);


    if ( pai->noh_cor(n) == VERMELHO &&  irmao->noh_cor(n) == PRETO &&
            irmao->getEsq()->noh_cor(n) == PRETO &&  irmao->getDir()->noh_cor(n) == PRETO)
    {
        irmao->setCor(VERMELHO);
        pai->setCor(PRETO);

    }
    else
        deleta_caso5(n);
}

/*
Irmao (I) eh preto, o filho esquerdo de I eh vermelho, o filho direito de I eh preto e N eh
o filho esquerdo de seu pai. Nesse caso, giramos para a direita em I, de modo que
o filho esquerdo de I se torne o pai de I e o novo irm�o de N. Em seguida, trocamos as
 cores de I e de seu novo pai. Todos os caminhos ainda tem o mesmo n�mero de nohs pretos,
 mas agora N tem um irmao preto cujo filho direito eh vermelho, ent�o caimos no caso 6.
 Nem N nem seu pai s�o afetados por esta transforma��o. (Novamente, para o caso 6, renomeamos o novo irm�o de N como I.)

*/
void AVP::deleta_caso5(NoVP* n)
{
    NoVP* irmao = n->GetIrmao(n);

    // Esta instru��o if � trivial, devido ao caso 2 (mesmo que o caso 2 tenha mudado
    // irm�o do filho do irm�o, o filho do irm�o n�o pode ser vermelho, pois
    // nenhum pai vermelho pode ter um filho vermelho).
    if (irmao->getCor() == PRETO)
    {
        // As instru��es a seguir apenas for�am o vermelho a ficar � esquerda do
         // esquerda do pai, ou direita da direita, ent�o o caso seis ir� girar
         // corretamente.
        if ((n == n->getPai(n)->getEsq()) && (irmao->getDir()->getCor() == PRETO) &&
                (irmao->getEsq()->getCor() == VERMELHO))
        {
            // Este �ltimo teste tamb�m � trivial devido aos casos 2-4.
            irmao->setCor(VERMELHO);
            irmao->getEsq()->setCor(PRETO);
            rotacao_direita(irmao);

        }
        else if ((n == n->getPai(n)->getDir()) && (irmao->getEsq()->getCor() == PRETO) &&
                 (irmao->getDir()->getCor() == VERMELHO))
        {
           // Este �ltimo teste tamb�m � trivial devido aos casos 2-4.
            irmao->setCor(VERMELHO);
            irmao->getDir()->setCor(PRETO);
            rotacao_esquerda(irmao);

        }
    }
    deleta_caso6(n);
}
/*
Irmao (I) eh preto, filho direito de I eh vermelho, e N eh o filho esquerdo do pai P .
Neste caso, giramos a esquerda em P , de modo que I torna-se o pai de P.
Em seguida, trocamos as cores de P e I e tornamos o filho certo de I preto.
A subarvore ainda tem a mesma cor em sua raiz, ent�o as propriedades 4
(ambos os filhos de cada noh vermelho s�o pretos) e 5 (todos os caminhos
de qualquer noh dado para seus
nohss folha cont�m o mesmo n�mero de n�s pretos)
nao foram violadas
*/
void AVP::deleta_caso6(NoVP* n)
{
    NoVP* irmao = n->GetIrmao(n);
    NoVP* pai = n->getPai(n);

    irmao->setCor(pai->getCor());
    pai->setCor(PRETO);


    if (n == pai->getEsq())
    {
        irmao->getDir()->setCor(PRETO);
        rotacao_esquerda(pai);

    }
    else
    {
        irmao->getEsq()->setCor(PRETO);
        rotacao_direita(pai);

    }
}


/*
 * substitui um no
 */
void AVP::substitui_no(NoVP* velho, NoVP* novo) {

 if (velho->getPai(velho) == NULL)
    {
        this->raiz = novo;
    }
    else
    {
        if (velho == velho->getPai(velho)->getEsq())
            velho->getPai(velho)->setEsq(novo);
        else
            velho->getPai(velho)->setDir(novo);
    }
    if (novo != NULL)
    {
        novo->setPai(velho->getPai(velho));
    }
}


/*
 * Deleta noh da AVP
 */


void AVP::deleta(int val)
{
    NoVP* filho;

    NoVP* n = busca_no(val);

    if (n == NULL)
        return;
    if (n->getEsq() != NULL && n->getDir() != NULL)
    {
        NoVP* pred = noMaximo(n->getEsq());
        n->setInfo(pred->getInfo());
        n = pred;
    }
    assert(n->getEsq()== NULL || n->getDir() == NULL);

    filho = n->getDir() == NULL ? n->getEsq()  : n->getDir();

    if (n->noh_cor(n) == PRETO)
    {
        n->setCor(filho->noh_cor(n));
        deleta_caso1(n);
    }
    substitui_no(n, filho);
    free(n);
    //delete(n);
    verifica_propriedades();
}


//Busca
bool AVP::busca(int val)
{
    return auxBusca(raiz, val);
}

bool AVP::auxBusca(NoVP *p, int val)
{
    if(p == NULL)
    {
        return false;
    }
    else if(p->getInfo() == val)
    {

        return true;
    }

    else if(val < p->getInfo())
    {

        return auxBusca(p->getEsq(), val);
    }
    else
    {
        return auxBusca(p->getDir(), val);
    }

}

void AVP::rotacao_esquerda(NoVP* n)
{

    //nnovo eh noh auxiliar
    NoVP* nnovo = n->getDir();
    //p eh noh pai do no passado
    NoVP* p = n->getPai(n);

    //A fun��o assert() testa se uma express�o � true (verdadeira). Sa express�o for falsa (false),
    //o assert interrompe a execucao do programa.

    assert(nnovo != nullptr);  //Como as folhas de uma arvore vermelho-preto estao vazias,
    //elas nao podem se tornar nos internos.

    //realiza a rotacao
    n->setDir(nnovo->getEsq());
    nnovo->setEsq(n);
    n->setPai(nnovo);

    // Lidar com outros ponteiros filho/pai.

    if (n->getDir() != nullptr)
    {
        n->getDir()->setPai(n);

    }

    //Inicialmente n poderia ser a raiz.
    if (p != nullptr)
    {
        if (n == p->getEsq())
        {
            p->setEsq(nnovo);
        }
        else if (n == p->getDir())
        {
            p->setDir(nnovo);
        }
    }
    nnovo->setPai(p);
}

void AVP::rotacao_direita(NoVP* n)
{

    //nnovo eh um noh auxiliar
    NoVP* nnovo = n->getEsq();
    //p eh noh pai do no passado
    NoVP* p = n->getPai(n);

    assert(nnovo != nullptr); //Como as folhas de uma arvore vermelho-preto estao vazias,
    //elas nao podem se tornar nos internos.

    //realiza a rotacao
    n->setEsq(nnovo->getDir());
    nnovo->setDir(n);
    n->setPai(nnovo);

    //Lidar com outros ponteiros filho/pai.
    if (n->getEsq() != nullptr)
    {
        n->getEsq()->setPai(n);

    }

    //Inicialmente n poderia ser a raiz.
    if (p != nullptr)
    {
        if (n == p->getEsq())
        {
            p->setEsq(nnovo);
        }
        else if (n == p->getDir())
        {
            p->setDir(nnovo);
        }
    }
    nnovo->setPai(p);
}

//Insercao
/*
* A insercao come�a adicionando o noh de uma maneira muito semelhante a uma insercao de arvore de pesquisa binaria
de busca. A grande diferen�a eh que na arvore binaria de busca um novo noh
eh adicionado como uma folha,que nao contem nenhuma informacao sobre cor e sem verificacao. Na arvore vermelho-preto,
entao, em vez disso, o novo noh eh inserido como folha e vermelho, em seguida, eh verificado se as propriedades da arvore vermelho preto
foram violadas
*
*/

/*
Observa-se que:

A propriedade 1 (cada n� � vermelho ou preto) e a propriedade 3 (todas as folhas s�o pretas) sempre s�o v�lidas.
A propriedade 2 (a raiz � preta) � verificada e corrigida com o caso 1.
A propriedade 4 (n�s vermelhos t�m apenas filhos pretos) � amea�ada apenas pela adi��o de um n� vermelho, repintura de um n� de preto para vermelho ou uma rota��o.
A propriedade 5 (todos os caminhos de qualquer n� dado para suas folhas t�m o mesmo n�mero de n�s pretos) � amea�ada apenas pela adi��o de um n� preto, repintura de um n� ou uma rota��o.
*/

/*
Caso 1: O n� atual N est� na raiz da �rvore. Nesse caso, � repintado de preto para satisfazer a propriedade 2
 (a raiz � preta). Uma vez que isso adiciona um n� preto a cada caminho de uma vez, a propriedade 5
 (todos os caminhos de qualquer n� dado para seus n�s folha cont�m o mesmo n�mero de n�s pretos) n�o � violada.
*/
void AVP::insereCaso1(NoVP* n)
{
    n->setCor(PRETO);
}

/*
Caso 2: A propriedade 2 (a raiz � preta) � verificada e corrigida com o caso 1

Sendo o pai P do noh atual preto, ent�o a propriedade 4 (ambos os filhos de cada n�
vermelho s�o pretos) � v�lida. A propriedade 5 (todos os caminhos de qualquer n� dado
 para seus n�s folhas cont�m o mesmo n�mero de n�s pretos) n�o est� amea�ada, porque o
 novo n� N tem dois filhos folhas pretas, mas porque N � vermelho, os caminhos atrav�s
de cada um de seus filhos t�m o mesmo n�mero de n�s pretos que o caminho atrav�s da
folha que ele substituiu, que era preto, e assim essa propriedade permanece satisfeita.
Portanto, a �rvore permanece v�lida.
*/
void AVP::insereCaso2(NoVP* n)
{
//Nao faz nada, pois a arvore continua valida.
    return;
}

/*
Caso 3: se o pai P e o tio U s�o vermelhos, ambos podem ser repintados de preto e
o av� G torna-se vermelho para manter a propriedade 5 (todos os caminhos de um
n� para as folhas cont�m o mesmo n�mero de n�s pretos) . Uma vez que qualquer
caminho atrav�s dos pais ou tio deve passar pelo av�, o n�mero de n�s pretos
nesses caminhos n�o mudou. No entanto, o av� G pode agora violar a Propriedade
2 (a raiz � preta) se for a raiz ou a Propriedade 4 (ambos os filhos de cada n� vermelho s�o pretos)
se ele tiver um pai vermelho. Para corrigir isso, o procedimento de reparo vermelho-preto da �rvore
� executado novamente em G.
*/

void AVP::insereCaso3(NoVP* n)
{
    n->getPai(n)->setCor(PRETO);
    n->GetTio(n)->setCor(PRETO);
    n->GetAvo(n)->setCor(VERMELHO);
    insereCorrecao(n->GetAvo(n));
}

/*
Caso 4, etapa 1: O pai P � vermelho, mas o tio U � preto. Neste caso, realizamos uma rota��o em P
que muda os pap�is do novo n� N e de seu pai P. E tanto P quanto N s�o vermelhos, ent�o propriedade 5
(todos os caminhos de um n� para suas folhas cont�m o mesmo n�mero de preto n�s) � preservado.
 A propriedade 4 (ambos os filhos de cada n� vermelho s�o pretos) � restaurada na etapa 2
*/

void AVP::insereCaso4(NoVP* n)
{

    NoVP* p = n->getPai(n);
    NoVP* g = n->GetAvo(n);

    if (n == p->getDir() && p == g->getEsq())
    {
        rotacao_esquerda(p);
        n = n->getEsq();
    }
    else if (n == p->getEsq() && p == g->getDir())
    {
        rotacao_direita(p);
        n = n->getDir();
    }

    insereCaso4etapa2(n);
}

/*
Caso 4, etapa 2: Faz a rota��o sobre o av� G,  colocando P no lugar de G e tornando P o pai
de N e G. G � preto e seu antigo filho P � vermelho, pois a propriedade 4 foi violada.
Trocamos ent�o as cores de P e G.
*/

void AVP::insereCaso4etapa2(NoVP* n)
{

    NoVP* p = n->getPai(n);
    NoVP* g = n->GetAvo(n);

    if (n == p->getEsq())
    {
        rotacao_direita(g);
    }
    else
    {
        rotacao_esquerda(g);
    }
    p->setCor(PRETO);
    g->setCor(VERMELHO);
}

void AVP::insereRecursivo(NoVP* raiz, NoVP* n)
{
    //Desce recursivamente na �rvore ate que uma folha seja encontrada.

    //se raiz nao eh nula
    if (raiz != nullptr)
    {
        //se a info eh menor vai para esquerda
        if (n->getInfo() < raiz->getInfo())
        {
            if (raiz->getEsq() != nullptr)
            {
                insereRecursivo(raiz->getEsq(), n);
                return;
            }
            else
            {
                raiz->setEsq(n);
            }
        }
        else     // se a info eh maior ou igual vai para direita
        {
            if (raiz->getDir() != nullptr)
            {
                insereRecursivo(raiz->getDir(), n);
                return;
            }
            else
            {
                raiz->setDir(n);
            }
        }
    }

    //inser um novo noh n.
    n->setPai(raiz);
    n->setEsq(nullptr);
    n->setDir(nullptr);
    n->setCor(VERMELHO);
}

/*
Para correcao, existem varios casos de insercao da arvore vermelho-preto para lidar:

1) N eh o noh raiz, ou seja, o primeiro noh da arvoreVP
2) O pai de N (P) eh preto
3) P eh vermelho (entao nao pode ser a raiz da arvore) e o tio de N (T) eh vermelho
4) P eh vermelho e T eh preto
*/
void AVP::insereCorrecao(NoVP* n)
{
    if (n->getPai(n) == nullptr)
    {
        insereCaso1(n);
    }
    else if (n->getPai(n)->getCor()== PRETO)
    {
        insereCaso2(n);
    }
    else if (n->GetTio(n) != nullptr && n->GetTio(n)->getCor() == VERMELHO)
    {
        insereCaso3(n);
    }
    else
    {
        insereCaso4(n);
    }
}

NoVP* AVP::auxinsere(NoVP* raiz, NoVP* n)
{
//Insere um novo noh na �rvore atual.
    insereRecursivo(raiz, n);

    //Repara a arvore no caso de qualquer uma das propriedades vermelho-preto ter sido violada.
    insereCorrecao(n);

    //Encontre a nova raiz para retornar.
    raiz = n;
    while (raiz->getPai(raiz) != nullptr)
    {
        raiz = raiz->getPai(raiz);
    }
    return raiz;
}

void AVP::insere(int val)
{
    NoVP* n = new NoVP();
    n->setCor(VERMELHO);
    n->setInfo(val);
    n->setEsq(NULL);
    n->setDir(NULL);
    raiz = auxinsere(raiz, n);


}

/*
 * Imprime Arvore Vermelho-Preta
 */
void AVP::imprime_aux(NoVP* n, int indent)
{
    int i;
    if (n == NULL)
    {
        fputs("<empty tree>", stdout);
        return;
    }
    if (n->dir != NULL)
    {
        imprime_aux(n->dir, indent + INDENT_STEP);
    }
    for(i = 0; i < indent; i++)
        fputs(" ", stdout);
    if (n->getCor() == PRETO)
        cout<<(int)n->info<<endl;
    else
        //noh vermelho aparece entre o simbolo "<>"
        cout<<"<"<<(int)n->info<<">"<<endl;
    if (n->esq != NULL)
    {
        imprime_aux(n->esq, indent + INDENT_STEP);
    }
}

void AVP::imprime_AVP()
{
    imprime_aux(raiz, 0);
    puts("");
}

