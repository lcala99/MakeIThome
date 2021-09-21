#include "cocktailpage.h"

CocktailPage::CocktailPage(QWidget* parent,const Vettore<DeepPtr<Cocktail>>& vec_coc): QWidget(parent), lista(vec_coc), q(0){
    cocktailList = new QVBoxLayout(this);
    addItems();
    connect(back, &QPushButton::clicked, this, &CocktailPage::showHomePage);
    connect(cart, &QPushButton::clicked, this, &CocktailPage::showCarrelloPage);
}

void CocktailPage::addItems(){
    this->setMinimumSize(920,800);
    QLabel* title = new QLabel("Cocktails");
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

        //nome analcolico
        aux = it->get()->getNome();
        QString* saveNome = new QString(aux.c_str()); //converto a const char*
        QLabel* nome = new QLabel(*saveNome);
        nome->setStyleSheet("font-size: 24px;");

        //quantità
        QLabel* quantitaLabel = new QLabel("Quantità :");
        quantitaLabel->setStyleSheet("font-size: 24px;");
        quantity = new QSpinBox();
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

        QListWidgetItem* entry = new QListWidgetItem;
        QString info = "Ingredienti: \n";
        Vettore<Ingrediente> ingr = it->get()->getIngredienti();
        for(auto itv = ingr.begin(); itv!=ingr.end(); itv++){
            info +=QString::fromStdString(itv->getNome());
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
    cocktailList->addWidget(header);
    cocktailList->addWidget(catalogue);
}

void CocktailPage::showHomePage(){
    emit toHomePage();
}

void CocktailPage::showCarrelloPage(){
    emit toCarrelloPage();
}

void CocktailPage::updateQuantity(int quant){
    q=quant;
}
