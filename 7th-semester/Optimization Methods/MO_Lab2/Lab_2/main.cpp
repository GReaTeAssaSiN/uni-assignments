#include <iostream>
#include "myfuncs.h"

int main() {
    setlocale(LC_ALL, "Rus");

    // Открытие файла для вывода результатов
    std::ofstream results_file_first("results_first.txt");
    if (!results_file_first.is_open()) {
        std::cerr << "Не удалось открыть файл для записи!" << std::endl;
        return 1;
    }
    std::ofstream results_file_second("results_second.txt");
    if (!results_file_second.is_open()) {
        std::cerr << "Не удалось открыть файл для записи!" << std::endl;
        return 1;
    }

    // ЗАДАНИЕ
    results_file_first << "ЗАДАНИЕ:\n"
        << "Минимизировать функцию F(X) = 5*x1^2 + 5*x2^2 + 8*x1*x2, используя в качестве начального многогранник "
        << "с вершинами X1=(-1;4)^T, X2=(-1;8)^T, X3=(-3;6)^T."
        << std::endl;
    // ЗАДАНИЕ
    results_file_second << "ЗАДАНИЕ:\n"
        << "Минимизировать функцию F(X) = 5*x1^2 + 5*x2^2 + 8*x1*x2, используя в качестве начального многогранник "
        << "с вершинами X1=(-1;4)^T, X2=(-1;8)^T, X3=(-3;6)^T."
        << std::endl;

    // ПОИСК ПО ПРАВИЛЬНОМУ СИМПЛЕКСУ
    results_file_first << "ПОИСК ПО ПРАВИЛЬНОМУ СИМПЛЕКСУ." << std::endl;

    // Вызовы с различными параметрами.
    perform_search_first(results_file_first, 1e-1, 1.0);
    perform_search_first(results_file_first, 1e-2, 1.0);
    perform_search_first(results_file_first, 1e-3, 1.0);
    perform_search_first(results_file_first, 1e-3, 0.5);
    perform_search_first(results_file_first, 1e-3, 2.0);

    // ПОИСК ПО ДЕФОРМИРУЕМОМУ МНОГОГРАННИКУ.
    results_file_second << "ПОИСК ПО ДЕФОРМИРУЕМОМУ МНОГОГРАННИКУ." << std::endl;
    // Вызовы с различными параметрами.
    perform_search_second(results_file_second, 1e-1, 1, 0.4, 2);
    perform_search_second(results_file_second, 1e-2, 1, 0.4, 2);
    perform_search_second(results_file_second, 1e-3, 1, 0.4, 2);

    // Закрытие файла для вывода результатов
    results_file_first.close();
    results_file_second.close();
    return 0;
}