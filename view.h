#ifndef VIEW_H
#define VIEW_H

#include "view/home.h"
#include "view/carrellopage.h"
#include "view/alcolicopage.h"
#include "view/analcolicopage.h"
#include "view/ingredientpage.h"
#include "view/cocktailpage.h"
#include "view/cibopage.h"
#include "model/catalogo.h"
#include "controller.h"

#include <QWidget>
#include <QApplication>
#include <QDesktopWidget>

class Controller;
class Catalogo;
class Home;
class Carrellopage;

class View : public QWidget{
   Q_OBJECT
private:
    Controller* _controller;
    Home* homepg = nullptr;
    Carrellopage* cartpg = nullptr;
    AlcolicoPage* alcolpg = nullptr;
    AnalcolicoPage* analcolpg = nullptr;
    IngredientPage* listpg = nullptr;
    CocktailPage* cocktailpg = nullptr;
    Cibopage* cibopg = nullptr;

public:
    explicit View(Controller* controller);
    void hideCurrent();
    const Catalogo& getCatalogo() const;
    void windowSize(QWidget*);
public slots:
    void v_showCocktail();
    void v_showCarrello();
    void v_showAlcolico();
    void v_showAnalcolico();
    void v_showHome();
    void v_showCibo();
    void v_showIngredients();
};

#endif // VIEW_H
