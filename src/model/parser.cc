#include "parser.h"

namespace s21 {

void ObjParser::parserVertex(std::string path) {
 fileOpen_ = false;
 std::ifstream file(path);
 all_size_ = 0;
 if (!file.is_open()) {
   throw std::runtime_error("файл не открылся");
 }
 std::string line;
 initMinMaxValue_();
 while (std::getline(file, line)) {
   if (line.substr(0, 2) == "v " || line.substr(0, 2) == "v\t") {
     if (takeV_(line)) {
       file.close();
       throw std::runtime_error("проблемма с координатами точек");
     }
  //  } else if (line.substr(0, 3) == "vt " || line.substr(0, 3) == "vt\t") {
  //    if (takeVT_(line)) {
  //      file.close();
  //      throw std::runtime_error("проблемма с координатами точек");
  //    }
  //  } else if (line.substr(0, 3) == "vn " || line.substr(0, 3) == "vn\t") {
  //    if (takeVN_(line)) {
  //      file.close();
  //      throw std::runtime_error("проблемма с координатами точек");
  //    }
   } else if (line.substr(0, 2) == "f " || line.substr(0, 2) == "f\t") {
     if (takeF_(line)) {
       file.close();
       throw std::runtime_error("проблемма с номерами точек");
     }
   }
 }
 if (vertex_.empty()) {
   throw std::runtime_error("некорректный файл");
 }
//  if (!texture_.empty()) {
//    gluingVector_();
//  }
 file.close();
 centering_();
 float scale = calculateScale_();
 setScale_(scale);
  // for (int i = 0; i < fff.size(); ++i) {
  //   std::cout << std::endl << "i = " << i << std::endl;
  //   for (auto it : fff[i]) {
  //     std::cout << it << " ";
  //   }
  // }
  // std::cout << "\nvertex = " << vertex_.size() << " texture = " << texture_.size() << " normals = " << normals_.size();
//  gluingVector_();
  // for (int i = 0; i < all_.size(); ++i) {
  //   std::cout << all_[i] << std::endl;
  // }
  // std::cout << all_size_;
 fileOpen_ = true;
 return;
}

void ObjParser::gluingVector_() {
  // std::cout << "all = " << all_.size() << " all_size = " << all_size_ << std::endl;
  all_.resize(all_size_);
  int j = -1;
  for (auto it : fff) {
    // all_.resize(all_.size() + it.size());

    for(int i = 0; i < it.size();++i) {
      all_[++j] = vertex_[it[i]];
      all_[++j] = vertex_[it[i] + 1];
      all_[++j] = vertex_[it[i] + 2];

      if (!texture_.empty()) {
        ++i;
        all_[++j] = texture_[it[i]];
        all_[++j] = texture_[it[i] + 1];
      }

      if (!normals_.empty()) {
        ++i;
        all_[++j] = normals_[it[i]];
        all_[++j] = normals_[it[i] + 1];
        all_[++j] = normals_[it[i] + 2];
      }
    }
  }
}

std::vector<float>* ObjParser::getVert() { return &vertex_; }

std::vector<unsigned int>* ObjParser::getSegments() { return &object_; }

void ObjParser::modelDemolisher() {
  vertex_.clear();
  object_.clear();
}

bool ObjParser::checkFileStatus() {
  return fileOpen_;
}

bool ObjParser::takeV_(std::string& line) {
  float x, y, z;
  std::istringstream iss(line);
  char v;
  iss >> v;
  if (iss >> x >> y >> z) {
    vertex_.push_back(x);
    vertex_.push_back(y);
    vertex_.push_back(z);
  } else {
    return 1;
    // file.close();
    // throw std::runtime_error("проблемма с координатами точек");
  }
  findingMinMax_(x, y, z);
  return 0;
}

bool ObjParser::takeVT_(std::string& line) {
  float x, y;
  std::istringstream iss(line);
  char v;
  iss >> v;
  iss >> v;
  if (iss >> x >> y) {
    texture_.push_back(x);
    texture_.push_back(y);
  } else {
    return 1;
  }
  return 0;
}

bool ObjParser::takeVN_(std::string& line) {
  float x, y, z;
  std::istringstream iss(line);
  char v;
  iss >> v;
  iss >> v;
  if (iss >> x >> y >> z) {
    normals_.push_back(x);
    normals_.push_back(y);
    normals_.push_back(z);
  } else {
    return 1;
    // file.close();
    // throw std::runtime_error("проблемма с координатами точек");
  }
  findingMinMax_(x, y, z);
  return 0;
}

// bool ObjParser::takeF_(std::string& line) {
//   // int res = 0;
//   // size_t i = 0;
//   std::vector<int> pol;
//   line.replace(0, 2, "");
//   std::istringstream iss(line);
//   char f;
//   // fff.push_back();
//   while (iss >> f) {
//     if (std::isdigit(f) || f == '-') {  //????
//       int num;
//       iss.unget();
//       if (iss >> num) {
//         // std::cout << "do " << num << std::endl;
//         // if (checkObj(num)) return 1;
//         num--;
//         if (num == -1) return 1;
//         if (num >= 0) {
//           if ((int)(vertex_.size() / 3) < num) return 1;
//         } else {
//           num -= -(vertex_.size() / 3) - 1;
//           if (num < 0 || (int)(vertex_.size() / 3) < num) return 1;
//         }
//         // std::cout << "posle " << num << std::endl;
//         // fff.back().push_back(num);
//         pol.push_back(num);
//       }
//     }
//     // else { // ?????????????????????
//     //   iss.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
//     // }
//     iss >> f;
//     if (f == ' ') continue;
//     if (f == '/') {
//       iss >> f;
//       if (f != '/' && std::isdigit(f) || f == '-') {
//         int num;
//         iss.unget();
//         if (iss >> num) {
//           num--;
//           if (num == -1) return 1;
//           if (num >= 0) {
//             if ((int)(texture_.size() / 2) < num) return 1;
//           } else {
//             num -= -(texture_.size() / 2) - 1;
//             if (num < 0 || (int)(texture_.size() / 2) < num) return 1;
//           }
//           // if (checkObj(num)) return 1;
//           // fff.back().push_back(num);
//           pol.push_back(num);
//           iss >> f;
//         }
//       } 
//       // else { iss >> f; }
//       // else if (f == '/') {
//       //   iss >> f;
//       //   if (std::isdigit(f) || f == '-') {
//       //     int num;
//       //     iss.unget();
//       //     if (iss >> num) {
//       //       num--;
//       //       if (num == -1) return 1;
//       //       if (num >= 0) {
//       //         if ((int)(normals_.size() / 3) < num) return 1;
//       //       } else {
//       //         num -= -(normals_.size() / 3) - 1;
//       //         if (num < 0 || (int)(normals_.size() / 3) < num) return 1;
//       //       }
//       //       // if (checkObj(num)) return 1;
//       //       // fff.back().push_back(num);
//       //       pol.push_back(num);
//       //     }
//       //   }
//       // }
//     }
//     if (f == ' ') continue;
//     if (f == '/') {
//       iss >> f;
//     if (f != '/' && std::isdigit(f) || f == '-') {
//         int num;
//         iss.unget();
//         if (iss >> num) {
//           num--;
//           if (num == -1) return 1;
//           if (num >= 0) {
//             if ((int)(normals_.size() / 3) < num) return 1;
//           } else {
//             num -= -(normals_.size() / 3) - 1;
//             if (num < 0 || (int)(normals_.size() / 3) < num) return 1;
//           }
//           // if (checkObj(num)) return 1;
//           // fff.back().push_back(num);
//           pol.push_back(num);
//         }
//       }
//     }
//     // iss >> f;
//     // if (f != '/') {
//     //   iss >> f;
//     //   if (f != '/' && std::isdigit(f) || f == '-') {
//     //     int num;
//     //     iss.unget();
//     //     if (iss >> num) {
//     //       // if (checkObj(num)) return 1;
//     //       num--;
//     //       if (num == -1) return 1;
//     //       if (num >= 0) {
//     //         if ((int)(normals_.size() / 3) < num) return 1;
//     //       } else {
//     //         num -= -(normals_.size() / 3) - 1;
//     //         if (num < 0 || (int)(normals_.size() / 3) < num) return 1;
//     //       }
//     //       // fff.back().push_back(num);
//     //       pol.push_back(num);
//     //     }
//     //   }
//     // }
//   }
//   if (!pol.empty()) {
//     fff.push_back(pol);
//     // std::cout << pol.size() << std::endl;
//     all_size_+=pol.size();
//   }
//   // if (i != 1) {
//   //   pol.push_back(pol[0]);
//   // }
//   // for (long unsigned int j = 0; j < pol.size(); j++) {
//   //   object_.push_back(pol[j]);
//   // }
//   return 0;
// }
bool ObjParser::takeF_(std::string& line) {
  // int res = 0;
  size_t i = 0;
  std::vector<unsigned int> pol;
  std::istringstream iss(line);
  char f;
  while ((iss >> f)) {
    if (std::isdigit(f) || f == '-') {
      int number;
      iss.unget();
      if (iss >> number) {
        number--;
        if (number == -1) {
          // res = 4;
          return 1;
        }
        if (number >= 0) {
          if ((int)(vertex_.size() / 3) < number) return 1;
          // res = (int)(vertex_.size() / 3) < number ? 1 : res;
          duplicateFunction_(i, pol, number);
        } else {
          number -= -(vertex_.size() / 3) - 1;
          if (number < 0 || (int)(vertex_.size() / 3) < number) {
            // res = 3;
            return 1;
          }
          // res = (int)(vertex_.size() / 3) < number ? 1 : res;
          duplicateFunction_(i, pol, number);
        }
      }
    } else {
      iss.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    }
  }
  if (i != 1) {
    pol.push_back(pol[0]);
  }
  for (long unsigned int j = 0; j < pol.size(); j++) {
    object_.push_back(pol[j]);
  }
  return 0;
}

void ObjParser::duplicateFunction_(size_t& i, std::vector<unsigned int>& victor,
                                   float num) {
  victor.push_back(num);
  if (i) {
    victor.push_back(num);
    ++i;
  }
  ++i;
}

bool ObjParser::checkObj_(int& num) {
  num--;
  if (num == -1) return 1;
  if (num >= 0) {
    if ((int)(vertex_.size() / 3) < num) return 1;
  } else {
    num -= -(vertex_.size() / 3) - 1;
    if (num < 0 || (int)(vertex_.size() / 3) < num) return 1;
  }
  return 0;
}

void ObjParser::findingMinMax_(float x, float y, float z) {
  scope_.minX = fmin(scope_.minX, x);
  scope_.minY = fmin(scope_.minY, y);
  scope_.minZ = fmin(scope_.minZ, z);
  scope_.maxX = fmax(scope_.maxX, x);
  scope_.maxY = fmax(scope_.maxY, y);
  scope_.maxZ = fmax(scope_.maxZ, z);
}

void ObjParser::centering_() {
  float centerX = scope_.minX + (scope_.maxX - scope_.minX) / 2;
  float centerY = scope_.minY + (scope_.maxY - scope_.minY) / 2;
  float centerZ = scope_.minZ + (scope_.maxZ - scope_.minZ) / 2;
  for (long unsigned int i = 0; i < vertex_.size(); ++i) {
    switch (i % 3) {
      case 0:
        vertex_[i] -= centerX;
        break;
      case 1:
        vertex_[i] -= centerY;
        break;
      case 2:
        vertex_[i] -= centerZ;
        break;
    }
  }
}

float ObjParser::calculateScale_() {
  float x = scope_.maxX - scope_.minX;
  float y = scope_.maxY - scope_.minY;
  float z = scope_.maxZ - scope_.minZ;
  float max = fmax(fmax(x, y), z);
  return (START_VALUE_SCALE) / max;
}

void ObjParser::setScale_(float scale) {
  for (long unsigned int i = 0; i < vertex_.size(); ++i) vertex_[i] *= scale;
}

void ObjParser::initMinMaxValue_() {
  scope_.minX = DBL_MAX;
  scope_.minY = DBL_MAX;
  scope_.minZ = DBL_MAX;
  scope_.maxX = -DBL_MAX;
  scope_.maxY = -DBL_MAX;
  scope_.maxZ = -DBL_MAX;
}

}  // namespace s21

// int main() {
//   s21::ObjParser objeckt;
//   std::string path = "./cube.obj";
//   objeckt.parserVertex(path);
//   return 0;
// }
