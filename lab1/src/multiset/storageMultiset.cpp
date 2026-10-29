#include "storageMultiset.hpp"

bool storageMultiset::insert(const std::string &nameSet, const multiset &otherSet)
{
    auto inserted = this->storage.try_emplace(nameSet, otherSet);
    return inserted.second;
}

bool storageMultiset::empty() const
{
    return this->storage.empty();
}

bool storageMultiset::remove(const std::string &nameSet)
{
    auto iterator = this->storage.find(nameSet);

    if (iterator != this->storage.end())
    {
        this->storage.erase(iterator);
        return true;
    }

    return false;
}

multiset &storageMultiset::operator[](const std::string &nameSet)
{
    auto iterator = this->storage.find(nameSet);

    try
    {
        return iterator->second;
    }
    catch (const std::exception &)
    {
        throw std::runtime_error("Out of range!");
    }
}

std::map<std::string, multiset>::iterator storageMultiset::begin()
{
    return this->storage.begin();
}

std::map<std::string, multiset>::iterator storageMultiset::end()
{
    return this->storage.end();
}