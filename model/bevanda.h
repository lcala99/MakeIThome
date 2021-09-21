#ifndef BEVANDA_H
#define BEVANDA_H
#include<iostream>
#include <string>
#include "vettore.h"
#include "ingrediente.h"
#include "carrello.h"
#include "prodotto.h"
#include "jsonio.h"

typedef unsigned int u_int;
using std::string;

class Bevanda: public Prodotto {
    protected:
        u_int gradazione;
    public:
        Bevanda(string Nome,u_int Quantita,string path, u_int Gradazione = 0);
        Bevanda(const Bevanda& b);

        virtual u_int getGradazione() const;
        Vettore<Ingrediente> getIngredienti() const override;
        bool operator ==(const Prodotto &second)const override;
        Bevanda* clone() const override;
        void accept(JsonIO::Visitor *visitor) const override;
};

#endif // BEVANDA_H
