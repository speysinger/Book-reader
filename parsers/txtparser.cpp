#include "txtparser.h"

#include <qfile.h>
#include <qmessagebox.h>

#include <QTextStream>

#include "settings.h"

TxtParser::TxtParser() {}

const QString TxtParser::parseFile(const QString fileName) {
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
