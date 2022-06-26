#include "custommsgitem.h"
#include "ui_custommsgitem.h"

#include <QPainter>
#include <QLabel>
#include <QDebug>

CustomMsgItem::CustomMsgItem(QWidget *parent, E_WHOSAY eWhoSay) :
    QWidget(parent),
    ui(new Ui::CustomMsgItem),
    m_strMsg(""),
    m_colorBackgroundMsg(WECHATGREEN),
    m_eWhoSay(eWhoSay)
{
    ui->setupUi(this);

    m_pLbMsg = new QLabel(this);
    m_pLbMsg->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->horizontalLayout->addWidget(m_pLbMsg);
    m_pLbMsg->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QFont font;
    font.setPixelSize(20);
    m_pLbMsg->setFont(font);
    m_pLbMsg->setWordWrap(true);
}

CustomMsgItem::~CustomMsgItem()
{
    delete ui;
}

void CustomMsgItem::paintEvent(QPaintEvent *)
{
    m_pLbMsg->setText(m_strMsg);
    //根据当前文字长度设置气泡长度
    QFontMetrics fontMetrics(m_pLbMsg->font());

    //如果当前字体长度大于窗体宽度的二分之一
    //就不断分割
    if (fontMetrics.width(m_pLbMsg->text()) > this->parentWidget()->width() / 2) {
        setFixedWidth(30 + this->parentWidget()->width() / 2);
        int iLine = (fontMetrics.width(m_pLbMsg->text()) % (this->parentWidget()->width() / 2)) == 0 ? 0 : fontMetrics.height();
        setFixedHeight(30 + fontMetrics.height() * ((fontMetrics.width(m_pLbMsg->text()) / (this->parentWidget()->width() / 2))) + iLine);
    } else {
        setFixedWidth(fontMetrics.width(m_pLbMsg->text()) + 30);
        setFixedHeight(fontMetrics.height() + 25);
    }


    QPainter painter(this);

    QRectF rectangle;
    QPainterPath trianglePath;
    if (m_eWhoSay == E_WHOSAY::eMe) {
        rectangle = QRectF(0, 0, width() - 5, height());
        trianglePath = QPainterPath(QPointF(width() - 5, height() / 2 - 7));
        trianglePath.lineTo(width(), height() / 2);
        trianglePath.lineTo(width() - 5, height() / 2 + 7);
        trianglePath.lineTo(width() - 5, height() / 2 - 7);
    } else if (m_eWhoSay == E_WHOSAY::eFriend) {
        m_colorBackgroundMsg.setRgb(WHITE);
        rectangle = QRectF(5, 0, width() - 5, height());
        trianglePath = QPainterPath(QPointF(5, height() / 2 - 7));
        trianglePath.lineTo(0, height() / 2);
        trianglePath.lineTo(5, height() / 2 + 7);
        trianglePath.lineTo(5, height() / 2 - 7);
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(m_colorBackgroundMsg);
    //画矩形
    painter.drawRoundedRect(rectangle, 5.0, 5.0);
    //画三角形
    painter.drawPath(trianglePath);
}

void CustomMsgItem::setMsg(QString strMsg)
{
    this->m_strMsg = strMsg;
}

QString CustomMsgItem::getMsg()
{
    return m_strMsg;
}

void CustomMsgItem::setMsgBackgroudColor(E_COLOR eColor)
{
    if (eColor == E_COLOR::eWechatGreen) {
        m_colorBackgroundMsg.setRgb(WECHATGREEN);
    } else if (eColor == E_COLOR::eWhite) {
        m_colorBackgroundMsg.setRgb(WHITE);
    }
}
