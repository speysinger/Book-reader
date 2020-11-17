#include "translater.h"

#include <QByteArray>
#include <QEventLoop>

void Translater::translate(QString text) {
  QNetworkReply* reply;
  try {
    reply = translateText(text);
  } catch (NetworkReplyException error) {
    throw std::runtime_error("Network error");
  }
  QByteArray result = reply->readAll();

  qDebug() << result;
  reply->deleteLater();
  emit translated(result);
}

QNetworkReply* Translater::translateText(QString text) {
  QEventLoop loop;
  connect(&m_manager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
  QNetworkReply* translatedText;
  QString url =
      "http://translate.google.ru/translate_a/t?client=x&text=" + text +
      "&hl=en&sl=en&tl=ru";
  translatedText = m_manager.get(QNetworkRequest(QUrl(url)));
  loop.exec();

  if (translatedText->error() != QNetworkReply::NoError) {
    translatedText->abort();
    translatedText->deleteLater();
    m_manager.clearAccessCache();
    throw NetworkReplyException("in DataLoader: " +
                                translatedText->errorString().toStdString());
  }

  return translatedText;
}
