// Copyright 2021 Alexsand Guchkov <firer.a45@gmail.com>

#ifndef INCLUDE_DIRECTORYANALIZ_HPP
#define INCLUDE_DIRECTORYANALIZ_HPP

#include <iostream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>

using boost::filesystem::path;
using boost::filesystem::directory_iterator;
using boost::filesystem::file_type;

struct BrokerData
{
  std::string account = "";
  std::string name_dir = "";
  unsigned int count_files = 0;
  std::string last_date = "";
};

class DirectoryAnaliz
{
 public:
  explicit DirectoryAnaliz(const std::string &dir_path);
  void analiz();
  void reading_directory(std::string name_dir, const std::string &new_dir_path);
  void out_br_information();
  bool check_old_filename(const std::string &new_dir_path);
  bool check_filename(std::string dir, std::string filename);
  ~DirectoryAnaliz();
 private:
  std::vector<struct BrokerData> broker_information;
  int n = 0;
  directory_iterator dir_iter;
  path dir_path;
};

#endif  // INCLUDE_DIRECTORYANALIZ_HPP
