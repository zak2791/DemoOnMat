#include "item_category_0_0.h"
#include "qgraphicsscene.h"
#include "qgraphicsview.h"
#include "qjsonobject.h"
#include "qpainter.h"
#include  <QJsonArray>
#include  <QGraphicsSceneMouseEvent>
#include  <QInputDialog>

Item_category_0_0::Item_category_0_0(QJsonArray* arr) {

    jArr = arr;

    arrCount = jArr->count();
    setAcceptHoverEvents(true);

    for(int i = 0; i < arrCount; i++){
        lRectDraw.append(QRect(  0, i * 40, 40, 40));
        lRectName.append(QRect( 40, i * 40, 100, 40));
        lRectNameT.append(QRect( 40 + offsetText, i * 40, 100 - offsetText, 40));
        lRectTeam.append(QRect(140, i * 40, 100, 40));
        lRectTeamT.append(QRect(140 + offsetText, i * 40, 100 - offsetText, 40));
        lRectRange.append(QRect(240, i * 40, 40, 40));
        lRectRate1.append(QRect(280, i * 40, 40, 40));
        lRectRate2.append(QRect(320, i * 40, 40, 40));
        lRectRate3.append(QRect(360, i * 40, 40, 40));
        lRectRate4.append(QRect(400, i * 40, 40, 40));
        lRectRate5.append(QRect(440, i * 40, 40, 40));
        lRectRateSum.append(QRect(480, i * 40, 40, 40));
        lRectAddRate.append(QRect(520, i * 40, 40, 40));
        lRectPlace.append(QRect(560, i * 40, 40, 40));
        lRectHover.append(QRect(0, i * 40, 600, 40));
        hoverFlags.append(false);
        hoverAddRate.append(false);
        workFlags.append(false);
        listSortRates.append({i, 0});
    }

    rectRate = QRect(480, -40,  40, 40);

    update();
}

int Item_category_0_0::getHeight()
{
    return arrCount * 40;
}

QRectF Item_category_0_0::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(penWidth / 2 - 10, penWidth / 2 - 10 - 40,
                  600 + penWidth + 20, 40 * 1 + penWidth + 10 + 40 * arrCount);
}

void Item_category_0_0::paint(QPainter *painter,
                              const QStyleOptionGraphicsItem*,
                              QWidget*)
{
    QFont f = painter->font();
    QFont newFont = painter->font();
    int size = newFont.pointSize();
    newFont.setPointSize(size * 0.8);
    painter->setFont(newFont);
    painter->drawRect(QRect(  0, -40,  40, 40));
    painter->drawText(QRect(  0, -40,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, "№\nп/п");
    painter->drawRect(QRect( 40, -40, 100, 40));
    painter->drawText(QRect( 40, -40, 100, 40), Qt::AlignVCenter | Qt::AlignHCenter, "Спортсмен");
    painter->drawRect(QRect(140, -40, 100, 40));
    painter->drawText(QRect(140, -40, 100, 40), Qt::AlignVCenter | Qt::AlignHCenter, "Команда");
    painter->drawRect(QRect(240, -40,  40, 40));
    painter->drawText(QRect(240, -40,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, "Разряд");
    painter->drawRect(QRect(280, -40,  200, 20));
    painter->drawText(QRect(280, -40,  200, 20), Qt::AlignVCenter | Qt::AlignHCenter, "Оценки");
    painter->drawRect(QRect(280, -20,  40, 20));
    painter->drawText(QRect(280, -20,  40, 20), Qt::AlignVCenter | Qt::AlignHCenter, "1");
    painter->drawRect(QRect(320, -20,  40, 20));
    painter->drawText(QRect(320, -20,  40, 20), Qt::AlignVCenter | Qt::AlignHCenter, "2");
    painter->drawRect(QRect(360, -20,  40, 20));
    painter->drawText(QRect(360, -20,  40, 20), Qt::AlignVCenter | Qt::AlignHCenter, "3");
    painter->drawRect(QRect(400, -20,  40, 20));
    painter->drawText(QRect(400, -20,  40, 20), Qt::AlignVCenter | Qt::AlignHCenter, "4");
    painter->drawRect(QRect(440, -20,  40, 20));
    painter->drawText(QRect(440, -20,  40, 20), Qt::AlignVCenter | Qt::AlignHCenter, "5");
    if(hoverRate)
        painter->fillRect(rectRate, "lightgray");
    else
        painter->drawRect(rectRate);
    painter->drawText(rectRate, Qt::AlignVCenter | Qt::AlignHCenter, "Итог");
    painter->drawRect(QRect(520, -40,  40, 40));
    painter->drawText(QRect(520, -40,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, "Доп.\nоценка");
    painter->drawRect(QRect(560, -40,  40, 40));
    painter->drawText(QRect(560, -40,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, "Место");

    painter->setFont(f);


    for(int i = 0; i < arrCount; i++){
        if(workFlags.at(i))
            painter->fillRect(lRectHover.at(i), "red");
        else
            if(hoverFlags.at(i))
                painter->fillRect(lRectHover.at(i), "lightgray");

        painter->drawRect(lRectDraw.at(i));
        painter->drawText(lRectDraw.at(i), Qt::AlignVCenter | Qt::AlignHCenter, QString::number(i + 1));
        painter->drawRect(lRectName.at(i));
        painter->drawText(lRectNameT.at(i), Qt::AlignVCenter | Qt::AlignLeft, jArr->at(listSortRates[i][0].toInt()).toObject().value("Name").toString());
        painter->drawRect(lRectTeam.at(i));
        painter->drawText(lRectTeamT.at(i), Qt::AlignVCenter | Qt::AlignLeft, jArr->at(listSortRates[i][0].toInt()).toObject().value("Team").toString());
        painter->drawRect(lRectRange.at(i));
        painter->drawText(lRectRange.at(i), Qt::AlignVCenter | Qt::AlignHCenter, jArr->at(listSortRates[i][0].toInt()).toObject().value("Range").toString());
        painter->drawRect(lRectRate1.at(i));
        painter->drawRect(lRectRate2.at(i));
        painter->drawRect(lRectRate3.at(i));
        painter->drawRect(lRectRate4.at(i));
        painter->drawRect(lRectRate5.at(i));
        painter->drawRect(lRectRateSum.at(i));

        if(hoverAddRate.at(i))
            painter->fillRect(lRectAddRate.at(i), "yellow");
        else
            painter->drawRect(lRectAddRate.at(i));

        QString addRate = QString::number(jArr->at(listSortRates[i][0].toInt()).toObject().value("AddRate").toInt());
        painter->drawText(lRectAddRate.at(i),  Qt::AlignVCenter | Qt::AlignHCenter, addRate);

        painter->drawRect(lRectPlace.at(i));

        int currentTask = jArr->at(i).toObject().value("CurrentTask").toInt();
        if(currentTask > 0){
            QString rate1 = QString::number(jArr->at(listSortRates[i][0].toInt()).toObject().value("Task1Rate").toDouble());
            QString total = QString::number(jArr->at(listSortRates[i][0].toInt()).toObject().value("TotalRate").toDouble());
            painter->drawText(lRectRate1.at(i),  Qt::AlignVCenter | Qt::AlignHCenter, rate1);
            painter->drawText(lRectRateSum.at(i),  Qt::AlignVCenter | Qt::AlignHCenter, total);
            if(currentTask > 1){
                QString rate2 = QString::number(jArr->at(listSortRates[i][0].toInt()).toObject().value("Task2Rate").toDouble());
                painter->drawText(lRectRate2.at(i),  Qt::AlignVCenter | Qt::AlignHCenter, rate2);
            }
            if(currentTask > 2){
                QString rate3 = QString::number(jArr->at(listSortRates[i][0].toInt()).toObject().value("Task3Rate").toDouble());
                painter->drawText(lRectRate3.at(i),  Qt::AlignVCenter | Qt::AlignHCenter, rate3);
            }
            if(currentTask > 3){
                QString rate4 = QString::number(jArr->at(listSortRates[i][0].toInt()).toObject().value("Task4Rate").toDouble());
                painter->drawText(lRectRate4.at(i),  Qt::AlignVCenter | Qt::AlignHCenter, rate4);
            }
            if(currentTask == 5){
                QString rate5 = QString::number(jArr->at(listSortRates[i][0].toInt()).toObject().value("Task5Rate").toDouble());
                painter->drawText(lRectRate5.at(i),  Qt::AlignVCenter | Qt::AlignHCenter, rate5);
            }
        }
    }
    painter->drawText(lRectPlace.at(0), Qt::AlignVCenter | Qt::AlignHCenter, place1);
    painter->drawText(lRectPlace.at(1), Qt::AlignVCenter | Qt::AlignHCenter, place2);
    painter->drawText(lRectPlace.at(2), Qt::AlignVCenter | Qt::AlignHCenter, place3);
    painter->drawText(lRectPlace.at(3), Qt::AlignVCenter | Qt::AlignHCenter, place4);
}

void Item_category_0_0::mousePressEvent(QGraphicsSceneMouseEvent * e)
{
    int x = e->pos().x();
    int y = e->pos().y();

    int count = jArr->count();
    if(rectRate.contains(x, y)){
        listSortRates.clear();
        for(int i = 0; i < count; i++)
            listSortRates.append({i, jArr->at(i).toObject().value("TotalRate").toDouble(), jArr->at(i).toObject().value("AddRate").toInt()});
        std::sort(listSortRates.begin(), listSortRates.end(), [](QVariantList list1, QVariantList list2){
            if(list1.at(1).toDouble() > list2.at(1).toDouble())
                return true;
            else if (list1.at(1).toDouble() < list2.at(1).toDouble())
                return false;
            else{
                return list1.at(2).toInt() > list2.at(2).toInt();
            }
        });
        QList<double> listRates;
        QList<int> listAddRates;
        for(int i = 0; i < count; i++){
            if(i == 5) break;
            listRates.append(listSortRates.at(i).at(1).toDouble());
            listAddRates.append(listSortRates.at(i).at(2).toInt());
        }
        place1 = "";
        place2 = "";
        place3 = "";
        place4 = "";
        if(listRates.count() == 1) place1 = "1";
        else{
            for(int i = 1; i < listRates.count(); i++){
                if(i == 5) break;
                if(listRates.at(i) == listRates.at(i - 1) && listAddRates.at(i) == listAddRates.at(i - 1)) return;
            }
            if(count == 2){
                place1 = "1";
                place2 = "2";
            }
            else if(count == 3){
                place1 = "1";
                place2 = "2";
                place3 = "3";
            }else{
                place1 = "1";
                place2 = "2";
                place3 = "3";
                place4 = "4";
            }
        }
    }

    if(hoverAddRate.contains(true)){
        bool ok;
        int ret = QInputDialog::getInt(nullptr, "Ввoд доп. оценки", "Дополнительная оценка", 0, 0, jArr->size() - 1, 1, &ok);
        int i = hoverAddRate.indexOf(true);
        if(ok){
            QJsonObject o = jArr->at(listSortRates[i][0].toInt()).toObject();
            o.insert("AddRate", ret);
            jArr->removeAt(listSortRates[i][0].toInt());
            jArr->insert(listSortRates[i][0].toInt(), o);
            emit sigUpdateData();
        }
        return;
    }

    for(int i = 0; i < lRectHover.count(); i++){
        workFlags[i] = 0;
        if(lRectHover.at(i).contains(x, y)){
            workFlags[i] = 1;
            emit sigSendToControlPanel(jArr->at(listSortRates[i][0].toInt()).toObject());
        }
    }

    update();

}

void Item_category_0_0::hoverMoveEvent(QGraphicsSceneHoverEvent * e)
{
    int x = e->pos().x();
    int y = e->pos().y();
    for(int i = 0; i < lRectHover.count(); i++){
        hoverFlags[i] = false;
        hoverAddRate[i] = false;
        if(lRectHover.at(i).contains(x, y)){
            hoverFlags[i] = true;
        }
        if(lRectAddRate.at(i).contains(x, y)){
            hoverAddRate[i] = true;
        }
    }
    if(rectRate.contains(x, y)) hoverRate = true;
    else hoverRate = false;

    update();
}
