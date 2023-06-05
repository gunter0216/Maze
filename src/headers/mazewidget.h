#ifndef SRC_HEADERS_MAZEWIDGET_H_
#define SRC_HEADERS_MAZEWIDGET_H_

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include "Matrix.h"
#include "FileController.h"
#include "Labyrinth.h"

class MazeWidget : public QWidget {
  Q_OBJECT

 public:
  explicit MazeWidget(QWidget *parent = nullptr);
  ~MazeWidget() {}
  int mazeWidth() { return mazeWidth_; }
  int mazeHeight() { return mazeHeight_; }
  int getX() { return bottomMatr.getCols(); }
  int getY() { return bottomMatr.getRows(); }
  void solveMaze(int x1, int y1, int x2, int y2);
  void drawCoords() { drawCoords_ = !drawCoords_; }
  void readLabyrinthFromFile(const std::string &fileName);
  void saveLabyrinth(const std::string &fileName) {
      s21::FileController::writeLabyrinthToFile(fileName,
                                                rightMatr,
                                                bottomMatr);
  }
  void createMaze(int w, int h);

 protected:
  void paintEvent(QPaintEvent *event);

 private:
  int mazeWidth_ = 500;
  int mazeHeight_ = 500;
  int cellSize_ = 10;
  bool drawCoords_ = false;
  s21::Matrix<bool> bottomMatr;
  s21::Matrix<bool> rightMatr;
  std::forward_list<std::pair<int, int>> path;

  int setCellSize_();
  void resizeField_();
  void drawGreeting_(QPainter *painter);
  void drawSolution_();

  enum XorY { X, Y };
  int findCell_(int click, XorY axis);
};

#endif  // SRC_HEADERS_MAZEWIDGET_H_
