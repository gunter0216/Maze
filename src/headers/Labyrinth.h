#pragma once
#include <iostream>

#include "Matrix.h"
#include "forward_list"

namespace s21 {
/// Standard labyrinth constructor.
class Labyrinth {
 public:
  /// создаёт лабиринт
  static void createLabyrinth(Matrix<bool> &right, Matrix<bool> &bottom, const int width, const int height);
  /// поиск пути
  static void findingAWay(std::forward_list<std::pair<int, int>> &list,
                          Matrix<bool> &right,
                          Matrix<bool> &bottom,
                          const int x1, const int y1, const int x2, const int y2);

 private:
  /// объединяет множества
  static void unionSet(Matrix<int> &matrix, const int num1, const int num2, const int number_row);
  /// считает кол-во клеток без нижний стенки в строке number_row в множестве set
  static int countCellsInSetWithoutBottomBorder(Matrix<int> &matrix,
                                                Matrix<bool> &bottom,
                                                const int set,
                                                const int number_row);
  /// проверяет начилие хоть одной нижней стенки в каждом множестве и исправляет
  static void correctBottomBorder(Matrix<int> &matrix, Matrix<bool> &bottom, const int number_row);
  /// считает кол-во элементов в множестве set в строке number_row
  static int countRepeatableNumbers(Matrix<int> &matrix, const int set, const int number_row);
  /// создаёт нижнюю стенку в строке number_row
  static void createBottomBorder(Matrix<int> &matrix, Matrix<bool> &bottom, const int number_row);
  /// создаёт правую стенку в строке number_row
  static void createRightBorder(Matrix<int> &matrix, Matrix<bool> &right, const int number_row);
  /// создаёт новую строку из предыдущей
  static void createNewRow(Matrix<int> &matrix,
                           Matrix<bool> &right,
                           Matrix<bool> &bottom,
                           const int number_new_row);
  /// создаёт стенки справа и снизу
  static void createDefaultBorder(Matrix<bool> &right, Matrix<bool> &bottom);
  /// создаёт конец лабиринта
  static void createEndLabyrinth(Matrix<int> &matrix, Matrix<bool> &right, Matrix<bool> &bottom);
  /// создаёт матрцу путей по алгоритму Ли
  static void createLeeMatrix(Matrix<int> &newMatrix,
                              Matrix<bool> &right,
                              Matrix<bool> &bottom,
                              const int x1, const int y1, const int x2, const int y2);
  /// создаёт список координат пути
  static void createAWayList(std::forward_list<std::pair<int, int>> &list,
                             Matrix<int> &matrix,
                             Matrix<bool> &right,
                             Matrix<bool> &bottom,
                             const int x1, const int y1, const int x2, const int y2);
};
}  // namespace s21
