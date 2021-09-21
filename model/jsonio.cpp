#include "jsonio.h"
#include "model/catalogo.h"
#include "model/prodotto.h"
#include "model/bevanda.h"
#include "model/cocktail.h"
#include "model/cibo.h"

JsonIO::JsonIO(){

}

void JsonIO::Visitor::visitCatalogo(const Catalogo *catalogo){
    QJsonArray array;
    for(auto it = catalogo->listaProdotti().cbegin(); it!=  catalogo->listaProdotti().cend(); it++){
        Visitor v;
        (*it)->accept(&v);
        array.append(v.getJson());
    }
    qjson = {{"catalogo",array}};
}

void JsonIO::Visitor::visitIngrediente(const Ingrediente *ingrediente){
    qjson ["nome"] = ingrediente->getNome().c_str();
    qjson ["quantita"]= static_cast<int>(ingrediente->getQuantita());
    qjson ["isLiquido"] =ingrediente->IsLiquido() ;
}

void JsonIO::Visitor::visitProdotto(const Prodotto *prodotto){
    qjson ["path"] = prodotto->getPath().c_str();
    qjson ["tipo"] = "Prodotto";
    qjson ["quantita"] = static_cast<int>(prodotto->getQuantita());
    qjson ["nome"] = prodotto->getNome().c_str();
}

void JsonIO::Visitor::visitBevanda(const Bevanda *bevanda){
    visitProdotto(bevanda);
    qjson["tipo"] = "Bevanda";
    qjson ["gradazione"] = static_cast<int>(bevanda->getGradazione());
}

void JsonIO::Visitor::visitCocktail(const Cocktail *cocktail){
    QJsonArray array;
    Vettore<Ingrediente> vec =cocktail->getIngredienti();
    for(auto it = vec.begin(); it!=  vec.end(); it++){
        Visitor v;
        it->accept(&v);
        QJsonObject j=v.getJson();
        array.append(j);

    }
    visitBevanda(cocktail);

    qjson["tipo"] = "Cocktail";
    qjson["ingredienti"] = array;
}

void JsonIO::Visitor::visitCibo(const Cibo *cibo){
    visitProdotto(cibo);
    QJsonArray array;
    Vettore<Ingrediente> vec =cibo->getIngredienti();
    for(auto it = vec.begin(); it!=  vec.end(); it++){
        Visitor v;
        it->accept(&v);
        array.append(v.getJson());

    }
    qjson["tipo"]="Cibo";
    qjson["ingredienti"] = array;

}


void JsonIO::load(std::string path, Catalogo *catalogo) {
  if (QFile::exists(path.c_str())) {
    QFile file(path.c_str());
    if (file.open(QIODevice::ReadOnly)) {
      QString str = file.readAll();
      file.close();
      QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
      if (doc.isObject()) {
        QJsonObject cObj = doc.object();
        if (cObj["catalogo"].isArray() ) {
          QJsonArray cArr = cObj["catalogo"].toArray();
          loadCatalogo(catalogo, cArr);

        }
      }
    }
  }
}

void JsonIO::save(std::string path, const Catalogo *catalogo) {
  if (catalogo) {
    Visitor *v = new Visitor();
    catalogo->accept(v);
    QJsonDocument saveDoc(v->getJson());
    delete v;

    QFile saveFile(path.c_str());
    if (saveFile.open(QIODevice::WriteOnly)) {
      saveFile.write(saveDoc.toJson());
    }
  }
}

void JsonIO::loadBevanda(Catalogo *catalogo, QJsonObject jsObjElement){
    std::string path = jsObjElement["path"].toString().toStdString();
    std::string nome = jsObjElement["nome"].toString().toStdString();
    int gradazione = static_cast<u_int>(jsObjElement["gradazione"].toInt());
    int quantita = static_cast<u_int>(jsObjElement["quantita"].toInt());
    Bevanda b(nome,quantita,path,gradazione);
    catalogo->aggiungiProdotto(b);
}

void JsonIO::loadCocktail(Catalogo *catalogo, QJsonObject jsObjElement){
    std::string path = jsObjElement["path"].toString().toStdString();
    std::string nome = jsObjElement["nome"].toString().toStdString();
    int gradazione = static_cast<u_int>(jsObjElement["gradazione"].toInt());
    int quantita = static_cast<u_int>(jsObjElement["quantita"].toInt());
    QJsonArray ingArray =jsObjElement["ingredienti"].toArray();
    Vettore<Ingrediente> ingredienti;
    for(auto ingElement = ingArray.begin(); ingElement!= ingArray.end(); ingElement++){
        std::string ingNome = ingElement->toObject()["nome"].toString().toStdString();
        u_int ingQuantita = ingElement->toObject()["quantita"].toInt();
        bool ingLiquid = ingElement->toObject()["isLiquido"].toBool();
        Ingrediente ing(ingNome, ingQuantita, ingLiquid);
        ingredienti.push_back(ing);
    }
    Cocktail c(nome, quantita, path, ingredienti, gradazione);
    catalogo->aggiungiProdotto(c);
}

void JsonIO::loadCibo(Catalogo *catalogo, QJsonObject jsObjElement){
    std::string path = jsObjElement["path"].toString().toStdString();
    std::string nome = jsObjElement["nome"].toString().toStdString();
    int quantita = static_cast<u_int>(jsObjElement["quantita"].toInt());
    QJsonArray ingArray =jsObjElement["ingredienti"].toArray();
    Vettore<Ingrediente> ingredienti;
    for(auto ingElement = ingArray.begin(); ingElement!= ingArray.end(); ingElement++){
        std::string ingNome = ingElement->toObject()["nome"].toString().toStdString();
        u_int ingQuantita = ingElement->toObject()["quantita"].toInt();
        bool ingLiquid = ingElement->toObject()["isLiquido"].toBool();
        Ingrediente ing(ingNome, ingQuantita, ingLiquid);
        ingredienti.push_back(ing);
    }
    Cibo c(nome,quantita,path,ingredienti);
    catalogo->aggiungiProdotto(c);
}

void JsonIO::loadCatalogo(Catalogo *catalogo, QJsonArray cArr){
    for(auto cArrElement = cArr.begin(); cArrElement != cArr.end(); cArrElement++){
        QJsonObject jsObjElement= cArrElement->toObject();
        if (jsObjElement["tipo"].toString() == QString("Bevanda")){
            loadBevanda(catalogo, jsObjElement);

        }else if (jsObjElement["tipo"].toString() == QString("Cocktail")){
            loadCocktail(catalogo, jsObjElement);

        }else if (jsObjElement["tipo"].toString() == QString("Cibo")){
            loadCibo(catalogo, jsObjElement);

        }
    }
}

const QJsonObject& JsonIO::Visitor::getJson() const {
    return qjson;
}
