#include "controller.h"
#include "category_0_0.h"
#include "mainwindow.h"
#include "qdebug.h"
#include "qjsonobject.h"

Controller::Controller(QListWidget* list, QObject *parent)
    : QObject{parent}
{
    baseController = new DataBaseController(this);
    currentBaseName = "";
    transferController = new DataTransferController(&currentBaseName, this);
    listWidget = list;
    p = parent;
}

Controller::~Controller()
{
    delete baseController;
    foreach (auto each, listCategories)
        delete each;
}

void Controller::openCompetition(QString name)
{
    QList<std::tuple<int, int, int, int, int, QString, QString, QString, QString>> listData = baseController->readCategories(name + ".db");
    currentBaseName = name;
    if(listData.count() == 0)
        return;

    foreach (auto each, listCategories)
        delete each;
    listCategories.clear();

    foreach(auto each, listData){
        int id = std::get<0>(each);
        int id_category = std::get<1>(each);
        int id_system = std::get<2>(each);
        int mode = std::get<3>(each);
        int status = std::get<4>(each);
        QString category = std::get<5>(each);
        QString age = std::get<6>(each);
        QString weight = std::get<7>(each);
        QString data = std::get<8>(each);

        if(id_system == 0){
            if(mode == 0){
                Category* cat = new Category_0_0(id, id_category, status, category, age, weight, data);
                connect(cat, &Category::sigScene, this, &Controller::setCategoryScene);
                //connect(cat, &Category::sigSendData, transferController, &DataTransferController::sendOnMat);
                listCategories.append(cat);
                QListWidgetItem* item  = new QListWidgetItem();
                item->setSizeHint(cat->sizeHint());
                item->setData(Qt::UserRole, id);
                listWidget->addItem(item);
                listWidget->setItemWidget(item, cat);
            }
        }
        //listData.append(std::tuple(id, category, age, weight));
    }
}

void Controller::changeConnection()
{
    transferController->changeConnection();
}

bool Controller::addCategory(QString _data)
{
    QJsonDocument doc = QJsonDocument::fromJson(_data.toUtf8());
    QJsonObject obj = doc.object();
    int id_base = obj.value("Id_category").toInt();
    foreach(auto each, listCategories)
        if(each->getBaseCategory() == id_base)
            return true;                        //категория уже существует
    int id_system = obj.value("Id_system").toInt();
    int mode = obj.value("Mode").toInt();
    QString category =  obj.value("Category").toString();
    QString age =  obj.value("Age").toString();
    QString weight =  obj.value("Weight").toString();
    QJsonObject data = obj.value("Data").toObject();
    doc.setObject(data);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    int id = baseController->addCategory(id_base, id_system, mode, category, age, weight, strJson);
    if(id == -1)
        return false;

    if(id_system == 0){
        if(mode == 0){
            Category* cat = new Category_0_0(id, id_base, 0, category, age, weight, strJson);
            listCategories.append(cat);
        }
    }
    return true;
}

void Controller::setCategoryScene(QGraphicsScene * scene)
{
    static_cast<MainWindow*>(p)->setCategoryScene(scene);
}
