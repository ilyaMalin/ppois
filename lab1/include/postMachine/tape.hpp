#ifndef TAPE_HPP

#define TAPE_HPP
#include <vector>
#include <string>
#include <fstream>

/**
 * @brief Представляет ленту машины Поста.
 *
 * Лента хранится в виде последовательности символов.
 * Ячейки используют символы '0' и '1' для обозначения
 * отсутствия и наличия метки соответственно.
 */
class tape
{
private:
    std::vector<char> tape_;

public:
    /**
     * @brief Создаёт пустую ленту.
     */
    tape() = default;

    /**
     * @brief Создаёт ленту из первой строки входного файла.
     */
    tape(std::ifstream &);

    /**
     * @brief Создаёт ленту из строкового представления.
     */
    tape(const std::string &);

    /**
     * @brief Копирует содержимое другой ленты.
     * @return Ссылка на текущий объект.
     */
    tape &operator=(const tape &);

    /**
     * @brief Возвращает количество ячеек ленты.
     */
    int size() const;

    /**
     * @brief Устанавливает метку в указанной ячейке.
     */
    void setMark(const int &);

    /**
     * @brief Удаляет метку из указанной ячейки.
     */
    void removeMark(const int &);

    /**
     * @brief Предоставляет доступ к ячейке ленты по индексу.
     * @return Ссылка на символ выбранной ячейки.
     */
    char &operator[](const int &);

    /**
     * @brief Выводит содержимое ленты в поток.
     */
    friend std::ostream &operator<<(std::ostream &, tape &);

    /**
     * @brief Считывает строку и использует её как содержимое ленты.
     */
    friend std::istream &operator>>(std::istream &, tape &);
};

#endif