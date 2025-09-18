#ifndef LEDWIDGET_H
#define LEDWIDGET_H

#include "qwidget.h"

class LEDWidget : public QWidget {
    Q_OBJECT

public:
    LEDWidget(int, QWidget* parent = nullptr);
    void turnOnOff(bool);

protected:
    void paintEvent(QPaintEvent* event) override;

    void resizeEvent(QResizeEvent* event) override;

// private slots:
//     void setStatus(int);

private:
    bool status;    // Состояние светодиода
    int mode;       // Режим: 0 - красный - зелёный
                    //        1 - серый - красный

};

#endif // LEDWIDGET_H
