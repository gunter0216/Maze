#include "../headers/view.h"
#include "ui_view.h"

View::View(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::View) {
    ui->setupUi(this);
    setSpinBoxesLimit();
}

View::~View() {
    delete ui;
}

void View::paintEvent(QPaintEvent *event) {
    if (ui->tabWidget->currentWidget() == ui->Maze) {
        auto g = geometry();
        g.setWidth(std::max(ui->widget->mazeWidth() + 20, 260));
        setGeometry(g);
    } else {
        auto g = geometry();
        g.setWidth(520);
        setGeometry(g);
        g = ui->widgetCave->geometry();
        g.setWidth(ui->widgetCave->caveWidth() + 2);
        g.setHeight(ui->widgetCave->caveHeight() + 2);
        ui->widgetCave->setGeometry(g);
    }
}

void View::timerEvent(QTimerEvent *event) {
    on_genStep_clicked();
}

void View::on_actionOpen_triggered() {
    QString str = QFileDialog::getOpenFileName();
    if (ui->tabWidget->currentWidget() == ui->Maze) {
        ui->widget->readLabyrinthFromFile(str.toStdString());
    } else {
        ui->widgetCave->openCave(str.toStdString());
    }
    setSpinBoxesLimit();
    setSizeToSpinBoxes();
}

void View::on_actionSave_triggered() {
    QString str;
    str = QFileDialog::getSaveFileName();
    if (ui->tabWidget->currentWidget() == ui->Maze) {
        ui->widget->saveLabyrinth(str.toStdString());
    } else {
        ui->widgetCave->saveCave(str.toStdString());
    }
}

void View::on_pushButton_clicked() {
    if (ui->sbAX == ui->sbBX && ui->sbAY == ui->sbBY) {
        QApplication::beep();
    } else {
        ui->widget->solveMaze(ui->sbAX->value(), ui->sbAY->value(), ui->sbBX->value(), ui->sbBY->value());
    }
}

void View::setSpinBoxesLimit() {
    ui->sbAX->setMaximum(std::max(0, ui->widget->getX() - 1));
    ui->sbBX->setMaximum(std::max(0, ui->widget->getX() - 1));
    ui->sbAY->setMaximum(std::max(0, ui->widget->getY() - 1));
    ui->sbBY->setMaximum(std::max(0, ui->widget->getY() - 1));
}

void View::clearSpinBoxes() {
    ui->sbAX->setValue(0);
    ui->sbBX->setValue(0);
    ui->sbAY->setValue(0);
    ui->sbBY->setValue(0);
}
void View::setSizeToSpinBoxes() {
    ui->sbGenW->setValue(ui->widget->getX());
    ui->sbGenH->setValue(ui->widget->getY());
    ui->sbGenWCave->setValue(ui->widgetCave->getX());
    ui->sbGenHCave->setValue(ui->widgetCave->getY());
}

void View::on_generateButton_clicked() {
    ui->widget->createMaze(ui->sbGenW->value(), ui->sbGenH->value());
    setSpinBoxesLimit();
    clearSpinBoxes();
}

void View::on_genCaveButton_clicked() {
    ui->widgetCave->generateCave(ui->sbGenWCave->value(), ui->sbGenHCave->value(), ui->sbInit->value());
}

void View::on_genStep_clicked() {
    if (!ui->widgetCave->nextStep(ui->sbBLim->value(), ui->sbDLim->value())
        && ui->genStartStop->text() == "Stop") {
        on_genStartStop_clicked();
    }
    ui->widgetCave->update();
}

void View::on_genStartStop_clicked() {
    if (ui->genStartStop->text() == "Start") {
        ui->genStartStop->setText("Stop");
        timer.start(ui->sbDelay->value(), this);
    } else {
        timer.stop();
        ui->genStartStop->setText("Start");
    }
}
