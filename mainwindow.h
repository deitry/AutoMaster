#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUrlQuery>

class NetworkManager;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    NetworkManager *netman;

    // настройки - пока тупо в виде флагов
    bool isRecursive = {false};
    bool clearOnStart = {true};

private slots:
    void slotGo();
    void slotError();
    //void slotDownloadProgress(qint64, qint64);
    void slotDone(const QString&, const QString& requestParam);

};

#endif // MAINWINDOW_H
