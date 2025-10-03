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

QList<std::tuple<int, int, int, int, int, QString, QString, QString, QString>> DataBaseController::readCategories(QString name)
{
    if(db.open())
        db.close();
    db.setDatabaseName(name);
    QList<std::tuple<int, int, int, int, int, QString, QString, QString, QString>> listData;
    if(!db.open())
        return listData;

    //qDebug()<<"db open";
    //if (!db.tables().contains(QLatin1String("categories"))) return listData;

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
        QString category = query.value("category").toString();
        QString age = query.value("age").toString();
        QString weight = query.value("weight").toString();
        QString data = query.value("data").toString();
        listData.append(std::tuple(id, id_category, id_system, mode, status, category, age, weight, data));
    }
    return listData;
}

int DataBaseController::addCategory(int id_base,
                                    int id_system,
                                    int mode,
                                    QString category,
                                    QString age,
                                    QString weight,
                                    QString data)
{
    QMessageBox msgBox;
    QString sql("INSERT INTO categories (id_category, id_system, mode, status, category, age, weight, data) VALUES (%1, %2, %3, %4, %5, %6, %7, %8);");
    sql = sql.arg(QString::number(id_base))
             .arg(QString::number(id_system))
             .arg(QString::number(mode))
             .arg(QString::number(0))
             .arg("'" + category + "'")
             .arg("'" + age + "'")
             .arg("'" + weight + "'")
             .arg("'" + data + "'");
    if(!query->exec(sql)){
        msgBox.setText("Ошибка добавления категории 2" + db.lastError().text());
        msgBox.exec();
        qDebug()<<db.lastError().text();
        return -1;
    }
    return query->lastInsertId().toInt();
}

bool DataBaseController::removeCategory(int id)
{
    QMessageBox msgBox;
    QString sql("DELETE FROM categories WHERE id = %1");
    sql = sql.arg(QString::number(id));
    if(!query->exec(sql)){
        msgBox.setText("Ошибка удаления категории" + db.lastError().text());
        msgBox.exec();
        qDebug()<<db.lastError().text();
        return false;
    }
    return true;
}

void DataBaseController::writeData(int id, QString strJson)
{
    QMessageBox msgBox;
    QString sql("UPDATE categories SET data = '%1' WHERE id = %2");
    sql = sql.arg(strJson).arg(QString::number(id));
    if(!query->exec(sql)){
        msgBox.setText("Ошибка обновления данных" + db.lastError().text());
        msgBox.exec();
        qDebug()<<db.lastError().text();
        return;
    }
}

void DataBaseController::updateStatus(int id, int status)
{
    QMessageBox msgBox;
    QString sql("UPDATE categories SET status = '%1' WHERE id = %2");
    sql = sql.arg(status).arg(QString::number(id));
    if(!query->exec(sql)){
        msgBox.setText("Ошибка обновления данных" + db.lastError().text());
        msgBox.exec();
        qDebug()<<db.lastError().text();
        return;
    }
}
