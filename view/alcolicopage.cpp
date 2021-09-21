#include "alcolicopage.h"

AlcolicoPage::AlcolicoPage(QWidget* parent, const Vettore<DeepPtr<Bevanda>>& vec_alcol): QWidget(parent), lista(vec_alcol){
    AlcolList = new QVBoxLayout(this);
    addItems();
    connect(back, &QPushButton::clicked, this, &AlcolicoPage::showHomePage);
    connect(cart, &QPushButton::clicked, this, &AlcolicoPage::showCarrelloPage);
}

void AlcolicoPage::addItems(){
    this->setMinimumSize(920,800);
    QLabel* title = new QLabel("Bevande alcoliche");
    title->setFont(QFont("Verdana", 20));

    back = new QPushButton();
    cart = new QPushButton();
    QPixmap plotBackImg = QPixmap(":/icons/foto/home.png");
    QPixmap plotCartImg = QPixmap(":/icons/foto/iconcart.png");
    QWidget* header = new Header(back, title, cart,plotBackImg,plotCartImg);
    QListWidget* catalogue = new QListWidget(this);
    QListWidgetItem* entry = new QListWidgetItem;
    catalogue->addItem(entry);

    for(auto it=lista.begin(); it!=lista.end(); it++){
        QWidget* w= new QWidget;

        QHBoxLayout* item = new QHBoxLayout(w);

        QPushButton* plotImg = new QPushButton();
        std::string aux = it->get()->getPath();
        QString* savePath = new QString(aux.c_str()); //converto a const char*
        QPixmap cocktailImg = QPixmap(*savePath);
        plotImg->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
        plotImg->setIcon(cocktailImg);
        plotImg->setIconSize(QSize(100,100));
        plotImg->resize(QSize(100,100));

        aux = it->get()->getNome();
        QString* saveNome = new QString(aux.c_str()); //converto a const char*
        QLabel* nome = new QLabel(*saveNome);
        nome->setStyleSheet("font-size: 24px;");

        QLabel* quantitaLabel = new QLabel("Quantità :");
        quantitaLabel->setStyleSheet("font-size: 24px;");
        quantity = new QSpinBox;
        quantity->setMaximumWidth(70);
        quantity->setStyleSheet("font-size: 24px;");

        connect(quantity, SIGNAL(valueChanged(int)), this, SLOT(updateQuantity(int)));

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

    AlcolList->addWidget(header);
    AlcolList->addWidget(catalogue);
}

void AlcolicoPage::showHomePage(){
    emit toHomePage();
}

void AlcolicoPage::showCarrelloPage(){
    emit toCarrelloPage();
}

void AlcolicoPage::updateQuantity(int quant){
    q=quant;
}
