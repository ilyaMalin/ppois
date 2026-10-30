#ifndef MULTISET_HPP

#define MULTISET_HPP
#include "type.hpp"
#include <map>

/**
 * @brief Класс мультимножества.
 *
 * Хранит элементы и количество вхождений каждого элемента.
 */
class multiset
{
private:
    std::map<element, size_t> multiplicity;
    size_t cardinal = 0;

    /**
     * @brief Разбирает строковое представление мультимножества.
     */
    bool parser(const std::string &, int &);

public:
    /**
     * @brief Создаёт пустое мультимножество.
     */
    multiset() = default;

    /**
     * @brief Создаёт мультимножество из строки в формате C.
     */
    explicit multiset(const char *);

    /**
     * @brief Создаёт мультимножество из строки.
     */
    explicit multiset(const std::string &);

    /**
     * @brief Создаёт мультимножество, содержащее один элемент.
     */
    explicit multiset(const element &);

    /**
     * @brief Создаёт копию другого мультимножества.
     */
    multiset(const multiset &);

    /**
     * @brief Копирует содержимое другого мультимножества.
     * @return Ссылка на текущий объект.
     */
    multiset &operator=(const multiset &);

    /**
     * @brief Проверяет, пусто ли мультимножество.
     * @return true, если мощность равна нулю.
     */
    bool empty() const;

    /**
     * @brief Добавляет одно вхождение элемента.
     */
    void insert(const element &);

    /**
     * @brief Добавляет другое мультимножество как один вложенный элемент.
     */
    void insert(const multiset &);

    /**
     * @brief Удаляет одно вхождение элемента, если он присутствует.
     */
    void remove(const element &);

    /**
     * @brief Возвращает мощность мультимножества.
     * @return Общее количество вхождений всех элементов.
     */
    size_t cardinality() const;

    /**
     * @brief Проверяет наличие элемента в мультимножестве.
     * @return true, если элемент присутствует хотя бы один раз.
     */
    bool operator[](const element &) const;

    /**
     * @brief Объединяет мультимножества, выбирая максимальную кратность
     * каждого элемента.
     * @return Новое мультимножество, содержащее результат операции.
     */
    multiset operator+(const multiset &);

    /**
     * @brief Объединяет мультимножества с изменением текущего объекта.
     * @return Ссылка на текущий объект.
     */
    multiset &operator+=(const multiset &);

    /**
     * @brief Пересекает мультимножества, выбирая минимальную кратность
     * общих элементов.
     * @return Новое мультимножество, содержащее результат операции.
     */
    multiset operator*(const multiset &);

    /**
     * @brief Выполняет пересечение с изменением текущего объекта.
     * @return Ссылка на текущий объект.
     */
    multiset &operator*=(const multiset &);

    /**
     * @brief Вычитает кратности элементов второго мультимножества
     * из кратностей текущего.
     * @return Новое мультимножество, содержащее результат операции.
     */
    multiset operator-(const multiset &);

    /**
     * @brief Выполняет вычитание с изменением текущего объекта.
     * @return Ссылка на текущий объект.
     */
    multiset &operator-=(const multiset &);

    /**
     * @brief Проверяет равенство мультимножеств по элементам и кратностям.
     * @return true, если мультимножества равны.
     */
    bool operator==(const multiset &) const;

    /**
     * @brief Проверяет неравенство мультимножеств.
     * @return true, если мультимножества не равны.
     */
    bool operator!=(const multiset &) const;

    /**
     * @brief Сравнивает мультимножества по мощности,
     * а при равной мощности — по содержимому.
     * @return Результат сравнения.
     */
    bool operator<(const multiset &) const;

    /**
     * @brief Сравнивает мультимножества по мощности,
     * а при равной мощности — по содержимому.
     * @return Результат сравнения.
     */
    bool operator>(const multiset &) const;

    /**
     * @brief Строит булеан мультимножества.
     * @return Мультимножество, элементы которого представляют
     * подмультимножества исходного мультимножества.
     */
    multiset buildBoolean();

    /**
     * @brief Выводит мультимножество в поток в фигурных скобках.
     * @return Ссылка на выходной поток.
     */
    friend std::ostream &operator<<(std::ostream &, const multiset &);

    /**
     * @brief Считывает строковое представление мультимножества из потока.
     * @return Ссылка на входной поток.
     */
    friend std::istream &operator>>(std::istream &, multiset &);
};

#endif