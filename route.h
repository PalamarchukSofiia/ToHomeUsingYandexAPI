#pragma once

#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <filesystem>
#include <chrono>
#include <thread>


class Route
{

private:

    const std::string API_KEY = "тут должен быть апишник";
    nlohmann::json jsonResponseArr;
    nlohmann::json jsonResponseBack;

public:

    std::string DateArr;
    std::string DateBack;

    void jRoutes(const std::string& date, const std::string stationStart, const std::string stationFinish, const std::string FlagOriente);
    void jParse(const std::string FlagOriente);

    void IsThereFile(const std::string& filePath, const std::string& Flag);
    void Fdeleter(const std::string& filePath, int seconds);
    
};

