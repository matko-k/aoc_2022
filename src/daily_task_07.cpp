#include <DailyTask/daily_task_07.h>
#include <memory>

struct File
{
  std::string name;
  long size;
};

class Dir
{
public:
  typedef std::shared_ptr<Dir> DirPtr;
  DirPtr parent_;
  std::string name_;
  std::vector<DirPtr> subdirectories_;
  std::vector<File> files_;

  Dir(std::string name, DirPtr parent) :name_(name), parent_(parent)
  {};
};

using DirPtr = Dir::DirPtr;

void getDirSize(long& size, DirPtr dir)
{
  for (const auto& f : dir->files_)
  {
    size += f.size;
  }
  if (dir->subdirectories_.empty())
  {
    return;
  }
  for (auto& d : dir->subdirectories_)
  {
    getDirSize(size, d);
  }
}

std::vector<DirPtr> readInput()
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_07_input.txt");

  DirPtr daddy = std::make_shared<Dir>("daddy", nullptr);
  DirPtr current_dir = daddy;

  std::string line;
  std::string buffer;
  std::vector<DirPtr> all_dirs = {};
  std::getline(file, line);
  std::getline(file, line);
  while (std::getline(file, line))
  {
    std::stringstream ss_line(line);
    ss_line >> buffer;
    if (buffer == "$")
    {
      ss_line >> buffer;
      if (buffer == "cd")
      {
        ss_line >> buffer;
        if (buffer == "..")
        {
          current_dir = current_dir->parent_;
          continue;
        }
        else
        {
          for (const auto& subdir : current_dir->subdirectories_)
          {
            if (subdir->name_ == buffer)
            {
              current_dir = subdir;
              break;
            }
          }
          continue;
        }
      }
      else
      {
        // ls
        continue;
      }
    }
    else if (buffer == "dir")
    {
      std::string subdir_name;
      ss_line >> subdir_name;
      DirPtr subdir = std::make_shared<Dir>(subdir_name, current_dir);
      current_dir->subdirectories_.push_back(subdir);
      all_dirs.push_back(subdir);
    }
    else
    {
      // file
      long size = stol(buffer);
      ss_line >> buffer;
      File f;
      f.size = size;
      f.name = buffer;
      current_dir->files_.push_back(f);
    }
  }
  file.close();
  all_dirs.push_back(daddy);
  return all_dirs;
}

void DailyTask07::part1()
{
  std::vector<DirPtr> all_dirs = readInput();
  long total_size = 0;

  for (const auto& d : all_dirs)
  {
    long current_size = 0;
    getDirSize(current_size, d);
    if (current_size <= 100000)
    {
      total_size += current_size;
    }
  }
  std::cout<<"Part 1: result: " << total_size <<"\n";
}

void DailyTask07::part2()
{
  std::vector<DirPtr> all_dirs = readInput();

  long used = 0;
  getDirSize(used, all_dirs.back());
  long unused = 70000000L - used;
  long to_be_freed = 30000000L - unused;
  long smallest = std::numeric_limits<long>::max();

  for (const auto& d : all_dirs)
  {
    long current_size = 0;
    getDirSize(current_size, d);
    if (current_size >= to_be_freed && current_size < smallest)
    {
      smallest = current_size;
    }
  }

  std::cout<<"Part 2: result: " << smallest <<"\n";
}

int main() {

  DailyTask07 dt07("--- Day 7: No Space Left On Device ---");
  dt07.part1();
  dt07.part2();

  return 0;
}