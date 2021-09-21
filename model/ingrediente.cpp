#include "ingrediente.h"
#include<iostream>
Ingrediente::Ingrediente(){}

Ingrediente::Ingrediente(string n, u_int q, bool l):nome(n), quantita(q),isLiquido(l){}

Ingrediente::Ingrediente(const Ingrediente& ing):nome(ing.getNome()), quantita(ing.getQuantita()),isLiquido(ing.isLiquido){}


Ingrediente::~Ingrediente(){}


Ingrediente Ingrediente::operator*(const u_int c)const{

    return  Ingrediente(nome,quantita*c,isLiquido);
}

Ingrediente Ingrediente::operator/(const u_int c)const{
    return  Ingrediente(nome,quantita/c,isLiquido);
}

Ingrediente Ingrediente::operator+(const Ingrediente& ing) const {
    return Ingrediente(nome, quantita+ing.quantita, isLiquido);
}

Ingrediente Ingrediente::operator+(const u_int c)const{
    return  Ingrediente(nome,quantita+c,isLiquido);
}

bool Ingrediente::operator==(Ingrediente& c) const{
    return nome==c.getNome() && quantita== c.getQuantita() && isLiquido==c.isLiquido;
}

string Ingrediente:: getNome()const{return nome;}


u_int Ingrediente::getQuantita()const{return quantita; }

bool Ingrediente::IsLiquido()const{return isLiquido;}

Ingrediente::operator u_int() const{return quantita;}

Ingrediente* Ingrediente::clone() const{
    return new Ingrediente(*this);
}

void Ingrediente::accept(JsonIO::Visitor *visitor)const{
    visitor->visitIngrediente(this);
}
