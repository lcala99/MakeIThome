#ifndef INGREDIENTE_H
#define INGREDIENTE_H
#include<iostream>
#include "jsonio.h"

typedef unsigned int u_int;
using std::string;

class Ingrediente
{

private:
    string nome;
    u_int quantita;
    bool isLiquido;

public:
    Ingrediente();
    Ingrediente(string n, u_int q=1, bool l=true);
    Ingrediente(const Ingrediente& ing);
    Ingrediente* clone()const;
    ~Ingrediente();

    /*  @brief * moltiplica la quantità dell'ingrediente
     *  @param unsigned int: moltiplicatore
     *  @return Ingrediente
     * */
    Ingrediente operator*(const u_int c)const;

    /*  @brief * divide la quantità dell'ingrediente
     *  @param unsigned int: divisore
     *  @return Ingrediente
     * */
    Ingrediente operator/(const u_int c)const;

    /*  @brief * somma la quantità dell'ingrediente
    *  @param unsigned int: addizione
    *  @return Ingrediente
    * */
    Ingrediente operator+(const u_int c) const;

    /*  @brief * somma la quantità di due ingredienti
    *  @param unsigned int: addizione tra ing
    *  @return Ingrediente
    * */
    Ingrediente operator+(const Ingrediente& ing) const;

    bool operator==(Ingrediente& c) const;

    /*  @brief getNome restituisce il nome
     *  @return string
     * */
    string getNome()const;

    /*  @brief getQuantita restituisce la quantia
     *  @return unsigned int
     * */
    u_int getQuantita()const;

    /*  @brief getIsLiquido restituisce true se l'ingrediente è liquido
     *  @return bool
     * */
    bool IsLiquido()const;

    operator u_int() const;

    void accept(JsonIO::Visitor *visitor) const;

};
#endif // INGREDIENTE_H
