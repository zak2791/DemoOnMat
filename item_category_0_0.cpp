#include "item_category_0_0.h"
#include "qgraphicsscene.h"
#include "qgraphicsview.h"
#include "qjsonobject.h"
#include "qpainter.h"
#include  <QJsonArray>
#include  <QGraphicsSceneMouseEvent>

Item_category_0_0::Item_category_0_0(QJsonArray* arr) {

    jArr = arr;
    //qDebug()<<"obj"<<obj;
    // arrId = jObj.value("Id").toArray();
    // arrName = jObj.value("Name").toArray();
    // arrTeam = jObj.value("Team").toArray();
    // arrRange= jObj.value("Range").toArray();
    arrCount = jArr->count();
    setAcceptHoverEvents(true);

    //qDebug()<<jArr<<jArr.count();

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
        workFlags.append(false);
        // lRectRate.append(QRect(280, i * 40, 40, 40));
        // lRectAddRate.append(QRect(320, i * 40, 40, 40));
        // lRectPlace.append(QRect(360, i * 40, 40, 40));
    }

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

    // QGraphicsScene s = scene();
    // QGraphicsView v = s.views().at(0);
    // v.setMinimumHeight(100);

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
    painter->drawRect(QRect(480, -40,  40, 40));
    painter->drawText(QRect(480, -40,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, "Итог");
    painter->drawRect(QRect(520, -40,  40, 40));
    painter->drawText(QRect(520, -40,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, "Доп.\nоценка");
    painter->drawRect(QRect(560, -40,  40, 40));
    painter->drawText(QRect(560, -40,  40, 40), Qt::AlignVCenter | Qt::AlignHCenter, "Место");
    // painter->drawRect(rSortPlace);
    // painter->drawText(rSortPlace, Qt::AlignVCenter | Qt::AlignHCenter, "Место");

    painter->setFont(f);


    for(int i = 0; i < arrCount; i++){
        if(workFlags.at(i))
            painter->fillRect(lRectHover.at(i), "red");
        // else if(workFlags.at(i) == 1)
        //     painter->fillRect(lRectHover.at(i), "yellow");
        else
            if(hoverFlags.at(i))
                painter->fillRect(lRectHover.at(i), "lightgray");

        painter->drawRect(lRectDraw.at(i));
        painter->drawText(lRectDraw.at(i), Qt::AlignVCenter | Qt::AlignHCenter, QString::number(i + 1));
        painter->drawRect(lRectName.at(i));
        painter->drawText(lRectNameT.at(i), Qt::AlignVCenter | Qt::AlignLeft, jArr->at(i).toObject().value("Name").toString());
        painter->drawRect(lRectTeam.at(i));
        painter->drawText(lRectTeamT.at(i), Qt::AlignVCenter | Qt::AlignLeft, jArr->at(i).toObject().value("Team").toString());
        painter->drawRect(lRectRange.at(i));
        painter->drawText(lRectRange.at(i), Qt::AlignVCenter | Qt::AlignHCenter, jArr->at(i).toObject().value("Range").toString());
        painter->drawRect(lRectRate1.at(i));
        painter->drawRect(lRectRate2.at(i));
        painter->drawRect(lRectRate3.at(i));
        painter->drawRect(lRectRate4.at(i));
        painter->drawRect(lRectRate5.at(i));
        painter->drawRect(lRectRateSum.at(i));
        painter->drawRect(lRectAddRate.at(i));
        painter->drawRect(lRectPlace.at(i));

        int currentTask = jArr->at(i).toObject().value("CurrentTask").toInt();
        if(currentTask > 0){
            QString rate1 = QString::number(jArr->at(i).toObject().value("Task1Rate").toDouble());
            QString total = QString::number(jArr->at(i).toObject().value("TotalRate").toDouble());
            painter->drawText(lRectRate1.at(i),  Qt::AlignVCenter | Qt::AlignHCenter, rate1);
            painter->drawText(lRectRateSum.at(i),  Qt::AlignVCenter | Qt::AlignHCenter, total);
            if(currentTask > 1){
                QString rate2 = QString::number(jArr->at(i).toObject().value("Task2Rate").toDouble());
                painter->drawText(lRectRate2.at(i),  Qt::AlignVCenter | Qt::AlignHCenter, rate2);
            }
            if(currentTask > 2){
                QString rate3 = QString::number(jArr->at(i).toObject().value("Task3Rate").toDouble());
                painter->drawText(lRectRate3.at(i),  Qt::AlignVCenter | Qt::AlignHCenter, rate3);
            }
            if(currentTask > 3){
                QString rate4 = QString::number(jArr->at(i).toObject().value("Task4Rate").toDouble());
                painter->drawText(lRectRate4.at(i),  Qt::AlignVCenter | Qt::AlignHCenter, rate4);
            }
            if(currentTask == 5){
                QString rate5 = QString::number(jArr->at(i).toObject().value("Task5Rate").toDouble());
                painter->drawText(lRectRate5.at(i),  Qt::AlignVCenter | Qt::AlignHCenter, rate5);
            }
        }



        //painter->drawRect(lRectRate.at(i));
        //painter->drawRect(lRectAddRate.at(i));

        // if(hoverPlaceFlags.at(i))
        //     painter->fillRect(lRectPlace.at(i), "lightgray");
        // else
        //     painter->drawRect(lRectPlace.at(i));

        // for(int j = 0; j < lAthletes.count(); j++){
        //     if((*data)["Id"].toArray().at(j) == lAthletes.at(i).id){
        //         painter->drawText(lRectRate.at(i), Qt::AlignVCenter | Qt::AlignHCenter, QString::number((*data)["Rates"].toArray().at(j).toDouble()));
        //         painter->drawText(lRectAddRate.at(i), Qt::AlignVCenter | Qt::AlignHCenter, QString::number((*data)["AddRates"].toArray().at(j).toDouble()));

        //         if((*data)["Place1"] == (*data)["Id"][j]){
        //             painter->drawText(lRectPlace.at(i), Qt::AlignVCenter | Qt::AlignHCenter, "1");
        //         }
        //         else if((*data)["Place2"] == (*data)["Id"][j]){
        //             painter->drawText(lRectPlace.at(i), Qt::AlignVCenter | Qt::AlignHCenter, "2");
        //         }
        //         else if((*data)["Place3"] == (*data)["Id"][j]){
        //             painter->drawText(lRectPlace.at(i), Qt::AlignVCenter | Qt::AlignHCenter, "3");
        //         }
        //         else if((*data)["Place4"] == (*data)["Id"][j]){
        //             painter->drawText(lRectPlace.at(i), Qt::AlignVCenter | Qt::AlignHCenter, "4");
        //         }
        //     }
        // }

    }
}

void Item_category_0_0::mousePressEvent(QGraphicsSceneMouseEvent * e)
{
    int x = e->pos().x();
    int y = e->pos().y();

    for(int i = 0; i < lRectHover.count(); i++){
        workFlags[i] = 0;
        if(lRectHover.at(i).contains(x, y)){
            workFlags[i] = 1;
            // QJsonObject obj;
            // obj.insert("Name", jArr.at(i).toObject().value("Name"));
            // obj.insert("Team", jArr.at(i).toObject().value("Team"));
            qDebug()<<jArr->at(i).toObject();
            emit sigSendToControlPanel(jArr->at(i).toObject());
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
        if(lRectHover.at(i).contains(x, y)){
            hoverFlags[i] = true;
        }
    }

    update();
}
