#include "ingredientpage.h"

IngredientPage::IngredientPage(QWidget*parent,const Vettore<Ingrediente>& lista): QWidget(parent), ingr(lista){
    mainLayout = new QVBoxLayout(this);
    cart = new QListWidget(this);
    addList();

    connect(back, &QPushButton::clicked, this, &IngredientPage::showHomePage);
    connect(switchToCarrello, &QPushButton::clicked, this, &IngredientPage::showCarrelloPage);
}

void IngredientPage::addList(){
    this->setMinimumSize(920,800);

    QLabel* title = new QLabel("Lista della spesa");
    title->setFont(QFont("Verdana", 20));
    back = new QPushButton();
    switchToCarrello = new QPushButton();
    QPixmap turnBackImg = QPixmap(":/icons/foto/home.png");
    QPixmap SwitchImg = QPixmap(":/icons/foto/iconcart.png");
    QWidget* header = new Header(back, title, switchToCarrello, turnBackImg, SwitchImg);

    for(Vettore<Ingrediente>::Iteratore it=ingr.begin(); it!=ingr.end(); it++){
        QWidget* w= new QWidget;
        QHBoxLayout* oggettoLista = new QHBoxLayout(w);

        //nome ingrediente
        std::string aux = it->getNome();
        QString* saveNome = new QString(aux.c_str());
        QLabel* nome = new QLabel(*saveNome);
        nome->setStyleSheet("font-size: 24px;");

        QLabel* quantityLabel = new QLabel("Quantità: ");
        quantityLabel->setStyleSheet("font-size: 24px;");

        quantity = new QLabel();
        quantity->setNum(int(it->getQuantita()));
        quantity->setStyleSheet("font-size: 24px;");

        QLabel* unit = new QLabel();
        if(it->IsLiquido()) unit->setText("ml");
        else unit->setText("gr");
        unit->setStyleSheet("font-size: 24px");

        oggettoLista->addWidget(nome);
        oggettoLista->addWidget(quantityLabel);
        oggettoLista->addWidget(quantity);
        oggettoLista->addWidget(unit);
        oggettoLista->setAlignment(quantity, Qt::AlignCenter);
        oggettoLista->setAlignment(quantityLabel, Qt::AlignRight);
        oggettoLista->setAlignment(unit, Qt::AlignLeft);

        QListWidgetItem* item = new QListWidgetItem;
        item->setSizeHint(QSize(cart->sizeHint().width(),80));
        cart->addItem(item);
        cart->setItemWidget(item, w);
    }
    mainLayout->addWidget(header);
    mainLayout->addWidget(cart);
}

void IngredientPage::setLista(Vettore<Ingrediente> v){
    ingr=v;
}

void IngredientPage::showHomePage(){
    emit toHomePage();
}

void IngredientPage::showCarrelloPage(){
    emit toCarrelloPage();
}
