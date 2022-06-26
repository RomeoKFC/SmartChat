#include "topaopao.h"
#include <QApplication>

#include "custommsgitem.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ToPaoPao w;
    w.show();
    return a.exec();
}
