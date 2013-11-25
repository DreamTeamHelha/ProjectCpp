ifndef TOOLS_H
#define TOOLS_H

#include <QWidget>

namespace Ui {
class tools;
}

class tools : public QWidget
{
    Q_OBJECT

public:
    explicit tools(QWidget *parent = 0);
    ~tools();

private:
    Ui::tools *ui;
};

#endif // TOOLS_H
