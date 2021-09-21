#ifndef HEADER_H
#define HEADER_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QObject>
#include <QPixmap>
#include <QHBoxLayout>
#include <QColor>
#include <QPalette>


class Header: public QWidget {
    Q_OBJECT
public:
    explicit Header(QPushButton* sx, QLabel* titolo, QPushButton* dx,QPixmap plotsx, QPixmap plotdx);
};

#endif // HEADER_H
