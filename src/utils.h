#include <dirent.h>
#include <memory>
#include <string>
#include <sys/types.h>
#include <vector>
#ifndef FILE_UTIL
#define FILE_UTIL
enum ReadStatus {
  Read_Succes,
  Read_Falied,
};
ReadStatus
read_dir(std::string path,
         std::unique_ptr<std::vector<std::unique_ptr<struct dirent>>> &data);
void print_content(std::string path,
    std::unique_ptr<std::vector<std::unique_ptr<struct dirent>>> &data);
struct stat * get_file_info(std::string path,std::string name);
#endif
