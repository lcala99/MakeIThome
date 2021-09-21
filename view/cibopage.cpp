#include "cibopage.h"

Cibopage::Cibopage(QWidget* parent,const Vettore<DeepPtr<Cibo>>& food): QWidget(parent), lista(food) {
    ciboList = new QVBoxLayout(this);
    addItems();
    connect(back, &QPushButton::clicked, this, &Cibopage::showHomePage);
    connect(cart, &QPushButton::clicked, this, &Cibopage::showCarrelloPage);
}

void Cibopage::addItems(){
    this->setMinimumSize(920,800);
    QLabel* title = new QLabel("Cibo");
    title->setFont(QFont("Verdana", 20));

    back = new QPushButton();
    cart = new QPushButton();
    QPixmap plotHomeImg = QPixmap(":/icons/foto/home.png");
    QPixmap plotCartImg = QPixmap(":/icons/foto/iconcart.png");
    QWidget* header = new Header(back, title, cart,plotHomeImg,plotCartImg);

    QListWidget* catalogue = new QListWidget(this);

    for(auto it=lista.begin(); it!=lista.end(); it++){
        QWidget* w= new QWidget;

        QHBoxLayout* item = new QHBoxLayout(w);

        //immagine elemento
        QPushButton* plotImg = new QPushButton();
        std::string aux = it->get()->getPath();
        QString* savePath = new QString(aux.c_str()); //converto a const char*
        QPixmap cocktailImg = QPixmap(*savePath);
        plotImg->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
        plotImg->setIcon(cocktailImg);
        plotImg->setIconSize(QSize(100,100));
        plotImg->resize(QSize(100,100));

        //nome cibo
        aux = it->get()->getNome();
        QString* saveNome = new QString(aux.c_str()); //converto a const char*
        QLabel* nome = new QLabel(*saveNome);
        nome->setStyleSheet("font-size: 24px;");

        QLabel* quantitaLabel = new QLabel("Quantità :");
        quantitaLabel->setStyleSheet("font-size: 24px;");
        quantity = new QSpinBox();
        quantity->setMaximumWidth(70);

        connect(quantity, SIGNAL(valueChanged(int)), this, SLOT(updateQuantity(int)));

        quantity->setStyleSheet("font-size: 24px;");
        add = new QPushButton("Aggiungi al carrello");
        add->setCursor(Qt::PointingHandCursor);

        connect(add, &QPushButton::clicked, [=](){
            connect(quantity, SIGNAL(valueChanged(int)), this, SLOT(updateQuantity(int)));
            emit addToCart(it->get(),q);
            q=0;
        } );
        add->setStyleSheet("font: bold; font-size: 20px;");
        add->resize(25,60);

        //add to layout
        item->addWidget(plotImg);
        item->addWidget(nome);
        item->addWidget(quantitaLabel);
        item->addWidget(quantity);
        item->addWidget(add);
        item->setAlignment(plotImg, Qt::AlignLeft);
        item->setAlignment(quantity, Qt::AlignCenter);
        item->setAlignment(quantitaLabel, Qt::AlignRight);

        QListWidgetItem* entry = new QListWidgetItem;

        QString info = "Ingredienti: \n";
        Vettore<Ingrediente> ingr = it->get()->getIngredienti();
        for(auto itv = ingr.begin(); itv!=ingr.end(); itv++){
            info += QString::fromStdString(itv->getNome());
            info += " ";
            int i=itv->getQuantita();
            QString printable = QStringLiteral("%1").arg(i);
            info += printable;
            if(itv->IsLiquido()) info += " ml\n";
            else info += " gr\n";
        }
        entry->setToolTip((info));
        entry->setSizeHint(QSize(catalogue->sizeHint().width(),130));
        catalogue->addItem(entry);

        catalogue->setItemWidget(entry, w);
    }
    ciboList->addWidget(header);
    ciboList->addWidget(catalogue);
}

void Cibopage::showHomePage(){
    emit toHomePage();
}

void Cibopage::showCarrelloPage(){
    emit toCarrelloPage();
}

void Cibopage::updateQuantity(int quant){
    q=quant;
}
