#ifndef STORAGEMULTISET_HPP

#define STORAGEMULTISET_HPP
#include "multiset.hpp"

/**
 * @brief Хранилище мультимножеств, доступных по строковым именам.
 */
class storageMultiset
{
private:
    std::map<std::string, multiset> storage;

public:
    /**
     * @brief Получает мультимножество по имени.
     * @return Ссылка на сохранённое мультимножество.
     */
    multiset &operator[](const std::string &);

    /**
     * @brief Добавляет мультимножество в хранилище.
     * @return true, если имя добавлено; false, если оно уже существует.
     */
    bool insert(const std::string &, const multiset &);

    /**
     * @brief Удаляет мультимножество по имени.
     * @return true, если элемент найден и удалён; иначе false.
     */
    bool remove(const std::string &);

    /**
     * @brief Проверяет, пусто ли хранилище.
     * @return true, если хранилище не содержит элементов.
     */
    bool empty() const;

    /**
     * @brief Возвращает итератор на первый элемент хранилища.
     */
    std::map<std::string, multiset>::iterator begin();

    /**
     * @brief Возвращает итератор за последним элементом хранилища.
     */
    std::map<std::string, multiset>::iterator end();
};

#endif