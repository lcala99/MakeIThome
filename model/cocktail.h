#ifndef COCKTAIL_H
#define COCKTAIL_H

#include<iostream>
#include "vettore.h"
#include "ingrediente.h"
#include "carrello.h"
#include "bevanda.h"
#include "jsonio.h"

typedef unsigned int u_int;

class Cocktail : public Bevanda{
private:
    Vettore<Ingrediente> ingredienti;
public:
    Cocktail(string Nome, u_int Quantita,string path,Vettore<Ingrediente> ing, u_int Grad=0);
     Vettore<Ingrediente> getIngredienti() const override;
    bool operator ==(const Prodotto &second)const override;
    Cocktail* clone() const override;
    void accept(JsonIO::Visitor *visitor) const override;
};

#endif // COCKTAIL_H
