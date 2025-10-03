#include "controller.h"
#include "category_0.h"
#include "category_1.h"
#include "controlpanel_0.h"
#include "controlpanel_1.h"
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
    connect(transferController, &DataTransferController::sigConnect, this, [this](){
        static_cast<MainWindow*>(p)->turnOnStatus();
    });
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

    int index = currentBaseName.lastIndexOf("_");
    QString name1 = currentBaseName.first(index);
    QString name2 = currentBaseName.last(1);

    static_cast<MainWindow*>(p)->openCompetition(name1 + "    Ковёр " + name2);

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
                Category* cat = new Category_0(id, id_category, status, category, age, weight, data);
                connect(cat, &Category::sigScene, this, &Controller::setCategoryScene);
                connect(cat, &Category::sigDataControlPanel, this, &Controller::slotDataControlPanel);
                connect(cat, &Category::sigSaveData, this, &Controller::slotSaveData);
                connect(cat, &Category::sigSendData, this, &Controller::slotSendData);
                listCategories.append(cat);
                QListWidgetItem* item  = new QListWidgetItem();
                item->setSizeHint(cat->sizeHint());
                listWidget->addItem(item);
                listWidget->setItemWidget(item, cat);
            }
        }
        else if(id_system == 1){
            if(mode == 0){
                Category* cat = new Category_0(id, id_category, status, category, age, weight, data);
                connect(cat, &Category::sigScene, this, &Controller::setCategoryScene);
                connect(cat, &Category::sigDataControlPanel, this, &Controller::slotDataControlPanel);
                connect(cat, &Category::sigSaveData, this, &Controller::slotSaveData);
                connect(cat, &Category::sigSendData, this, &Controller::slotSendData);
                listCategories.append(cat);
                QListWidgetItem* item  = new QListWidgetItem();
                item->setSizeHint(cat->sizeHint());
                listWidget->addItem(item);
                listWidget->setItemWidget(item, cat);
            }
            else if(mode == 2){
                Category* cat = new Category_1(id, id_category, status, category, age, weight, data);
                connect(cat, &Category::sigScene, this, &Controller::setCategoryScene);
                connect(cat, &Category::sigDataControlPanel, this, &Controller::slotDataControlPanel);
                connect(cat, &Category::sigSaveData, this, &Controller::slotSaveData);
                connect(cat, &Category::sigSendData, this, &Controller::slotSendData);
                listCategories.append(cat);
                QListWidgetItem* item  = new QListWidgetItem();
                item->setSizeHint(cat->sizeHint());
                listWidget->addItem(item);
                listWidget->setItemWidget(item, cat);
            }
        }
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
    QJsonArray data = obj.value("Data").toArray();
    //qDebug() << "-------------------"<<_data<<data;
    QString strJson = createCategoryData(id_system, mode, data);

    int id = baseController->addCategory(id_base, id_system, mode, category, age, weight, strJson);
    if(id == -1)
        return false;

    Category* cat = nullptr;
    if(id_system == 0){
        if(mode == 0)
            cat = new Category_0(id, id_base, 0, category, age, weight, strJson);
    } else if(id_system == 1){
        if(mode == 0)
            cat = new Category_0(id, id_base, 0, category, age, weight, strJson);
        else if(mode == 2)
            cat = new Category_1(id, id_base, 0, category, age, weight, strJson);
    }
    connect(cat, &Category::sigScene, this, &Controller::setCategoryScene);
    connect(cat, &Category::sigDataControlPanel, this, &Controller::slotDataControlPanel);
    connect(cat, &Category::sigSaveData, this, &Controller::slotSaveData);
    connect(cat, &Category::sigSendData, this, &Controller::slotSendData);
    listCategories.append(cat);
    QListWidgetItem* item  = new QListWidgetItem();
    item->setSizeHint(cat->sizeHint());
    listWidget->addItem(item);
    listWidget->setItemWidget(item, cat);
    return true;
}

bool Controller::removeCategory(int _id)
{
    for(int i = 0; i < listCategories.length(); i++){
        if(listCategories.at(i)->getBaseCategory() == _id){
            if(listCategories.at(i)->getStatus() > 0)
                return false;
            int id = listCategories.at(i)->getId();
            if(!baseController->removeCategory(id))
                return false;
            delete listCategories.at(i);
            listCategories.remove(i);
            QListWidgetItem* item = listWidget->item(i);
            listWidget->removeItemWidget(item);
            delete item;
            listWidget->update();
            return true;
        }
    }
    return true;
}

void Controller::setCategoryScene(QGraphicsScene * scene, Category* cat)
{
    static_cast<MainWindow*>(p)->setCategoryScene(scene);
    foreach(auto each, listCategories){
        each->setStyleSheet("background-color: white");
        each->setStatus(0);
    }
    cat->setStyleSheet("background-color: yellow");
    cat->setStatus(1);
}

void Controller::slotDataControlPanel(int _id, int _id_system, QJsonObject obj)
{
    if(panel != nullptr){
        if(panel->getIdSystem() != _id_system){
            static_cast<MainWindow*>(p)->removeControlPanel(panel);
            delete panel;
            if(_id_system == 0)
                panel = new ControlPanel_0;
            else                                // if(_id_system == 1)
                panel = new ControlPanel_1;
            static_cast<MainWindow*>(p)->setControlPanel(panel);
            connect(panel, &ControlPanel::sigFixResult, this, &Controller::slotFixResult);
        }
    }
    else{
        if(_id_system == 0)
            panel = new ControlPanel_0;
        else                                    // if(_id_system == 1)
            panel = new ControlPanel_1;
        static_cast<MainWindow*>(p)->setControlPanel(panel);
    }
    panel->setData(_id, obj);
    connect(panel, &ControlPanel::sigFixResult, this, &Controller::slotFixResult);
}

void Controller::slotFixResult(int id, QJsonObject obj)
{
    foreach(auto each, listCategories){
        if(id == each->getId()){
            each->setDataFromControlPanel(obj);
            return;
        }
    }
}

void Controller::slotSaveData(int id, QString strJson)
{
    baseController->writeData(id, strJson);
}

void Controller::slotSendData(int _id, QString _data)
{
    if(transferController->sendData(_data)){
        foreach (auto each, listCategories) {
            if(each->getId() == _id){
                each->setStatus(3);
                baseController->updateStatus(_id, 3);
                break;
            }
        }
    }
    else{
        foreach (auto each, listCategories) {
            if(each->getId() == _id){
                each->setStatus(2);
                baseController->updateStatus(_id, 2);
                break;
            }
        }
    }
}

QString Controller::createCategoryData(int id_system, int mode, QJsonArray _arr){
    if(id_system == 0 || id_system == 1){
        if(mode == 0 || mode == 2){
            QJsonArray mainArray;
            for(int i = 0; i < _arr.size(); i++){
                QJsonObject o = _arr.at(i).toObject();
                o.insert("CurrentTask", 0);
                o.insert("TotalRate", 0.0);
                o.insert("AddRate", 0);
                o.insert("Task1Rate", 0.0);
                o.insert("Task2Rate", 0.0);
                o.insert("Task3Rate", 0.0);
                o.insert("Task4Rate", 0.0);
                o.insert("Task5Rate", 0.0);
                o.insert("Task1Ref1Rate", 0.0);
                o.insert("Task1Ref2Rate", 0.0);
                o.insert("Task1Ref3Rate", 0.0);
                o.insert("Task1Ref4Rate", 0.0);
                o.insert("Task1Ref5Rate", 0.0);
                o.insert("Task2Ref1Rate", 0.0);
                o.insert("Task2Ref2Rate", 0.0);
                o.insert("Task2Ref3Rate", 0.0);
                o.insert("Task2Ref4Rate", 0.0);
                o.insert("Task2Ref5Rate", 0.0);
                o.insert("Task3Ref1Rate", 0.0);
                o.insert("Task3Ref2Rate", 0.0);
                o.insert("Task3Ref3Rate", 0.0);
                o.insert("Task3Ref4Rate", 0.0);
                o.insert("Task3Ref5Rate", 0.0);
                o.insert("Task4Ref1Rate", 0.0);
                o.insert("Task4Ref2Rate", 0.0);
                o.insert("Task4Ref3Rate", 0.0);
                o.insert("Task4Ref4Rate", 0.0);
                o.insert("Task4Ref5Rate", 0.0);
                o.insert("Task5Ref1Rate", 0.0);
                o.insert("Task5Ref2Rate", 0.0);
                o.insert("Task5Ref3Rate", 0.0);
                o.insert("Task5Ref4Rate", 0.0);
                o.insert("Task5Ref5Rate", 0.0);
                o.insert("Task1Ref1Err", "");
                o.insert("Task1Ref2Err", "");
                o.insert("Task1Ref3Err", "");
                o.insert("Task1Ref4Err", "");
                o.insert("Task1Ref5Err", "");
                o.insert("Task2Ref1Err", "");
                o.insert("Task2Ref2Err", "");
                o.insert("Task2Ref3Err", "");
                o.insert("Task2Ref4Err", "");
                o.insert("Task2Ref5Err", "");
                o.insert("Task3Ref1Err", "");
                o.insert("Task3Ref2Err", "");
                o.insert("Task3Ref3Err", "");
                o.insert("Task3Ref4Err", "");
                o.insert("Task3Ref5Err", "");
                o.insert("Task4Ref1Err", "");
                o.insert("Task4Ref2Err", "");
                o.insert("Task4Ref3Err", "");
                o.insert("Task4Ref4Err", "");
                o.insert("Task4Ref5Err", "");
                o.insert("Task5Ref1Err", "");
                o.insert("Task5Ref2Err", "");
                o.insert("Task5Ref3Err", "");
                o.insert("Task5Ref4Err", "");
                o.insert("Task5Ref5Err", "");

                mainArray.append(o);
            }

            QJsonDocument doc(mainArray);
            return doc.toJson(QJsonDocument::Compact);
        }

        return "";
    }
    return "";
}
