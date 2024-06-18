#ifndef SUDOKU_H
#define SUDOKU_H

#include <string>

/**
 * @file sudoku.h
 * @brief Файл-хэдер
 *
 * Здесь объявляются функции консольной игры судоку.
 *
 * @bug Нет известных багов
 */

/// Размер поля судоку (9x9)
const int N = 9;

/**
 * @brief Функция проверяет, можно ли поместить число в указанную пользователем
 * ячейку.
 *
 * @param board Игровое поле.
 * @param row Строка ячейки.
 * @param col Столбец ячейки.
 * @param num Число для проверки.
 * @return true, если можно поместить число, false в противном случае.
 */
bool isSafe(int board[N][N], int row, int col, int num);

/**
 * @brief Выводит игровое поле на экран.
 *
 * @param grid Игровое поле.
 */
void printBoard(int grid[N][N]);

/**
 * @brief Решает судоку.
 *
 * @param board Игровое поле.
 * @param row Начальная строка.
 * @param col Начальный столбец.
 * @return true, если судоку решено, false в ином случае.
 */
bool solveSudoku(int board[N][N], int row, int col);

/**
 * @brief Проверяет, полностью ли решено судоку.
 *
 * @param grid Игровое поле.
 * @return true, если судоку решено, false в ином случае.
 */
bool isSolvedCompletely(int grid[N][N]);

/**
 * @brief Сохраняет текущее состояние игрового поля в файл.
 *
 * @param board Игровое поле.
 * @param filename Имя файла для сохранения.
 */
void saveBoard(int board[N][N], const std::string &filename);

/**
 * @brief Загружает игровое поле из файла.
 *
 * @param board Игровое поле.
 * @param filename Имя файла для загрузки.
 */
void loadBoard(int board[N][N], const std::string &filename);

/**
 * @brief Начинает игру с текущим игровым полем.
 *
 * @param board Игровое поле.
 */
void playGame(int board[N][N]);

#endif
