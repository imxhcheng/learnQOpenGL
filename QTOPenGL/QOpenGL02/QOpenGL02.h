#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QOpenGL02.h"

class QOpenGL02 : public QMainWindow
{
    Q_OBJECT

public:
    QOpenGL02(QWidget *parent = Q_NULLPTR);

private:
    Ui::QOpenGL02Class ui;
};
