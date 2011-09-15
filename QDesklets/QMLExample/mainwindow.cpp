#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
  setAttribute(Qt::WA_TranslucentBackground);
  setStyleSheet("background:transparent;");
  setWindowFlags(Qt::FramelessWindowHint);

  ui = new QDeclarativeView;
  ui->setSource(QUrl("qrc:/ui.qml"));
  setCentralWidget(ui);
}

MainWindow::~MainWindow()
{
    delete ui;
}
