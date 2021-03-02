// Copyright 2021 Alexsand Guchkov <firer.a45@gmail.com>

#include "DirectoryAnaliz.hpp"

using boost::filesystem::directory_entry;
using boost::filesystem::filesystem_error;
using boost::filesystem::file_type;

DirectoryAnaliz::DirectoryAnaliz(const std::string &path_to_dir)
{
  try {
    dir_path = path(path_to_dir);
    dir_iter = directory_iterator(dir_path);
  }
  catch(const filesystem_error& er)
  {
    dir_path = path(".");
    dir_iter = directory_iterator(dir_path);
  }
  BrokerData brok_data;
  broker_information.push_back(brok_data);
  analiz();
}

void DirectoryAnaliz::analiz()
{
  boost::filesystem::directory_iterator end;
  for (; dir_iter != end; ++ dir_iter) {

    boost::filesystem::file_status fs =
        boost::filesystem::status(*dir_iter);{
      switch (fs.type()) {
        case boost::filesystem::directory_file: {
          std::string dir_name = dir_iter->path().filename().string();
          reading_directory(dir_name,dir_iter->path().string());
          break;
        }
        default:
          std::string dir_name = dir_iter->path().filename().string();
          reading_directory(dir_name,dir_iter->path().string());
          std::cout << "NO DIRECTORY";
          break;
      }
    }
  }
}

void DirectoryAnaliz::reading_directory(std::string name_dir, const std::string &new_dir_path)
{
  path dir_path_in_file = path(new_dir_path);
  directory_iterator dir_iter_in_file = directory_iterator(dir_path_in_file);
  std::string str;
  boost::filesystem::directory_iterator end;
  for (; dir_iter_in_file != end; ++ dir_iter_in_file)
  {
    if (dir_iter_in_file->path().extension() == ".txt")
    {
      bool u = check_old_filename(dir_iter->path().string());
      if (u == true)
      {
        bool t;
        t = check_filename(name_dir, dir_iter_in_file->path().stem().string());
        if(t == true)
        {
          std::cout << name_dir << " "
                    << dir_iter_in_file->path().filename().string() << std::endl;
        }
      }
    }
  }
}


bool DirectoryAnaliz::check_filename(std::string dir, std::string filename)
{
  std::string date = "";
  std::string id = "";
  const std::string for_check = "0123456789";
  auto it_first = filename.find_first_of('_') + 1;
  auto it_last = filename.find_last_of('_') - 1;
  id = filename.substr(it_first, it_last - it_first + 1);
  date =
      filename.substr(it_last + 2, filename.length() - it_last);
  if ((id.find_first_not_of(for_check) != std::string::npos)
      || (date.find_first_not_of(for_check) != std::string::npos))
  {
    return false;
  }
  if (filename.find("balance") == 0)
  {
    if(dir != broker_information[n].name_dir)
    {
      BrokerData brok_data;
      brok_data.name_dir = dir;
      brok_data.count_files = 1;
      brok_data.account = id;
      brok_data.last_date = date;
      n += 1;
      broker_information.push_back(brok_data);
    }
    else
    {
      BrokerData brok_data;
      brok_data.name_dir = dir;
      brok_data.account = id;
      brok_data.last_date = date;
      int k = 0;
      for (int i = 1; i <= n; i++)
      {
        if (id == broker_information[i].account)
        {
          broker_information[i].count_files += 1;
          int a = std::stoi(date);
          int b = std::stoi(broker_information[i].last_date);
          if (a > b)
          {
            broker_information[i].last_date = date;
          }
          k = 1;
        }
      }
      if (k == 0)
      {
        n += 1;
        brok_data.count_files = 1;
        broker_information.push_back(brok_data);
      }
    }
  }
  else
  {
    return false;
  }
  return true;
}

bool DirectoryAnaliz::check_old_filename(const std::string &new_dir_path)
{
  path dir_path_in_file = path(new_dir_path);
  directory_iterator iter = directory_iterator(dir_path_in_file);
  if (iter->path().extension() == ".old")
  {
    return false;
  }
  return true;
}

void DirectoryAnaliz::out_br_information()
{
  std::cout << std::endl;
  for (int i = 1; i <= n; i++)
  {
    std::cout << "broker:" << broker_information[i].name_dir << " account:" <<
              broker_information[i].account <<" files:" <<
              broker_information[i].count_files << " lastdate:" <<
        broker_information[i].last_date << std::endl;
  }
}

DirectoryAnaliz::~DirectoryAnaliz(){}
