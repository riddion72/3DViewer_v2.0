#ifndef CPP4_3DVIEWER_V2_1_MODEL_TEXTURE_H_
#define CPP4_3DVIEWER_V2_1_MODEL_TEXTURE_H_

#include <QImage>
#include <QOpenGLTexture>
#include <QString>

namespace s21 {

class TextureKeeper {
  public:
    TextureKeeper(){};

    ~TextureKeeper(){};
    
    void tryTakeTexture(std::string path);

    void freeTexture();

    QImage getTexture() {return texture_;}

  private:

  QImage texture_;
  bool textureAvailable = false;


};
}  //  namespace s21

#endif  // CPP4_3DVIEWER_V2_1_MODEL_TEXTURE_H_
