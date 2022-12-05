#include <DailyTask/daily_task_05.h>

const std::vector<std::vector<char>> start_state = {{'D', 'T', 'W', 'F', 'J', 'S', 'H', 'N'},
                                                    {'H', 'R', 'P', 'Q', 'T', 'N', 'B', 'G'},
                                                    {'L', 'Q', 'V'},
                                                    {'N', 'B', 'S', 'V', 'R', 'Q'},
                                                    {'N', 'D', 'F', 'T', 'V', 'M', 'B'},
                                                    {'M', 'D', 'B', 'V', 'H', 'T', 'R'},
                                                    {'D', 'B', 'Q', 'J'},
                                                    {'D', 'N', 'J', 'V', 'R', 'Z', 'H', 'Q'},
                                                    {'B', 'N', 'H', 'M', 'S'}};

void DailyTask05::part1()
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_05_input.txt");

  std::vector<std::vector<char>> state = start_state;
  std::string dummy;
  std::string count;
  std::string start;
  std::string goal;

  for (int i = 0; i < 10; i++)
    std::getline(file, dummy);

  while (file >> dummy >> count >> dummy >> start >> dummy >> goal)
  {
    int i_count = stoi(count);
    int i_start = stoi(start);
    int i_goal = stoi(goal);

    for (int i = 0; i < i_count; i++)
    {
      char buffer = state[i_start - 1].back();
      state[i_start - 1].pop_back();
      state[i_goal - 1].push_back(buffer);
    }
  }
  file.close();

  std::string result = "";
  for (const auto& stack : state)
    result+= stack.back();

  std::cout<<"Part 1: result: " << result <<"\n";

}

void DailyTask05::part2()
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_05_input.txt");

  std::vector<std::vector<char>> state = start_state;
  std::string dummy;
  std::string count;
  std::string start;
  std::string goal;

  for (int i = 0; i < 10; i++)
    std::getline(file, dummy);

  while (file >> dummy >> count >> dummy >> start >> dummy >> goal)
  {
    int i_count = stoi(count);
    int i_start = stoi(start);
    int i_goal = stoi(goal);
    std::vector<char> buffer = {};

    for (int i = 0; i < i_count; i++)
    {
      char b = state[i_start - 1].back();
      state[i_start - 1].pop_back();
      buffer.push_back(b);
    }

    while (buffer.size() > 0)
    {
      state[i_goal - 1].push_back(buffer.back());
      buffer.pop_back();
    }
  }
  file.close();

  std::string result = "";
  for (const auto& stack : state)
    result+= stack.back();

  std::cout<<"Part 2: result: " << result <<"\n";
}

int main() {

  DailyTask05 dt05("--- Day 5: Supply Stacks ---");
  dt05.part1();
  dt05.part2();

  return 0;
}