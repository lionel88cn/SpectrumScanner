#include "mainwindow.h"
#include <QApplication>
#include "MessageWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /* uncomment if not developing using QtCreator */
    qInstallMessageHandler(MessageWindow::AppendMsgWrapper);
    MessageWindow debugWindow;
    debugWindow.show();
    debugWindow.resize(800, 800);
    MainWindow w;
    w.show();
    return a.exec();
}
