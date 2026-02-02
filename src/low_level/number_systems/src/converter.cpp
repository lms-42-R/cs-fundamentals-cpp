#include "number_systems.hpp"
#include <sstream>
#include <iomanip>
#include <bitset>
#include <algorithm>

namespace number_systems {

std::string decimal_to_binary(int64_t number, size_t bits) {
    if (bits == 0) {
        // Автоопределение минимального количества бит
        if (number == 0) return "0";
        
        int64_t temp = (number < 0) ? -number : number;
        bits = 0;
        while (temp > 0) {
            temp >>= 1;
            bits++;
        }
        // +1 бит для знака если отрицательное
        if (number < 0) bits++;
        // Минимум 8 бит для читаемости
        if (bits < 8) bits = 8;
    }
    
    if (bits <= 64) {
        uint64_t mask = (1ULL << bits) - 1;
        uint64_t value = (number < 0) ? get_twos_complement(-number, bits) : number;
        value &= mask;
        
        std::string result;
        for (int i = bits - 1; i >= 0; i--) {
            result += ((value >> i) & 1) ? '1' : '0';
            if (i % 4 == 0 && i != 0) result += '\'';
        }
        return result;
    }
    
    return std::bitset<64>(number).to_string();
}

std::string decimal_to_hex(int64_t number, bool prefix) {
    std::stringstream ss;
    
    if (number < 0) {
        // Для отрицательных показываем two's complement в 64 битах
        uint64_t value = get_twos_complement(-number, 64);
        ss << (prefix ? "0x" : "") << std::hex << std::uppercase << value;
    } else {
        ss << (prefix ? "0x" : "") << std::hex << std::uppercase << number;
    }
    
    return ss.str();
}

int64_t parse_number(const std::string& str) {
    if (str.empty()) return 0;
    
    std::string lower_str = str;
    std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(), ::tolower);
    
    if (lower_str.substr(0, 2) == "0b") {
        // Binary: 0b1010
        return std::stoll(lower_str.substr(2), nullptr, 2);
    } else if (lower_str.substr(0, 2) == "0x") {
        // Hex: 0xFF
        return std::stoll(lower_str.substr(2), nullptr, 16);
    } else if (lower_str[0] == '0' && lower_str.length() > 1) {
        // Octal: 0777
        return std::stoll(lower_str.substr(1), nullptr, 8);
    } else {
        // Decimal: 123
        return std::stoll(lower_str);
    }
}

std::string hex_dump(const void* data, size_t size, size_t bytes_per_line) {
    const unsigned char* bytes = static_cast<const unsigned char*>(data);
    std::stringstream ss;
    
    for (size_t i = 0; i < size; i += bytes_per_line) {
        // Адрес
        ss << std::hex << std::setw(8) << std::setfill('0') << i << "  ";
        
        // Hex данные
        for (size_t j = 0; j < bytes_per_line; j++) {
            if (i + j < size) {
                ss << std::hex << std::setw(2) << std::setfill('0') 
                   << static_cast<int>(bytes[i + j]) << " ";
            } else {
                ss << "   ";
            }
            if (j == bytes_per_line/2 - 1) ss << " "; // Разделитель
        }
        
        // ASCII представление
        ss << " |";
        for (size_t j = 0; j < bytes_per_line && i + j < size; j++) {
            unsigned char c = bytes[i + j];
            ss << (c >= 32 && c < 127 ? static_cast<char>(c) : '.');
        }
        ss << "|\n";
    }
    
    return ss.str();
}

template<typename T>
std::string get_bits(T number, bool show_bytes) {
    std::string result;
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&number);
    size_t size = sizeof(T);
    
    // Для little-endian показываем байты в обратном порядке
    if (is_little_endian()) {
        for (int i = size - 1; i >= 0; i--) {
            std::bitset<8> byte(bytes[i]);
            result += byte.to_string();
            if (show_bytes && i > 0) result += " ";
        }
    } else {
        for (size_t i = 0; i < size; i++) {
            std::bitset<8> byte(bytes[i]);
            result += byte.to_string();
            if (show_bytes && i < size - 1) result += " ";
        }
    }
    
    return result;
}

bool is_little_endian() {
    uint32_t test = 0x12345678;
    uint8_t* bytes = reinterpret_cast<uint8_t*>(&test);
    return bytes[0] == 0x78;
}

uint64_t get_twos_complement(uint64_t value, size_t bits) {
    if (bits >= 64) {
        return ~value + 1;
    }
    uint64_t mask = (1ULL << bits) - 1;
    return (~value + 1) & mask;
}

// Явная инстанциация шаблона для часто используемых типов
template std::string get_bits<int8_t>(int8_t, bool);
template std::string get_bits<uint8_t>(uint8_t, bool);
template std::string get_bits<int32_t>(int32_t, bool);
template std::string get_bits<uint32_t>(uint32_t, bool);
template std::string get_bits<int64_t>(int64_t, bool);
template std::string get_bits<uint64_t>(uint64_t, bool);
template std::string get_bits<float>(float, bool);
template std::string get_bits<double>(double, bool);

} // namespace number_systems