#include "../headers/Cave.h"

void s21::Cave::initializeCave(Matrix<bool> &matrix,
                               const int height,
                               const int width,
                               const int chance_to_initialize) {
    if (height <= 0 || width <= 0)
        std::__throw_out_of_range("Размер пещеры должен быть больше 0.");
    if (chance_to_initialize < 0 || chance_to_initialize > 100)
        std::__throw_out_of_range("Шанс на создание живой клетки должен находиться в пределах [0;100].");
    matrix = Matrix<bool>(height, width);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if ((std::rand() % 101) <= chance_to_initialize) {
                matrix[i][j] = false;
            } else {
                matrix[i][j] = true;
            }
        }
    }
}

bool s21::Cave::nextStep(Matrix<bool> &firstMatrix,
                         Matrix<bool> &helpMatrix,
                         const int birth_limit,
                         const int limit_of_death,
                         const bool circle) {
    if (birth_limit < 0 || birth_limit > 8)
        std::__throw_out_of_range("Предел рождения должен находиться в пределах [0;7].");
    if (limit_of_death < 0 || limit_of_death > 8)
        std::__throw_out_of_range("Предел смерти должен находиться в пределах [0;7].");
    if (helpMatrix.getCols() != firstMatrix.getCols() || helpMatrix.getRows() != firstMatrix.getRows()) {
        helpMatrix = Matrix<bool>(firstMatrix.getRows(), firstMatrix.getCols());
    }
    bool result = false;
    const int dx[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
    const int dy[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int width = firstMatrix.getCols();
    int height = firstMatrix.getRows();
    int newX, newY;
    int number_of_living_cells;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            number_of_living_cells = 0;
            for (int k = 0; k < 8; ++k) {
                newY = i + dy[k];
                newX = j + dx[k];
                if (!circle) {
                    if (newX < width && newX >= 0 && newY >= 0 && newY < height &&
                        firstMatrix[newY][newX] == false) {
                        ++number_of_living_cells;
                    }
                } else {
                    newY = newY < 0 ? height - 1 : newY % height;
                    newX = newX < 0 ? width - 1 : newX % width;
                    if (firstMatrix[newY][newX] == false)
                        ++number_of_living_cells;
                }
            }
            if (firstMatrix[i][j] == false && number_of_living_cells < limit_of_death) {
                helpMatrix[i][j] = true;
                result = true;
            } else if (firstMatrix[i][j] == true && number_of_living_cells > birth_limit) {
                helpMatrix[i][j] = false;
                result = true;
            } else {
                helpMatrix[i][j] = firstMatrix[i][j];
            }
        }
    }
    firstMatrix.swap(helpMatrix);
    return result;
}
