#ifndef RTFPARSER_H
#define RTFPARSER_H

#include <QString>

class RtfParser {
 public:
  RtfParser();
  const QString parseFile(const QString fileName);
};

#endif  // RTFPARSER_H
