#ifndef TRANSLATER_H
#define TRANSLATER_H

#include <QtNetwork/qnetworkreply.h>

#include <QtNetwork/QNetworkAccessManager>

class Translater : public QObject {
  Q_OBJECT
 public:
  struct NetworkReplyException : public std::invalid_argument {
    NetworkReplyException(std::string what) : std::invalid_argument(what) {}
  };

  void translate(QString text);
 signals:
  void translated(QByteArray &text);

 private:
  QNetworkReply *translateText(QString text);

 private:
  QNetworkAccessManager m_manager;
};

#endif  // TRANSLATER_H
