#ifndef SRC_HEADERS_VIEW_H_
#define SRC_HEADERS_VIEW_H_

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QBasicTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE

class View : public QMainWindow {
  Q_OBJECT

 public:
  explicit View(QWidget *parent = nullptr);
  ~View();

 private:
  Ui::View *ui;
  QBasicTimer timer;
  void setSpinBoxesLimit();
  void setSizeToSpinBoxes();
  void clearSpinBoxes();

 protected:
  void paintEvent(QPaintEvent *event);
  void timerEvent(QTimerEvent *event);

 private slots:
      void on_actionOpen_triggered();
  void on_pushButton_clicked();
  void on_generateButton_clicked();
  void on_actionSave_triggered();
  void on_genCaveButton_clicked();
  void on_genStep_clicked();

  void on_genStartStop_clicked();
};
#endif  // SRC_HEADERS_VIEW_H_
