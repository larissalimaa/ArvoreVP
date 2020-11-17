#include <iostream>
#include "AVP.h"

using namespace std;


int main()
{

    //int i;
    AVP* arvoreVP = new AVP();

    /*for (i = 0; i < 12; i++)
    {
        //int x = rand() % 10;
        //int x = i;
        cout<<"Inserindo "<<x<<" -> "<<endl<<endl;
        arvoreVP->insere(x);
        arvoreVP->imprime_AVP();
    }*/

    cout<<"Inserting "<<1<<" -> "<<endl<<endl;
    arvoreVP->insere(1);
    arvoreVP->imprime_AVP();

    cout<<"Inserting "<<4<<" -> "<<endl<<endl;
    arvoreVP->insere(4);
    arvoreVP->imprime_AVP();

    cout<<"Inserting "<<9<<" -> "<<endl<<endl;
    arvoreVP->insere(9);
    arvoreVP->imprime_AVP();

    cout<<"Inserting "<<8<<" -> "<<endl<<endl;
    arvoreVP->insere(8);
    arvoreVP->imprime_AVP();

    cout<<"Inserting "<<2<<" -> "<<endl<<endl;
    arvoreVP->insere(2);
    arvoreVP->imprime_AVP();


    cout<<"Inserting "<<5<<" -> "<<endl<<endl;
    arvoreVP->insere(5);
    arvoreVP->imprime_AVP();

    cout<<"Inserting "<<1<<" -> "<<endl<<endl;
    arvoreVP->insere(1);
    arvoreVP->imprime_AVP();

    cout<<"Inserting "<<1<<" -> "<<endl<<endl;
    arvoreVP->insere(1);
    arvoreVP->imprime_AVP();

    cout<<"Inserting "<<5<<" -> "<<endl<<endl;
    arvoreVP->insere(5);
    arvoreVP->imprime_AVP();

    cout<<"Inserting "<<7<<" -> "<<endl<<endl;
    arvoreVP->insere(7);
    arvoreVP->imprime_AVP();

    cout<<"Inserting "<<1<<" -> "<<endl<<endl;
    arvoreVP->insere(1);
    arvoreVP->imprime_AVP();

    cout<<"Inserting "<<2<<" -> "<<endl<<endl;
    arvoreVP->insere(2);
    arvoreVP->imprime_AVP();

    bool achou = arvoreVP->busca(2);
    cout<< endl << endl;
    cout << "Achou? -> ";
    cout << achou << endl;

    cout<<"Deletando "<<8<<" -> "<<endl<<endl;
    arvoreVP->deleta(8);
    arvoreVP->imprime_AVP();

    return 0;
}


