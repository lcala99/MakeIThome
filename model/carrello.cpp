#include "carrello.h"
#include "cocktail.h"

Carrello::Carrello() {}

Vettore<Ingrediente> Carrello::calcolaIngredienti()const{
    Vettore<Ingrediente> ret;
    //scorro i prodotti
    for(auto it=prodotti.cbegin(); it!=prodotti.cend(); it++){
        Prodotto* p=it->first.get();
        if(p){
            Vettore<Ingrediente> ingr = p->getIngredienti();
            //scorro l'ingrediente del prodotto
            for(auto iti=ingr.begin(); iti!= ingr.end(); iti++){
                bool trovato=false;
                //scorro lista per vedere se quell'ingrediente è gia presente
                for(auto itr=ret.begin(); itr!=ret.end() && !trovato; itr++){
                    if(iti->getNome() == itr->getNome()){
                        (*itr) = (*itr)*(it->second);
                        trovato=true;
                    }
                }
                if(!trovato){
                    (*iti) = (*iti)*it->second;
                    ret.push_back(*iti);
                }
            }
        }
    }
    return ret;
}

Vettore<std::pair<DeepPtr<Prodotto>,u_int>> Carrello::getProdotti()const{
    return prodotti;
}

void Carrello::aggiungiProdotto(const Prodotto& bev,int Quantita){
    bool trovato = false;
    for(Vettore<std::pair<DeepPtr<Prodotto>,u_int>>::Iteratore it = prodotti.begin(); !trovato && it!=prodotti.end(); it++ ){
        if(it->first.get()->getNome() == bev.getNome()){
            it->second += Quantita;
            trovato=true;
        }
    }
    if(!trovato){
        prodotti.push_back(std::pair<DeepPtr<Prodotto>,u_int>(bev.clone(),Quantita));
    }
}

void Carrello::rimuoviProdotto(const Prodotto& bev){
    bool trovato = false;
    for(Vettore<std::pair<DeepPtr<Prodotto>,u_int>>::Iteratore it = prodotti.begin(); !trovato && it!=prodotti.end(); it++ ){
        if(it->first.get()->getNome() == bev.getNome()){
            prodotti.remove(it);
            trovato=true;
        }
    }
}























