#include<typeinfo>
#include "cibo.h"

Cibo::Cibo(string Nome, u_int Quantita,string path, Vettore<Ingrediente> ing) :
    Prodotto(Nome,Quantita,path), ingredienti(ing) {}

bool Cibo::operator ==(const Prodotto &second)const{
    return Prodotto::operator==(second) && ingredienti == static_cast<const Cibo&>(second).ingredienti;
}

Vettore<Ingrediente> Cibo::getIngredienti() const{
    return ingredienti;
}

Cibo* Cibo::clone() const{
    return new Cibo(*this);
}

void Cibo::accept(JsonIO::Visitor *visitor)const{
    visitor->visitCibo(this);
}

