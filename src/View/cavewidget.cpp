#include "../headers/cavewidget.h"

CaveWidget::CaveWidget(QWidget *parent)
    : QWidget{parent} {}

void CaveWidget::paintEvent(QPaintEvent *event) {
    if (caveMatr.getCols()) {
        QPainter pain;
        pain.begin(this);
        QPen pen;
        pen.setWidth(2);
        pain.drawRect(0, 0, caveWidth_, caveHeight_);
        pain.setPen(pen);
        QBrush brush;
        QBrush wbrush;
        brush.setStyle(Qt::SolidPattern);
        wbrush.setStyle(Qt::SolidPattern);
        wbrush.setColor("black");
        brush.setColor("white");
        pain.setBrush(brush);
        for (int i = 0; i < caveMatr.getRows(); ++i) {
            for (int j = 0; j < caveMatr.getCols(); ++j) {
                int cellj = i * cellSize_;
                int celli = j * cellSize_;
                if (!caveMatr(i, j)) {
                    pain.setBrush(brush);
                    pain.drawRect(celli, cellj, celli + cellSize_, cellj + cellSize_);
                } else {
                    pain.setBrush(wbrush);
                    pain.drawRect(celli, cellj, celli + cellSize_, cellj + cellSize_);
                }
            }
        }
        pain.end();
    }
}

void CaveWidget::resizeField_() {
    caveHeight_ = caveMatr.getRows() * cellSize_;
    caveWidth_ = caveMatr.getCols() * cellSize_;
}

int CaveWidget::setCellSize_() {
    cellSize_ = 500 / std::max(caveMatr.getCols(), caveMatr.getRows());
    return cellSize_;
}

void CaveWidget::openCave(const std::string &fileName) {
    s21::FileController::readCaveFromFile(fileName, caveMatr);
    if (caveMatr.getCols()) {
        setCellSize_();
        resizeField_();
        update();
    }
}

void CaveWidget::generateCave(int w, int h, int chance) {
    s21::Cave::initializeCave(caveMatr, h, w, chance);
    setCellSize_();
    resizeField_();
    update();
}

