#include "transform.h"

namespace s21 {

void Transform::Move(QVector3D rotate, QVector3D translate, float zoom) {
  matrix_.setToIdentity();
  Translation_(translate.x(), translate.y(), translate.z());
  Scaling_(zoom);
  Rotation_(rotate.x(), rotate.y(), rotate.z());
}

QMatrix4x4 Transform::Getter() { return matrix_; }

void Transform::Translation_(float x, float y, float z) {
  matrix_.translate(x, y, -2.0 + z);
}

void Transform::Rotation_(float x, float y, float z) {
  matrix_.rotate(x, 0.0, 1.0, 0.0f);
  matrix_.rotate(y, 1.0, 0.0, 0.0f);
  matrix_.rotate(z, 0.0, 0.0, 1.0f);
}

void Transform::Scaling_(float zoom) { matrix_.scale(zoom); }

}  // namespace s21
