#ifndef BLANKPAGE_HPP

#define BLANKPAGE_HPP
#include <string>
#include <fstream>
#include <memory>

class blankPage
{
private:
    std::string _path;
    std::unique_ptr<blankPage> _prevPage;
    std::unique_ptr<blankPage> _nextPage;

public:
    blankPage(const std::string, blankPage *, blankPage *);
};

#endif