#ifndef SRC_HEADERS_CAVE_H_
#define SRC_HEADERS_CAVE_H_

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "Matrix.h"

namespace s21 {
class Cave {
 public:
  /// создаёт первичную пещеру
  /// @param matrix                    матрца в которую запишется результат
  /// @param chance_to_initialize      шанс на создание живой клетки при начальной инициализации [0;100]%
  static void initializeCave(Matrix<bool> &matrix,
                             const int height,
                             const int width,
                             const int chance_to_initialize);
  /// переходит на следующий шаг жизни
  /// @param firstMatrix               матрица которая преобразовывается
  /// @param helpMatrix                вспомогательная матрица(не требует инициализации)
  /// @param birth_limit               лимит рождения клетки [0;7]
  /// @param limit_of_death            лимит смерти клетки [0;7]
  /// @param circle                    зацикливается ли матрица
  /// @return произошли ли изменения
  static bool nextStep(Matrix<bool> &firstMatrix,
                       Matrix<bool> &helpMatrix,
                       const int birth_limit,
                       const int limit_of_death,
                       const bool circle);
};
}  // namespace s21

#endif  // SRC_HEADERS_CAVE_H_
