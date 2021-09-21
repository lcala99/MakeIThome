#include <typeinfo>
#include "catalogo.h"
#include"jsonio.h"

Catalogo::Catalogo(){
    JsonIO::load("database.json",this);
}

Catalogo::~Catalogo(){
    JsonIO::save("database.json",this);
}

Catalogo::Catalogo(Vettore<DeepPtr<Prodotto>> _prodotto):prodotto(_prodotto){}

void Catalogo::aggiungiProdotto(const Prodotto& bev){
    if(prodotto.empty()){
        prodotto.push_back(DeepPtr<Prodotto>(bev.clone()));
        return;
    }
    for(Vettore<DeepPtr<Prodotto>>::Iteratore it = prodotto.begin(); it != prodotto.end(); it++){
        if((*it).get() == &bev)return;
    }
    prodotto.push_back(DeepPtr<Prodotto>(bev.clone()));
}

const Vettore<DeepPtr<Prodotto>>& Catalogo::listaProdotti()const{
    return prodotto;
}


Vettore<DeepPtr<Bevanda> > Catalogo::listaAnalcolici() const{
    Vettore<DeepPtr<Bevanda>> aux;
    for(auto it = prodotto.cbegin(); it != prodotto.cend(); it++){
        Bevanda *temp = dynamic_cast<Bevanda*>(it->get());
        if(temp && temp->getGradazione()==0){
            aux.push_back(DeepPtr<Bevanda>(temp->clone()));
        }
    }
    return aux;
}

Vettore<DeepPtr<Bevanda> > Catalogo::listaAlcolici() const{
    Vettore<DeepPtr<Bevanda>> aux;
    for(auto it = prodotto.cbegin(); it != prodotto.cend(); it++){
        Bevanda *temp = dynamic_cast<Bevanda*>(it->get());
        if(temp && temp->getGradazione()>0){
            aux.push_back(DeepPtr<Bevanda>(temp->clone()));
        }
    }
    return aux;
}

Vettore<DeepPtr<Cocktail>> Catalogo::listaCocktail()const{
    Vettore<DeepPtr<Cocktail>> aux;
    for(auto it = prodotto.cbegin(); it != prodotto.cend(); it++){
        Cocktail *temp = dynamic_cast<Cocktail*>(it->get());
        if(temp){
            aux.push_back(DeepPtr<Cocktail>(temp->clone()));
        }
    }
    return aux;
}
Vettore<DeepPtr<Cibo>> Catalogo::listaCibi()const{
    Vettore<DeepPtr<Cibo>> aux = Vettore<DeepPtr<Cibo>>();
    for(auto it = prodotto.cbegin(); it != prodotto.cend(); it++){
        Cibo *temp = dynamic_cast<Cibo*>(it->get());
        if(temp){
            aux.push_back(DeepPtr<Cibo>(temp->clone()));
        }
    }
    return aux;
}

void Catalogo::accept(JsonIO::Visitor *visitor) const {
    visitor->visitCatalogo(this);
}

