#pragma once

#include <string>
#include "common/forward.hpp"

class digitalSignature
{
    std::string id;
    std::string name;
    std::string status;
    certificate *certificateRef = nullptr;

public:
    digitalSignature(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool validateSignature() const;
    void signDocument();
    void linkCertificate(certificate &);
};
