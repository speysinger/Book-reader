#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>

#include "singleton.h"

class TextSettings {
 public:
  int fontSize = 16;
  QString fontType = "";
};

#define TEXTSETTINGS Singleton<TextSettings>::instance()

#endif  // SETTINGS_H
