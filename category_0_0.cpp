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
    //hbFirstRow->addWidget(new QLabel("Первый круг"));
    lblStage.setText("Первый круг");
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    jArr = doc.array();

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
            break;
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

void Category_0_0::slotSendingData(){
    QJsonObject obj;
    obj.insert("Id", id_base);
    QJsonArray arrToSend;
    foreach(auto each, jArr){
        QJsonObject o = each.toObject();
        QJsonObject newObj;
        newObj.insert("Id", o.value("Id"));
        newObj.insert("Rate1", o.value("Task1Rate"));
        newObj.insert("Rate2", o.value("Task2Rate"));
        newObj.insert("Rate3", o.value("Task3Rate"));
        newObj.insert("Rate4", o.value("Task4Rate"));
        newObj.insert("Rate5", o.value("Task5Rate"));
        newObj.insert("TotalRate", o.value("TotalRate"));
        newObj.insert("AddRate", o.value("AddRate"));
        arrToSend.append(newObj);
    }
    arrToSend.append(obj);
    QJsonDocument doc(arrToSend);
    QString strJson = doc.toJson(QJsonDocument::Compact);
    emit sigSendData(id, strJson);

}
