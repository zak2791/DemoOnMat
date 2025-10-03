#ifndef CATEGORY_1___H
#define CATEGORY_1___H

#include "category.h"
#include "item_category_1.h"
#include "qgraphicsview.h"

///////////////////////////////////////////////////////////
/// \brief The Category_1_0 class
/// Общий круг для System_1
////////////////////////////////////////////////////////
class Category_1 : public Category
{
public:
    Category_1(
        int,       // id категории
        int,       // id базовой категории (с компьютера секретаря)
        int,       // статус: 0 - исходный,
        // 1 - выбрана категория,
        // 2 - в работе,
        // 3 - данные отправдены секретарю
        QString,
        QString,
        QString,
        QString    // данные (спортсмены, оценки ...)
        );

    virtual void setDataFromControlPanel(QJsonObject);

private:
    QGraphicsView v;
    QGraphicsScene scene;
    Item_category_1* item;
    QJsonArray jArr;
    // QList<int> err1;    //
    // QList<int> err2;    //
    // QList<int> err3;    //
    // QList<int> err4;    //
    // QList<int> err5;    //
    // float rate1
    //

    void slotSendingData(void);
    void mousePressEvent(QMouseEvent*);
};

#endif // CATEGORY_1___H
