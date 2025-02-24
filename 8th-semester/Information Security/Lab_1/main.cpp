#include <iostream>
#include <cstdlib> //std::srand() и std::rand()
#include <ctime> //std::time()
#include <string>

//ГПСЧ для генерации случайных чисел в заданном диапазоне.
static int getRandomNumber(int min, int max) {
    return min + std::rand() % (max - min + 1);
}

//Функция для генерации случайного пароля.
static std::string generatePassword(int length) {
    const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZабвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    std::string password = "";
    for (int i{}; i < length; ++i) {
        int randomIndex = getRandomNumber(0, alphabet.size() - 1); //Случайный индекс из alphabet.
        password += alphabet[randomIndex];
    }
    return password;
}

int main() {
    setlocale(LC_ALL, "Rus");
    //std::srand() используется в std::rand(), разные последовательности случайных чисел.
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    //Количество и длина паролей.
    const int count{ 20 };
    const int length{ 6 };

    //Генерация 20 паролей длиной 6 символов.
    for (int i{}; i < count; ++i)
        std::cout << generatePassword(length) << "\n";

    return 0;
}
