#include "route.h"

namespace fs = std::filesystem;


void Route::IsThereFile(const std::string& filePath, const std::string& Flag){

    if (!fs::exists("./cache")) {
        fs::create_directory("./cache");
    }


    if (fs::exists(filePath)){

        std::ifstream file(filePath);
        nlohmann::json jsonData;
        file >> jsonData;
        file.close();

        if (Flag == "Arr")
            jsonResponseArr = jsonData;   
        else if(Flag == "Back")
            jsonResponseBack = jsonData;

        return;
    }
}


void Route::Fdeleter(const std::string& filePath, int seconds) {

    std::this_thread::sleep_for(std::chrono::seconds(seconds)); 

    if (fs::exists(filePath)) {
        fs::remove(filePath);
    }

}
