#ifndef CARRELLO_H
#define CARRELLO_H

using namespace std;

#include <iostream>
#include "vettore.h"
#include "deepptr.h"
#include "prodotto.h"
#include "ingrediente.h"
#include "cibo.h"
#include "bevanda.h"

class Ingrediente;
class Prodotto;

typedef unsigned int u_int;

class Carrello{

private:
    Vettore<pair<DeepPtr<Prodotto>,u_int>> prodotti;
public:
    Carrello();
    Vettore<Ingrediente> calcolaIngredienti()const;
    Vettore<pair<DeepPtr<Prodotto>,u_int>> getProdotti()const;
    void aggiungiProdotto(const Prodotto& bev,int Quantita);
    void rimuoviProdotto(const Prodotto& bev);
};

#endif // CARRELLO_H
