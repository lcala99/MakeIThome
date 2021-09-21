#include "controller.h"

Controller::Controller(Model* modello):_model(modello), _view(nullptr){}

void Controller::setView(View* view){
    _view = view;

    //connect tutte le cose
}

const Catalogo& Controller::getCatalogo() const{
    return _model->getCatalogo();
}

const Carrello &Controller::getCarrello() const{
    return _model->getCarrello();
}

void Controller::c_addToCart(Prodotto* prod, int q){
    if(q>0) _model->aggiungiProdottoCarrello(*prod,q);
}

void Controller::c_removeFromCart(Prodotto& prod){
    _model->rimuoviProdottoCarrello(prod);
}
