#include "view.h"


View::View(Controller* ctr):_controller(ctr){
    homepg  = new Home(this);
    setMinimumSize(840,270);
    setMaximumSize(840,270);
    move(QPoint(600,280));
    homepg->show();
    connect(homepg, &Home::toCocktailPage, this, &View::v_showCocktail);
    connect(homepg, &Home::toAlcolicoPage, this, &View::v_showAlcolico);
    connect(homepg, &Home::toAnalcolicoPage, this, &View::v_showAnalcolico);
    connect(homepg, &Home::toCiboPage, this, &View::v_showCibo);
    connect(homepg, &Home::toCarrelloPage, this, &View::v_showCarrello);
    setWindowIcon(QIcon(":/icons/foto/bar.png"));
}

void View::v_showCocktail(){
    hideCurrent();
    delete cocktailpg;
    cocktailpg=new CocktailPage(this, _controller->getCatalogo().listaCocktail());
    windowSize(cocktailpg);

    connect(cocktailpg, &CocktailPage::toHomePage, this, &View::v_showHome);
    connect(cocktailpg, &CocktailPage::toCarrelloPage, this, &View::v_showCarrello);
    connect(cocktailpg, &CocktailPage::addToCart, _controller, &Controller::c_addToCart);
}

void View::v_showCarrello(){
    hideCurrent();
    delete cartpg;
    cartpg = new Carrellopage(this, _controller->getCarrello().getProdotti());
    windowSize(cartpg);

    connect(cartpg, &Carrellopage::toHomePage, this, &View::v_showHome);
    connect(cartpg, &Carrellopage::toIngredientsPage, this, &View::v_showIngredients);
    connect(cartpg, &Carrellopage::removeItem, [=](Prodotto& p){
        _controller->c_removeFromCart(p);
        cartpg->setLista(_controller->getCarrello().getProdotti());
        cartpg->refresh();
    });
}

void View::v_showAlcolico(){
    hideCurrent();
    delete alcolpg;
    alcolpg = new AlcolicoPage(this, _controller->getCatalogo().listaAlcolici());
    windowSize(alcolpg);

    connect(alcolpg, &AlcolicoPage::toHomePage, this, &View::v_showHome);
    connect(alcolpg, &AlcolicoPage::toCarrelloPage, this, &View::v_showCarrello);
    connect(alcolpg, &AlcolicoPage::addToCart, _controller, &Controller::c_addToCart);

}

void View::v_showAnalcolico(){
    hideCurrent();
    delete analcolpg;
    analcolpg = new AnalcolicoPage(this,_controller->getCatalogo().listaAnalcolici());
    windowSize(analcolpg);

    connect(analcolpg, &AnalcolicoPage::toHomePage, this, &View::v_showHome);
    connect(analcolpg, &AnalcolicoPage::toCarrelloPage, this, &View::v_showCarrello);
    connect(analcolpg, &AnalcolicoPage::addToCart, _controller, &Controller::c_addToCart);
}

void View::v_showCibo(){
    hideCurrent();
    delete cibopg;
    cibopg = new Cibopage(this,_controller->getCatalogo().listaCibi());
    windowSize(cibopg);

    connect(cibopg, &Cibopage::toHomePage, this, &View::v_showHome);
    connect(cibopg, &Cibopage::toCarrelloPage, this, &View::v_showCarrello);
    connect(cibopg, &Cibopage::addToCart, _controller, &Controller::c_addToCart);
}

void View::v_showHome(){
    hideCurrent();
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x=(screenGeometry.width()-homepg->width())/2;
    int y=(screenGeometry.height()-homepg->height())/2;
    setMinimumSize(840,270);
    setMaximumSize(840,270);
    move(QPoint(x,y));
    homepg->show();
}

void View::v_showIngredients(){
    hideCurrent();
    delete listpg;
    listpg = new IngredientPage(this, _controller->getCarrello().calcolaIngredienti());
    windowSize(listpg);
    listpg->show();

    connect(listpg, &IngredientPage::toCarrelloPage, this, &View::v_showCarrello);
    connect(listpg, &IngredientPage::toHomePage, this, &View::v_showHome);
}

void View::windowSize(QWidget* q){
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x=(screenGeometry.width()-q->width())/2;
    int y=(screenGeometry.height()-q->height())/2;
    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    move(QPoint(x,y));
    if( dynamic_cast<IngredientPage*>(q) ||
        dynamic_cast<CocktailPage*>(q)||
        dynamic_cast<AlcolicoPage*>(q) ||
        dynamic_cast<AnalcolicoPage*>(q) ||
        dynamic_cast<Cibopage*>(q) ||
        dynamic_cast<Carrellopage*>(q)){
        setMaximumSize(920,800);
        setMinimumSize(920,800);

    }
    else {
        setMinimumSize(840,270);
        setMaximumSize(840,270);
    }
    q->show();
}

void View::hideCurrent(){
    if(homepg && homepg->isVisible()) {
        homepg->hide();
    }
    else if(analcolpg && analcolpg->isVisible()){
        analcolpg->hide();
    }
    else if(alcolpg && alcolpg->isVisible()){
        alcolpg->hide();
    }
    else if(listpg && listpg->isVisible()){
        listpg->hide();
    }
    else if(cartpg && cartpg->isVisible()){
        cartpg->hide();
    }
    else if(cocktailpg && cocktailpg->isVisible()){
        cocktailpg->hide();
    }
    else if(cibopg && cibopg->isVisible()){
            cibopg->hide();
    }
}


