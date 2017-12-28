#ifndef LMREQUESTFACTORY_H
#define LMREQUESTFACTORY_H

#include <QtNetwork/QNetworkRequest>

// предоставляет правильным образом подготовленные запросы к ярмарке мастеров
// и обрабатывает ответы (?)
class LmRequestFactory // : public IRequestFactory
{
private:
    // так как мы собираемся обращаться только к статическим методам, прячем хвосты
    LmRequestFactory() = default;
    ~LmRequestFactory() = default;

public:
    static QNetworkRequest CreateRequest();

    // отдельная функция, которая добавляет к собственно искомому значению обвязку
    static QUrlQuery CreateRequestString(const QString& requestParam);
    static QString CreateRequestString2(const QString& requestParam);
};

#endif // LMREQUESTFACTORY_H
