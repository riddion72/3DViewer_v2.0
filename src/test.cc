#include <gtest/gtest.h>

#include "model/parser.h"

TEST(ModelTest, Test1) {
  s21::ObjParser o;
  std::string path = "test_object/test.obj";
  o.parserVertex(path);
  std::vector<double> orig = {0.25,  -0.25, -0.25, 0.25,  -0.25, 0.25,
                              -0.25, -0.25, 0.25,  -0.25, -0.25, -0.25,
                              0.25,  0.25,  -0.25, 0.25,  0.25,  0.25,
                              -0.25, 0.25,  0.25,  -0.25, 0.25,  -0.25};
  ASSERT_EQ(o.getVertex().size(), orig.size());
  for (int i = 0; i < orig.size(); ++i) {
    EXPECT_EQ(o.getVertex()[i], orig[i]);
  }
}

TEST(ModelTest, Test2) {
  s21::ObjParser o;
  std::string path = "test_object/test.obj";
  o.parserVertex(path);
  std::vector<double> orig = {
      1, 2, 2, 3, 3, 1, 7, 6, 6, 5, 5, 7, 4, 5, 5, 1, 1, 4, 5, 6, 6, 2, 2, 5,
      2, 6, 6, 7, 7, 2, 0, 3, 3, 7, 7, 0, 0, 1, 1, 3, 3, 0, 4, 7, 7, 5, 5, 4,
      0, 4, 4, 1, 1, 0, 1, 5, 5, 2, 2, 1, 3, 2, 2, 7, 7, 3, 4, 0, 0, 7, 7, 4};
  ASSERT_EQ(o.getVertex().size(), orig.size() / 3);
  for (int i = 0; i < orig.size(); ++i) {
    EXPECT_EQ(o.getSegments()[i], orig[i]);
  }
}

TEST(ModelTest, Test3) {
  s21::ObjParser o;
  std::string path = "test_object/test.obj";
  o.modelDemolisher();
  EXPECT_EQ(o.getVertex().empty(), 1);
  EXPECT_EQ(o.getSegments().empty(), 1);
}

TEST(ModelTest, Test4) {
  s21::ObjParser o;
  std::string path = "test_object/????.obj";
  EXPECT_THROW(o.parserVertex(path), std::runtime_error);
}

TEST(ModelTest, Test5) {
  s21::ObjParser o;
  std::string path = "test_object/test_vertex.obj";
  EXPECT_THROW(o.parserVertex(path), std::runtime_error);
}

TEST(ModelTest, Test6) {
  s21::ObjParser o;
  std::string path = "test_object/empty.obj";
  EXPECT_THROW(o.parserVertex(path), std::runtime_error);
}

TEST(ModelTest, Test7) {
  s21::ObjParser o;
  std::string path = "test_object/test_object1.obj";
  EXPECT_THROW(o.parserVertex(path), std::runtime_error);
}

TEST(ModelTest, Test8) {
  s21::ObjParser o;
  std::string path = "test_object/test_object2.obj";
  EXPECT_THROW(o.parserVertex(path), std::runtime_error);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}