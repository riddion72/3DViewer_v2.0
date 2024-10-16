#ifndef CPP4_3DVIEWER_V2_1_VIEW_SETTINGS_H_
#define CPP4_3DVIEWER_V2_1_VIEW_SETTINGS_H_

#include <QColorDialog>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

namespace s21 {

/**
 * @class Settings
 * @brief A class representing the settings for the 3D viewer.
 */
class Settings {
 public:
  /// @brief Default constructor
  Settings();

  //  Settings(const Settings &other) = delete;
  //  Settings(Settings &&other) = delete;
  //  Settings &operator=(const Settings &other) = delete;
  //  Settings &operator=(Settings &&other) = delete;
  ~Settings() = default;

  /// @brief Function to save the current settings to a file
  void SaveSettings();

  /// @brief Function to load settings from a file
  void GetSettings();

  QColor line_color;        /**< QColor for line color */
  QColor back_color;        /**< QColor for background color */
  QColor vertex_color;      /**< QColor for vertex color */
  QColor glow_color;        /**< QColor for glow color */
  bool projection_orth;     /**< Flag for orthogonal projection */
  int vertex_type;          /**< Type of vertex representation */
  int line_type;            /**< Type of line representation */
  float line_width = 0.01;  /**< Width of the lines */
  float vertex_size = 0.01; /**< Size of the vertices */
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_1_VIEW_SETTINGS_H_
