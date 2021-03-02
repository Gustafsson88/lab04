// Copyright 2020 Danil Postvaykin <postvaykin01@mail.ru>

#include <DirectoryAnaliz.hpp>

int main()
{
  std::string path_to_dir = "../misc/ftp";
  DirectoryAnaliz analiz(path_to_dir);
  analiz.out_br_information();
  return 0;
}
