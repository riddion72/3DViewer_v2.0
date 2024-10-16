#ifndef CPP4_3DVIEWER_V2_1_CONTROLLER_GLVIEW_H_
#define CPP4_3DVIEWER_V2_1_CONTROLLER_GLVIEW_H_

#define GL_SILENCE_DEPRECATION  // Ignore OpenGL deprecation warnings

#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QVector>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <iostream>

#include "../controller/controller.h"
#include "../observer/observer.h"
#include "settings.h"

class glView : public QOpenGLWidget,
               public QOpenGLFunctions,
               public s21::Observer {
  Q_OBJECT

 public:
  /**
   * @brief Get a singleton instance of the glView class.
   * @param c Pointer to the controller instance.
   * @param parent QWidget parent.
   * @return Pointer to the glView instance.
   */
  static glView *getInstance(s21::Controller *c, QWidget *parent);

  /// @brief Destructor
  ~glView();

  /**
   * @brief Function to handle scrollbar events.
   * @param Value of the scrollbar.
   * @param QString representing the type of scrollbar.
   */
  void scrollBar(int, QString);

  /**
   * @brief Virtual function to set options based on the provided settings.
   * @param options The Settings object containing configuration options.
   */
  virtual void setOptions(s21::Settings options) override {
    settings.back_color = options.back_color;
    settings.vertex_color = options.vertex_color;
    settings.line_color = options.line_color;
    settings.glow_color = options.glow_color;
    settings.projection_orth = options.projection_orth;
    settings.line_width = options.line_width;
    settings.vertex_size = options.vertex_size;
    settings.vertex_type = options.vertex_type;
    settings.line_type = options.line_type;
    options.SaveSettings();
    update();
  };

  /**
   * @brief Function to translate and display the 3D model.
   * @param vertex Vector containing vertex coordinates.
   * @param object Vector containing object segments.
   */
  void translate();

  // bool openChecker();

 private slots:

 protected:
  /// @brief Function to initialize OpenGL context.
  void initializeGL() override;

  /// @brief Function to handle resizing of the OpenGL widget.
  void resizeGL(int, int) override;

  /// @brief Function to handle painting (drawing) on the OpenGL widget.
  void paintGL() override;

  /// @brief Function to handle mouse press events.
  void mousePressEvent(QMouseEvent *) override;

  /// @brief Function to handle mouse move events.
  void mouseMoveEvent(QMouseEvent *) override;

  /// @brief Function to handle wheel (scroll) events.
  void wheelEvent(QWheelEvent *event) override;

  /// @brief Function to initialize drawing settings.
  void initDraw();

 private:
  /// @brief Helper function to reset internal variables.
  void zeroing();

  /// @brief Constructor
  glView(s21::Controller *c, QWidget *parent = nullptr);

  static glView *instance; /**< Pointer to the singleton instance of glView */
  s21::Controller *controller; /**< Pointer to the controller instance */
  s21::Settings settings;
  QMatrix4x4 projection_m; /**< QMatrix4x4 for projection */
  QOpenGLShaderProgram
      m_program; /**< QOpenGLShaderProgram for OpenGL shaders */
  QOpenGLVertexArrayObject
      m_vao;                   /**< QOpenGLVertexArrayObject for vertex array */
  QOpenGLBuffer m_arrayBuffer; /**< QOpenGLBuffer for vertex data */
  QOpenGLBuffer m_indexBuffer; /**< QOpenGLBuffer for index data */
  QVector2D m_mousePosition;   /**< QVector2D for mouse position */
  QVector3D m_rotation;        /**< QVector3D for rotation angles */
  QVector3D m_translation;     /**< QVector3D for translation */
  QVector<float> pointsGL = { 1.0/4, -1.0/4, -1.0/4, 1.0/4, -1.0/4, 1.0/4, -1.0/4, -1.0/4, 1.0/4, -1.0/4, -1.0/4, -1.0/4, 1.0/4, 1.0/4, -1.0/4, 1.0/4, 1.0/4, 1.0/4, -1.0/4, 1.0/4, 1.0/4, -1.0/4, 1.0/4, -1.0/4, }; /**< QVector<float> for vertex coordinates */
  QVector<unsigned int> modelGL = { 2, 3, 4, 8, 7, 6, 5, 6, 2, 6, 7, 3, 3, 7, 8, 1, 4, 8, 1, 2, 4, 5, 8, 6, 1, 5, 2, 2, 6, 3, 4, 3, 8, 5, 1, 8};                  /**< QVector<unsigned int> for object segments */
  float scale;             /**< Scaling factor */
  // bool open_file_flag = 0; /**< Flag to indicate if a file is open */
};

#endif  // CPP4_3DVIEWER_V2_1_CONTROLLER_GLVIEW_H_
