#include "home.h"

Home::Home(QWidget *parent) : QWidget(parent){
    LayoutMain=new QVBoxLayout(this);
    addProducts();
    //setLayout(LayoutMain);
    connect(cocktails, &QPushButton::clicked, this, &Home::showCocktailPage);
    connect(analcolici, &QPushButton::clicked, this, &Home::showAnalcolicoPage);
    connect(alcolici, &QPushButton::clicked, this, &Home::showAlcolicoPage);
    connect(carrello, &QPushButton::clicked, this, &Home::showCarrelloPage);
    connect(cibo, &QPushButton::clicked, this, &Home::showCiboPage);
}

void Home::addProducts(){
    QLabel* welcome = new QLabel("Benvenuto su MakeITHome");
    welcome->setFont(QFont("Verdana", 20));
    welcome->setAlignment(Qt::AlignCenter);
    QLabel* titolo = new QLabel("Seleziona il servizio:");
    titolo->setFont(QFont("Verdana", 14));
    titolo->setAlignment(Qt::AlignCenter);

    ProdottiLayout = new QHBoxLayout();
    ProdottiLayout->setAlignment(Qt::AlignCenter);
    cocktails = new QPushButton();
    alcolici = new QPushButton();
    analcolici = new QPushButton();
    carrello = new QPushButton();
    cibo = new QPushButton();

    QHBoxLayout* labelLayout = new QHBoxLayout();
    QLabel* cock = new QLabel("Cocktails");
    QLabel* alcol = new QLabel("Alcolici");
    QLabel* analc = new QLabel("Analcolici");
    QLabel* cart = new QLabel("Carrello");
    QLabel* food = new QLabel("Cibo");
    cock->setAlignment(Qt::AlignCenter);
    alcol->setAlignment(Qt::AlignCenter);
    analc->setAlignment(Qt::AlignCenter);
    cart->setAlignment(Qt::AlignCenter);
    food->setAlignment(Qt::AlignCenter);
    cock->setFont(QFont("Verdana", 14));
    alcol->setFont(QFont("Verdana", 14));
    analc->setFont(QFont("Verdana", 14));
    cart->setFont(QFont("Verdana", 14));
    food->setFont(QFont("Verdana", 14));

    //pulsante cocktails
    QPixmap cocktailsIcon = QPixmap(":/icons/foto/cocktail.png");
    setIconTOButton(cocktailsIcon, cocktails);

    //pulsante analcolici
    QPixmap analcoliciIcon = QPixmap(":/icons/foto/softdrinks.png");
    setIconTOButton(analcoliciIcon, analcolici);

    //pulsante alcolici
    QPixmap alcoliciIcon = QPixmap(":/icons/foto/beer.png");
    setIconTOButton(alcoliciIcon, alcolici);

    //pulsante cibo
    QPixmap ciboIcon = QPixmap(":/icons/foto/hamburger.png");
    setIconTOButton(ciboIcon, cibo);

    //pulsante carrello
    QPixmap carrelloIcon = QPixmap(":/icons/foto/shopping-cart.png");
    setIconTOButton(carrelloIcon, carrello);

    //aggiungi pulsanti
    ProdottiLayout->addWidget(cocktails);
    ProdottiLayout->addWidget(analcolici);
    ProdottiLayout->addWidget(alcolici);
    ProdottiLayout->addWidget(cibo);
    ProdottiLayout->addWidget(carrello);

    //aggiungi caption
    labelLayout->addWidget(cock);
    labelLayout->addWidget(analc);
    labelLayout->addWidget(alcol);
    labelLayout->addWidget(food);
    labelLayout->addWidget(cart);

    //layout principale
    LayoutMain->addWidget(welcome);
    LayoutMain->addWidget(titolo);
    LayoutMain->addLayout(ProdottiLayout);
    LayoutMain->addLayout(labelLayout);
}

void Home::setIconTOButton(const QPixmap& qp, QPushButton* but){
    but->setIcon(qp);
    but->setIconSize(QSize(150,150));
    but->resize(QSize(150,150));

    but->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    but->setStyleSheet("border:3px solid #e0e0e0;");
    QPalette pal1 = but->palette();
    pal1.setColor(QPalette::Button, QColor(Qt::white));
    but->setAutoFillBackground(true);
    but->setPalette(pal1);
    but->update();
    but->setCursor(Qt::PointingHandCursor);
}


void Home::showCocktailPage(){
    emit toCocktailPage();
}

void Home::showAlcolicoPage(){
    emit toAlcolicoPage();
}

void Home::showAnalcolicoPage(){
    emit toAnalcolicoPage();
}

void Home::showCarrelloPage(){
    emit toCarrelloPage();
}

void Home::showCiboPage(){
    emit toCiboPage();
}
