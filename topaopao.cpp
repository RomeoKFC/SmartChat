#include "topaopao.h"
#include "ui_topaopao.h"
#include "custommsgitem.h"
#include "common.h"
#include "iknow.h"

#include <QPlainTextEdit>
#include <QPropertyAnimation>
#include <QDebug>
#include <QScrollBar>
#include <QThread>

ToPaoPao::ToPaoPao(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToPaoPao)
{
    ui->setupUi(this);

    setFocus();

    m_pVboxLayout = new QVBoxLayout();
    ui->scrollAreaWidgetContents_2->setLayout(m_pVboxLayout);

    m_pIknow = new IKnow();
    connect(m_pIknow, SIGNAL(signalFindAnswer(QString&)), this, SLOT(slotFindAnswer(QString&)));
	connect(m_pIknow, SIGNAL(sgnAnswreString(QString&)), this, SLOT(OnGetRetString(QString&)));

    ui->texteditInput->installEventFilter(this);

	QString strQuestion = ui->texteditInput->toPlainText();
	m_pIknow->setQuestion(strQuestion);

    connect(ui->scrollArea->verticalScrollBar(), &QAbstractSlider::rangeChanged, this, &ToPaoPao::slider);
}

ToPaoPao::~ToPaoPao()
{
    delete m_pIknow;
    delete m_pVboxLayout;
    delete ui;
}

void ToPaoPao::slider()
{
    ui->scrollArea->verticalScrollBar()->setValue(ui->scrollArea->verticalScrollBar()->maximum());
}

void ToPaoPao::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}

bool ToPaoPao::eventFilter(QObject *pObj, QEvent *pEvent)
{
    if (pObj == ui->texteditInput) {
        QKeyEvent *pKeyEvent = dynamic_cast<QKeyEvent *>(pEvent);
        if (pKeyEvent) {
            if (pKeyEvent->key() == Qt::Key_Return || pKeyEvent->key() == Qt::Key_Return) {
                on_btnSend_clicked();
            }
        }
    }
    return QWidget::eventFilter(pObj, pEvent);
}

void ToPaoPao::slotFindAnswer(QString& strAnswer)
{
    QHBoxLayout *pHboxLayout = new QHBoxLayout();
    CustomMsgItem *pItem = new CustomMsgItem(ui->scrollAreaWidgetContents_2, E_WHOSAY::eFriend);
    pHboxLayout->addWidget(pItem);
    pHboxLayout->insertStretch(1);
	pItem->setMsg(strAnswer);
    //pItem->setMsg(m_pIknow->answer());
    m_pVboxLayout->addLayout(pHboxLayout);
}

void ToPaoPao::OnGetRetString(QString& strRet)
{
	m_strRet = strRet;
}

void ToPaoPao::on_btnSend_clicked()
{
    QString strInput = ui->texteditInput->toPlainText();
    //去除回车
    strInput.remove(QChar('\n'));
    ui->texteditInput->clear();

    //判断输入框是否为空
    if (strInput.isEmpty()) {
        return ;
    }

    QHBoxLayout *pHboxLayout = new QHBoxLayout();

    CustomMsgItem *pItem = new CustomMsgItem(ui->scrollAreaWidgetContents_2, E_WHOSAY::eMe);
    pHboxLayout->insertStretch(0);
    pHboxLayout->addWidget(pItem);
    pItem->setMsg(strInput);
    m_pVboxLayout->addLayout(pHboxLayout);

    m_pIknow->setQuestion(strInput);
	m_pIknow->findAnswer();
}
