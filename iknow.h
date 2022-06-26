#ifndef IKNOW_H
#define IKNOW_H

#include <QString>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class QProcess;
class IKnow : public QObject
{
    Q_OBJECT
public:
    IKnow();
    ~IKnow();
    QString answer();
    void setQuestion(QString);
    bool findAnswer();
    void exec();

signals:
    void signalFindAnswer(QString&);
	void sgnAnswreString(QString&);

private slots:
    void recvStandOut();
protected slots:
	void OnGetReplyFromUrlRtn(QNetworkReply* pRply);

private:
    QProcess *m_pProc;
    QString m_strAnswer;
    QString m_strQuestion;
	QNetworkAccessManager* m_pNetAcsMgr;
};

#endif // IKNOW_H
