#include "scrolledtextbrowser.h"

#include <qcoreapplication.h>

#include <QMouseEvent>
#include <QScrollBar>
#include <QStyle>

ScrolledTextBrowser::ScrolledTextBrowser(QWidget* parent)
    : QTextBrowser(parent), m_cursorPos_y(0) {}

int ScrolledTextBrowser::getPagesCount() {
  // todo: pagescount
  return this->verticalScrollBar()->height();
}

void ScrolledTextBrowser::emitKeyboardClick(Qt::Key key) {
  QKeyEvent* event;  // = new QKeyEvent(QEvent::KeyPress, Qt::Key_Enter,
                     // Qt::NoModifier);
  switch (key) {
    case Qt::Key_Left:
      event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);
      break;
    case Qt::Key_Right:
      event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);
      break;
    default:
      return;
  }

  QCoreApplication::postEvent(this, event);
}

/*void ScrolledTextBrowser::mousePressEvent(QMouseEvent* event) {
  m_cursorPos_y = event->pos().y();
  m_isMouseButtonPressed = true;
}

void ScrolledTextBrowser::mouseMoveEvent(QMouseEvent* event) {
  if (m_isMouseButtonPressed == false) return;

  int distance = event->pos().y() - m_cursorPos_y;

  QScrollBar* vScroll = this->verticalScrollBar();
  if (vScroll == nullptr) return;

  int scrollValue = vScroll->value();

  vScroll->setValue(scrollValue - distance);
  m_cursorPos_y = event->pos().y();
}

void ScrolledTextBrowser::mouseReleaseEvent(QMouseEvent*) {
  m_isMouseButtonPressed = false;
}*/

void ScrolledTextBrowser::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Left || Qt::Key_Right) {
    int shift = event->key() == Qt::Key_Left
                    ? this->verticalScrollBar()->pos().y() - this->height()
                    : this->verticalScrollBar()->pos().y() + this->height();
    int scrollValue = this->verticalScrollBar()->value();
    this->verticalScrollBar()->setValue(scrollValue + shift);
  }
}
