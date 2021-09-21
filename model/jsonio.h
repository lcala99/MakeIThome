#ifndef JSONIO_H
#define JSONIO_H
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <string>


class Prodotto;
class Catalogo;
class Cocktail;
class Cibo;
class Bevanda;
class Ingrediente;

typedef unsigned int u_int;

class JsonIO
{
public:
    JsonIO();
    static void load(std::string path, Catalogo *catalogo);
    static void save(std::string path, const Catalogo *catalogo);
    static void loadCatalogo(Catalogo* catalogo, QJsonArray cArr);
    static void loadBevanda(Catalogo* catalogo, QJsonObject cArr);
    static void loadCocktail(Catalogo* catalogo, QJsonObject cArr);
    static void loadCibo(Catalogo* catalogo, QJsonObject cArr);
    class Visitor
    {
    private:
        QJsonObject qjson;
    public:
        const QJsonObject& getJson()const;
        void visitProdotto(const Prodotto *prodotto);
        void visitCatalogo(const Catalogo *catalogo);
        void visitCocktail(const Cocktail *cocktail);
        void visitCibo(const Cibo *cibo);
        void visitBevanda(const Bevanda *bevanda);
        void visitIngrediente(const Ingrediente *ingrediente);
    };


};

#endif // JSONIO_H
