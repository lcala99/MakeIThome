#include <iostream>
#include<typeinfo>
#include "cocktail.h"

Cocktail::Cocktail(string Nome, u_int Quantita,string path, Vettore<Ingrediente> ing,  u_int Gradazione) :
    Bevanda(Nome,Quantita,path, Gradazione), ingredienti(ing) {}

Vettore<Ingrediente> Cocktail::getIngredienti() const{
    return ingredienti;
}

bool Cocktail::operator ==(const Prodotto &second)const{
    return Bevanda::operator==(second) && ingredienti == static_cast<const Cocktail&>(second).ingredienti;
}

Cocktail* Cocktail::clone() const{
    return new Cocktail(*this);
}

void Cocktail::accept(JsonIO::Visitor *visitor)const{
    visitor->visitCocktail(this);
}
