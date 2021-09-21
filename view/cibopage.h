#ifndef CIBOPAGE_H
#define CIBOPAGE_H

#include "view/header.h"
#include "model/vettore.h"
#include "model/deepptr.h"
#include "model/cibo.h"

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLayout>
#include <QLabel>
#include <QSpinBox>
#include <QListWidget>
#include <QString>
#include <QLineEdit>

class Cibopage: public QWidget {
    Q_OBJECT
private:
    QVBoxLayout* ciboList;
    QPushButton* back;
    QPushButton* cart;
    QPushButton* add;
    QSpinBox* quantity;
    Vettore<DeepPtr<Cibo>> lista;
    int q;
public:
    explicit Cibopage(QWidget* parent,const Vettore<DeepPtr<Cibo>>& vec_food);
    void addItems();
signals:
    void toHomePage();
    void toCarrelloPage();
    void addToCart(Cibo* food, int quantity);
public slots:
    void showHomePage();
    void showCarrelloPage();
    void updateQuantity(int quant);

};

#endif // COCKTAILPAGE_H
