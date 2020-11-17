#ifndef TXTPARSER_H
#define TXTPARSER_H

#include <QString>

class TxtParser {
 public:
  TxtParser();
  const QString parseFile(const QString fileName);
};

#endif  // TXTPARSER_H
