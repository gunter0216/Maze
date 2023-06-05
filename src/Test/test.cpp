#include <gtest/gtest.h>

#include "../headers/Cave.h"
#include "../headers/Labyrinth.h"

TEST(Cave, initialize_1) {
    bool result = true;
    s21::Matrix<bool> matrix{};
    s21::Cave::initializeCave(matrix, 5, 10, 50);
    if (matrix.getCols() != 10 || matrix.getRows() != 5) {
        result = false;
    }
    ASSERT_TRUE(result);
}

TEST(Cave, initialize_2) {
    bool result = true;
    s21::Matrix<bool> matrix{};
    s21::Cave::initializeCave(matrix, 1, 1, 50);
    if (matrix.getCols() != 1 || matrix.getRows() != 1) {
        result = false;
    }
    ASSERT_TRUE(result);
}

TEST(Cave, initialize_3) {
    bool result = false;
    s21::Matrix<bool> matrix{};
    try {
        s21::Cave::initializeCave(matrix, -1, -1, 50);
    } catch (...) {
        result = true;
    }
    ASSERT_TRUE(result);
}

TEST(Cave, initialize_4) {
    bool result = false;
    s21::Matrix<bool> matrix{};
    try {
        s21::Cave::initializeCave(matrix, 1, 1, 101);
    } catch (...) {
        result = true;
    }
    ASSERT_TRUE(result);
}

TEST(Cave, nextStep_1) {
    bool result = true;
    s21::Matrix<bool> matrix{{0, 1, 0, 1},
                             {0, 0, 1, 0},
                             {0, 0, 0, 0},
                             {1, 1, 1, 1}};
    s21::Matrix<bool> helpMatrix{};
    s21::Matrix<bool> nextMatrix{{1, 0, 1, 1},
                                 {0, 0, 0, 1},
                                 {1, 0, 0, 1},
                                 {1, 1, 1, 1}};
    s21::Cave::nextStep(matrix, helpMatrix, 3, 4, false);
    if (matrix != nextMatrix) {
        result = false;
    }
    ASSERT_TRUE(result);
}

TEST(Cave, nextStep_2) {
    bool result = false;
    s21::Matrix<bool> matrix{{0, 1, 0, 1},
                             {0, 0, 1, 0},
                             {0, 0, 0, 0},
                             {1, 1, 1, 1}};
    s21::Matrix<bool> helpMatrix{};
    try {
        s21::Cave::nextStep(matrix, helpMatrix, -1, 4, false);
    } catch (...) {
        result = true;
    }
    ASSERT_TRUE(result);
}

TEST(Cave, nextStep_3) {
    bool result = false;
    s21::Matrix<bool> matrix{{0, 1, 0, 1},
                             {0, 0, 1, 0},
                             {0, 0, 0, 0},
                             {1, 1, 1, 1}};
    s21::Matrix<bool> helpMatrix{};
    try {
        s21::Cave::nextStep(matrix, helpMatrix, 1, 10, false);
    } catch (...) {
        result = true;
    }
    ASSERT_TRUE(result);
}

TEST(Cave, nextStep_4) {
    bool result = true;
    s21::Matrix<bool> matrix{{0, 1, 0, 1},
                             {0, 0, 1, 0},
                             {0, 0, 0, 0},
                             {1, 1, 1, 1}};
    s21::Matrix<bool> helpMatrix{};
    s21::Matrix<bool> nextMatrix{{1, 0, 1, 0},
                                 {0, 0, 0, 0},
                                 {0, 0, 0, 0},
                                 {0, 0, 0, 0}};
    int birth_limit = 3;
    int death_limit = 4;
    s21::Cave::nextStep(matrix, helpMatrix, birth_limit, death_limit, true);
    if (matrix != nextMatrix) {
        result = false;
    }
    ASSERT_TRUE(result);
}

TEST(Labyrinth, create_labyrinth_1) {
    bool result = true;
    s21::Matrix<bool> right;
    s21::Matrix<bool> bottom;
    int width = 10;
    int height = 5;

    s21::Labyrinth::createLabyrinth(right, bottom, width, height);
    if ((right.getCols() != 10 || right.getRows() != 5) &&
        (bottom.getCols() != 10 || bottom.getRows() != 5)) {
        result = false;
    }

    ASSERT_TRUE(result);
}

TEST(Labyrinth, create_labyrinth_2) {
    bool result = false;
    s21::Matrix<bool> right;
    s21::Matrix<bool> bottom;

    try {
        s21::Labyrinth::createLabyrinth(right, bottom, -1, 1);
    } catch (...) {
        result = true;
    }
    ASSERT_TRUE(result);
}

TEST(Labyrinth, create_labyrinth_3) {
    bool result = false;
    s21::Matrix<bool> right;
    s21::Matrix<bool> bottom;

    try {
        s21::Labyrinth::createLabyrinth(right, bottom, 1, -1);
    } catch (...) {
        result = true;
    }
    ASSERT_TRUE(result);
}

TEST(Labyrinth, findingAWay_1) {
    bool result = true;
    std::forward_list<std::pair<int, int>> list{};
    s21::Matrix<bool> right{{0, 0, 0, 1},
                            {1, 0, 1, 1},
                            {0, 1, 0, 1},
                            {0, 0, 0, 1}};
    s21::Matrix<bool> bottom{{1, 0, 1, 0},
                             {0, 0, 1, 0},
                             {1, 1, 0, 1},
                             {1, 1, 1, 1}};
    s21::Labyrinth::findingAWay(list, right, bottom,
                                1, 1, 2, 3);
    const int x[] = {1, 1, 2, 3, 3, 3, 2, 2};
    const int y[] = {1, 0, 0, 0, 1, 2, 2, 3};
    int i = 0;
    for (
        auto item : list) {
        if (item.first != y[i] ||
            item.second != x[i]) {
            result = false;
        }
        ++i;
    }
    ASSERT_TRUE(result);
}

TEST(Labyrinth, findingAWay_2) {
    bool result = false;
    std::forward_list<std::pair<int, int>> list{};
    s21::Matrix<bool> right{{0, 0, 0, 1},
                            {1, 0, 1, 1},
                            {0, 1, 0, 1},
                            {0, 0, 0, 1}};
    s21::Matrix<bool> bottom{{1, 0, 1, 0},
                             {0, 0, 1, 0},
                             {1, 1, 0, 1},
                             {1, 1, 1, 1}};
    try {
        s21::Labyrinth::findingAWay(list, right, bottom, -1, 1, 2, 3);
    } catch (...) {
        result = true;
    }
    ASSERT_TRUE(result);
}

TEST(Labyrinth, findingAWay_3) {
    bool result = false;
    std::forward_list<std::pair<int, int>> list{};
    s21::Matrix<bool> right{{0, 0, 0, 1},
                            {1, 0, 1, 1},
                            {0, 1, 0, 1},
                            {0, 0, 0, 1}};
    s21::Matrix<bool> bottom{{1, 0, 1, 0},
                             {0, 0, 1, 0},
                             {1, 1, 0, 1},
                             {1, 1, 1, 1}};
    try {
        s21::Labyrinth::findingAWay(list, right, bottom,
                                    1, 1, 5, 3);
    } catch (...) {
        result = true;
    }

    ASSERT_TRUE(result);
}

TEST(Labyrinth, findingAWay_4) {
    bool result = true;
    std::forward_list<std::pair<int, int>> list{std::pair<int, int>(1, 2)};
    s21::Matrix<bool> right{{0, 0, 0, 1},
                            {1, 0, 1, 1},
                            {0, 1, 0, 1},
                            {0, 0, 0, 1}};
    s21::Matrix<bool> bottom{{1, 0, 1, 0},
                             {0, 0, 1, 0},
                             {1, 1, 0, 1},
                             {1, 1, 1, 1}};
    s21::Labyrinth::findingAWay(list, right, bottom, 1, 1, 2, 3);
    const int x[] = {1, 1, 2, 3, 3, 3, 2, 2, 2};
    const int y[] = {1, 0, 0, 0, 1, 2, 2, 3, 1};
    int i = 0;
    for (auto item : list) {
        if (item.first != y[i] ||
            item.second != x[i]) {
            result = false;
        }
        ++i;
    }
    ASSERT_TRUE(result);
}

TEST(Labyrinth, findingAWay_5) {
    bool result = false;
    std::forward_list<std::pair<int, int>> list{};
    s21::Matrix<bool> right{{0, 0, 0, 1},
                            {1, 0, 1, 1},
                            {0, 1, 0, 1},
                            {0, 0, 0, 1}};
    s21::Matrix<bool> bottom{{1, 0, 1, 0},
                             {0, 0, 1, 0},
                             {1, 1, 0, 1}};
    try {
        s21::Labyrinth::findingAWay(list, right, bottom,
                                    1, 1, 2, 2);
    } catch (...) {
        result = true;
    }

    ASSERT_TRUE(result);
}

void test() {
    s21::Matrix<bool> matrix{{0, 1, 0, 1},
                             {0, 0, 1, 0},
                             {0, 0, 0, 0},
                             {1, 1, 1, 1}};
    s21::Matrix<bool> helpMatrix{};
    s21::Matrix<bool> nextMatrix{{1, 0, 1, 0},
                                 {0, 0, 0, 0},
                                 {0, 0, 0, 0},
                                 {0, 0, 0, 0}};
    int birth_limit = 3;
    int death_limit = 4;
    s21::Cave::nextStep(matrix, helpMatrix, birth_limit, death_limit, true);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
