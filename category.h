#ifndef CATEGORY_H
#define CATEGORY_H

#include "qboxlayout.h"
#include "qgraphicsscene.h"
#include "qlabel.h"
#include <QFrame>
#include <QJsonObject>

///////////////////////////////////////////////////
/// \brief The Category class
///Класс отображения весовой категории
///
/// id системы проведения:
/// 0 - 0 - system_0 общий круг (category_0_0)
/// 1 - 0 - system_0 полуфинал (category_0_1)
/// 2 - 0 - system_0 финал (category_0_2)
///
/// статус:
/// 0 - исходный
/// 1 - отработан   ???????????????
/// 2 - отправлен секретарю
//////////////////////////////////////////////////
class Category : public QFrame
{
    Q_OBJECT
public:
    Category(int,       // id категории
             int,       // id базовой категории (с коьпьютера секретаря)
             int,       // 0 - статус
             QString,   // категория
             QString,   // возраст
             QString,   // вес
             QString,   // данные (спортсмены, оценки ...)
             QWidget* parent = nullptr);

    void setRates(QString);
    virtual void setDataFromControlPanel(QJsonObject);
    int getBaseCategory(void){return id_base;}
    //int getIdSystem(void){return id_system;}
    int getId(void){return id;}

private:
    QLabel lblCategory;
    QLabel lblAge;
    QLabel lblWeight;
    QString category;
    QString age;
    QString weight;

protected:
    int id;
    int id_system;      // id системы проведения
    int id_base;
    int status;
    QVBoxLayout* layout;
    QHBoxLayout* hbFirstRow;
    QString data;

signals:
    /////////////////////////////////////////////////
    /// \brief sigSendData
    /// отправка данных на компьютер секретаря
    /////////////////////////////////////////////////
    void sigDataControlPanel(
                             int,           //id
                             int,           //id_system
                             QJsonObject    //data
                             );
    void sigDataTransfer(int,       //id_base
                         QString    //data
                         );

    void sigScene(QGraphicsScene*);

    //////////////////////////////////////////////////////
    /// Сохранение данных в базе
    //////////////////////////////////////////////////////
    void sigSaveData(int,       //id категории
                     QString    //строка с json ланными
                     );


};

#endif // CATEGORY_H
