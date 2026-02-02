#include "number_systems.hpp"
#include <iostream>
#include <vector>
#include <string>

int main() {
    using namespace number_systems;
    
    std::cout << "=== Демонстрация систем счисления ===\n\n";
    
    // 1. Конвертация чисел
    std::cout << "1. Конвертация чисел:\n";
    int numbers[] = {42, -42, 255, -128, 0};
    
    for (int n : numbers) {
        std::cout << "  " << n << " = " 
                  << decimal_to_binary(n, 8) << " (bin) = "
                  << decimal_to_hex(n) << " (hex)\n";
    }
    
    // 2. Парсинг разных форматов
    std::cout << "\n2. Парсинг строк:\n";
    std::string inputs[] = {"0b101010", "0xFF", "0777", "123", "-42"};
    
    for (const auto& str : inputs) {
        std::cout << "  " << str << " = " << parse_number(str) << "\n";
    }
    
    // 3. Hex-дамп
    std::cout << "\n3. Hex-дамп строки:\n";
    std::string test_str = "Hello, Computer Science!";
    std::cout << hex_dump(test_str.data(), test_str.size());
    
    // 4. Битовое представление
    std::cout << "\n4. Битовое представление:\n";
    float pi = 3.14159f;
    std::cout << "  float pi = " << pi << "\n";
    std::cout << "  БитЫ: " << get_bits(pi, true) << "\n";
    
    // 5. Endianness
    std::cout << "\n5. Endianness системы:\n";
    std::cout << "  Система " << (is_little_endian() ? "little-endian" : "big-endian") << "\n";
    
    // 6. Two's complement
    std::cout << "\n6. Two's complement:\n";
    int8_t negative = -42;
    std::cout << "  int8_t -42 = " << get_bits(negative) 
              << " = " << decimal_to_hex(negative) << "\n";
    
    std::cout << "\n=== Демонстрация завершена ===\n";
    return 0;
}