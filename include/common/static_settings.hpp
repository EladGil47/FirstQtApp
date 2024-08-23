#ifndef STATIC_SETTINGS_HPP
#define STATIC_SETTINGS_HPP

#include <cstdint>
#include <memory>
#include <vector>
#include "settings.hpp"

class StaticSettings
{
public:
    static void init(std::shared_ptr<Settings> settings);

    // Static member variables
    static std::vector<int32_t> players_in_team_range;
    static std::vector<int32_t> team_range;
};

#endif // STATIC_SETTINGS_HPP
