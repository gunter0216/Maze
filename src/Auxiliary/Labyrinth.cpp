#include "../headers/Labyrinth.h"

void s21::Labyrinth::findingAWay(std::forward_list<std::pair<int, int>> &list,
                                 Matrix<bool> &right,
                                 Matrix<bool> &bottom,
                                 const int x1, const int y1, const int x2, const int y2) {
    if (x1 >= right.getCols() || x2 >= right.getCols() ||
        y1 >= right.getRows() || y2 >= right.getRows() ||
        x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0)
        std::__throw_out_of_range("Неверно заданы координаты.");
    if (right.getCols() != bottom.getCols() ||
        right.getRows() != bottom.getRows())
        std::__throw_out_of_range("Размеры матриц не совпадают.");
    Matrix<int> newMatrix(right.getRows(), right.getCols());
    createLeeMatrix(newMatrix, right, bottom, x1, y1, x2, y2);
    createAWayList(list, newMatrix, right, bottom, x1, y1, x2, y2);
}

void s21::Labyrinth::createLeeMatrix(Matrix<int> &newMatrix,
                                     Matrix<bool> &right,
                                     Matrix<bool> &bottom,
                                     const int x1, const int y1, const int x2, const int y2) {
    int d = 1;
    bool stop = false;
    newMatrix[y1][x1] = d;
    int width = right.getCols();
    int height = right.getRows();
    do {
        stop = true;
        for (int i = 0; i < height; ++i)
            for (int j = 0; j < width; ++j)
                if (newMatrix[i][j] == d) {
                    if (i > 0 && newMatrix[i - 1][j] == 0 && !bottom[i - 1][j]) {  // top
                        newMatrix[i - 1][j] = d + 1;
                        stop = false;
                    }
                    if (j > 0 && newMatrix[i][j - 1] == 0 && !right[i][j - 1]) {  // left
                        newMatrix[i][j - 1] = d + 1;
                        stop = false;
                    }
                    if (i < height - 1 && newMatrix[i + 1][j] == 0 && !bottom[i][j]) {  // bottom
                        newMatrix[i + 1][j] = d + 1;
                        stop = false;
                    }
                    if (j < width - 1 && newMatrix[i][j + 1] == 0 && !right[i][j]) {  // right
                        newMatrix[i][j + 1] = d + 1;
                        stop = false;
                    }
                }
        d++;
    } while (!stop && newMatrix[y2][x2] == 0);
}

void s21::Labyrinth::createAWayList(std::forward_list<std::pair<int, int>> &list,
                                    Matrix<int> &matrix,
                                    Matrix<bool> &right,
                                    Matrix<bool> &bottom,
                                    const int x1, const int y1, const int x2, const int y2) {
    int x = x2;
    int y = y2;
    int d = matrix[y][x];
    int width = matrix.getCols();
    int height = matrix.getRows();
    while (d > 0) {
        list.push_front(std::pair<int, int>(y, x));
        d--;
        if (x > 0 && matrix[y][x - 1] == d && !right[y][x - 1]) {
            --x;
        } else if (x < width - 1 && matrix[y][x + 1] == d && !right[y][x]) {
            ++x;
        } else if (y > 0 && matrix[y - 1][x] == d && !bottom[y - 1][x]) {
            --y;
        } else if (y < height - 1 && matrix[y + 1][x] == d && !bottom[y][x]) {
            ++y;
        }
    }
}

void s21::Labyrinth::createLabyrinth(Matrix<bool> &right,
                                     Matrix<bool> &bottom,
                                     const int width,
                                     const int height) {
    if (width <= 0 || height <= 0)
        std::__throw_out_of_range("Размер лабиринта должен быть больше 0.");
    Matrix<int> matrix(height, width);
    right = Matrix<bool>(height, width);
    bottom = Matrix<bool>(height, width);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            right[i][j] = false;
            bottom[i][j] = false;
            matrix[i][j] = 0;
        }
    }

    createDefaultBorder(right, bottom);
    if (width > 1 && height > 1) {
        for (int i = 0; i < width; ++i)
            matrix[0][i] = i;
        createRightBorder(matrix, right, 0);
        createBottomBorder(matrix, bottom, 0);
        for (int i = 1; i < height; ++i) {
            createNewRow(matrix, right, bottom, i);
            createRightBorder(matrix, right, i);
            createBottomBorder(matrix, bottom, i);
        }
        createEndLabyrinth(matrix, right, bottom);
    }
}

void s21::Labyrinth::createNewRow(Matrix<int> &matrix,
                                  Matrix<bool> &right,
                                  Matrix<bool> &bottom,
                                  const int number_new_row) {
    int width = right.getCols();
    int max = 0;
    for (int i = 0; i < width; ++i) {
        if (bottom[number_new_row - 1][i]) {
            matrix[number_new_row][i] = -1;
        } else {
            if (matrix[number_new_row - 1][i] > max)
                max = matrix[number_new_row - 1][i];
            matrix[number_new_row][i] = matrix[number_new_row - 1][i];
        }
    }
    for (int i = 0; i < width; ++i) {
        if (matrix[number_new_row][i] == -1)
            matrix[number_new_row][i] = ++max;
    }
}

void s21::Labyrinth::createRightBorder(Matrix<int> &matrix, Matrix<bool> &right, const int number_row) {
    int width = right.getCols();
    for (int i = 0; i < width - 1; ++i) {
        char choose = std::rand() % 2;
        if (choose == 0 || matrix[number_row][i] == matrix[number_row][i + 1]) {
            right[number_row][i] = true;
        } else {
            unionSet(matrix, matrix[number_row][i], matrix[number_row][i + 1], number_row);
        }
    }
}

void s21::Labyrinth::unionSet(Matrix<int> &matrix, const int num1, const int num2, const int number_row) {
    for (int i = 0; i < matrix.getCols(); ++i) {
        if (matrix[number_row][i] == num2) {
            matrix[number_row][i] = num1;
        }
    }
}

void s21::Labyrinth::createBottomBorder(Matrix<int> &matrix, Matrix<bool> &bottom, const int number_row) {
    for (int i = 0; i < matrix.getCols(); ++i) {
        char choose = std::rand() % 2;
        if (choose == 0 && countRepeatableNumbers(matrix, matrix[number_row][i], number_row) != 1)
            bottom[number_row][i] = true;
    }
    correctBottomBorder(matrix, bottom, number_row);
}

int s21::Labyrinth::countRepeatableNumbers(Matrix<int> &matrix, const int set, const int number_row) {
    int result = 0;
    for (int i = 0; i < matrix.getCols(); ++i) {
        if (matrix[number_row][i] == set)
            ++result;
    }
    return result;
}

void s21::Labyrinth::correctBottomBorder(Matrix<int> &matrix, Matrix<bool> &bottom, const int number_row) {
    for (int i = 0; i < matrix.getCols(); ++i) {
        if (countCellsInSetWithoutBottomBorder(matrix, bottom, matrix[number_row][i], number_row) == 0) {
            bottom[number_row][i] = false;
        }
    }
}

int s21::Labyrinth::countCellsInSetWithoutBottomBorder(Matrix<int> &matrix,
                                                       Matrix<bool> &bottom,
                                                       const int set,
                                                       const int number_row) {
    int result = 0;
    for (int i = 0; i < matrix.getCols(); ++i) {
        if (matrix[number_row][i] == set && !bottom[number_row][i]) {
            ++result;
        }
    }
    return result;
}

void s21::Labyrinth::createEndLabyrinth(Matrix<int> &matrix, Matrix<bool> &right, Matrix<bool> &bottom) {
    int width = right.getCols();
    int height = right.getRows();
    for (int i = 0; i < width - 1; ++i) {
        if (matrix[height - 1][i] != matrix[height - 1][i + 1]) {
            right[height - 1][i] = false;
            unionSet(matrix, matrix[height - 1][i], matrix[height - 1][i + 1], height - 1);
        }
    }
}

void s21::Labyrinth::createDefaultBorder(Matrix<bool> &right, Matrix<bool> &bottom) {
    int width = right.getCols();
    int height = right.getRows();
    for (int i = 0; i < height; ++i)
        right[i][width - 1] = true;
    for (int i = 0; i < width; ++i)
        bottom[height - 1][i] = true;
}
