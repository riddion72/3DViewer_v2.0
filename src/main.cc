#include <QApplication>

#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
  QSurfaceFormat window_surface = QSurfaceFormat::defaultFormat();
  window_surface.setMajorVersion(4);
  window_surface.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(window_surface);
  QApplication a(argc, argv);
  s21::ObjParser model;
  s21::Transform afines;
  s21::Facade facade(&model, &afines);
  s21::Controller controller(&facade);
  s21::Controller *ptr = &controller;
  MainWindow w(ptr); //s21::controller *Controller, QWidget *parent = nullptr);
  w.setFixedSize(1310, 1050);
  w.setWindowTitle("3DViewer v2");
  w.show();
  return a.exec();
}
