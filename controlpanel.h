#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
#include <QJsonObject>

class ControlPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ControlPanel(QWidget *parent = nullptr);
    int getIdSystem(void){return id_system;}
    virtual void setData(int, QJsonObject) = 0;

private:
    int id_system;

protected:
    int id_category;

signals:
    void sigFixResult(int, QJsonObject);

};

#endif // CONTROLPANEL_H
