#include <DailyTask/daily_task_01.h>

void DailyTask01::part1()
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_01_input.txt");

  std::string line;
  std::vector<std::vector<int>> all_food;
  int food;
  int largest = 0;
  int current_food = 0;
  std::vector<int> elf_food;

  while (std::getline(file, line))
  {
    if (line.empty())
    {
      all_food.push_back(elf_food);
      if (current_food > largest)
      {
        largest = current_food;
      }
      current_food = 0;
      elf_food.clear();
      continue;
    }
    food = stoi(line);
    current_food += food;
    elf_food.push_back(food);

  }
  file.close();

  std::cout<<"Part 1: " << largest <<"\n";
}


void DailyTask01::part2() {
  std::ifstream file;
  file.open("../daily_inputs/daily_task_01_input.txt");

  std::string line;
  std::vector<int> all_food;
  int food;
  int current_food = 0;

  while (std::getline(file, line))
  {
    if (line.empty())
    {
      all_food.push_back(current_food);

      current_food = 0;

      continue;
    }
    food = stoi(line);
    current_food += food;
  }
  file.close();

  std::sort(all_food.begin(), all_food.end(), std::greater<int>());

  std::cout<<"Part 2: " << all_food[0] + all_food[1] + all_food[2] <<"\n";
}

int main() {

  DailyTask01 dt1("--- Day 1: Calorie Counting ---");
  dt1.part1();
  dt1.part2();

  return 0;
}