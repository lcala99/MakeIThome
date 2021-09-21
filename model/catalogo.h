#ifndef CATALOGO_H
#define CATALOGO_H
#include"vettore.h"
#include"prodotto.h"
#include "deepptr.h"
#include "ingrediente.h"
#include "bevanda.h"
#include "cocktail.h"
#include "cibo.h"
#include "jsonio.h"
class Catalogo
{
private:
     Vettore<DeepPtr<Prodotto>> prodotto;
public:
    Catalogo();
    ~Catalogo();
    Catalogo(Vettore<DeepPtr<Prodotto>> _prodotto);
    void aggiungiProdotto(const Prodotto& bev);
    const Vettore<DeepPtr<Prodotto>>& listaProdotti()const;
    Vettore<DeepPtr<Bevanda>> listaAnalcolici()const;
    Vettore<DeepPtr<Bevanda>> listaAlcolici()const;
    Vettore<DeepPtr<Cocktail>> listaCocktail()const;
    Vettore<DeepPtr<Cibo>> listaCibi()const;
    virtual void accept(JsonIO::Visitor *visitor) const ;
};

#endif // CATALOGO_H
