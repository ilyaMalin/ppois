#ifndef POSTMACHINE_HPP

#define POSTMACHINE_HPP
#include "rule.hpp"
#include "tape.hpp"

/**
 * @brief Представляет программу машины Поста.
 *
 * Хранит последовательность команд и ленту, над которой выполняются
 * операции.
 */
class programm
{
private:
    bool flog = false;
    std::vector<rule> rule_;
    tape tape_;

    /**
     * @brief Разбирает строковое представление одной команды.
     */
    void parser(const std::string &, ALPHABET &, int &, int &);

    /**
     * @brief Разбирает последовательность строк с командами.
     */
    void parser(std::vector<std::string> &);

    /**
     * @brief Считывает команды из входного файла.
     */
    void parser(std::ifstream &);

    /**
     * @brief Выполняет одну команду программы.
     *
     * Обновляет позицию каретки и номер следующей команды
     * в соответствии с символом текущего правила.
     * @return false при выполнении команды остановки, иначе true.
     */
    bool step(int &, int &);

public:
    /**
     * @brief Создаёт программу со значениями по умолчанию.
     */
    programm() = default;

    /**
     * @brief Создаёт программу, считывая ленту и команды из файла.
     */
    programm(std::ifstream &);

    /**
     * @brief Создаёт программу из строкового представления ленты
     * и последовательности строк с командами.
     */
    programm(const std::string &, std::vector<std::string> &);

    /**
     * @brief Копирует команды и ленту другой программы.
     * @return Ссылка на текущий объект.
     */
    programm &operator=(const programm &);

    /**
     * @brief Возвращает текущее значение флага flog.
     */
    bool getFlog() const;

    /**
     * @brief Проверяет, не содержит ли программа команд и ячеек ленты.
     */
    bool empty();

    /**
     * @brief Разбирает строку и добавляет соответствующую команду.
     */
    void append(const std::string &);

    /**
     * @brief Добавляет готовое правило в программу.
     */
    void append(const rule &);

    /**
     * @brief Удаляет команду по индексу.
     */
    void remove(const int &);

    /**
     * @brief Выводит все правила программы.
     */
    void viewRule() const;

    /**
     * @brief Выводит текущее содержимое ленты.
     */
    void viewTape();

    /**
     * @brief Инвертирует значение флага flog.
     */
    void changeFlog();

    /**
     * @brief Выполняет программу машины Поста.
     *
     * Выполнение начинается с первой команды и первой ячейки ленты.
     * При включённом параметре flog состояние ленты выводится
     * после каждой успешно выполненной команды.
     * После завершения программы текущее состояние ленты выводится
     * независимо от значения параметра.
     */
    void performOperations(bool);
};

#endif