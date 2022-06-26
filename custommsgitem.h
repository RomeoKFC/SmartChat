#ifndef CUSTOMMSGITEM_H
#define CUSTOMMSGITEM_H

#include <QWidget>
#include "common.h"

namespace Ui {
class CustomMsgItem;
}
class QLabel;
class CustomMsgItem : public QWidget
{
    Q_OBJECT

public:
    explicit CustomMsgItem(QWidget *parent = 0, E_WHOSAY = E_WHOSAY::eMe);
    ~CustomMsgItem();

    void paintEvent(QPaintEvent *);

    void setMsg(QString strMsg);
    QString getMsg();

    void setMsgBackgroudColor(E_COLOR);

private:
    Ui::CustomMsgItem *ui;
    QString m_strMsg;
    QLabel *m_pLbMsg;
    QColor m_colorBackgroundMsg;

    E_WHOSAY m_eWhoSay;
};

#endif // CUSTOMMSGITEM_H
