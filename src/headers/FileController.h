#ifndef SRC_HEADERS_FILECONTROLLER_H_
#define SRC_HEADERS_FILECONTROLLER_H_

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "Matrix.h"

namespace s21 {
class FileController {
 public:
  static void readLabyrinthFromFile(const std::string &name_file, Matrix<bool> &right, Matrix<bool> &bottom);
  static void readCaveFromFile(const std::string &name_file, Matrix<bool> &matrix);
  static void writeLabyrinthToFile(const std::string &name_file, Matrix<bool> &right, Matrix<bool> &bottom);
  static void writeCaveToFile(const std::string &name_file, Matrix<bool> &matrix);
 private:
  static std::pair<int, int> readSize(std::ifstream &file);
  static void readMatrix(std::ifstream &file, Matrix<bool> &matrix);
  static void writeMatrix(std::ofstream &file, Matrix<bool> &matrix);
};
}  // namespace s21

#endif  // SRC_HEADERS_FILECONTROLLER_H_
