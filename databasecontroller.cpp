#include "databasecontroller.h"

#include <QMessageBox>
#include <QSqlError>

DataBaseController::DataBaseController(QObject *parent)
    : QObject{parent}
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    query = new QSqlQuery;
    query->exec(" PRAGMA synchronous = OFF, journal_mode = MEMORY");
}

DataBaseController::~DataBaseController()
{
    if(db.open())
        db.close();
    delete query;
}

QList<std::tuple<int, int, int, int, int, QString>> DataBaseController::openDataBase(QString name)
{
    if(db.open())
        db.close();
    db.setDatabaseName(name);
    QList<std::tuple<int, int, int, int, int, QString>> listData;
    if(!db.open())
        return listData;

    QMessageBox msgBox;
    QString sqlCategories("SELECT * FROM categories;");
    QSqlQuery query;
    if(!query.exec(sqlCategories)){
        msgBox.setText("Ошибка чтения таблицы категорий " + db.lastError().text());
        msgBox.exec();
        db.close();
        return listData;
    }
    while(query.next()){
        int id = query.value("id").toInt();
        int id_category = query.value("id_category").toInt();
        int id_system = query.value("id_system").toInt();
        int mode = query.value("mode").toInt();
        int status = query.value("status").toInt();
        QString data = query.value("data").toString();
        listData.append(std::tuple(id, id_category, id_system, mode, status,  data));
    }
    return listData;
}

void DataBaseController::writeData(int, QString)
{

}
