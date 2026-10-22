#ifndef POSTMACHINE_HPP

#define POSTMACHINE_HPP
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

/**
 * @brief Символы команд машины Поста.

 * Каждому символу соответствует определённая операция над лентой
 * или управление выполнением программы.
 */
enum class ALPHABET
{
    /** @brief Установить метку в текущей ячейке. */
    SETMARK = 'V',

    /** @brief Удалить метку из текущей ячейки. */
    REMOVEMARK = 'X',

    /** @brief Переместить каретку вправо. */
    RIGHT = 'R',

    /** @brief Переместить каретку влево. */
    LEFT = 'L',

    /**
     * @brief Условный переход.
     *
     * Если текущая ячейка содержит '0', выполняется основной переход,
     * иначе выполняется альтернативный переход.
     */
    IF = '?',

    /** @brief Остановить выполнение программы. */
    STOP = '!'
};

/**
 * @brief Представляет одну команду машины Поста.
 *
 * Хранит символ команды и номера следующей команды,
 * включая альтернативный переход для условной команды.
 */
class rule
{
private:
    ALPHABET symbol;
    int numberNextCommand = -1;
    int altNumberNextCommand = -1;

public:
    /**
     * @brief Создаёт правило со значениями по умолчанию.
     */
    rule() = default;

    /**
     * @brief Копирует данные другого правила.
     * @return Ссылка на текущий объект.
     */
    rule &operator=(const rule &);

    /**
     * @brief Задаёт символ команды и номера переходов.
     *
     * Альтернативный переход используется условной командой.
     */
    void setRule(ALPHABET &, const int &, const int &);

    /**
     * @brief Возвращает символ команды.
     */
    ALPHABET getSymbol() const;

    /**
     * @brief Возвращает номер следующей команды.
     */
    int getNextCommand() const;

    /**
     * @brief Возвращает номер альтернативной команды.
     */
    int getAltNextCommand() const;

    /**
     * @brief Выводит правило в поток.
     *
     * Для условной команды также выводится альтернативный переход,
     * отделённый точкой с запятой.
     */
    friend std::ostream &operator<<(std::ostream &, const rule &);
};

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