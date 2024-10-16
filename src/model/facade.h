#ifndef CPP4_3DVIEWER_V2_1_MODEL_FACADE_H_
#define CPP4_3DVIEWER_V2_1_MODEL_FACADE_H_

#include "parser.h"
#include "transform.h"
#include "texture.h"

namespace s21 {

class Facade {
 public:
  /// @brief Constructor
  /// @param m Pointer to the ObjParser instance for handling model parsing
  /// @param a Pointer to the Transform instance for handling transformations
  Facade(ObjParser *m, Transform *a) : object_(m), afines_(a){};

  /// @brief Function to parse a .obj file
  /// @param path_to_file The path to the .obj file to be parsed
  void parse(std::string path_to_file, bool file_type) {
    // texture_->freeTexture();
    if (!file_type) {
      object_->modelDemolisher();
      object_->parserVertex(path_to_file);
    // } else if(object_->checkFileStatus()) {
    //   texture_->tryTakeTexture(path_to_file);
    }
  }

  /// @brief Getter function to retrieve vertex coordinates from the model
  /// @return Vector containing vertex coordinates
  std::vector<float> *getVertex() { return object_->getVert(); }

  /// @brief Getter function to retrieve polygon information from the model
  /// @return Vector containing polygon indices
  std::vector<unsigned int> *getPolygon() { return object_->getSegments(); }

  /// @brief Function to perform transformation on the model
  /// @param rotate A QVector3D representing rotation angles in degrees around
  /// the x, y, and z axes
  /// @param translate A QVector3D representing translation along the x, y, and
  /// z axes
  /// @param zoom A float representing scaling (zoom) factor
  void Move(QVector3D rotate, QVector3D translate, float zoom) {
    afines_->Move(rotate, translate, zoom);
  }

  /// @brief Getter function to retrieve the transformation matrix from the
  /// Transform instance
  /// @return QMatrix4x4 representing the transformation matrix
  QMatrix4x4 GetTransformationMatrix() { return afines_->Getter(); }

  bool flileStatus() {return object_->checkFileStatus(); }

 private:
  ObjParser *object_; /**< Pointer to the ObjParser instance for handling model
                         parsing */
  Transform *afines_; /**< Pointer to the Transform instance for handling
                          transformations */
//  TextureKeeper *texture_;
};
}  //  namespace s21

#endif  // CPP4_3DVIEWER_V2_1_MODEL_FACADE_H_
