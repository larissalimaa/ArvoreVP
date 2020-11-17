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

// Função auxiliar do destrutor da árvore VP
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
Removemos um noh preto de cada caminho e a nova raiz eh preta, portanto, as propriedades são preservadas.
 */
void AVP::deleta_caso1(NoVP* n)
{
    if (n->getPai(n) == NULL)
        return;
    else
        deleta_caso2(n);
}

/*
 * Caso 2: O irmão(I) é vermelho. Nesse caso, invertemos as cores do pai (P) e  do irmao (I) e, em seguida,
 giramos para a esquerda em P, transformando irmão(I) no avô de N. Observe que P tem que ser
 preto porque teve um filho vermelho. A subárvore resultante tem um caminho curto um nó
 preto, então não terminamos. Agora N tem um irmão preto e um pai vermelho, então podemos
 prosseguir para a etapa 4, 5 ou 6. (Seu novo irmão é preto porque já foi filho do (I) vermelho).
 Em casos posteriores, vamos renomear N novo irmão como I.
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
 Caso 3:  Pai (P), Irmao (I) e filhos de I são pretos. Neste caso, simplesmente repintamos I vermelho.
 O resultado eh que todos os caminhos que passam por I, que são precisamente aqueles caminhos que nao
 passam por N, tem um noh preto a menos. Como a exclusao do pai original de N fez com que
 todos os caminhos que passam por N tivessem um noh preto a menos, isso equilibra as coisas.
 No entanto, todos os caminhos através de P agora têm um noh preto a menos do que os caminhos
 que não passam por P, entao a propriedade 5 (todos os caminhos de qualquer noh dado para
 seus nos folha contêm o mesmo numero de nos pretos) ainda eh violada.
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
 * Caso4: Os filhos de I(Irmao) e o I são pretos, mas Pai (P) é vermelho. Neste caso, simplesmente trocamos as cores de I e P.
 Isso nao afeta o numero de nós pretos nos caminhos que passam por I, mas adiciona um ao numero de nohs pretos
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
o filho esquerdo de I se torne o pai de I e o novo irmão de N. Em seguida, trocamos as
 cores de I e de seu novo pai. Todos os caminhos ainda tem o mesmo número de nohs pretos,
 mas agora N tem um irmao preto cujo filho direito eh vermelho, então caimos no caso 6.
 Nem N nem seu pai são afetados por esta transformação. (Novamente, para o caso 6, renomeamos o novo irmão de N como I.)

*/
void AVP::deleta_caso5(NoVP* n)
{
    NoVP* irmao = n->GetIrmao(n);

    // Esta instrução if é trivial, devido ao caso 2 (mesmo que o caso 2 tenha mudado
    // irmão do filho do irmão, o filho do irmão não pode ser vermelho, pois
    // nenhum pai vermelho pode ter um filho vermelho).
    if (irmao->getCor() == PRETO)
    {
        // As instruções a seguir apenas forçam o vermelho a ficar à esquerda do
         // esquerda do pai, ou direita da direita, então o caso seis irá girar
         // corretamente.
        if ((n == n->getPai(n)->getEsq()) && (irmao->getDir()->getCor() == PRETO) &&
                (irmao->getEsq()->getCor() == VERMELHO))
        {
            // Este último teste também é trivial devido aos casos 2-4.
            irmao->setCor(VERMELHO);
            irmao->getEsq()->setCor(PRETO);
            rotacao_direita(irmao);

        }
        else if ((n == n->getPai(n)->getDir()) && (irmao->getEsq()->getCor() == PRETO) &&
                 (irmao->getDir()->getCor() == VERMELHO))
        {
           // Este último teste também é trivial devido aos casos 2-4.
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
A subarvore ainda tem a mesma cor em sua raiz, então as propriedades 4
(ambos os filhos de cada noh vermelho são pretos) e 5 (todos os caminhos
de qualquer noh dado para seus
nohss folha contêm o mesmo número de nós pretos)
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

    //A função assert() testa se uma expressão é true (verdadeira). Sa expressão for falsa (false),
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
* A insercao começa adicionando o noh de uma maneira muito semelhante a uma insercao de arvore de pesquisa binaria
de busca. A grande diferença eh que na arvore binaria de busca um novo noh
eh adicionado como uma folha,que nao contem nenhuma informacao sobre cor e sem verificacao. Na arvore vermelho-preto,
entao, em vez disso, o novo noh eh inserido como folha e vermelho, em seguida, eh verificado se as propriedades da arvore vermelho preto
foram violadas
*
*/

/*
Observa-se que:

A propriedade 1 (cada nó é vermelho ou preto) e a propriedade 3 (todas as folhas são pretas) sempre são válidas.
A propriedade 2 (a raiz é preta) é verificada e corrigida com o caso 1.
A propriedade 4 (nós vermelhos têm apenas filhos pretos) é ameaçada apenas pela adição de um nó vermelho, repintura de um nó de preto para vermelho ou uma rotação.
A propriedade 5 (todos os caminhos de qualquer nó dado para suas folhas têm o mesmo número de nós pretos) é ameaçada apenas pela adição de um nó preto, repintura de um nó ou uma rotação.
*/

/*
Caso 1: O nó atual N está na raiz da árvore. Nesse caso, é repintado de preto para satisfazer a propriedade 2
 (a raiz é preta). Uma vez que isso adiciona um nó preto a cada caminho de uma vez, a propriedade 5
 (todos os caminhos de qualquer nó dado para seus nós folha contêm o mesmo número de nós pretos) não é violada.
*/
void AVP::insereCaso1(NoVP* n)
{
    n->setCor(PRETO);
}

/*
Caso 2: A propriedade 2 (a raiz é preta) é verificada e corrigida com o caso 1

Sendo o pai P do noh atual preto, então a propriedade 4 (ambos os filhos de cada nó
vermelho são pretos) é válida. A propriedade 5 (todos os caminhos de qualquer nó dado
 para seus nós folhas contêm o mesmo número de nós pretos) não está ameaçada, porque o
 novo nó N tem dois filhos folhas pretas, mas porque N é vermelho, os caminhos através
de cada um de seus filhos têm o mesmo número de nós pretos que o caminho através da
folha que ele substituiu, que era preto, e assim essa propriedade permanece satisfeita.
Portanto, a árvore permanece válida.
*/
void AVP::insereCaso2(NoVP* n)
{
//Nao faz nada, pois a arvore continua valida.
    return;
}

/*
Caso 3: se o pai P e o tio U são vermelhos, ambos podem ser repintados de preto e
o avô G torna-se vermelho para manter a propriedade 5 (todos os caminhos de um
nó para as folhas contêm o mesmo número de nós pretos) . Uma vez que qualquer
caminho através dos pais ou tio deve passar pelo avô, o número de nós pretos
nesses caminhos não mudou. No entanto, o avô G pode agora violar a Propriedade
2 (a raiz é preta) se for a raiz ou a Propriedade 4 (ambos os filhos de cada nó vermelho são pretos)
se ele tiver um pai vermelho. Para corrigir isso, o procedimento de reparo vermelho-preto da árvore
é executado novamente em G.
*/

void AVP::insereCaso3(NoVP* n)
{
    n->getPai(n)->setCor(PRETO);
    n->GetTio(n)->setCor(PRETO);
    n->GetAvo(n)->setCor(VERMELHO);
    insereCorrecao(n->GetAvo(n));
}

/*
Caso 4, etapa 1: O pai P é vermelho, mas o tio U é preto. Neste caso, realizamos uma rotação em P
que muda os papéis do novo nó N e de seu pai P. E tanto P quanto N são vermelhos, então propriedade 5
(todos os caminhos de um nó para suas folhas contêm o mesmo número de preto nós) é preservado.
 A propriedade 4 (ambos os filhos de cada nó vermelho são pretos) é restaurada na etapa 2
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
Caso 4, etapa 2: Faz a rotação sobre o avô G,  colocando P no lugar de G e tornando P o pai
de N e G. G é preto e seu antigo filho P é vermelho, pois a propriedade 4 foi violada.
Trocamos então as cores de P e G.
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
    //Desce recursivamente na árvore ate que uma folha seja encontrada.

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
//Insere um novo noh na árvore atual.
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

