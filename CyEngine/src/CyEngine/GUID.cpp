#include "cypch.h"
#include "GUID.h"
#include <iostream>
#include <random>
#include <sstream>
#include <iomanip>

namespace Cy
{
    std::string generate_guid()
    {
        // Create a random number generator
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 15);

        // Generate the GUID
        std::stringstream ss;
        for (int i = 0; i < 8; i++) {
            ss << std::hex << dis(gen);
        }
        ss << "-";
        for (int i = 0; i < 4; i++) {
            ss << std::hex << dis(gen);
        }
        ss << "-4";
        for (int i = 0; i < 3; i++) {
            ss << std::hex << dis(gen);
        }
        ss << "-";
        ss << std::hex << dis(gen) % 4 + 8;
        for (int i = 0; i < 3; i++) {
            ss << std::hex << dis(gen);
        }
        ss << "-";
        for (int i = 0; i < 12; i++) {
            ss << std::hex << dis(gen);
        }

        // Return the GUID as a string
        return ss.str();
    }

    GUID Cy::GUID::Make()
    {
        GUID guid;
        guid.Value = generate_guid();
        return guid;
    }
}
