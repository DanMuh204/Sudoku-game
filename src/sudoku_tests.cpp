#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "sudoku.h"

/**
 * @file sudoku_test.cpp
 * @brief Тесты ко всем функциям программной реализации игры судоку, покрывающие
 * положительные и отрицательные результаты
 *
 * @bug Нет известных багов
 */

/**
 * @brief Тестирует функцию isSafe.
 *
 * Тестирует корректность работы функции isSafe при различных условиях:
 * - Число безопасно для вставки.
 * - Число уже присутствует в той же строке, столбце или 3x3 блоке.
 */
TEST_CASE("Testing isSafe") {
  int board[N][N] = {{5, 3, 0, 0, 7, 0, 0, 0, 0}, {6, 0, 0, 1, 9, 5, 0, 0, 0},
                     {0, 9, 8, 0, 0, 0, 0, 6, 0}, {8, 0, 0, 0, 6, 0, 0, 0, 3},
                     {4, 0, 0, 8, 0, 3, 0, 0, 1}, {7, 0, 0, 0, 2, 0, 0, 0, 6},
                     {0, 6, 0, 0, 0, 0, 2, 8, 0}, {0, 0, 0, 4, 1, 9, 0, 0, 5},
                     {0, 0, 0, 0, 8, 0, 0, 7, 9}};

  // Положительный результат: число 4 безопасно для вставки
  CHECK(isSafe(board, 0, 2, 4) == true);

  // Отрицательные результаты:
  // 3 уже есть в той же строке
  CHECK(isSafe(board, 0, 2, 3) == false);

  // 6 уже есть в том же столбце
  CHECK(isSafe(board, 0, 2, 6) == false);

  // 5 уже есть в том же 3x3 блоке
  CHECK(isSafe(board, 0, 2, 5) == false);
}

/**
 * @brief Тестирует функцию solveSudoku.
 *
 * Тестирует функцию solveSudoku, проверяя успешное решение судоку.
 * Также проверяет, что после решения все клетки заполнены.
 */
TEST_CASE("Testing solveSudoku") {
  int board[N][N] = {{5, 3, 0, 0, 7, 0, 0, 0, 0}, {6, 0, 0, 1, 9, 5, 0, 0, 0},
                     {0, 9, 8, 0, 0, 0, 0, 6, 0}, {8, 0, 0, 0, 6, 0, 0, 0, 3},
                     {4, 0, 0, 8, 0, 3, 0, 0, 1}, {7, 0, 0, 0, 2, 0, 0, 0, 6},
                     {0, 6, 0, 0, 0, 0, 2, 8, 0}, {0, 0, 0, 4, 1, 9, 0, 0, 5},
                     {0, 0, 0, 0, 8, 0, 0, 7, 9}};

  // Положительный результат: судоку решен успешно
  CHECK(solveSudoku(board, 0, 0) == true);

  // Проверка правильности решения
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      CHECK(board[i][j] != 0);
    }
  }
}

/**
 * @brief Тестирует функцию isSolvedCompletely.
 *
 * Проверяет правильность работы функции isSolvedCompletely на полностью
 * решенном и неполном судоку.
 */
TEST_CASE("Тестирование функции isSolvedCompletely") {
  int solvedBoard[N][N] = {
      {5, 3, 4, 6, 7, 8, 9, 1, 2}, {6, 7, 2, 1, 9, 5, 3, 4, 8},
      {1, 9, 8, 3, 4, 2, 5, 6, 7}, {8, 5, 9, 7, 6, 1, 4, 2, 3},
      {4, 2, 6, 8, 5, 3, 7, 9, 1}, {7, 1, 3, 9, 2, 4, 8, 5, 6},
      {9, 6, 1, 5, 3, 7, 2, 8, 4}, {2, 8, 7, 4, 1, 9, 6, 3, 5},
      {3, 4, 5, 2, 8, 6, 1, 7, 9}};

  int incompleteBoard[N][N] = {
      {5, 3, 4, 6, 7, 8, 9, 1, 2}, {6, 7, 2, 1, 9, 5, 3, 4, 8},
      {1, 9, 8, 3, 4, 2, 5, 6, 7}, {8, 5, 9, 7, 6, 1, 4, 2, 3},
      {4, 2, 6, 8, 5, 3, 7, 9, 1}, {7, 1, 3, 9, 2, 4, 8, 5, 6},
      {9, 6, 1, 5, 3, 7, 2, 8, 4}, {2, 8, 7, 4, 1, 9, 6, 3, 5},
      {3, 4, 5, 2, 8, 6, 1, 7, 0}};

  // Положительный тест: полностью решенная доска
  CHECK(isSolvedCompletely(solvedBoard) == true);

  // Отрицательный тест: неполностью решенная доска
  CHECK(isSolvedCompletely(incompleteBoard) == false);
}

/**
 * @brief Тестирует функцию saveBoard.
 *
 * Проверяет успешность сохранения игрового поля в файл, существование файла,
 * а также правильность сохраненных данных путём последующей загрузки.
 */
TEST_CASE("Тестирование функции saveBoard") {
  int board[N][N] = {{5, 3, 4, 6, 7, 8, 9, 1, 2}, {6, 7, 2, 1, 9, 5, 3, 4, 8},
                     {1, 9, 8, 3, 4, 2, 5, 6, 7}, {8, 5, 9, 7, 6, 1, 4, 2, 3},
                     {4, 2, 6, 8, 5, 3, 7, 9, 1}, {7, 1, 3, 9, 2, 4, 8, 5, 6},
                     {9, 6, 1, 5, 3, 7, 2, 8, 4}, {2, 8, 7, 4, 1, 9, 6, 3, 5},
                     {3, 4, 5, 2, 8, 6, 1, 7, 9}};

  std::string filename = "test_save.txt";
  saveBoard(board, filename);

  std::ifstream file(filename);
  bool fileExists = file.good();
  file.close();

  // Положительный тест: файл успешно созданx
  CHECK(fileExists == true);

  // Чтение сохраненного файла и проверка его содержимого
  int loadedBoard[N][N];
  loadBoard(loadedBoard, filename);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      CHECK(loadedBoard[i][j] == board[i][j]);
    }
  }

  // Удаление тестового файла после проверки
  std::remove(filename.c_str());
}

/**
 * @brief Тестирует функцию loadBoard.
 *
 * Проверяет правильность загрузки игрового поля из файла, сравнивая загруженные
 * данные с ожидаемыми. Также создает и удаляет тестовый файл для проверки.
 */
TEST_CASE("Тестирование функции loadBoard") {
  int expectedBoard[N][N] = {
      {5, 3, 4, 6, 7, 8, 9, 1, 2}, {6, 7, 2, 1, 9, 5, 3, 4, 8},
      {1, 9, 8, 3, 4, 2, 5, 6, 7}, {8, 5, 9, 7, 6, 1, 4, 2, 3},
      {4, 2, 6, 8, 5, 3, 7, 9, 1}, {7, 1, 3, 9, 2, 4, 8, 5, 6},
      {9, 6, 1, 5, 3, 7, 2, 8, 4}, {2, 8, 7, 4, 1, 9, 6, 3, 5},
      {3, 4, 5, 2, 8, 6, 1, 7, 9}};

  std::string filename = "test_load.txt";
  std::ofstream file(filename);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      file << expectedBoard[i][j] << " ";
    }
    file << std::endl;
  }
  file.close();

  int loadedBoard[N][N];
  loadBoard(loadedBoard, filename);

  // Положительный тест: данные загружены правильно
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      CHECK(loadedBoard[i][j] == expectedBoard[i][j]);
    }
  }

  // Удаление тестового файла после проверки
  std::remove(filename.c_str());
}
