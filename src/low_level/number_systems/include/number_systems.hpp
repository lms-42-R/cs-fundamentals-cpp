#ifndef NUMBER_SYSTEMS_HPP
#define NUMBER_SYSTEMS_HPP

#include <string>
#include <cstdint>
#include <vector>

namespace number_systems {

/**
 * @brief Конвертирует десятичное число в двоичную строку
 * @param number Десятичное число
 * @param bits Количество бит для отображения (0 = auto)
 * @return Двоичная строка (например, "101010")
 */
std::string decimal_to_binary(int64_t number, size_t bits = 0);

/**
 * @brief Конвертирует десятичное число в шестнадцатеричную строку
 * @param number Десятичное число
 * @param prefix Добавить префикс "0x"
 * @return Шестнадцатеричная строка (например, "2A" или "0x2A")
 */
std::string decimal_to_hex(int64_t number, bool prefix = true);

/**
 * @brief Конвертирует строку в число с автоопределением системы
 * @param str Строка ("0b1010", "0xFF", "123")
 * @return Десятичное число
 */
int64_t parse_number(const std::string& str);

/**
 * @brief Показывает hex-дамп области памяти
 * @param data Указатель на данные
 * @param size Размер данных в байтах
 * @param bytes_per_line Байт на строку (обычно 16)
 * @return Строка с hex-дампом
 */
std::string hex_dump(const void* data, size_t size, size_t bytes_per_line = 16);

/**
 * @brief Возвращает битовое представление числа
 * @param number Число для анализа
 * @param show_bytes Показывать разделение по байтам
 * @return Строка с битами (например, "00101010")
 */
template<typename T>
std::string get_bits(T number, bool show_bytes = true);

/**
 * @brief Проверяет endianness системы
 * @return true если little-endian
 */
bool is_little_endian();

/**
 * @brief Получает two's complement отрицательного числа
 * @param value Абсолютное значение отрицательного числа
 * @param bits Количество бит
 * @return Беззнаковое представление
 */
uint64_t get_twos_complement(uint64_t value, size_t bits);

} // namespace number_systems

#endif // NUMBER_SYSTEMS_HPP