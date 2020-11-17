#include "rtfparser.h"

#include <qfile.h>
#include <qmessagebox.h>
#include <qtextstream.h>

#include <QDebug>
#include <QTextBlock>
#include <QTextDocument>

#include "settings.h"

RtfParser::RtfParser() {}

const QString RtfParser::parseFile(const QString fileName) {
  QFile file(fileName);

  if (!file.open(QIODevice::ReadOnly)) {
    QMessageBox::information(nullptr, "Unable to open file",
                             file.errorString());
    return "";
  }

  int fontSize = TEXTSETTINGS.fontSize;

  QString book =
      "<!DOCTYPE HTML><html><style>p { text-indent: 20px; }</style><body "
      "style=\"font-size:" +
      QString::number(fontSize) + "px\">";

  QTextStream in(&file);
  QString text = in.readAll();

  QTextDocument *newDoc = new QTextDocument(text);
  QTextBlock currentBlock = newDoc->begin();

  /*while (currentBlock.isValid()) {
    // qDebug() << currentBlock.text();
    auto test = currentBlock.begin();
    qDebug() << currentBlock.document()->rootFrame()->
    currentBlock = currentBlock.next();
  }*/

  int emptyLines = -1;
  while (!in.atEnd()) {
    QString line = in.readLine();
    // todo: add to settings header dthreshold
    if (line == "")
      emptyLines++;
    else if (emptyLines == -1 || emptyLines >= 4) {
      book.append("<h1><b><center>" + line + "</center></b></h1>");
      emptyLines = 0;
    } else {
      book.append("<p>" + line + "</p>");
      emptyLines = 0;
    }
  }
  book.append("</body></html>");
  return book;
}
