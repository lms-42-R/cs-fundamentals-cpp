#include <iostream>
#include <string>
#include "../src/low_level/number_systems/include/number_systems.hpp"

#define TEST(cond, message) \
    if (!(cond)) { \
        std::cerr << "❌ FAIL: " << message << " (" << #cond << ")\n"; \
        return false; \
    } else { \
        std::cout << "  ✅ " << message << "\n"; \
    }

using namespace number_systems;

bool test_conversions() {
    std::cout << "\n🔧 Тест конвертаций:\n";
    
    TEST(decimal_to_binary(42, 8) == "0010'1010", "42 → binary");
    TEST(decimal_to_binary(255, 8) == "1111'1111", "255 → binary");
    TEST(decimal_to_binary(-1, 8) == "1111'1111", "-1 → binary");
    TEST(decimal_to_binary(0, 8) == "0000'0000", "0 → binary");
    
    TEST(decimal_to_hex(42) == "0x2A", "42 → hex");
    TEST(decimal_to_hex(255) == "0xFF", "255 → hex");
    TEST(decimal_to_hex(0) == "0x0", "0 → hex");
    
    return true;
}

bool test_parsing() {
    std::cout << "\n🔧 Тест парсинга:\n";
    
    TEST(parse_number("0b1010") == 10, "0b1010 → 10");
    TEST(parse_number("0b11111111") == 255, "0b11111111 → 255");
    TEST(parse_number("0xFF") == 255, "0xFF → 255");
    TEST(parse_number("0xff") == 255, "0xff → 255 (lowercase)");
    TEST(parse_number("0777") == 511, "0777 → 511");
    TEST(parse_number("123") == 123, "123 → 123");
    
    return true;
}

bool test_bit_operations() {
    std::cout << "\n🔧 Тест битовых операций:\n";
    
    TEST(is_little_endian() == true, "little-endian detection");
    
    // Тест для int8_t (8 бит)
    std::string bits8 = get_bits<int8_t>(42);
    TEST(bits8.length() == 8, "int8_t has 8 bits");
    
    // Тест для int32_t (32 бита = 4 байта × 8 бит)
    std::string bits32 = get_bits<int32_t>(0x12345678, false); // без пробелов
    TEST(bits32.length() == 32, "int32_t has 32 bits");
    
    // Проверка two's complement
    TEST(get_twos_complement(42, 8) == 214, "two's complement of 42 (8-bit)");
    TEST(get_twos_complement(1, 8) == 255, "two's complement of 1 (8-bit)");
    
    return true;
}

bool test_hex_dump() {
    std::cout << "\n🔧 Тест hex-дампа:\n";
    
    std::string test_data = "ABC";
    std::string dump = hex_dump(test_data.data(), test_data.size());
    
    TEST(!dump.empty(), "hex_dump returns non-empty string");
    TEST(dump.find("41 42 43") != std::string::npos, "hex dump contains ABC");
    
    return true;
}

int main() {
    std::cout << "🧪 Запуск тестов для number_systems\n";
    std::cout << "====================================\n";
    
    int passed = 0;
    int total = 0;
    
    auto run_test = [&](bool result, const std::string& name) {
        total++;
        if (result) {
            passed++;
            std::cout << "🎉 Тест '" << name << "' пройден\n";
        } else {
            std::cout << "💥 Тест '" << name << "' не пройден\n";
        }
        return result;
    };
    
    bool all_passed = true;
    all_passed &= run_test(test_conversions(), "Конвертации");
    all_passed &= run_test(test_parsing(), "Парсинг");
    all_passed &= run_test(test_bit_operations(), "Битовые операции");
    all_passed &= run_test(test_hex_dump(), "Hex-дамп");
    
    std::cout << "\n====================================\n";
    std::cout << "📊 Результат: " << passed << "/" << total << " тестов пройдено\n";
    
    if (all_passed) {
        std::cout << "🎊 Все тесты успешно пройдены!\n";
        return 0;
    } else {
        std::cout << "⚠️  Некоторые тесты не пройдены\n";
        return 1;
    }
}