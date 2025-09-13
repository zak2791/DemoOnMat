#ifndef CATEGORY_____H
#define CATEGORY_____H

#include "category.h"
#include "item_category_0_0.h"
#include "qgraphicsview.h"

#include <QMouseEvent>

/////////////////////////////////////////////////
/// \brief The Category_0_0 class
///Класс представления системы проведения соревнований System_0, общий круг
////////////////////////////////////////////////////////////////////
class Category_0_0 : public Category
{
public:
    Category_0_0(
                int,       // id категории
                int,       // id базовой категории (с компьютера секретаря)
                int,       // 0 - статус
                QString,
                QString,
                QString,
                QString    // данные (спортсмены, оценки ...)
                );

    virtual void setDataFromControlPanel(QJsonObject);

private:
    QGraphicsView v;
    QGraphicsScene s;
    Item_category_0_0* item;
    QJsonArray jArr;
    // QList<int> err1;    //
    // QList<int> err2;    //
    // QList<int> err3;    //
    // QList<int> err4;    //
    // QList<int> err5;    //
    // float rate1



    void mousePressEvent(QMouseEvent*);

};

#endif // CATEGORY_____H
