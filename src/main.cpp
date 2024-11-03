#include <dirent.h>
#include <sys/types.h>
#include <iostream>
#include "utils.h"
#include <memory>
#include <vector>
#include <string>
#include <unistd.h>

void handle_dir(char* dir){
    if(!dir){
        std::cout<<"could not get directory"<<'\n'; 
        exit(1);
    }
}
void handle_status(ReadStatus status){
    if(ReadStatus::Read_Falied == status){
        std::cout << "Could not read directory"<<'\n';
        exit(1);
    }
}
int main(int argc, char*argv[]){
    auto content = std::make_unique<std::vector<std::unique_ptr<struct dirent>>>();
    if(1==argc){
        const int size = 1024;
        char buffer[size];
        handle_dir(getcwd(buffer, size)); 
        handle_status(read_dir(std::string(buffer),content));
        print_content(std::string(buffer), content);
    }


    return 0;
}
