#include "model.h"

Model::Model(Catalogo cat): catalogo(cat), carrello(){}

const Catalogo& Model::getCatalogo()const{return catalogo;}

const Carrello& Model::getCarrello()const{return carrello;}

void Model::aggiungiProdottoCarrello(const Prodotto &prodotto, int quantita){
    carrello.aggiungiProdotto(prodotto, quantita);
}

void Model::rimuoviProdottoCarrello(const Prodotto &prodotto){
    carrello.rimuoviProdotto(prodotto);
}

void Model::aggiungiProdottoCatalogo(const Prodotto &prodotto){
    catalogo.aggiungiProdotto(prodotto);
}

Model::~Model(){}
