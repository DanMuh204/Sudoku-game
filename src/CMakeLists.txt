cmake_minimum_required(VERSION 3.10.0)

# Добавляем исполняемый файл для тестов
add_executable(sudoku-test sudoku.cpp sudoku_tests.cpp)
target_link_libraries(sudoku-test PUBLIC doctest default)
add_test(NAME sudoku-test COMMAND sudoku-test --force-colors -d)
add_custom_target(cloud-test COMMAND sudoku-test --force-colors -d)

# Добавляем основной исполняемый файл
add_executable(sudoku main.cpp sudoku.cpp)
target_link_libraries(sudoku PUBLIC default)
