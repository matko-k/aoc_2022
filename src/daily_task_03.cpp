#include <DailyTask/daily_task_03.h>

void DailyTask03::part1()
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_03_input.txt");
  std::string line;
  int priorities = 0;
  while (std::getline(file, line))
  {
    std::string first = line.substr(0, line.size()/2);
    std::string second = line.substr(line.size()/2, line.size());
    for (char c : first)
    {
      if (second.find(c) != std::string::npos)
      {
        if (islower(c))
          priorities += c - 'a' + 1;
        else
          priorities += c - 'A' + 27;
        break;
      }
    }
  }
  file.close();

  std::cout<<"Part 1: priorities sum: " << priorities <<"\n";
}

void DailyTask03::part2()
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_03_input.txt");
  std::string first;
  std::string second;
  std::string third;
  int priorities = 0;
  while (file >> first >> second >> third)
  {
    for (char c : first)
    {
      if (second.find(c) != std::string::npos && third.find(c) != std::string::npos)
      {
        if (islower(c))
          priorities += c - 'a' + 1;
        else
          priorities += c - 'A' + 27;
        break;
      }
    }
  }
  file.close();

  std::cout<<"Part 2: priorities sum: " << priorities <<"\n";
}

int main() {

  DailyTask03 dt03("--- Day 3: Rucksack Reorganization ---");
  dt03.part1();
  dt03.part2();

  return 0;
}