#ifndef CONTROLPANEL_____H
#define CONTROLPANEL_____H

#include <QWidget>

namespace Ui {
class ControlPanel_0_0;
}

class ControlPanel_0_0 : public QWidget
{
    Q_OBJECT

public:
    explicit ControlPanel_0_0(QWidget *parent = nullptr);
    ~ControlPanel_0_0();

private:
    Ui::ControlPanel_0_0 *ui;
};

#endif // CONTROLPANEL_____H
