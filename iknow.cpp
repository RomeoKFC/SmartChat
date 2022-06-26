#include "iknow.h"

#include <QProcess>
#include <QDebug>
#include <QTextCodec>
#include <QCoreApplication>
#include <QByteArray>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>

IKnow::IKnow()
{
	m_pNetAcsMgr = new QNetworkAccessManager(this);
    QString strPorc = QCoreApplication::applicationDirPath() + "/IKNOW.exe";

    m_pProc = new QProcess();
    m_pProc->setReadChannel(QProcess::StandardOutput);
    m_pProc->start(strPorc);

    connect(m_pProc, SIGNAL(readyReadStandardOutput()), this, SLOT(recvStandOut()));
}

IKnow::~IKnow()
{
    m_pProc->kill();
    delete m_pProc;
    m_pProc = nullptr;
}

void IKnow::recvStandOut()
{
    exec();
}

QString IKnow::answer()
{
    return m_strQuestion;
}

void IKnow::setQuestion(QString strQuestion)
{
    //向IKNOW.exe发送消息
    /*QByteArray byte = strQuestion.toLocal8Bit();
    const char *pChar = byte.data();
    m_pProc->write(pChar);
    m_pProc->write("\r\n");
    qDebug() << m_pProc->waitForBytesWritten(2000);*/
	m_strQuestion = strQuestion;
}

void IKnow::OnGetReplyFromUrlRtn(QNetworkReply* pRply)
{
	int iError = pRply->error();
	if (iError == QNetworkReply::NoError)
	{
		QByteArray bytes = pRply->readAll();
		QString jsonString = QString::fromUtf8(bytes);

		QJsonParseError jsonParseError;
		QJsonDocument jsonDoc = QJsonDocument::fromJson(bytes, &jsonParseError);
		if (!jsonDoc.isNull() && jsonParseError.error == QJsonParseError::NoError)
		{
			if (jsonDoc.isArray())
			{
				
			}
			else
			{
				QJsonObject jsonObject = jsonDoc.object();
				QString strRet = jsonObject["content"].toString();
				//用换车替换{br}
				strRet.replace("{br}", QChar('\n'));
				emit signalFindAnswer(strRet);
			}
		}
		else
		{
		}
	}
}

bool IKnow::findAnswer()
{
    //收到IKNOW.exe的消息
	// 方案1.根据C++调用python进程来获取答案
    /*QByteArray byte = m_pProc->readAllStandardOutput();
    QTextCodec *pTextCodec = QTextCodec::codecForName("GBK");
    QString strMsg = pTextCodec->toUnicode(byte);
    if (strMsg.isEmpty()) {
        return false;
    }
    //用换车替换{br}
    strMsg.replace("{br}", QChar('\n'));

    m_strQuestion = strMsg;
    return true;*/

	//方案2.C++独立请求后台接口来得到答案
	QObject::connect(m_pNetAcsMgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(OnGetReplyFromUrlRtn(QNetworkReply*)));
	QString strUrl = QString("http://api.qingyunke.com/api.php?key=free&appid=0&msg=%1").arg(m_strQuestion);
	QUrl url(strUrl);
	QNetworkRequest req(url);
	req.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json;charset=utf-8"));
	m_pNetAcsMgr->get(req);
	return true;
}

void IKnow::exec()
{
    if (findAnswer()) {
        //emit signalFindAnswer();
    }
}
