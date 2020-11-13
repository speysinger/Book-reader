#ifndef FB2PARSER_H
#define FB2PARSER_H

#include <QString>

class Fb2Parser {
 public:
  Fb2Parser();
  const QString parseFile(const QString fileName);
};

#endif  // FB2PARSER_H
