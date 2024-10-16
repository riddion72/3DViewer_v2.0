#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QDir>
#include <QFileSystemModel>
#include <QMainWindow>
#include <QStringList>
#include <QWidget>
#include <QtGui>
#include <QtOpenGLWidgets/QOpenGLWidget>

#include "../controller/controller.h"
// #include "gifimage/qgifimage.h"
// #include "gif/gif.h"
#include "glview.h"
#include "settings.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(s21::Controller *controller, QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_listView_doubleClicked(const QModelIndex &index);
  void take_path();
  void set_color();
  void proection_changed();
  void dot_type_changed();
  void line_type_changed();
  void radio_button_value();
  void type_model_change();
  void take_texture();

  void on_verticalScrollBar_valueChanged(int value);
  void take_GIF();
  void take_JPG();
  void take_BTR();
  void slotTimerFinish();

 private:
  void set_connect();
  void setting_config();
   bool textureChosen = false;
  Ui::MainWindow *ui;
  s21::Controller *controller;
  glView *win;
  QFileSystemModel *fileList;
  QDir dir;
  QString choiceDirectory;
  s21::Settings Options;
  int index = 0;
  int valueScrolBar = 50;
  int valueZoomeLine = 0;
  int valueZoomeDot = 0;
  int valueZoomeModel = 50;
  QColor color;
  QString checkerName;
  std::vector<QImage> images;
  int imagesCounter;
  QTimer *timer;
};
#endif  // MAINWINDOW_H
