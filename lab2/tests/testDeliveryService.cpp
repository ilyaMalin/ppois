#include <UnitTest++/UnitTest++.h>
#include "registration/deliveryService.hpp"
#include <string>

TEST(deliveryServiceTest)
{
    deliveryService value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateDeliveryService());
    deliveryService invalid("", "");
    CHECK(!invalid.validateDeliveryService());
    value.activateDeliveryService();
    CHECK_EQUAL(std::string("activatedeliveryservice"), value.getStatus());
}
