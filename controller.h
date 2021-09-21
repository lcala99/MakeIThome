#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>
#include "model.h"
#include "view.h"

class View;

class Controller: public QObject {
    Q_OBJECT
public:
    Controller(Model* model);
    void setView(View* view);
    const Catalogo& getCatalogo() const;
    const Carrello& getCarrello() const;
private:
    Model* _model;
    View* _view;

public slots:
    void c_addToCart(Prodotto* prov, int q);
    void c_removeFromCart(Prodotto& prod);
};

#endif // CONTROLLER_H
