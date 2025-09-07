#ifndef ITEM_CATEGORY_____H
#define ITEM_CATEGORY_____H

#include "qjsonarray.h"
#include <QGraphicsObject >

class Item_category_0_0 : public QGraphicsObject
{
    Q_OBJECT
public:
    Item_category_0_0(QJsonObject);
    int getHeight(void);

private:
    QRectF boundingRect(void) const ;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) ;

    QJsonArray arrId;
    QJsonArray arrName;
    QJsonArray arrRange;
    QJsonArray arrTeam;
    int arrCount;

    int offsetText = 3;
    QList<QRect> lRectDraw;
    QList<QRect> lRectName;
    QList<QRect> lRectNameT;
    QList<QRect> lRectTeam;
    QList<QRect> lRectTeamT;
    QList<QRect> lRectRange;
    QList<QRect> lRectRate1;
    QList<QRect> lRectRate2;
    QList<QRect> lRectRate3;
    QList<QRect> lRectRate4;
    QList<QRect> lRectRate5;
    QList<QRect> lRectRateSum;
    QList<QRect> lRectAddRate;
    QList<QRect> lRectPlace;

};

#endif // ITEM_CATEGORY_____H
