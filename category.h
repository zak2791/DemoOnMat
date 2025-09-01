#ifndef CATEGORY_H
#define CATEGORY_H

#include <QFrame>

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
             QString    // данные (спортсмены, оценки ...)
             );

    void setRates(QString);

protected:
    int id;
    int id_system;      // id системы проведения
    int id_base;
    int status;
    QString category;
    QString age;
    QString weight;
    QString data;

signals:
    /////////////////////////////////////////////////
    /// \brief sigSendData
    /// отправка данных на компьютер секретаря
    /////////////////////////////////////////////////
    void sigSendData(int,       //id
                     QString    //data
                     );


};

#endif // CATEGORY_H
