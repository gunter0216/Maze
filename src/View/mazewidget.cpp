#include "../headers/mazewidget.h"
#include <QList>

MazeWidget::MazeWidget(QWidget *parent)
    : QWidget{parent} {}

void MazeWidget::solveMaze(int x1, int y1, int x2, int y2) {
    path.clear();
    if (rightMatr.getCols() && rightMatr.getRows())
        s21::Labyrinth::findingAWay(path, rightMatr, bottomMatr, x1, y1, x2, y2);
    update();
}

void MazeWidget::readLabyrinthFromFile(const std::string &fileName) {
    s21::FileController::readLabyrinthFromFile(fileName, rightMatr, bottomMatr);
    path.clear();
}

void MazeWidget::createMaze(int w, int h) {
    s21::Labyrinth::createLabyrinth(rightMatr, bottomMatr, w, h);
    path.clear();
    update();
}

void MazeWidget::paintEvent(QPaintEvent *event) {
    QPainter painter;
    painter.begin(this);
    QPen pen;
    pen.setWidth(2);
    painter.setPen(pen);
    if (rightMatr.getCols() == 0) {
        drawGreeting_(&painter);
    } else {
        setCellSize_();
        resizeField_();
        painter.drawRect(0, 0, mazeWidth_, mazeHeight_);
        for (int y = 0; y < rightMatr.getRows(); ++y)
            for (int x = 0; x < rightMatr.getCols(); ++x) {
                int cellX = x * cellSize_;
                int cellY = y * cellSize_;
                if (rightMatr(y, x))
                    painter.drawLine(cellX + cellSize_, cellY, cellX + cellSize_, cellY + cellSize_);
                if (bottomMatr(y, x))
                    painter.drawLine(cellX, cellY + cellSize_, cellX + cellSize_, cellY + cellSize_);
                if (drawCoords_)
                    painter.drawText(cellX + (cellSize_ >> 1),
                                     cellY + (cellSize_ >> 1),
                                     "x:" + QString::number(x) + " y:" + QString::number(y));
            }
        if (!path.empty())
            drawSolution_();
    }
    painter.end();
}


int MazeWidget::setCellSize_() {
    cellSize_ = 500 / std::max(rightMatr.getCols(), rightMatr.getRows());
    return cellSize_;
}

void MazeWidget::resizeField_() {
    mazeHeight_ = rightMatr.getRows() * cellSize_;
    mazeWidth_ = rightMatr.getCols() * cellSize_;
}

void MazeWidget::drawGreeting_(QPainter *painter) {
    painter->drawRect(0, 0, 500, 500);
    auto tmpPen = painter->pen();
    painter->setFont(QFont("OldEnglish", 180, QFont::Bold));
    painter->drawText(2, 250, "MAZE");
    painter->setPen(tmpPen);
}

void MazeWidget::drawSolution_() {
    QPainter pain;
    pain.begin(this);
    pain.setPen(QColor("red"));
    QPainterPath pth;
    pth.moveTo(path.front().second * cellSize_ + (cellSize_ >> 1),
               path.front().first * cellSize_ + (cellSize_ >> 1));
    for (auto i : path) {
        pth.lineTo(i.second * cellSize_ + (cellSize_ >> 1), i.first * cellSize_ + (cellSize_ >> 1));
    }
    pain.drawPath(pth);
    pth.clear();
    pain.end();
}

int MazeWidget::findCell_(int click, XorY axis) {
    int len = mazeHeight_;
    int cells = bottomMatr.getCols();
    if (axis == X) {
        len = mazeWidth_;
        cells = bottomMatr.getRows();
    }
    if (len < click)
        throw std::out_of_range("");
    int guess = cells >> 1;
    int guessCoord = guess * cellSize_;
    while (!(guessCoord < click && click < guessCoord + cellSize_)) {
        if (click <= guessCoord) {
            guess >>= 1;
        } else {
            guess += ((cells - guess) >> 1);
        }
        guessCoord = guess * cellSize_;
    }
    return guess;
}
