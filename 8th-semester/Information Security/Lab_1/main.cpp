#include <iostream>
#include <cstdlib> //std::srand() � std::rand()
#include <ctime> //std::time()
#include <string>

//���� ��� ��������� ��������� ����� � �������� ���������.
static int getRandomNumber(int min, int max) {
    return min + std::rand() % (max - min + 1);
}

//������� ��� ��������� ���������� ������.
static std::string generatePassword(int length) {
    const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ��������������������������������";
    std::string password = "";
    for (int i{}; i < length; ++i) {
        int randomIndex = getRandomNumber(0, alphabet.size() - 1); //��������� ������ �� alphabet.
        password += alphabet[randomIndex];
    }
    return password;
}

int main() {
    setlocale(LC_ALL, "Rus");
    //std::srand() ������������ � std::rand(), ������ ������������������ ��������� �����.
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    //���������� � ����� �������.
    const int count{ 20 };
    const int length{ 6 };

    //��������� 20 ������� ������ 6 ��������.
    for (int i{}; i < count; ++i)
        std::cout << generatePassword(length) << "\n";

    return 0;
}
