#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "gif/gif.h"

MainWindow::MainWindow(s21::Controller *controller, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), controller(controller) {
  ui->setupUi(this);
  setting_config();
  win = glView::getInstance(controller, ui->openGLWidget);
  win->resize(1000, 1000);
  win->setOptions(Options);
  choiceDirectory = QApplication::applicationDirPath();
  fileList = new QFileSystemModel(this);
  fileList->setFilter(QDir::AllEntries | QDir::NoDot);
  ui->listView->setModel(fileList);
  ui->listView->setRootIndex(
      fileList->setRootPath(choiceDirectory.section("/", 0, -4)));

  ui->pushButtonTexture->setEnabled(false);

  set_connect();
  imagesCounter = 0;
  timer = new QTimer();
  //  images = new QImage[50];
  connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerFinish()));
}

MainWindow::~MainWindow() {
  delete fileList;
  delete win;
  delete timer;
  //  delete[] images;
  delete ui;
}

void MainWindow::set_connect() {
  connect(ui->pushButtonColorDot, SIGNAL(clicked()), SLOT(set_color()));
  connect(ui->pushButtonColorLine, SIGNAL(clicked()), SLOT(set_color()));
  connect(ui->pushButtonColorBack, SIGNAL(clicked()), SLOT(set_color()));
  connect(ui->pushButtonColorGlow, SIGNAL(clicked()), SLOT(set_color()));
  connect(ui->radioButtoCentralProection, SIGNAL(clicked()),
          SLOT(proection_changed()));
  connect(ui->radioButtonParallelProection, SIGNAL(clicked()),
          SLOT(proection_changed()));
  connect(ui->radioButtonDotCircle, SIGNAL(clicked()),
          SLOT(dot_type_changed()));
  connect(ui->radioButtonDotSquare, SIGNAL(clicked()),
          SLOT(dot_type_changed()));
  connect(ui->radioButtonDotNothing, SIGNAL(clicked()),
          SLOT(dot_type_changed()));
  connect(ui->radioButtonLineSolid, SIGNAL(clicked()),
          SLOT(line_type_changed()));
  connect(ui->radioButtonLineDotted, SIGNAL(clicked()),
          SLOT(line_type_changed()));
  connect(ui->radioButtonLineNothing, SIGNAL(clicked()),
          SLOT(line_type_changed()));
  connect(ui->radioButtonRotationX, SIGNAL(clicked()),
          SLOT(radio_button_value()));
  connect(ui->radioButtonRotationY, SIGNAL(clicked()),
          SLOT(radio_button_value()));
  connect(ui->radioButtonRotationZ, SIGNAL(clicked()),
          SLOT(radio_button_value()));
  connect(ui->radioButtonMoveX, SIGNAL(clicked()), SLOT(radio_button_value()));
  connect(ui->radioButtonMoveY, SIGNAL(clicked()), SLOT(radio_button_value()));
  connect(ui->radioButtonMoveZ, SIGNAL(clicked()), SLOT(radio_button_value()));
  connect(ui->radioButtonZoomeLine, SIGNAL(clicked()),
          SLOT(radio_button_value()));
  connect(ui->radioButtonZoomeDot, SIGNAL(clicked()),
          SLOT(radio_button_value()));
  connect(ui->radioButtonZoomeModel, SIGNAL(clicked()),
          SLOT(radio_button_value()));
  connect(ui->radioButtonFrame, SIGNAL(clicked()), SLOT(type_model_change()));
  connect(ui->radioButtonSolid, SIGNAL(clicked()), SLOT(type_model_change()));
  connect(ui->pushButton, SIGNAL(clicked()), SLOT(take_path()));
  connect(ui->pushButtonGIF, SIGNAL(clicked()), SLOT(take_GIF()));
  connect(ui->pushButtonJPG, SIGNAL(clicked()), SLOT(take_JPG()));
  connect(ui->pushButtonBMP, SIGNAL(clicked()), SLOT(take_BTR()));
  connect(ui->pushButtonTexture, SIGNAL(clicked()), SLOT(take_texture()));
}

void MainWindow::setting_config() {
  Options.GetSettings();
  if (Options.vertex_type == 0) {
    ui->radioButtonDotCircle->setChecked(1);
  } else if (Options.vertex_type == 1) {
    ui->radioButtonDotSquare->setChecked(1);
  } else if (Options.vertex_type == 2) {
    ui->radioButtonDotNothing->setChecked(1);
  }
  if (Options.line_type == 0) {
    ui->radioButtonLineSolid->setChecked(1);
  } else if (Options.line_type == 1) {
    ui->radioButtonLineDotted->setChecked(1);
  } else if (Options.line_type == 2) {
    ui->radioButtonLineNothing->setChecked(1);
  }
  if (Options.projection_orth) {
    ui->radioButtoCentralProection->setChecked(1);
  } else {
    ui->radioButtonParallelProection->setChecked(1);
  }
  ui->labelColorLine->setStyleSheet(
      QString("background-color: %1").arg(Options.line_color.name()));
  ui->labelColorDot->setStyleSheet(
      QString("background-color: %1").arg(Options.vertex_color.name()));
  ui->labelColorBack->setStyleSheet(
      QString("background-color: %1").arg(Options.back_color.name()));
  ui->labelColorGlow->setStyleSheet(
      QString("background-color: %1").arg(Options.glow_color.name()));
  valueZoomeDot = Options.vertex_size;
  valueZoomeLine = Options.line_width;
}

void MainWindow::proection_changed() {
  if (ui->radioButtonParallelProection->isChecked()) {
    Options.projection_orth = true;
  } else {
    Options.projection_orth = false;
  }
  win->setOptions(Options);
}

void MainWindow::dot_type_changed() {
  if (ui->radioButtonDotCircle->isChecked()) {
    Options.vertex_type = 0;
  } else if (ui->radioButtonDotSquare->isChecked()) {
    Options.vertex_type = 1;
  } else {
    Options.vertex_type = 2;
  }
  win->setOptions(Options);
}

void MainWindow::line_type_changed() {
  if (ui->radioButtonLineSolid->isChecked()) {
    Options.line_type = 0;
  } else if (ui->radioButtonLineDotted->isChecked()) {
    Options.line_type = 1;
  } else if (ui->radioButtonLineNothing->isChecked()) {
    Options.line_type = 2;
  }
  win->setOptions(Options);
}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index) {
  QFileInfo fileInfo = fileList->fileInfo(index);
  if (fileInfo.fileName() == "..") {
    dir = fileInfo.dir();
    dir.cdUp();
    ui->listView->setRootIndex(fileList->index(dir.absolutePath()));
  } else if (fileInfo.fileName() == ".") {
    ui->listView->setRootIndex(fileList->index(""));
  } else if (fileInfo.isDir()) {
    ui->listView->setRootIndex(index);
  } else if (fileInfo.completeSuffix() == "obj") {
    QString filePath = fileInfo.filePath();
    ui->lineEdit->setText(filePath);
    textureChosen = false;
  } else if (fileInfo.completeSuffix() == "bmp") {
    QString texturePath = fileInfo.filePath();
    ui->lineEdit->setText(texturePath);
    textureChosen = true;
  } else {
    ui->statusBar->showMessage("⛔️ INPUT ERROR", 3000);
  }
}

void MainWindow::take_path() {
  ui->pushButton->setEnabled(false);
  if ((textureChosen) && (controller->getFlileStatus())) {
    ui->pushButtonTexture->setEnabled(true);
    //      ui->textureWidget->setStyleSheet(
    //          QString("border-image: url(:%1) 0 0 0 0 stretch
    //          stretch;").arg(ui->lineEdit->text()));
    QImageReader reader(ui->lineEdit->text());
    QImage image = reader.read();
    ui->labelTexture->setPixmap(QPixmap::fromImage(image));
    ui->labelTexture->show();

  } else {
    try {
      controller->parse(ui->lineEdit->text().toStdString(), textureChosen);
      win->translate();
      ui->statusBar->showMessage(
          QString("Количество Вершин: %1      Количество Ребер: %2")
              .arg(controller->getVertexes()->size() / 3)
              .arg(controller->getPolygons()->size() / 2));
    } catch (std::exception const &errorMessage) {
      ui->statusBar->showMessage(
          "ОШИБКА: возможно " + QString::fromStdString(errorMessage.what()),
          3000);
    }
  }
  ui->pushButton->setEnabled(true);
}

void MainWindow::set_color() {
  color = QColorDialog::getColor();
  if (color.isValid()) {
    QObject *obj = (QObject *)(sender());
    if (obj->objectName() == "pushButtonColorDot") {
      ui->labelColorDot->setStyleSheet(
          QString("background-color: %1").arg(color.name()));
      Options.vertex_color = color;
    } else if (obj->objectName() == "pushButtonColorLine") {
      ui->labelColorLine->setStyleSheet(
          QString("background-color: %1").arg(color.name()));
      Options.line_color = color;
    } else if (obj->objectName() == "pushButtonColorBack") {
      ui->labelColorBack->setStyleSheet(
          QString("background-color: %1").arg(color.name()));
      Options.back_color = color;
    } else if (obj->objectName() == "pushButtonColorGlow") {
      ui->labelColorGlow->setStyleSheet(
          QString("background-color: %1").arg(color.name()));
      Options.glow_color = color;
    }
    win->setOptions(Options);
  }
}

void MainWindow::radio_button_value() {
  QObject *obj = (QObject *)(sender());
  valueScrolBar = 50;
  if (obj->objectName() == "radioButtonRotationX") {
    ui->verticalScrollBar->setValue(valueScrolBar);
    win->scrollBar(0, obj->objectName());
  }
  if (obj->objectName() == "radioButtonRotationY") {
    ui->verticalScrollBar->setValue(valueScrolBar);
    win->scrollBar(0, obj->objectName());
  }
  if (obj->objectName() == "radioButtonRotationZ") {
    ui->verticalScrollBar->setValue(valueScrolBar);
    win->scrollBar(0, obj->objectName());
  }
  if (obj->objectName() == "radioButtonMoveX") {
    ui->verticalScrollBar->setValue(valueScrolBar);
    win->scrollBar(0, obj->objectName());
  }
  if (obj->objectName() == "radioButtonMoveY") {
    ui->verticalScrollBar->setValue(valueScrolBar);
    win->scrollBar(0, obj->objectName());
  }
  if (obj->objectName() == "radioButtonMoveZ") {
    ui->verticalScrollBar->setValue(valueScrolBar);
    win->scrollBar(0, obj->objectName());
  }
  if (obj->objectName() == "radioButtonZoomeLine") {
    ui->verticalScrollBar->setValue(Options.line_width * 1000);
  }
  if (obj->objectName() == "radioButtonZoomeDot") {
    ui->verticalScrollBar->setValue(Options.vertex_size * 1000);
  }
  if (obj->objectName() == "radioButtonZoomeModel") {
    ui->verticalScrollBar->setValue(valueScrolBar);
    win->scrollBar(1, obj->objectName());
  }
  win->setOptions(Options);
}

void MainWindow::type_model_change() {
  //  тут нужно что-нибудь написать
}

void MainWindow::take_texture() {}

void MainWindow::on_verticalScrollBar_valueChanged(int value) {
  if (ui->radioButtonRotationX->isChecked()) {
    checkerName = ui->radioButtonRotationX->objectName();
  }
  if (ui->radioButtonRotationY->isChecked()) {
    checkerName = ui->radioButtonRotationY->objectName();
  }
  if (ui->radioButtonRotationZ->isChecked()) {
    checkerName = ui->radioButtonRotationZ->objectName();
  }
  if (ui->radioButtonMoveX->isChecked()) {
    checkerName = ui->radioButtonMoveX->objectName();
  }
  if (ui->radioButtonMoveY->isChecked()) {
    checkerName = ui->radioButtonMoveY->objectName();
  }
  if (ui->radioButtonMoveZ->isChecked()) {
    checkerName = ui->radioButtonMoveZ->objectName();
  }
  if (ui->radioButtonZoomeLine->isChecked()) {
    Options.line_width = value / 1000.0;
    checkerName = ui->radioButtonZoomeLine->objectName();
  }
  if (ui->radioButtonZoomeDot->isChecked()) {
    Options.vertex_size = value / 1000.0;
    checkerName = ui->radioButtonZoomeDot->objectName();
  }
  if (ui->radioButtonZoomeModel->isChecked()) {
    checkerName = ui->radioButtonZoomeModel->objectName();
  }
  int buffer = value;
  value -= valueScrolBar;
  valueScrolBar = buffer;
  win->scrollBar(value, checkerName);
  win->setOptions(Options);
}

void MainWindow::take_GIF() {
  ui->pushButtonGIF->setEnabled(false);
  timer->start(100);
}

void MainWindow::take_JPG() {
  QDateTime curTime = QDateTime::currentDateTime();
  QImage img = win->grabFramebuffer();
  QString formatDate = "hh:mm:ss_dd.MM.yyyy";
  QString dirPath = QDir::home().absolutePath() + "/Desktop/images/";
  if (QDir().exists(dirPath)) {
    img.save(dirPath + curTime.toString(formatDate) + ".jpg");
  } else {
    QDir().mkpath(dirPath);
    img.save(dirPath + curTime.toString(formatDate) + ".jpg");
  }
}

void MainWindow::slotTimerFinish() {
  if (imagesCounter < 50) {
    images.push_back(win->grabFramebuffer());
    imagesCounter++;
    ui->statusBar->showMessage(QString::number(imagesCounter), 100);
  } else {
    timer->stop();
    // QGifImage gif(QSize(640, 480));
    GifWriter gif;
    QString formatDate = "hh:mm:ss_dd.MM.yyyy";
    QDateTime curTime = QDateTime::currentDateTime();
    QString dirPath = QDir::home().absolutePath() + "/Desktop/images/";
    std::string path = dirPath.toStdString() +
                       curTime.toString(formatDate).toStdString() + ".gif";
    if (QDir().exists(dirPath)) {
      // gif.save(dirPath + curTime.toString(formatDate) + ".gif");
    } else {
      QDir().mkpath(dirPath);
      // gif.save(dirPath + curTime.toString(formatDate) + ".gif");
    }
    GifBegin(&gif, path.c_str(), 1000, 1000, 10);
    // gif.setDefaultDelay(100);
    // gif.setDefaultTransparentColor(Qt::yellow);
    for (int i = 0; i < 50; ++i) {
      // gif.addFrame(images[i].scaled(640, 480));
      GifWriteFrame(&gif,
                    images[i]
                        .convertToFormat(QImage::Format_Indexed8)
                        .convertToFormat(QImage::Format_RGBA8888)
                        .constBits(),
                    1000, 1000, 10);
    }
    // QImage img = win->grabFramebuffer();
    imagesCounter = 0;
    ui->pushButtonGIF->setEnabled(true);
    ui->statusBar->showMessage("Finish create gif ", 3000);
  }
}

void MainWindow::take_BTR() {
  QDateTime curTime = QDateTime::currentDateTime();
  QImage img = win->grabFramebuffer();
  QString formatDate = "hh:mm:ss_dd.MM.yyyy";
  QString dirPath = QDir::home().absolutePath() + "/Desktop/images/";
  if (QDir().exists(dirPath)) {
    img.save(dirPath + curTime.toString(formatDate) + ".bmp");
  } else {
    QDir().mkpath(dirPath);
    img.save(dirPath + curTime.toString(formatDate) + ".bmp");
  }
}
