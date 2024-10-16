#ifndef CPP4_3DVIEWER_V2_1_MODEL_PARSER_H_
#define CPP4_3DVIEWER_V2_1_MODEL_PARSER_H_

#include <cfloat>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#define START_VALUE_SCALE 0.50 /**< The starting value for scaling. */

namespace s21 {

/**
 * @struct vertex_scope
 * @brief Represents the scope of a vertex with its minimum and maximum
 * coordinate values.
 */
typedef struct vertex_scope {
  float minZ; /**< Minimum Z-coordinate value. */
  float maxZ; /**< Maximum Z-coordinate value. */
  float minY; /**< Minimum Y-coordinate value. */
  float maxY; /**< Maximum Y-coordinate value. */
  float minX; /**< Minimum X-coordinate value. */
  float maxX; /**< Maximum X-coordinate value. */
} vertex_scope;

/**
 * @class ObjParser
 * @brief A class for parsing .obj files and extracting vertex information.
 */
class ObjParser {
 public:
  /// @brief Default constructor
  ObjParser(){};

  /// @brief Default destructor
  ~ObjParser(){};

  /// @brief Main function that parses lines from a .obj file
  /// @param path The name of the .obj file to be parsed
  void parserVertex(std::string path);

  /// @brief Vertex point getter
  /// @return Vector containing vertex coordinates
  std::vector<float>* getVert();

  /// @brief Getter for object segments
  /// @return Vector containing object segments
  std::vector<unsigned int>* getSegments();

  /// @brief Function to reset the internal state of the object
  void modelDemolisher();

  bool checkFileStatus();

 private:
  /// @brief Helper function to process 'f' lines in the .obj file
  /// @param line The line to be processed
  /// @return Integer representing the result of processing
  bool takeF_(std::string& line);
  bool takeV_(std::string& line);
  bool takeVT_(std::string& line);
  bool takeVN_(std::string& line);

  /// @brief Helper function to duplicate vertex values in the internal vector
  /// @param i Pointer to the current index in the vector
  /// @param victor Pointer to the vector containing vertex values
  /// @param num The value to be duplicated
  void duplicateFunction_(size_t& i, std::vector<unsigned int>& victor,
                          float num);

  /// @brief Helper function to find the minimum and maximum coordinate values
  /// @param x X-coordinate value
  /// @param y Y-coordinate value
  /// @param z Z-coordinate value
  void findingMinMax_(float x, float y, float z);

  /// @brief Helper function to center the object by adjusting the vertex
  /// coordinates
  void centering_();

  /// @brief Helper function to calculate the scaling factor based on the
  /// coordinate scope
  /// @return Calculated scaling factor
  float calculateScale_();

  /// @brief Helper function to set the scaling factor for the vertex
  /// coordinates
  /// @param scale The scaling factor to be applied
  void setScale_(float scale);

  /// @brief Helper function to initialize the minimum and maximum coordinate
  /// values
  void initMinMaxValue_();

  void gluingVector_();
  bool checkObj_(int& num);
  // Private member variables
  std::vector<float> vertex_; /**< Vector to store vertex coordinates */
  std::vector<float> texture_;
  std::vector<float> normals_;
  std::vector<unsigned int> object_; /**< Vector to store object segments */
  vertex_scope scope_;               /**< Structure to store coordinate scope */
  std::vector<std::vector<int> > fff;
  std::vector<float> all_;
  size_t all_size_;
  bool fileOpen_ = false;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_1_MODEL_PARSER_H_
