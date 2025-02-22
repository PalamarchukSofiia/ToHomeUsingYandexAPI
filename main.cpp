#include "main.h"
#include "route.h"


int main(){

    std::string Flag = "true";

    if (IsInternet()) {
        LetS_Go(Flag);
    } else {
        std::cout << "Нет соединения с интернетом! ~_~" << std::endl;
        exit(0);
    }   


    return 0;
}