#include "utils.h"
#include <dirent.h>
#include <iostream>
#include <memory>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

void handle_dir(char *dir) {
  if (!dir) {
    std::cout << "could not get directory" << '\n';
    exit(1);
  }
}
void handle_status(ReadStatus status) {
  if (ReadStatus::Read_Falied == status) {
    std::cout << "Could not read directory" << '\n';
    exit(1);
  }
}
int main(int argc, char *argv[]) {
  auto content =
      std::make_unique<std::vector<std::unique_ptr<struct dirent>>>();
  if (1 == argc) {
    const int size = 1024;
    char buffer[size];
    handle_dir(getcwd(buffer, size));
    handle_status(read_dir(std::string(buffer), content));
    print_content(std::string(buffer), content);
  } else {
    const int size = 1024;
    char buffer[size];
    handle_dir(getcwd(buffer, size));
    std::string full_path = std::string(buffer);
    full_path += argv[1];
    std::cout<<full_path<<'\n';
    handle_status(read_dir(argv[1], content));
    print_content(argv[1],content);
  }

  return 0;
}
