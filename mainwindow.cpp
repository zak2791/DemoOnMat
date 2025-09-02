#include "mainwindow.h"

#include "connectiondialog.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QDir>
#include <QActionGroup>

#include <QJsonObject>
#include <QMessageBox>

#include <QTcpServer>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
    , httpServer(nullptr)
{
    ui->setupUi(this);

    view = ui->widget;
    view->load(QUrl("http://127.0.0.1:8080"));
    //view->load(QUrl("https://yandex.ru/search/?text=qwebengineview+yt+dblbn+kjrfkmysq+cthdth&clid=2064708&search_source=dzen_desktop_safe&lr=191"));

    // QTimer* tmr = new QTimer(this);
    // connect(tmr, &QTimer::timeout, this, [this](){
    //     view->reload();
    //     view->url();
    //     qDebug()<<"load"<<view->url();
    // });
    // tmr->start(3000);


    // view->resize(1024, 750);
    // view->show();

    controller = new Controller(this);
    //server = new Server(this);
    listCategories = ui->listWidget;

    connect(ui->actConnection, &QAction::triggered, this, [this](){
        ConnectionDialog dlg;
        int ret = dlg.exec();
        if(ret == QDialog::Accepted)
            controller->changeConnection();
    });

    fillMenuLastCompetitions();

    httpServerSetup();


    // QHttpServer* server = new QHttpServer(this);

    // QString http = "<html>"
    //                "<head>"
    //                "<meta charset='utf-8'>"
    //                "</head>"
    //                "<body>"
    //                "<h1>Hello!</h1>"
    //                "</body>"
    //                "</html>";
    // server->route("/", [&http] () {
    //     return "hello";
    // });

    // auto tcpserver = new QTcpServer(this);

    // if (!tcpserver->listen(QHostAddress::Any, 7000) || !server->bind(tcpserver)) {
    //     delete tcpserver;
    //     //return -1;
    // }
    // qDebug() << "Listening on port" << tcpserver->serverPort();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::httpServerSetup()
{
    // settings->beginGroup("webServer");
    // bool enabledWebServer = settings->value("enabled").toBool();
    // int portWebServer = settings->value("port", 6001).toInt();
    // posRedInfo = settings->value("positionRed", "right").toString() == "right" ? 0 : 1;
    // settings->endGroup();
    bool enabledWebServer = true;
    int portWebServer = 8080;
    if(!enabledWebServer){
        delete httpServer;
        httpServer = nullptr;
    }else{
        if(httpServer && httpServer->servers().count() &&  httpServer->servers().at(0)->isListening() && httpServer->servers().at(0)->serverPort() != portWebServer){
            delete httpServer;
            httpServer = nullptr;
        }
        if(!httpServer){
            httpServerCreate();
            QTcpServer *tcpServer = new QTcpServer(httpServer);
            if(!tcpServer->listen(QHostAddress::Any, portWebServer) || !httpServer->bind(tcpServer)){
                QMessageBox::critical(this, tr("Ошибка при запуске Web-сервера"), tr("Невозможно запустить Web-сервер хода поединка."));
                delete httpServer;
                httpServer = nullptr;
                //settings->setValue("webServer/enabled", false);
            }
        }
    }
}

void MainWindow::httpServerCreate()
{
    httpServer = new QHttpServer(this);
    httpServer->addAfterRequestHandler(httpServer, [](const QHttpServerRequest &, QHttpServerResponse &resp){
        auto headers = resp.headers();
        headers.replaceOrAppend("Access-Control-Allow-Origin", "*");
        headers.replaceOrAppend("Access-Control-Allow-Methods", "GET");
        headers.replaceOrAppend("Access-Control-Allow-Headers", "Content-Type, Origin, Accept, Authorization, Content-Length, X-Requested-With");
        resp.setHeaders(std::move(headers));
    });

    httpServer->route("/", [](){
        QFile file(QApplication::applicationDirPath() + "/TabloRB.html");
        if(!file.open(QFile::ReadOnly)){
            file.setFileName(":/TabloRB.html");
            if(!file.open(QFile::ReadOnly)){
                return u8"Ошибка: Невозможно открыть файл TabloRB.html";
            }
        }
        static std::string result;
        result = QString::fromUtf8(file.readAll()).toStdString();
        return result.c_str();
    });
    httpServer->route("/tablo", [this](){
        return QHttpServerResponse("application/json", getCurrentData().toJson());
    });
}

QJsonDocument MainWindow::getCurrentData()
{
    /* Формат JSON
     * {
     *      "PosRedInfo":           Расположение информации 0 - Спортсмен с красным поясом слева, 1 - Спортсмен с красным поясом справа
     *      "Time":                 Время поединка
     *      "TimeEnabled":          Время поединка идет
     *      "FamilyRed":            Фамилия спортсмена с красным поясом
     *      "RegionRed":            Регион спортсмена с красным поясом
     *      "RateRed":              Баллы спортсмена с красным поясом
     *      "PlusRed":              Первое техническое действие спортсмена с красным поясом
     *      "ViolationRed":         Нарушение правил спортсмена с красным поясом
     *      "ParterRed":            Время партера спортсмена с красным поясом
     *      "ParterRedEnabled":     Время партера спортсмена с красным поясом
     *      "TechnicalRed":         Техническое время спортсмена с красным поясом
     *      "TechnicalRedEnabled":  Техническое время спортсмена с красным поясом
     *      "DoctorRed":            Время на врача спортсмена с красным поясом
     *      "DoctorRedEnabled":     Время на врача спортсмена с красным поясом
     *      "FamilyBlue":           Фамилия спортсмена с синим поясом
     *      "RegionBlue":           Регион спортсмена с синим поясом
     *      "RateBlue":             Баллы спортсмена с синим поясом
     *      "PlusBlue":             Первое техническое действие спортсмена с синим поясом
     *      "ViolationBlue":        Нарушение правил спортсмена с синим поясом
     *      "ParterBlue":           Время партера спортсмена с синим поясом
     *      "ParterBlueEnabled":    Время партера спортсмена с синим поясом
     *      "TechnicalBlue":        Техническое время спортсмена с синим поясом
     *      "TechnicalBlueEnabled": Техническое время спортсмена с синим поясом
     *      "DoctorBlue":           Время на врача спортсмена с синим поясом
     *      "DoctorBlueEnabled":    Время на врача спортсмена с синим поясом
     *      "ShowNext":             Показывать следующую пару
     *      "NextFamilyRed:         Фамилия следующего спортсмена с красным поясом
     *      "NextFamilyBlue:        Фамилия следующего спортсмена с синим поясом
     * }
     */
    QJsonObject Obj;
    // Obj["PosRedInfo"] = posRedInfo;
    // Obj["Time"] = mainTimer->getTime();
    // Obj["TimeEnabled"] = (mainTimer->getStatus() == 1);
    // Obj["FamilyRed"] = fam_red->getText();
    // Obj["RegionRed"] = reg_red->getText();
    // Obj["RateRed"] = rateRed->getRate();
    // Obj["PlusRed"] = plus_red.getText();
    // Obj["ViolationRed"] = np_red->text();
    // if(sec_red->isVisible())
    //     Obj["ParterRed"] = sec_red->getTime();
    // Obj["ParterRedEnabled"] = (sec_red->getStatus() == 1);
    // if(sec_red_t->isVisible())
    //     Obj["TechnicalRed"] = sec_red_t->getTime();
    // Obj["TechnicalRedEnabled"] = (sec_red_t->getStatus() == 1);
    // if(sec_red_doctor->isVisible())
    //     Obj["DoctorRed"] = sec_red_doctor->getTime();
    // Obj["DoctorRedEnabled"] = (sec_red_doctor->getStatus() == 1);
    // Obj["FamilyBlue"] = fam_blue->getText();
    // Obj["RegionBlue"] = reg_blue->getText();
    // Obj["RateBlue"] = rateBlue->getRate();
    // Obj["PlusBlue"] = plus_blue.getText();
    // Obj["ViolationBlue"] = np_blue->text();
    // if(sec_blue->isVisible())
    //     Obj["ParterBlue"] = sec_blue->getTime();
    // Obj["ParterBlueEnabled"] = (sec_blue->getStatus() == 1);
    // if(sec_blue_t->isVisible())
    //     Obj["TechnicalBlue"] = sec_blue_t->getTime();
    // Obj["TechnicalBlueEnabled"] = (sec_blue_t->getStatus() == 1);
    // if(sec_blue_doctor->isVisible())
    //     Obj["DoctorBlue"] = sec_blue_doctor->getTime();
    // Obj["DoctorBlueEnabled"] = (sec_blue_doctor->getStatus() == 1);
    // Obj["ShowNext"] = settings->value("webServer/showNext", true).toBool();
    // Obj["NextFamilyRed"] = fam_next_red->getText();
    // Obj["NextFamilyBlue"] = fam_next_blue->getText();
    return QJsonDocument(Obj);
}

void MainWindow::fillMenuLastCompetitions()
{
    QDir dir = QDir::current();
    QFileInfoList lFiles = dir.entryInfoList({"*.db"}, QDir::Files, QDir::Time);
    if(lFiles.count() > 0){
        QActionGroup* gr = new QActionGroup(this);
        foreach(QFileInfo inf, lFiles){
            QAction* act = gr->addAction(inf.completeBaseName());
            act->setCheckable(true);
            connect(act, &QAction::triggered, this, [act, this]{
                controller->openCompetition(act->text());
            });
        }
        ui->mOpenLast->addActions(gr->actions());
    }

}
