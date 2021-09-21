#include <typeinfo>
#include "prodotto.h"

Prodotto::Prodotto(string Nome,u_int Quantita, std::string path): nome(Nome), quantita(Quantita), imgPath(path){}

Prodotto::~Prodotto(){}


bool Prodotto::operator ==(const Prodotto& second)const{
    return typeid (*this) == typeid (second) && nome == second.nome && quantita == second.quantita;
}

string Prodotto::getNome() const{
    return nome;
}

string Prodotto::getPath() const{
    return imgPath;
}

u_int Prodotto::getQuantita() const{
    return quantita;
}

