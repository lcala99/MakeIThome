#include "analcolicopage.h"

AnalcolicoPage::AnalcolicoPage(QWidget* parent,const Vettore<DeepPtr<Bevanda>>& vec_bev): QWidget(parent), lista(vec_bev){
    AnalcolList = new QVBoxLayout(this);
    addItems();
    connect(back, &QPushButton::clicked, this, &AnalcolicoPage::showHomePage);
    connect(cart, &QPushButton::clicked, this, &AnalcolicoPage::showCarrelloPage);
}

void AnalcolicoPage::addItems(){
    this->setMinimumSize(920,800);
    QLabel* title = new QLabel("Bevande analcoliche");
    title->setFont(QFont("Verdana", 20));

    back = new QPushButton();
    cart = new QPushButton();
    QPixmap plotBackImg = QPixmap(":/icons/foto/home.png");
    QPixmap plotCartImg = QPixmap(":/icons/foto/iconcart.png");
    QWidget* header = new Header(back, title, cart,plotBackImg,plotCartImg);

    QListWidget* catalogue = new QListWidget(this);

    for(auto it=lista.begin(); it!=lista.end(); it++){
        QWidget* w= new QWidget;

        QHBoxLayout* item = new QHBoxLayout(w);

        //immagine elemento
        QPushButton* plotImg = new QPushButton();
        std::string aux = it->get()->getPath();
        QString* savePath = new QString(aux.c_str()); //converto a const char*
        QPixmap cocktailImg = QPixmap(*savePath);
        plotImg->setIcon(cocktailImg);
        plotImg->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
        plotImg->setIconSize(QSize(100,100));
        plotImg->resize(QSize(100,100));

        //nome analcolico
        aux = it->get()->getNome();
        QString* saveNome = new QString(aux.c_str()); //converto a const char*
        QLabel* nome = new QLabel(*saveNome);
        nome->setStyleSheet("font-size: 24px;");

        QLabel* quantitaLabel = new QLabel("Quantità :");
        quantitaLabel->setStyleSheet("font-size: 24px;");
        quantity = new QSpinBox;
        quantity->setMaximumWidth(70);

        connect(quantity, SIGNAL(valueChanged(int)), this, SLOT(updateQuantity(int)));

        quantity->setStyleSheet("font-size: 24px;");

        add = new QPushButton("Aggiungi al carrello");
        add->setCursor(Qt::PointingHandCursor);

        connect(add, &QPushButton::clicked, [=](){
            emit addToCart(it->get(),q); // segnale prende Cocktail* e int
        } );


        add->setStyleSheet("font: bold; font-size: 20px;");
        add->resize(25,60);
        item->addWidget(plotImg);
        item->addWidget(nome);
        item->addWidget(quantitaLabel);
        item->addWidget(quantity);
        item->addWidget(add);
        item->setAlignment(plotImg, Qt::AlignLeft);
        item->setAlignment(quantity, Qt::AlignCenter);
        item->setAlignment(quantitaLabel, Qt::AlignRight);

        QListWidgetItem* oggetto = new QListWidgetItem;
        oggetto->setSizeHint(QSize(catalogue->sizeHint().width(),130));
        catalogue->addItem(oggetto);
        catalogue->setItemWidget(oggetto, w);
    }

    AnalcolList->addWidget(header);
    AnalcolList->addWidget(catalogue);
}

void AnalcolicoPage::showHomePage(){
    emit toHomePage();
}

void AnalcolicoPage::showCarrelloPage(){
    emit toCarrelloPage();
}


void AnalcolicoPage::updateQuantity(int quant){
    q=quant;
}
