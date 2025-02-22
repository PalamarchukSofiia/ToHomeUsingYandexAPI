#include "route.h"

void Route::jRoutes(const std::string& date, const std::string stationStart, const std::string stationFinish, const std::string FlagOriente) {

    std::string filePath = "./cache/" + FlagOriente + "_" + date + ".json";

    IsThereFile(filePath,FlagOriente);

    cpr::Response response = cpr::Get(
        cpr::Url{"https://api.rasp.yandex.net/v3.0/search/"},
        cpr::Parameters{
            {"apikey", API_KEY},
            {"from", stationStart},
            {"to", stationFinish},
            {"date", date},
            {"transport_types", "plane,train,bus"},
            {"format", "json"},
            {"transfers", "true"}
        }
    );

    if (response.status_code != 200) {
        std::cerr << "Ошибка запроса: " << response.status_code << "\n";
        return;
    }

    nlohmann::json jsonResponse = nlohmann::json::parse(response.text);

    if (FlagOriente == "Arr")
        jsonResponseArr = jsonResponse;   
    else if(FlagOriente == "Back")
        jsonResponseBack = jsonResponse;  

    std::ofstream outFile(filePath);
    outFile << jsonResponse.dump(4);
    outFile.close();

    std::thread deleter(&Route::Fdeleter, this, filePath, 86400);
    deleter.detach();

}



void Route::jParse(const std::string FlagOriente){

    nlohmann::json jsonResponse;
    if (FlagOriente == "Arr")
        jsonResponse = jsonResponseArr;
    else if (FlagOriente == "Back")
        jsonResponse = jsonResponseBack;

    if (!jsonResponse.contains("segments") || jsonResponse["segments"].empty()) {
        std::cout << "Маршруты не найдены.\n";
        return;
    }

    std::cout << "Маршрут без пересадки:\n";
    for (const auto& segment : jsonResponse["segments"]) {
        if (segment.contains("has_transfers") && segment["has_transfers"] == false) {

            std::cout << "Маршрут: " << segment["from"]["title"] << " -> " << segment["to"]["title"]  << "\n";
            std::cout << "Тип транспорта: " << segment["thread"]["transport_type"]  << "\n";
            std::cout << "Отправление: " << segment["departure"].get<std::string>().substr(0,10) << "\n";
            std::cout << "Время отправления(по местному): " <<  segment["departure"].get<std::string>().substr(11,5) << "\n";
            std::cout << "Прибытие: " << segment["arrival"].get<std::string>().substr(0,10)  << "\n";
            std::cout << "Время прибытия(по местному): " <<  segment["arrival"].get<std::string>().substr(11,5) << "\n";

            std::cout << "-----------------------------------\n";
        }  
        else if (segment.contains("details") && segment["details"].is_array() &&
            segment.contains("transport_types") && segment["transport_types"].size() == 2) { 

            std::cout << "Маршрут с пересадкой:\n";
            for (const auto& tr : segment["details"]) {
                if (tr.contains("from") && tr["from"].contains("title") && tr.contains("to") && tr["to"].contains("title") &&
                    tr.contains("thread") && tr["thread"].contains("transport_type")) {

                    std::cout << tr["from"]["title"]  << " -> ";

                    if (tr.contains("transfer_point") && tr["transfer_point"].contains("title")) {
                        std::cout << tr["transfer_point"]["title"]  << " -> ";
                    }

                    std::cout << tr["to"]["title"]  << "\n";
                    std::cout << "Тип транспорта: " << tr["thread"]["transport_type"]  << "\n";
                    std::cout << "Отправление: " << tr["departure"].get<std::string>().substr(0,10)  << "\n";
                    std::cout << "Время отправления(по местному): " <<  tr["departure"].get<std::string>().substr(11,5) << "\n";
                    std::cout << "Прибытие: " << tr["arrival"].get<std::string>().substr(0,10)  << "\n";
                    std::cout << "Время прибытия(по местному): " <<  tr["arrival"].get<std::string>().substr(11,5) << "\n";

                }
            }
            std::cout << "-----------------------------------\n";
        }  
    }  
}  


