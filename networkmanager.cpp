#include "networkmanager.h"
#include "gziptreater.h"


#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QUrl>
#include <QUrlQuery>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

NetworkManager::NetworkManager(QObject* pobj)
{
    m_pnam = new QNetworkAccessManager(this);

    connect(m_pnam, &QNetworkAccessManager::finished,
            this,   &NetworkManager::slotFinished
            );
}

NetworkManager::~NetworkManager()
{
    delete m_pnam;
}

void NetworkManager::doRequest(QNetworkRequest& request, const QUrlQuery& postData)
{
    auto str = postData.toString(QUrl::FullyEncoded);
    auto stru = str.toUtf8();
    request.setRawHeader("Content-Length", QString::number(stru.length()).toUtf8());

    QNetworkReply* pnr = m_pnam->post(request,
                                      stru);
                                      //requestString.toUtf8());

//    connect(pnr, &QNetworkReply::downloadProgress,
//            this, &Downloader::downloadProgress
//            );
}

void NetworkManager::slotFinished(QNetworkReply* reply)
{
    if (reply->error() != QNetworkReply::NoError)
    {
        emit error();
    }
    else
    {
        // по умолчанию ответы от ЯМ сжаты gzip,
        // но по-хорошему мы должны узнавать это из хидеров
        auto data = GzipTreater::uncompress(reply->readAll());
        QString allStrings = "";

        // анализ ответа - вычленяем все строки, обозначенные "string"
        QJsonDocument jsonObj = QJsonDocument::fromJson(data);
        QString name = "";

        if (jsonObj.isArray())
        {
            // строку запроса мы можем вычленить из значения с ключом "block"
            // - она выделена тегом <b></b>
            auto arr = jsonObj.array();

            auto first = (*arr.begin());
            if (first.isObject())
            {
                auto obj = first.toObject();
                auto str = obj.value("block").toString();

                QRegularExpression regex("b\\>([а-яА-Яa-zA-Z0-9 ])+\\<\\/b");
                int ind = 0;

                do
                {
                    QRegularExpressionMatch match;
                    str.indexOf(regex, ind, &match);
                    if (match.isValid() && match.hasMatch())
                    {
                        QString tmp = match.captured();
                        name += " " + tmp.mid(2, tmp.length()-5);
                        ind = match.capturedEnd();
                    }
                    else
                    {
                        break;
                    }

                } while (true);
            }

            for (QJsonValue entry : arr)
            {
                if (entry.isObject())
                {
                    auto obj = entry.toObject();
                    auto str = obj.value("string");
                    allStrings += str.toString() + '\n';
                }
            }
        }

        //auto ba = allStrings.toUtf8();
        emit done(allStrings, name);
    }
    reply->deleteLater();
}
