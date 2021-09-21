#ifndef PRODOTTO_H
#define PRODOTTO_H
#include <string>
#include "vettore.h"
#include "ingrediente.h"
#include "jsonio.h"

using namespace std;
typedef unsigned int u_int;

class Prodotto{
protected:
    string nome;
    u_int quantita;
    string imgPath;
public:
    Prodotto(string Nome,u_int Quantita, string path);
    virtual ~Prodotto();
    virtual Vettore<Ingrediente> getIngredienti() const= 0;
    virtual Prodotto* clone() const = 0;
    virtual bool operator ==(const Prodotto&)const;
    string getNome() const;
    string getPath() const;
    u_int getQuantita() const;
    virtual void accept(JsonIO::Visitor *visitor) const = 0;
};

#endif // PRODOTTO_H
