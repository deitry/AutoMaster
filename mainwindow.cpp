#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "networkmanager.h"
#include "lmrequestfactory.h"

#include <QMessageBox>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    netman = new NetworkManager(this);

    ui->setupUi(this);

    connect(ui->goBtn, &QPushButton::clicked,
            this, &MainWindow::slotGo);
//    connect(m_pdl, &Downloader::downloadProgress,
//            this, &MainWindow::slotDownloadProgress);
    connect(netman, &NetworkManager::done,
            this, &MainWindow::slotDone);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete netman;
}

void MainWindow::slotGo()
{
    // первым делом - очищаем содержимое replyEdit
    if (true) ui->replyEdit->clear();

//    QByteArray ba;
//    ba.append(ui->requestStrEdit->toPlainText());
//    m_pdl->download(QUrl(ui->urlEdit->text()),
//                    ba);

    // пока размещаем всю логику здесь, вероятно, имеет смысл вынести её в отдельный класс

    // проходимся по строкам в requestEdit
    // для каждой строки отправляем запрос с соответствующим параметром
    // в качестве первого приближения все ответы просто пишем в replyEdit

    // по-хорошему, надо запоминать порядок, соотносить друг с другом и сортировать в порядке
    // наиболее вероятного использования

    auto request = LmRequestFactory::CreateRequest();
    QStringList lines = ui->requestEdit->toPlainText()
                          .split('\n', QString::SkipEmptyParts);
    for (QString& str : lines)
    {
        // TODO: пропускать строку, если она начинается с "//"
        if (str.left(2) == "//") continue;

        // интересно, ничего, что мы передаём один и тот же объект запроса?
        netman->doRequest(request, LmRequestFactory::CreateRequestString(str));
    }

    // TODO: если рекурсивно, то надо будет пройтись
    // теперь уже по списку с ответами
}

//void MainWindow::slotDownloadProgress(qint64 nRecieved, qint64 nTotal)
//{
//    if (nTotal <= 0)
//    {
//        //slotError();
//        return;
//    }

//    ui->progressBar->setValue(100 * nRecieved / nTotal);
//}


void MainWindow::slotDone(const QString& replyStr, const QString& requestParam)
{
    auto list = replyStr.split("\n", QString::SkipEmptyParts);
    auto blackList = ui->blackListEdit->toPlainText().split("\n", QString::SkipEmptyParts);
    for (auto entry : blackList)
    {
        int i = list.size()-1;
        for (auto it = list.rbegin(); it < list.rend(); it++)
        {
            if (entry.left(2) == "//" || (*it).left(2) == "//")
                continue;

            if ((*it).contains(entry))
                list.removeAt(i);

            i--;
        }
    }

    // вставляем в начале "комментарий" с искомым значением
    // всё в одной строке для обеспечения какой-никакой атомарности
    ui->replyEdit->insertPlainText("//" + requestParam + '\n'
                                   + list.join('\n') + "\n");
}

void MainWindow::slotError()
{
    QMessageBox::critical(0,
                          tr("Error"),
                          tr("An error while process is occured")
                          );
}

