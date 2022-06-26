#ifndef TOPAOPAO_H
#define TOPAOPAO_H

#include <QWidget>

namespace Ui {
class ToPaoPao;
}
class QVBoxLayout;
class IKnow;
class ToPaoPao : public QWidget
{
    Q_OBJECT

public:
    explicit ToPaoPao(QWidget *parent = 0);
    ~ToPaoPao();

    void paintEvent(QPaintEvent *);

    bool eventFilter(QObject *, QEvent *);

private slots:
    void on_btnSend_clicked();
    void slotFindAnswer(QString&);
    void slider();
	void OnGetRetString(QString&);

private:
    Ui::ToPaoPao *ui;
    QVBoxLayout *m_pVboxLayout;
    IKnow *m_pIknow;
	QString m_strRet;
};

#endif // TOPAOPAO_H
