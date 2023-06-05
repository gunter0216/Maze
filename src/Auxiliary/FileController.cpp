#include "../headers/FileController.h"

void s21::FileController::readLabyrinthFromFile(const std::string &name_file,
                                                Matrix<bool> &right,
                                                Matrix<bool> &bottom) {
    std::ifstream file(name_file);
    if (file.is_open()) {
        auto size = readSize(file);

        right = Matrix<bool>(size.first, size.second);
        bottom = Matrix<bool>(size.first, size.second);

        readMatrix(file, right);
        readMatrix(file, bottom);
        file.close();
    }
}

void s21::FileController::readCaveFromFile(const std::string &name_file, Matrix<bool> &matrix) {
    std::ifstream file(name_file);
    if (file.is_open()) {
        auto size = readSize(file);

        matrix = Matrix<bool>(size.first, size.second);

        readMatrix(file, matrix);
        file.close();
    }
}

void s21::FileController::writeCaveToFile(const std::string &name_file, Matrix<bool> &matrix) {
    std::ofstream file(name_file);
    if (file.is_open()) {
        file << matrix.getRows() << ' ' << matrix.getCols() << std::endl;

        writeMatrix(file, matrix);
        file << std::endl;

        file.close();
    }
}

void s21::FileController::writeLabyrinthToFile(const std::string &name_file,
                                               Matrix<bool> &right,
                                               Matrix<bool> &bottom) {
    std::ofstream file(name_file);
    if (file.is_open()) {
        file << right.getRows() << ' ' << right.getCols() << std::endl;

        writeMatrix(file, right);
        file << std::endl;
        writeMatrix(file, bottom);

        file.close();
    }
}

void s21::FileController::writeMatrix(std::ofstream &file, Matrix<bool> &matrix) {
    for (int i = 0; i < matrix.getRows(); ++i) {
        for (int j = 0; j < matrix.getCols(); ++j) {
            file << matrix[i][j] << ' ';
        }
        file << std::endl;
    }
}

std::pair<int, int> s21::FileController::readSize(std::ifstream &file) {
    std::pair<int, int> size;
    file >> size.first >> size.second;
    return size;
}

void s21::FileController::readMatrix(std::ifstream &file, Matrix<bool> &matrix) {
    for (int i = 0; i < matrix.getRows(); ++i)
        for (int j = 0; j < matrix.getCols(); ++j)
            file >> matrix[i][j];
}
