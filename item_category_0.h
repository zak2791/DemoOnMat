#ifndef ITEM_CATEGORY_0____H
#define ITEM_CATEGORY_0____H

#include "qjsonarray.h"
#include <QGraphicsObject >
#include <QJsonObject>

/// Формат json для передачи данных на панель управления и для сохранения в базе данных:
/// "Name"
/// "Team"
/// "CurrentTask"
/// "TotalRate"
/// "Task1Rate"
/// "Task2Rate"
/// "Task3Rate"
/// "Task4Rate"
/// "Task5Rate"
/// "Task1Ref1Rate"
/// "Task1Ref2Rate"
/// "Task1Ref3Rate"
/// "Task1Ref4Rate"
/// "Task1Ref5Rate"
/// "Task2Ref1Rate"
/// "Task2Ref2Rate"
/// "Task2Ref3Rate"
/// "Task2Ref4Rate"
/// "Task2Ref5Rate"
/// "Task3Ref1Rate"
/// "Task3Ref2Rate"
/// "Task3Ref3Rate"
/// "Task3Ref4Rate"
/// "Task3Ref5Rate"
/// "Task4Ref1Rate"
/// "Task4Ref2Rate"
/// "Task4Ref3Rate"
/// "Task4Ref4Rate"
/// "Task4Ref5Rate"
/// "Task5Ref1Rate"
/// "Task5Ref2Rate"
/// "Task5Ref3Rate"
/// "Task5Ref4Rate"
/// "Task5Ref5Rate"
/// "Task1Ref1Err"
/// "Task1Ref2Err"
/// "Task1Ref3Err"
/// "Task1Ref4Err"
/// "Task1Ref5Err"
/// "Task2Ref1Err"
/// "Task2Ref2Err"
/// "Task2Ref3Err"
/// "Task2Ref4Err"
/// "Task2Ref5Err"
/// "Task3Ref1Err"
/// "Task3Ref2Err"
/// "Task3Ref3Err"
/// "Task3Ref4Err"
/// "Task3Ref5Err"
/// "Task4Ref1Err"
/// "Task4Ref2Err"
/// "Task4Ref3Err"
/// "Task4Ref4Err"
/// "Task4Ref5Err"
/// "Task5Ref1Err"
/// "Task5Ref2Err"
/// "Task5Ref3Err"
/// "Task5Ref4Err"
/// "Task5Ref5Err"


class Item_category_0 : public QGraphicsObject
{
    Q_OBJECT
public:
    Item_category_0(QJsonArray*);
    int getHeight(void);
    void clearWorkFlags(void){workFlags.fill(false);}

private:
    QRectF boundingRect(void) const ;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) ;
    void hoverMoveEvent(QGraphicsSceneHoverEvent*);
    void mousePressEvent(QGraphicsSceneMouseEvent*);

    QJsonArray* jArr;

    QString place1 = "";
    QString place2 = "";
    QString place3 = "";
    QString place4 = "";

    int arrCount;
    QMap<int, int> mapSortRates;
    QList<QVariantList> listSortRates;

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
    QList<QRect> lRectHover;
    QList<bool> hoverFlags;
    QList<bool> hoverAddRate;
    QList<bool> workFlags;
    QRect rectRate;
    bool hoverRate;

signals:
    void sigSendToControlPanel(QJsonObject);
    void sigUpdateData(void);

};

#endif // ITEM_CATEGORY_____H
