#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "category.h"
#include "databasecontroller.h"
#include "datatransfercontroller.h"
#include "qlistwidget.h"
#include <QObject>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();

    void openCompetition(QString);
    void changeConnection(void);

private:
    DataBaseController* baseController;
    DataTransferController* transferController;

    //QList<Category*> lCategory;
    QListWidget* lCategories;

    QString currentBaseName;


signals:
};

#endif // CONTROLLER_H
