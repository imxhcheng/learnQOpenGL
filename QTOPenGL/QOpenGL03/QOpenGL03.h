#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QOpenGL03.h"
#include <QImage>

class QOpenGL03 : public QMainWindow
{
    Q_OBJECT

public:
    QOpenGL03(QWidget *parent = Q_NULLPTR);

private:
    Ui::QOpenGL03Class ui;
};
