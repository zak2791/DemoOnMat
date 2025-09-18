#include "category_0_0.h"
#include "item_category_0_0.h"
#include "qjsondocument.h"
#include <QJsonObject>

Category_0_0::Category_0_0(int _id,
                           int _id_base,
                           int _status,
                           QString _category,
                           QString _age,
                           QString _weight,
                           QString _data) : Category(_id,
                                                    _id_base,
                                                    _status,
                                                    _category,
                                                    _age,
                                                    _weight,
                                                    _data)
{
    id_system = 0;
    hbFirstRow->addWidget(new QLabel("Первый круг"));
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    jArr = doc.array();
    //qDebug()<<"doc = "<<doc<<jObj;
    // QJsonObject o = doc.object();
    // if(o.contains("ObjArr"))
    //     jObj = o;
    // else{
    //     QJsonArray arr;
    //     foreach(auto each, o){
    //         //qDebug()<<each.toArray().at(0);
    //         QJsonArray arr(each.toArray());
    //         QJsonObject obj;
    //         obj.insert("Id", arr.at(0));
    //         obj.insert("Name", arr.at(1));
    //         obj.insert("Team", arr.at(3));
    //         qDebug()<<obj;
    //     }

    // }
    item = new Item_category_0_0(&jArr);
    connect(item, &Item_category_0_0::sigSendToControlPanel, this, [this](QJsonObject o){
        emit sigDataControlPanel(id, id_system, o);
    });

    connect(item, &Item_category_0_0::sigUpdateData, this, [this](){
        QJsonDocument doc(jArr);
        QString strJson = doc.toJson(QJsonDocument::Compact);
        emit sigSaveData(id, strJson);
    });

    s.addItem(item);

    // item = new Item_category_0_0(jObj);
    // s.addItem(item);
    // s.addRect(0, 0, 40, 20);
    // s.addText("Спортсмен");
    // s.addText("Команда");
    // s.addText("Разряд");
    // s.addText("Оценка 1");
    // s.addText("Оценка 2");
    // s.addText("Оценка 3");
    // s.addText("Оценка 4");
    // s.addText("Оценка 5");
    // s.addText("Итог");
    // s.addText("Доп. оценка");
    // s.addText("Место");
    //v.setScene(&s);
    //v.setMinimumHeight(item->getHeight());
    //v.set

    //layout->addWidget(&v);

    //setGeometry(0, 0, s.width(), 700);

    //setMinimumHeight(400);

}

void Category_0_0::setDataFromControlPanel(QJsonObject obj)
{
    int id_athlete = obj.value("Id").toInt();
    for(int i = 0; i < jArr.count(); i++){
        QJsonObject o = jArr.at(i).toObject();
        if(o.value("Id").toInt() == id_athlete){
            jArr.removeAt(i);
            jArr.insert(i, obj);
            item->update();
            continue;
        }
    }

    QJsonDocument doc(jArr);
    QString strJson = doc.toJson(QJsonDocument::Compact);
    emit sigSaveData(id, strJson);
}

void Category_0_0::mousePressEvent(QMouseEvent*)
{
    item->clearWorkFlags();
    item->update();
    emit sigScene(&s, this);
}
