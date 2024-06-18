#include "sudoku.h"
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>
#include <string>

/**
 * @mainpage Судоку
 *
 * Это консольная игра судоку, в которой имеются сохранения, загрузки и простые
 * карты, заранее записанные в файлы.
 * Все файлы с кодом оформлены в стиле LLVM.
 */

/**
 * @file   main.cpp
 * @brief  Основной файл для игры судоку
 *
 * Этот файл содержит основную функцию, которая инициализирует игру,
 * загружает игровое поле из файла или настраивает новую игру, а также
 * предоставляет меню для взаимодействия с игрой.
 *
 * @bug    Нет известных багов
 */

/**
 * @brief Основная функция, запускающая игру Судоку.
 *
 * Эта функция инициализирует игру, загружает сохраненное поле или настраивает
 * новое, предоставляет меню для выбора действий и управления игровым процессом.
 *
 * @return Код возврата. 0 при успешном завершении, 1 при ошибках.
 */
int main() {

  std::filesystem::current_path(
      "Sudoku/src"); // Переход в рабочую директорию проекта

  std::string difficulty;
  std::string level;
  int board[N][N];
  std::string choice;

  std::cout << "Хотите ли вы загрузить сохранение (yes/no): ";
  std::cin >> choice;

  if (choice == "yes") {
    std::string saveFilename;
    std::cout << "Введите имя файла сохранения (без расширения): ";
    std::cin >> saveFilename;
    loadBoard(board, "saves/" + saveFilename + ".txt");
  } else {
    std::cout << "Выберите сложность (E - Easy (Легко), N - Normal (Средняя), "
                 "H - Hard (Сложная)): ";
    std::cin >> difficulty;
    std::cout << "Выберите уровень: 1, 2 или 3: ";
    std::cin >> level;

    std::set<std::string> difficultySet = {"E", "N", "H"};
    std::set<std::string> levelSet = {"1", "2", "3"};

    if (difficultySet.find(difficulty) != difficultySet.end()) {
      if (levelSet.find(level) != levelSet.end()) {
        loadBoard(board, "maps/map" + difficulty + level + ".txt");
      } else {
        std::cerr << "Введено неккоректное значение уровня!" << std::endl;
        return 1;
      }
    } else {
      std::cerr << "Введена неккоректная сложность!" << std::endl;
      return 1;
    }
  }

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

  while (true) {
    int choice;
    std::cout << std::endl << std::endl;
    std::cout << "\t\t[1] Начать решение судоку" << std::endl;
    std::cout << "\t\t[2] Не можете решить? Посмотреть решенённое судоку"
              << std::endl;
    std::cout << "\t\t[3] Выход" << std::endl;
    std::cout << "\t\tВведите ваш выбор: ";
    std::cin >> choice;

    switch (choice) {
    case 1:
      playGame(board);
      break;
    case 2:
      if (solveSudoku(board, 0, 0)) {
        std::cout << "Полностью решённое судоку: " << std::endl;
        std::cout << std::endl << std::endl;
        for (int row = 0; row < N; row++) {
          for (int col = 0; col < N; col++) {
            if (col == 3 || col == 6)
              std::cout << " | ";
            std::cout << board[row][col] << " ";
          }
          if (row == 2 || row == 5) {
            std::cout << std::endl;
            for (int i = 0; i < N; i++)
              std::cout << "---";
          }
          std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << "Удачи в следующий раз!!!" << std::endl;
      } else
        std::cout << "Не найдено решения (при решении вы допустили ошибку)"
                  << std::endl;
      break;
    case 3:
      exit(0);
    default:
      std::cout << "Введено неккоректное действие" << std::endl;
    }
  }
  return 0;
}
