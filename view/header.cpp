#include "header.h"


Header::Header(QPushButton* sx, QLabel* titolo, QPushButton* dx, QPixmap plotsx, QPixmap plotdx){
    QHBoxLayout* h = new QHBoxLayout();
    h->addWidget(sx);
    h->addWidget(titolo);
    h->addWidget(dx);

    sx->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    sx->setStyleSheet("border:2px solid #ededed;");
    sx->setIconSize(QSize(50,50));
    sx->resize(QSize(50,50));
    sx->setIcon(plotsx);
    sx->setCursor(Qt::PointingHandCursor);

    dx->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    dx->setStyleSheet("border:2px solid #ededed;");
    dx->setIconSize(QSize(50,50));
    dx->resize(QSize(50,50));
    dx->setIcon(plotdx);
    dx->setCursor(Qt::PointingHandCursor);

    QColor transparent_color(0,0,0,0);
    QPalette sx_palette(sx->palette());

    sx_palette.setColor(QPalette::Button, transparent_color);
    sx->setPalette(sx_palette);

    h->setAlignment(sx,Qt::AlignLeft);
    h->setAlignment(titolo,Qt::AlignCenter);
    h->setAlignment(dx,Qt::AlignRight);
    setLayout(h);
}
