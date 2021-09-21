#ifndef CARRELLOPAGE_H
#define CARRELLOPAGE_H

#include "view/header.h"
#include "model/carrello.h"
#include "model/vettore.h"
#include "model/prodotto.h"
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
#include <QWidgetAction>
#include <QFormLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QString>
#include <iostream>
#include <QSpinBox>
#include <QSizePolicy>
#include <QDialog>
#include <QMessageBox>

class Carrellopage: public QWidget {
    Q_OBJECT
private:
    QVBoxLayout* container;
    QPushButton* back;
    QPushButton* switchToList;
    QPushButton* remove;
    QListWidget* cart;
    Header* header;
    Vettore<std::pair<DeepPtr<Prodotto>,u_int>> listaProdotti;
public:
    explicit Carrellopage(QWidget *parent, Vettore<std::pair<DeepPtr<Prodotto>,u_int>> cart);
    void setLista(Vettore<std::pair<DeepPtr<Prodotto>,u_int>>);
    void addCart();
    void refresh();
signals:
    void toHomePage();
    void toIngredientsPage();
    void removeItem(Prodotto& prod);
    void updateCart();
public slots:
    void showHomePage();
    void showIngredientsPage();
};

#endif
