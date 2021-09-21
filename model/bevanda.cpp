#include "bevanda.h"
#include<typeinfo>
#include <iostream>

Bevanda::Bevanda(string Nome,u_int Quantita, string path,u_int Gradazione):Prodotto(Nome,Quantita,path), gradazione(Gradazione){}

Bevanda::Bevanda(const Bevanda& b):Prodotto(b.nome,b.quantita, b.imgPath){
    gradazione=b.gradazione;
}

u_int Bevanda::getGradazione() const{
    return gradazione;
}

Vettore<Ingrediente> Bevanda::getIngredienti() const{
    return Vettore<Ingrediente>(Ingrediente(nome,quantita));

}

bool Bevanda::operator==(const Prodotto& second)const {
    return Prodotto::operator==(second) && gradazione == static_cast<const Bevanda&>(second).gradazione;
}

Bevanda* Bevanda::clone() const{
    return new Bevanda(*this);
}

void Bevanda::accept(JsonIO::Visitor *visitor)const{
    visitor->visitBevanda(this);
}
