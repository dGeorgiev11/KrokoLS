#include "utils.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dirent.h>
#include <memory>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <vector>
ReadStatus
read_dir(std::string path,
         std::unique_ptr<std::vector<std::unique_ptr<struct dirent>>> &data) {
  DIR *dir = opendir(path.c_str());
  if (!dir) {
    return Read_Falied;
  }
  struct dirent *entry;
  while ((entry = readdir(dir)) != nullptr) {
    data->push_back(std::make_unique<struct dirent>(*entry));
  }
  closedir(dir);
  return Read_Succes;
}
/*
 * *
printf("%c ", 0x6A) # ┘
printf("%c ", 0x6B) # ┐
printf("%c ", 0x6C) # ┌
printf("%c ", 0x6D) # └
printf("%c ", 0x6E) # ┼
printf("%c ", 0x71) # ─
printf("%c ", 0x74) # ├
printf("%c ", 0x75) # ┤
printf("%c ", 0x76) # ┴
printf("%c ", 0x77) # ┬
printf("%c\n", 0x78) # │
  * */
void print_content(
    std::string path,
    std::unique_ptr<std::vector<std::unique_ptr<struct dirent>>> &data) {
  struct stat *info;
  printf("\u250c");
  for (int i = 0; i < 63; i++) {
    if (i == 30 || i == 35) {
      printf("\u252c");
    } else {
      printf("\u2500");
    }
  }
  printf("\u2510\n");
  printf("\u2502");
  printf("%-30s%s%-4s%s%26s %s\n", "File Name", "\u2502", "Type", "\u2502",
         "Last Modified", "\u2502");

  printf("\u251c");
  for (int i = 0; i < 63; i++) {
    if (i == 30 || i == 35) {
      printf("\u253c");
    } else {
      printf("\u2500");
    }
  }
  printf("\u2524\n");
  for (const auto &entry : *data) {
    info = get_file_info(path.c_str(), entry->d_name);
    char *time;
    strftime(time, 24, "%b %d %Y %H:%M:%S", localtime(&info->st_mtime));
    printf("\u2502");
    printf("%-30s%s%-4s%s%26s %s\n", entry->d_name, "\u2502",
           0 != S_ISDIR(info->st_mode) ? "DIR" : "FILE", "\u2502", time,
           "\u2502");

    // std::cout << entry->d_name << ' ' << info->st_uid << ' '
    //         << ctime(&info->st_mtime) << std::endl;
  }
  free(info);
  printf("\u2514");
  for (int i = 0; i < 63; i++) {
    if (i == 30 || i == 35) {
      printf("\u2534");
    } else {
      printf("\u2500");
    }
  }
  printf("\u2518");
}

struct stat *get_file_info(std::string path, std::string name) {
  std::string full_path = path + '/' + name;
  struct stat *info = (struct stat *)malloc(sizeof(struct stat));
  lstat(full_path.c_str(), info);
  return info;
}
