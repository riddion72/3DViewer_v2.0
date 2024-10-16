#include "settings.h"

namespace s21 {

Settings::Settings() {
  vertex_type = 1;
  line_type = 1;
  projection_orth = false;
  line_color.setRgbF(1.0f, 1.0f, 1.0f, 1.0f);
  back_color.setRgbF(0.0f, 0.0f, 0.0f, 1.0f);
  vertex_color.setRgbF(1.0f, 0.0f, 1.0f, 1.0f);
  glow_color.setRgbF(1.0f, 1.0f, 1.0f, 1.0f);
  GetSettings();
}

void Settings::SaveSettings() {
  QJsonObject options;
  options["line_color_r"] = line_color.red();
  options["line_color_g"] = line_color.green();
  options["line_color_b"] = line_color.blue();
  options["line_color_a"] = line_color.alpha();
  options["back_color_r"] = back_color.red();
  options["back_color_g"] = back_color.green();
  options["back_color_b"] = back_color.blue();
  options["back_color_a"] = back_color.alpha();
  options["vertex_color_r"] = vertex_color.red();
  options["vertex_color_g"] = vertex_color.green();
  options["vertex_color_b"] = vertex_color.blue();
  options["vertex_color_a"] = vertex_color.alpha();
  options["glow_color_r"] = glow_color.red();
  options["glow_color_g"] = glow_color.green();
  options["glow_color_b"] = glow_color.blue();
  options["glow_color_a"] = glow_color.alpha();
  options["projection_orth"] = projection_orth;
  options["vertex_type"] = vertex_type;
  options["line_type"] = line_type;
  options["line_width"] = line_width;
  options["vertex_size"] = vertex_size;

  QJsonDocument doc(options);
  QFile file(static_cast<QDir>(QDir::homePath()).absolutePath() +
             "/Desktop/options.json");
  if (file.open(QIODevice::WriteOnly)) {
    file.write(doc.toJson());
    file.close();
  }
}

void Settings::GetSettings() {
  QFile file(static_cast<QDir>(QDir::homePath()).absolutePath() +
             "/Desktop/options.json");

  if (file.open(QIODevice::ReadOnly)) {
    QJsonDocument jsonchik = QJsonDocument::fromJson(file.readAll());
    QJsonObject options = jsonchik.object();

    line_color.setRed(options.value("line_color_r").toInt());
    line_color.setGreen(options.value("line_color_g").toInt());
    line_color.setBlue(options.value("line_color_b").toInt());
    line_color.setAlpha(options.value("line_color_a").toInt());
    back_color.setRed(options.value("back_color_r").toInt());
    back_color.setGreen(options.value("back_color_g").toInt());
    back_color.setBlue(options.value("back_color_b").toInt());
    back_color.setAlpha(options.value("back_color_a").toInt());
    vertex_color.setRed(options.value("vertex_color_r").toInt());
    vertex_color.setGreen(options.value("vertex_color_g").toInt());
    vertex_color.setBlue(options.value("vertex_color_b").toInt());
    vertex_color.setAlpha(options.value("vertex_color_a").toInt());
    glow_color.setRed(options.value("glow_color_r").toInt());
    glow_color.setGreen(options.value("glow_color_g").toInt());
    glow_color.setBlue(options.value("glow_color_b").toInt());
    glow_color.setAlpha(options.value("glow_color_a").toInt());
    projection_orth = options.value("projection_orth").toBool();
    vertex_type = options.value("vertex_type").toInt();
    line_type = options.value("line_type").toInt();
    line_width = options.value("line_width").toDouble();
    vertex_size = options.value("vertex_size").toDouble();

    file.close();
  }
}

}  // namespace s21
