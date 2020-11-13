#include "mainwindow.h"

#include <QCoreApplication>
#include <QDebug>
#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#include "parsers/fb2parser.h"
#include "scrolledtextbrowser.h"

MainWindow::MainWindow(QWidget* parent) : QWidget(parent) {
  QVBoxLayout* layer = new QVBoxLayout(this);
  setLayout(layer);

  Fb2Parser* fb2Parser = new Fb2Parser();
  ScrolledTextBrowser* textBrowser = new ScrolledTextBrowser;

  QPushButton* prevPage = new QPushButton("prevPage");
  QPushButton* nextPage = new QPushButton("nextPage");

  connect(prevPage, &QPushButton::clicked,
          [=] { textBrowser->emitKeyboardClick(Qt::Key_Left); });
  connect(nextPage, &QPushButton::clicked,
          [=] { textBrowser->emitKeyboardClick(Qt::Key_Right); });

  QLabel* label = new QLabel();

  QString fileName =
      QFileDialog::getOpenFileName(this, tr("Выберите книгу"), "",
                                   tr("Формат книги (*.fb2);;All Files (*)"));

  QString book = fb2Parser->parseFile(fileName);
  textBrowser->setHtml(book);

  int pagesCount = textBrowser->getPagesCount();
  qDebug() << pagesCount;
  label->setText(QString::number(pagesCount));

  layer->addWidget(prevPage);
  layer->addWidget(nextPage);
  layer->addWidget(textBrowser);
  layer->addWidget(label);
}

MainWindow::~MainWindow() {}
