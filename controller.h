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
    explicit Controller(QListWidget*, QObject *parent = nullptr);
    ~Controller();

    void openCompetition(QString);
    void changeConnection(void);
    bool addCategory(QString);

public slots:
    void setCategoryScene(QGraphicsScene*);

private:
    DataBaseController* baseController;
    DataTransferController* transferController;
    QObject* p;

    //QList<Category*> lCategory;
    QListWidget* listWidget;
    QList<Category*> listCategories;

    QString currentBaseName;


signals:
};

#endif // CONTROLLER_H
