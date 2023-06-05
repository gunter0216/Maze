#ifndef SRC_HEADERS_CAVEWIDGET_H_
#define SRC_HEADERS_CAVEWIDGET_H_

#include <QWidget>
#include <QPainter>
#include <headers/Matrix.h>
#include <headers/FileController.h>
#include <headers/Cave.h>

class CaveWidget : public QWidget {
  Q_OBJECT

 public:
  explicit CaveWidget(QWidget *parent = nullptr);
  ~CaveWidget() {}
  int caveWidth() { return caveWidth_; }
  int caveHeight() { return caveHeight_; }
  int getX() { return caveMatr.getCols(); }
  int getY() { return caveMatr.getRows(); }
  void setDelay(int millis);
  int getDelay() { return delayMSec_; }
  void startGenerate();
  void startGenerate(int delay);
  void openCave(const std::string &fileName);
  void saveCave(const std::string &fileName) { s21::FileController::writeCaveToFile(fileName, caveMatr); }
  void generateCave(int w, int h, int chance);
  bool nextStep(int birth, int death) {
      return s21::Cave::nextStep(caveMatr,
                                 helpMatr,
                                 birth + 1,
                                 death + 1,
                                 false);
  }

 protected:
  void paintEvent(QPaintEvent *event);

 private:
  s21::Matrix<bool> caveMatr, helpMatr;
  int caveWidth_ = 500;
  int caveHeight_ = 500;
  int cellSize_ = 10;
  int delayMSec_ = 20;

  int setCellSize_();
  void resizeField_();
};

#endif  // SRC_HEADERS_CAVEWIDGET_H_
