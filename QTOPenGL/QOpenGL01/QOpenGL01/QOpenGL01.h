#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QOpenGL01.h"

class QOpenGL01 : public QMainWindow
{
    Q_OBJECT

public:
    QOpenGL01(QWidget *parent = Q_NULLPTR);

private:
    Ui::QOpenGL01Class ui;
};
