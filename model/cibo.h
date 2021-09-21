#ifndef CIBO_H
#define CIBO_H
#include "prodotto.h"
#include "ingrediente.h"
#include "vettore.h"
#include "jsonio.h"

typedef unsigned int u_int;
class Cibo: public Prodotto{
    private:
        Vettore<Ingrediente> ingredienti;
    public:
        Cibo(string nome,u_int Quantita,string path,Vettore<Ingrediente> Comp);
        bool operator ==(const Prodotto &second)const override;
        Vettore<Ingrediente> getIngredienti()const override;
        Cibo* clone() const override;
        void accept(JsonIO::Visitor *visitor) const override;
};

#endif // CIBO_H
