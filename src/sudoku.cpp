#include "sudoku.h"
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

/**
 * @file sudoku.cpp
 * @brief Реализация функций для решения и управления игрой судоку.
 *
 * @bug Нет известных багов
 */

// Данный фрагмент кода заимствован из другого проекта

/**
 * @brief Проверяет, возможно ли по правилам игры разместить число в указанной
 * ячейке.
 *
 * @param board Игровое поле (карта).
 * @param row Номер строки.
 * @param col Номер столбца.
 * @param num Число для размещения.
 * @return true, если размещение возможно.
 * @return false, если размещение невозможно.
 */
bool isSafe(int board[N][N], int row, int col, int num) {
  // Проверяем строку
  for (int x = 0; x < N; x++) {
    if (board[row][x] == num) {
      return false; // Число уже существует в этой строке
    }
  }

  // Проверяем столбец
  for (int x = 0; x < N; x++) {
    if (board[x][col] == num) {
      return false; // Число уже существует в этом столбце
    }
  }

  // Проверяем 3x3 блок
  int startRow = row - row % 3; // Находим начальную строку 3x3 блока
  int startCol = col - col % 3; // Находим начальный столбец 3x3 блока
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i + startRow][j + startCol] == num) {
        return false; // Число уже существует в этом 3x3 блоке
      }
    }
  }

  // Если число не встречается ни в строке, ни в столбце, ни в 3x3 блоке
  return true; // Число нельзя вставить
}

// Конца заимствованного фрагмента

/**
 * @brief Выводит игровое поле (карту) на экран.
 *
 * @param grid Игровое поле (карта).
 */
void printBoard(int grid[N][N]) {
  system("clear");
  std::cout << "\t\t\t<========================================================"
               "========================>"
            << std::endl;
  std::cout << "\t\t\t|                    Добро пожаловать в игру Судоку!     "
               "                        |"
            << std::endl;
  std::cout << "\t\t\t| Заполните пустые числа (представленные нулём), чтобы "
               "завершить пазл.           |"
            << std::endl;
  std::cout << "\t\t\t<========================================================"
               "========================>"
            << std::endl;

  for (int col = 0; col < N; col++) {
    std::cout << col + 1 << " ";
    if (col == 2 || col == 5)
      std::cout << " | ";
  }
  std::cout << std::endl;
  for (int i = 0; i < N; i++) {
    std::cout << "---";
  }
  std::cout << std::endl;

  for (int row = 0; row < N; row++) {
    for (int col = 0; col < N; col++) {
      if (col == 3 || col == 6)
        std::cout << " | ";
      std::cout << grid[row][col] << " ";
    }
    if (row == 2 || row == 5) {
      std::cout << std::endl;
      for (int i = 0; i < N; i++)
        std::cout << "---";
    }
    std::cout << std::endl;
  }
}

/**
 * @brief Решает судоку автоматически.
 *
 * @param board Игровое поле (карта).
 * @param row Номер строки.
 * @param col Номер столбца.
 * @return true, если судоку решено.
 * @return false, если судоку не может быть решено.
 */
bool solveSudoku(int board[N][N], int row, int col) {
  // Проверяем, если достигли конца доски, то судоку решено
  if (row == N - 1 && col == N)
    return true;

  // Если достигли конца строки, переходим к следующей строке
  if (col == N) {
    row++;
    col = 0;
  }

  // Если ячейка уже заполнена, пропускаем её
  if (board[row][col] != 0)
    return solveSudoku(board, row, col + 1);

  // Пробуем вставить числа от 1 до 9 в текущую ячейку
  for (int num = 1; num <= 9; num++) {
    // Проверяем, безопасно ли вставить число число в текущую ячейку
    if (isSafe(board, row, col, num)) {
      // Если безопасно, устанавливаем число в ячейку
      board[row][col] = num;

      // Рекурсивно пытаемся решить оставшуюся часть доски
      if (solveSudoku(board, row, col + 1))
        return true;

      // Если решение не найдено, возвращаем ячейку к исходному состоянию
      board[row][col] = 0;
    }
  }

  // 9. Если ни одно число не подошло, решение судоку не возможно
  return false;
}

/**
 * @brief Проверяет, законченно ли судоку.
 *
 * @param grid Игровое поле (карта).
 * @return true, если судоку решено.
 * @return false, если судоку не решено.
 */
bool isSolvedCompletely(int grid[N][N]) {
  for (int row = 0; row < N; row++)
    for (int col = 0; col < N; col++)
      if (grid[row][col] == 0)
        return false;

  return true;
}

/**
 * @brief Сохраняет игровое поле (карту) в файл.
 *
 * @param board Игровое поле (карта).
 * @param filename Имя файла для сохранения.
 */
void saveBoard(int board[N][N], const std::string &filename) {
  std::ofstream file(filename);

  if (file.is_open()) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        file << board[i][j] << " ";
      }
      file << std::endl;
    }
    file.close();
  } else {
    std::cerr << "Не удалось открыть файл для сохранения " << filename << " !"
              << std::endl;
  }
}

/**
 * @brief Играет в судоку, позволяя пользователю вводить значения для пустых
 * клеток.
 *
 * Функция выводит текущее состояние игрового поля, позволяет пользователю
 * вводить значения для строк, столбцов и чисел. Пользователь может ввести -1
 * для автоматического решения судоку или -2 для сохранения текущего состояния и
 * выхода из игры. Функция проверяет правильность вводимых значений и обновляет
 * игровое поле (карту).
 *
 * @param board Двумерный массив, представляющий игровое поле (карту) судоку.
 */
void playGame(int board[N][N]) {
  int ch;
  int row, col, num;
  while (true) {
    printBoard(board);
    std::cout << std::endl << std::endl;
    std::cout << "Не получается решить? Введите -1 в поле строки, столбца и "
                 "номера, чтобы посмотреть решённое судоку."
              << std::endl;
    std::cout << "Если вы хотите сохраниться и выйти, введите -2 в поле "
                 "строки, столбца и номера."
              << std::endl;
    std::cout << "Введите номер строки: ";
    std::cin >> row;
    std::cout << "Введите номер столбца: ";
    std::cin >> col;
    std::cout << "Введите число: ";
    std::cin >> num;

    if (row == -1 || col == -1 || num == -1) {
      solveSudoku(board, 0, 0);
      printBoard(board);
      std::cout << std::endl;
      std::cout << "Удачи в следующий раз!!!" << std::endl;
      return;
    }

    else if (row == -2 || col == -2 || num == -2) {
      std::string saveFilename;
      std::cout << "Введите имя сохранённого файла: "; // Change this
      std::cin >> saveFilename;
      saveBoard(board, "/Users/muhametzanovdanis/AiP/Sudoku/src/saves/" +
                           saveFilename + ".txt");
      std::cout << "Игра сохранилась. Выход..." << std::endl;
      exit(0);
    }

    if (isSolvedCompletely(board))
      break;
    row--;
    col--;
    if (!isSafe(board, row, col, num)) {
      std::cout << "Введно невозможное значение. Попробуйте снова."
                << std::endl;
      continue;
    } else {
      std::cout << "Введено возможное значение." << std::endl;
    }
    board[row][col] = num;
  }

  bool solved = true;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (board[i][j] == 0) {
        solved = false;
        break;
      }
    }
  }

  if (solved) {
    std::cout << "Поздравляем! Вы решили судоку!" << std::endl;
    printBoard(board);
  } else {
    std::cout << "Судоку не решен. Удачи в следующий раз." << std::endl;
  }
}

/**
 * @brief Загружает игровое поле (карту) из файла.
 *
 * Функция открывает файл по указанному пути и загружает значения в двумерный
 * массив, представляющий игровое поле (карту) судоку. В случае неудачи при
 * открытии файла выводит сообщение об ошибке и завершает программу.
 *
 * @param board Двумерный массив, представляющий игровое поле (карту) судоку.
 * @param filename Имя файла, из которого загружается игровое поле (карту).
 */
void loadBoard(int board[N][N], const std::string &filename) {
  std::ifstream file(filename);

  if (file.is_open()) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        file >> board[i][j];
      }
    }
    file.close();
  } else {
    std::cerr << "Не удалось открыть файл " << filename << " !" << std::endl;
    exit(1);
  }
}
