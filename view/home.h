#ifndef Home_H
#define Home_H

#include "header.h"
#include <QWidget>

class QPushButton;
class QHBoxLayout;
class QVBoxLayout;

class Home: public QWidget {
    Q_OBJECT

    public:
    explicit Home(QWidget *parent = nullptr);
    //virtual ~Home();
    void addProducts();
    void setIconTOButton(const QPixmap& qp, QPushButton* but);

    private:
    QVBoxLayout* LayoutMain;
    QHBoxLayout* ProdottiLayout;
    QPushButton* cocktails;
    QPushButton* alcolici;
    QPushButton* analcolici;
    QPushButton* cibo;
    QPushButton* carrello;

    signals:
        void toCocktailPage();
        void toAlcolicoPage();
        void toAnalcolicoPage();
        void toCarrelloPage();
        void toCiboPage();
    public slots:
        void showCocktailPage();
        void showAlcolicoPage();
        void showAnalcolicoPage();
        void showCarrelloPage();
        void showCiboPage();
};

#endif // Home_H
