#ifndef CPP4_3DVIEWER_V2_1_MODEL_TRANSFORM_H_
#define CPP4_3DVIEWER_V2_1_MODEL_TRANSFORM_H_

#include <QMatrix4x4>

namespace s21 {

/**
 * @class Transform
 * @brief A class representing transformations applied to a 3D model using a 4x4
 * matrix.
 */
class Transform {
 public:
  /// @brief Default constructor
  Transform() = default;
  /// @brief Default destructor
  ~Transform() = default;
  /// @brief Function to perform translation, rotation, and scaling
  /// transformations
  /// @param rotate A QVector3D representing rotation angles in degrees around
  /// the x, y, and z axes
  /// @param translate A QVector3D representing translation along the x, y, and
  /// z axes
  /// @param zoom A float representing scaling (zoom) factor
  void Move(QVector3D rotate, QVector3D translate, float zoom);
  /// @brief Getter function to retrieve the transformation matrix
  /// @return QMatrix4x4 representing the transformation matrix
  QMatrix4x4 Getter();

 private:
  /// @brief Helper function to apply translation to the transformation matrix
  /// @param x Translation along the x-axis
  /// @param y Translation along the y-axis
  /// @param z Translation along the z-axis
  void Translation_(float x, float y, float z);
  /// @brief Helper function to apply rotation to the transformation matrix
  /// @param x Rotation angle around the x-axis in degrees
  /// @param y Rotation angle around the y-axis in degrees
  /// @param z Rotation angle around the z-axis in degrees
  void Rotation_(float x, float y, float z);
  /// @brief Helper function to apply scaling to the transformation matrix
  /// @param zoom Scaling factor
  void Scaling_(float zoom);

  QMatrix4x4 matrix_; /**< QMatrix4x4 to store the transformation matrix */
};
}  // namespace s21
#endif  // CPP4_3DVIEWER_V2_1_MODEL_TRANSFORM_H_
