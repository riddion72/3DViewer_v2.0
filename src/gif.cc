#include <vector>
#include <cstdint>
#include "view/gif/gif.h"
#include "model/parser.h"

int main()
{
	// int width = 100;
	// int height = 200;
	// std::vector<uint8_t> black(width * height * 4, 0);
	// std::vector<uint8_t> white(width * height * 4, 255);

	// auto fileName = "bwgif.gif";
	// int delay = 10;
	// GifWriter g;
	// GifBegin(&g, fileName, width, height, delay);
	// GifWriteFrame(&g, black.data(), width, height, delay);
	// GifWriteFrame(&g, white.data(), width, height, delay);
	// GifEnd(&g);

  // s21::ObjParser object;
	// float x, y, z, u;
	// char v;
	// std::string str = "f 2/1/1 3/2/1 4/3/1";
	// str.replace(0,1,"");
	// str.replace(0,1,"");
	// // while(!str.empty()) {
	// // str.replace(0,1,"");
	// std::cout << str << std::endl;
	// // }
	// std::istringstream iss(str);
	// // iss >> v;
	// iss >> x >> v >> y >> v >> z >> v >> v >> u;
	// std::cout << "x = " << x << " y = " << y << " z = " << z << " u = " << u << std::endl;
	// std::cout << std::stod(str) << std::endl;
	// std::cout << str << std::endl;

  s21::ObjParser object;
  // std::string path = "/Users/jigsawda/CPP5_3DViewer_v2.1-1/src/test_object/test.obj";
  // std::string path = "/Users/jigsawda/CPP5_3DViewer_v2.1-1/src/test_object/test.obj";
  std::string path = "/Users/alloha/Documents/School21/CPP/CPP5_3DViewer_v2.1-1/src/test_object/test.obj";
  object.parserVertex(path);
	std::cout << std::endl;
	return 0;
}