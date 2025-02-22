#include "main.h"
#include "route.h"

void LetS_Go(std::string &Flag)
{
    
    std::cout << "Введите даты в формате YYYY-MM-DD\n";
    while(Flag == "true"){

        Route route;

        std::cout << "Когда поедем в Саратов?\n";
        std::cin >> route.DateArr;
        std::cout << "А когда обратно в СПБ?\n";
        std::cin >> route.DateBack;
        bool flag = false;
    
        while (flag == false){
            if ( (std::stoi((route.DateBack).substr(0,4)) - std::stoi((route.DateArr).substr(0,4)) >= 0
                && std::stoi((route.DateBack).substr(5,2)) - std::stoi((route.DateArr).substr(5,2)) >= 0 
                && std::stoi((route.DateBack).substr(8,2)) - std::stoi((route.DateArr).substr(8,2)) > 1) ||
                (std::stoi((route.DateBack).substr(0,4)) - std::stoi((route.DateArr).substr(0,4)) >= 0
                && std::stoi((route.DateBack).substr(5,2)) - std::stoi((route.DateArr).substr(5,2)) > 0 
                && std::stoi((route.DateBack).substr(8,2)) - std::stoi((route.DateArr).substr(8,2)) <= 1) ){
                flag = true;
            }else{

                std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                std::cout << "Люди ещё не умеют путешествовать во времени! Выбери другую дату возвращения ^_^\n";
                std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

                std::cin >> route.DateBack;
            }
        }
    
        route.jRoutes(route.DateArr,"c2","c194", "Arr");
        route.jRoutes(route.DateBack,"c194","c2", "Back");

        std::cout << "#########################################################\n";
        std::cout << "Счастливого пути домой!\n";
        std::cout << "#########################################################\n";
    
        route.jParse("Arr");

        std::cout << "#########################################################\n";
        std::cout << "Уже обратно? Срочно на Невский за бабл ти по приезде!!!\n";
        std::cout << "#########################################################\n";
    
        route.jParse("Back");

        std::cout << "#########################################################\n";
        std::cout << "Посмотрим другие даты? ^_^ ( да - true | нет - false )\n";
        std::cout << "#########################################################\n";

        std::cin >> Flag;
    }
    exit(0);
}

bool IsInternet() {
    cpr::Response response = cpr::Get(cpr::Url{"http://www.google.com"});
    return response.status_code == 200;
}