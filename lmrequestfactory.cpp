#include "lmrequestfactory.h"
#include <QUrl>
#include <QUrlQuery>

QNetworkRequest LmRequestFactory::CreateRequest()
{
    QNetworkRequest request(QUrl("https://www.livemaster.ru/ajax/autocompleter.php")); // url

    // проставляем хидеры - без задних мыслей взято из браузера
    request.setRawHeader("Host", "www.livemaster.ru");
    request.setRawHeader("User-Agent", "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:57.0) Gecko/20100101 Firefox/57.0");
    request.setRawHeader("Accept", "application/json, text/javascript, */*; q=0.01");
    request.setRawHeader("Accept-Language", "ru-RU,ru;q=0.8,en-US;q=0.5,en;q=0.3");
    request.setRawHeader("Accept-Encoding", "gzip, deflate, br");
    request.setRawHeader("Referer", "https://www.livemaster.ru/");
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded; charset=UTF-8");
    //request.setRawHeader("Content-Length", QString::number(stru.length()).toUtf8());
        // переместили к тому месту, где мы точно знаем длину запроса
    request.setRawHeader("X-Requested-With", "XMLHttpRequest");
    request.setRawHeader("Cookie",      // "heavy_default=1; google_cookies_reset2=1; locale=ru_RU; uid=5a41bbb836a172.52371211; lmSubscriptions=%7B%222%22%3A%7B%22status%22%3Afalse%2C%22hiddenTopTen%22%3Afalse%7D%2C%223%22%3A%7B%22status%22%3Afalse%2C%22hiddenheader%22%3Afalse%7D%2C%2213%22%3A%7B%22status%22%3Afalse%2C%22hiddenMastersGroups%22%3Afalse%7D%7D; mastersSubscribes=%5B%5D; currencyID=643; definedOS=otherOS; mwebHeader=1; time_zone_real_offset=0; offset_from_utc=180; onlineAcademyTopEntry=close; _ym_uid=1514257458181884197; _ga=GA1.2.1821051826.1514257458; __utma=1.1821051826.1514257458.1514257458.1514257458.1; __utmz=1.1514257458.1.1.utmcsr=(direct)|utmccn=(direct)|utmcmd=(none); __gads=ID=9937f4910a434c8a:T=1514257458:S=ALNI_MZDZxfnWcOW4gktsmaNFJzkvzukcA; PHPSESSID=59pf06b6o1d3lbn7ua4q0r4pj2; firstEntryTopEntry=1; __utmc=1; geotarget=0; geotarget2=0");
                         "PHPSESSID=59pf06b6o1d3lbn7ua4q0r4pj2; heavy_default=1; geotarget=0; geotarget2=0; google_cookies_reset2=1; locale=ru_RU; uid=5a41bbb836a172.52371211; lmSubscriptions=%7B%222%22%3A%7B%22status%22%3Afalse%2C%22hiddenTopTen%22%3Afalse%7D%2C%223%22%3A%7B%22status%22%3Afalse%2C%22hiddenheader%22%3Afalse%7D%2C%2213%22%3A%7B%22status%22%3Afalse%2C%22hiddenMastersGroups%22%3Afalse%7D%7D; mastersSubscribes=%5B%5D; currencyID=643; definedOS=otherOS; mwebHeader=1; firstEntryTopEntry=1; time_zone_real_offset=0; offset_from_utc=180; onlineAcademyTopEntry=close; _ym_uid=1514257458181884197; _ym_visorc_45166209=w; _ga=GA1.2.1821051826.1514257458; _gid=GA1.2.1566696599.1514257458; __utma=1.1821051826.1514257458.1514257458.1514257458.1; __utmb=1.1.10.1514257458; __utmc=1; __utmz=1.1514257458.1.1.utmcsr=(direct)|utmccn=(direct)|utmcmd=(none); _ym_isad=2; __gads=ID=9937f4910a434c8a:T=1514257458:S=ALNI_MZDZxfnWcOW4gktsmaNFJzkvzukcA; _ym_visorc_3236596=w");
    request.setRawHeader("Connection", "keep-alive");

    return request;
}


QUrlQuery LmRequestFactory::CreateRequestString(const QString& requestParam)
{
    // searchType=1 - поиск по товарам на ЯМ
    QUrlQuery postData;
    postData.addQueryItem("search", requestParam);
    postData.addQueryItem("searchtype", "1");

    return postData;
//    return QString("search=" + requestParam + "&searchtype=1");
}

QString LmRequestFactory::CreateRequestString2(const QString& requestParam)
{
    return QString("search=" + requestParam + "&searchtype=1");
}
