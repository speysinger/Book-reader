#include "mainwindow.h"

#include <QCoreApplication>
#include <QDebug>
#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#include "parsers/fb2parser.h"
#include "parsers/rtfparser.h"
#include "parsers/txtparser.h"
#include "scrolledtextbrowser.h"

MainWindow::MainWindow(QWidget* parent) : QWidget(parent) {
  QVBoxLayout* layer = new QVBoxLayout(this);
  setLayout(layer);

  Fb2Parser* fb2Parser = new Fb2Parser();
  TxtParser* txtParser = new TxtParser();
  RtfParser* rtfParser = new RtfParser();

  ScrolledTextBrowser* textBrowser = new ScrolledTextBrowser;

  QPushButton* prevPage = new QPushButton("prevPage");
  QPushButton* nextPage = new QPushButton("nextPage");

  connect(prevPage, &QPushButton::clicked,
          [=] { textBrowser->emitKeyboardClick(Qt::Key_Left); });
  connect(nextPage, &QPushButton::clicked,
          [=] { textBrowser->emitKeyboardClick(Qt::Key_Right); });

  QLabel* label = new QLabel();

  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Выберите книгу"), "",
      tr("Формат книги (*.fb2, *.txt, *.rtf);;All Files (*)"));
  QString book;

  if (fileName.contains(".fb2")) {
    book = fb2Parser->parseFile(fileName);
  } else if (fileName.contains(".txt")) {
    book = txtParser->parseFile(fileName);
  } else if (fileName.contains(".rtf")) {
    book = rtfParser->parseFile(fileName);
  }
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
