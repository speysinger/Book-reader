#ifndef SCROLLEDTEXTBROWSER_H
#define SCROLLEDTEXTBROWSER_H
#include <QTextBrowser>

#include "translate/translater.h"

class ScrolledTextBrowser : public QTextBrowser {
  Q_OBJECT
 public:
  ScrolledTextBrowser(QWidget* parent = nullptr);
  /*void mousePressEvent(QMouseEvent* event);
  void mouseMoveEvent(QMouseEvent* event);*/
  void mouseReleaseEvent(QMouseEvent*);

  int getPagesCount();
  void emitKeyboardClick(Qt::Key);

  void keyPressEvent(QKeyEvent* event);

 public slots:
  void showTranslatedText(QByteArray& data);

 private:
  int m_cursorPos_y;
  bool m_isMouseButtonPressed;
  Translater translater;
};

#endif  // SCROLLEDTEXTBROWSER_H
