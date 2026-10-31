#ifndef TYPE_HPP

#define TYPE_HPP
#include <iostream>
#include <memory>
#include <string>

/**
 * @brief Предварительное объявление класса мультимножества.
 */
class multiset;

/**
 * @brief Представляет элемент, который может содержать строку или мультимножество.
 */
class element
{
private:
    std::unique_ptr<std::string> stringValue = nullptr;
    std::unique_ptr<multiset> setValue;

public:
    /**
     * @brief Создаёт элемент без значения.
     */
    element();

    /**
     * @brief Очищает память, занятую под элемент
     */
    ~element();

    /**
     * @brief Создаёт копию другого элемента.
     */
    element(const element &);

    /**
     * @brief Копирует значение другого элемента.
     * @return Ссылка на текущий объект.
     */
    element &operator=(const element &);

    /**
     * @brief Получает указатель на строковое значение.
     * @return Указатель на строку или nullptr, если строкового значения нет.
     */
    std::string *getStringValue() const;

    /**
     * @brief Получает указатель на вложенное мультимножество.
     * @return Указатель на мультимножество или nullptr, если его нет.
     */
    multiset *getSetValue() const;

    /**
     * @brief Устанавливает строковое значение элемента.
     */
    void setStringValue(const std::string &);

    /**
     * @brief Устанавливает строковое значение из строки в формате C.
     */
    void setStringValue(const char *);

    /**
     * @brief Устанавливает вложенное мультимножество.
     */
    void setSetValue(const multiset &);

    /**
     * @brief Проверяет равенство двух элементов.
     * @return true, если значения элементов равны и имеют одинаковый тип.
     */
    bool operator==(const element &) const;

    /**
     * @brief Сравнивает элементы оператором меньше.
     *
     * Строковые элементы располагаются после элементов-мультимножеств.
     * Элементы одного типа сравниваются по их значениям.
     * @return Результат сравнения.
     */
    bool operator<(const element &) const;

    /**
     * @brief Сравнивает элементы оператором больше.
     * @return true, если текущий элемент больше другого.
     */
    bool operator>(const element &) const;

    /**
     * @brief Выводит значение элемента в поток.
     * @return Ссылка на выходной поток.
     */
    friend std::ostream &operator<<(std::ostream &, const element &);
};

#endif