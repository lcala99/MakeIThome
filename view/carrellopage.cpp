#include "carrellopage.h"

Carrellopage::Carrellopage(QWidget *parent,Vettore<std::pair<DeepPtr<Prodotto>,u_int>> carr) : QWidget(parent), listaProdotti(carr){
    container = new QVBoxLayout(this);
    cart = new QListWidget(this);

    QLabel* title = new QLabel("Carrello");
    title->setFont(QFont("Verdana", 20));

    back = new QPushButton();
    switchToList = new QPushButton();
    QPixmap turnBackImg = QPixmap(":/icons/foto/home.png");
    QPixmap turnSwitchImg = QPixmap(":/icons/foto/to-do-list.png");
    header = new Header(back, title, switchToList, turnBackImg, turnSwitchImg);
    container->addWidget(header);
    addCart();

    connect(back, &QPushButton::clicked, this, &Carrellopage::showHomePage);
    connect(switchToList, &QPushButton::clicked, this, &Carrellopage::showIngredientsPage);
}

void Carrellopage::setLista(Vettore<std::pair<DeepPtr<Prodotto>,u_int>> v){
    listaProdotti=v;
}

void Carrellopage::addCart(){
    setMinimumSize(920,800);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    for(auto it=listaProdotti.begin(); it!=listaProdotti.end(); it++){
        QWidget* w= new QWidget;
        w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        QHBoxLayout* oggettoLista = new QHBoxLayout(w);

        //immagine cocktail
        QPushButton* plotImg = new QPushButton();
        std::string aux = it->first->getPath();
        QString* savePath = new QString(aux.c_str()); //converto a const char*
        QPixmap cocktailImg = QPixmap(*savePath);
        plotImg->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
        plotImg->setIcon(cocktailImg);
        plotImg->setIconSize(QSize(100,100));
        plotImg->resize(QSize(100,100));

        //nome prodotto
        aux = it->first->getNome();
        QString* saveNome = new QString(aux.c_str()); //converto a const char*
        QLabel* nome = new QLabel(*saveNome);
        nome->setStyleSheet("font-size: 28px;");

        QLabel* quantita = new QLabel();
        quantita->setNum(int(it->second));
        quantita->setStyleSheet("font-size: 24px;");

        //remove button
        remove = new QPushButton("Rimuovi");
        remove->setCursor(Qt::PointingHandCursor);

        connect(remove,&QPushButton::clicked,[=]{
            QMessageBox* quitBox = new QMessageBox();
            QPushButton* yes = quitBox->addButton("Si", QMessageBox::YesRole);
            quitBox->addButton("No", QMessageBox::NoRole);
            quitBox->setDefaultButton(yes);
            quitBox->setText("Sei sicuro di voler rimuovere questo prodotto?");
            quitBox->exec();
            if(quitBox->clickedButton()==yes){
                emit removeItem(*(it->first));
            }
        });
        remove->setStyleSheet("font-size: 20px;");
        remove->resize(25,60);

        oggettoLista->addWidget(plotImg);
        oggettoLista->addWidget(nome);
        oggettoLista->addWidget(quantita);
        oggettoLista->addWidget(remove);
        oggettoLista->setAlignment(plotImg, Qt::AlignLeft);
        oggettoLista->setAlignment(nome, Qt::AlignLeft);

        QListWidgetItem* item = new QListWidgetItem;
        item->setSizeHint(QSize(cart->sizeHint().width(),130));

        QString info = "Ingredienti: \n";
        Vettore<Ingrediente> ingr = it->first.get()->getIngredienti();
        for(auto itv = ingr.begin(); itv!=ingr.end(); itv++){
            info += QString::fromStdString(itv->getNome());
            info += " ";
            int i=itv->getQuantita();
            QString printable = QStringLiteral("%1").arg(i);
            info += printable;
            if(itv->IsLiquido()) info += " ml\n";
            else info += " gr\n";
        }
        item->setToolTip((info));
        cart->addItem(item);
        cart->setItemWidget(item, w);
        cart->setMinimumHeight(100);
    }

    container->addWidget(cart);
}

void Carrellopage::showHomePage(){
    emit toHomePage();
}

void Carrellopage::showIngredientsPage(){
    emit toIngredientsPage();
}

void Carrellopage::refresh(){
    cart->clear();
    addCart();
}
