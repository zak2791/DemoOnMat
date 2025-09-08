#include "category_0_0.h"
#include "item_category_0_0.h"
#include "qjsondocument.h"

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
    jObj = doc.object();
    item = new Item_category_0_0(jObj);
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

void Category_0_0::focusOutEvent(QFocusEvent *)
{

}

void Category_0_0::mousePressEvent(QMouseEvent*)
{
    qDebug()<<"press";
    emit sigScene(&s);
}
