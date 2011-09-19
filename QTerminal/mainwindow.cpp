#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tabWidget->setUsesScrollButtons(true);

    QIcon::setThemeName("oxygen");
    this->setWindowIcon(QIcon::fromTheme("utilities-terminal"));

    console = new QTermWidget();

    QFont font = QApplication::font();
    font.setFamily("Monospace");
    font.setPointSize(12);

    console->setTerminalFont(font);
    console->setScrollBarPosition(QTermWidget::ScrollBarRight);
    console->setColorScheme("WhiteOnBlack");

    ui->tabWidget->insertTab(ui->tabWidget->currentIndex(), console, QString(QDir::currentPath()));


}

MainWindow::~MainWindow()
{
    delete ui;
}
