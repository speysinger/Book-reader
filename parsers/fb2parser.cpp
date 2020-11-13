#include "fb2parser.h"

#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QXmlStreamReader>

#include "settings.h"

Fb2Parser::Fb2Parser() {}

const QString Fb2Parser::parseFile(const QString fileName) {
  QFile file(fileName);

  if (!file.open(QIODevice::ReadOnly)) {
    QMessageBox::information(nullptr, "Unable to open file",
                             file.errorString());
    return "";
  }

  QXmlStreamReader sr(&file);

  QString book;
  QStringList thisToken;
  QString imgId;
  QString imgType;

  int fontSize = TEXTSETTINGS.fontSize;
  while (!sr.atEnd()) {
    switch (sr.readNext()) {
      case QXmlStreamReader::NoToken:
        break;
      case QXmlStreamReader::StartDocument:
        book =
            "<!DOCTYPE HTML><html><style>p { text-indent: 20px; }</style><body "
            "style=\"font-size:" +
            QString::number(fontSize) + "px\">";
        break;
      case QXmlStreamReader::EndDocument:
        book.append("</body></html>");
        break;
      case QXmlStreamReader::StartElement:
        thisToken.append(sr.name().toString());
        if (sr.name().toString() == "image")  // расположение рисунков
        {
          if (sr.attributes().count() > 0)
            book.append("<p align=\"center\">" +
                        sr.attributes().at(0).value().toString() + "</p>");
        }
        if (sr.name() == "binary") {
          imgId = sr.attributes().at(0).value().toString();
          imgType = sr.attributes().at(1).value().toString();
        }
        break;
      case QXmlStreamReader::EndElement:
        if (thisToken.last() == sr.name().toString())
          thisToken.removeLast();
        else
          qDebug() << "error token";
        break;
      case QXmlStreamReader::Characters:
        QString text = sr.text().toString();
        if (text.contains(QRegExp("[A-Z]|[a-z]|[А-Я]|[а-я]"))) {
          if (thisToken.contains("description")) break;

          if (thisToken.contains("div")) break;

          if (!thisToken.contains("binary")) {
            if (thisToken.contains("title"))
              book.append("<h1><b><center>" + text + "</center></b></h1>");
            else if (thisToken.contains("emphasis"))
              book.append("<p><em>" + text + "</em></p>");
            else
              book.append("<p>" + text + "</p>");
          }
        }
        if (thisToken.contains("binary")) {
          QString image =
              "<img src=\"data:" + imgType + ";base64," + text + "\"/>";
          book.replace("#" + imgId, image);
        }
        break;
    }
  }
  return book;
}
