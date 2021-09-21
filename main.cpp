#include <QApplication>
#include <iostream>

#include "view.h"
#include "model.h"
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Catalogo cat;
    Model model(cat);
    Controller controller(&model);
    View* view = new View(&controller);
    view->show();

    return a.exec();
}
