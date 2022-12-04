#include <DailyTask/daily_task_04.h>

void DailyTask04::part1()
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_04_input.txt");
  std::string line;
  int count = 0;
  while (file >> line)
  {
    std::string task1 = line.substr(0, line.find(','));
    std::pair<int, int> task1_limits = std::make_pair(stoi(task1.substr(0, task1.find('-'))),
                                                      stoi(task1.substr(task1.find('-') + 1, task1.length())));
    std::string task2 = line.substr(line.find(',') + 1, line.length());
    std::pair<int, int> task2_limits = std::make_pair(stoi(task2.substr(0, task2.find('-'))),
                                                      stoi(task2.substr(task2.find('-') + 1, task2.length())));
    if (task1_limits.first >= task2_limits.first && task1_limits.second <= task2_limits.second
        || task2_limits.first >= task1_limits.first && task2_limits.second <= task1_limits.second)
      count++;

  }

  std::cout<<"Part 1: count: " << count <<"\n";
  file.close();
}

void DailyTask04::part2()
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_04_input.txt");
  std::string line;
  int count = 0;
  while (file >> line)
  {
    std::string task1 = line.substr(0, line.find(','));
    std::pair<int, int> task1_limits = std::make_pair(stoi(task1.substr(0, task1.find('-'))),
                                                      stoi(task1.substr(task1.find('-') + 1, task1.length())));
    std::string task2 = line.substr(line.find(',') + 1, line.length());
    std::pair<int, int> task2_limits = std::make_pair(stoi(task2.substr(0, task2.find('-'))),
                                                      stoi(task2.substr(task2.find('-') + 1, task2.length())));
    if (task1_limits.first >= task2_limits.first && task1_limits.first <= task2_limits.second
        || task2_limits.first >= task1_limits.first && task2_limits.first <= task1_limits.second)
      count++;

  }

  std::cout<<"Part 1: count: " << count <<"\n";
  file.close();
}

int main() {

  DailyTask04 dt04("--- Day 4: Camp Cleanup ---");
  dt04.part1();
  dt04.part2();

  return 0;
}