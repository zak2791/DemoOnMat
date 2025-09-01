#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

class DataBaseController : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseController(QObject *parent = nullptr);
    ~DataBaseController();

    QList<std::tuple<
                    int,    // id
                    int,    // id базовой категории (с компьютера секретаря)
                    int,    // id_system
                    int,    // mode system
                    int,    // status
                    QString // data
                    >> openDataBase(QString);

    int addCategory(
                    int,    // id базовой категории (с компьютера секретаря)
                    int,    // id_system
                    int,    // mode system
                    QString //data
                    );

public slots:
    void writeData(int,                         //id категории
                   QString                      //данные
                   );

private:
    QSqlDatabase db;
    QSqlQuery* query;

signals:
};

#endif // DATABASECONTROLLER_H
