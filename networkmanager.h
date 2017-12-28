#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>

class QNetworkAccessManager;
class QNetworkReply;

class NetworkManager : public QObject
{
Q_OBJECT

private:
    QNetworkAccessManager* m_pnam;

public:
    NetworkManager(QObject* pobj = nullptr);
    ~NetworkManager();

    void doRequest(QNetworkRequest&, const QUrlQuery& requestString);

signals:
    void processing(qint64, qint64);
    void done(const QString&, const QString& requestParam);
    void error();

private slots:
    void slotFinished(QNetworkReply*);
};


#endif // NETWORKMANAGER_H
