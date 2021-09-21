#ifndef ALCOLICOPAGE_H
#define ALCOLICOPAGE_H

#include "view/header.h"

#include "model/bevanda.h"
#include "model/vettore.h"
#include "model/deepptr.h"

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLayout>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QFrame>
#include <QScrollArea>
#include <QScrollBar>
#include <QLabel>
#include <QListView>
#include <QLineEdit>
#include <QWidgetAction>
#include <QFormLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QString>
#include <iostream>
#include <QTabWidget>
#include <QSpinBox>
#include <QSizePolicy>

class AlcolicoPage : public QWidget{
    Q_OBJECT
private:
    QVBoxLayout* AlcolList;
    QPushButton* back;
    QPushButton* cart;
    QPushButton* add;
    QSpinBox* quantity;
    Vettore<DeepPtr<Bevanda>> lista;
    int q;

public:
    explicit AlcolicoPage(QWidget* parent,const Vettore<DeepPtr<Bevanda>>& vec_alcol);
    void addItems();
signals:
    void toHomePage();
    void toCarrelloPage();
    void addToCart(Bevanda* bev, int quantita);
public slots:
    void showHomePage();
    void showCarrelloPage();
    void updateQuantity(int quant);
};

#endif // ALCOLICOPAGE_H
