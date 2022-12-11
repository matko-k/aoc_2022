#include <DailyTask/daily_task_10.h>

void checkCycle(long cycle, long x_register, long& result)
{
  if (cycle % 40 == 20)
  {
    result += x_register*cycle;
  }
}

void drawOutput(long cycle, long x_register, std::vector<char>& output)
{
  int position = cycle%40;

  int diff = position - x_register;

  if (diff >= 0 && diff < 3)
  {
    output.push_back('#');
  }
  else
  {
    output.push_back('.');
  }
}

void DailyTask10::part1()
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_10_input.txt");
  std::string line;

  long cycle = 0;
  long x_register = 1;
  long result = 0;

  while (std::getline(file, line))
  {
    if (line[0] == 'n')
    {
      cycle++;
      checkCycle(cycle, x_register, result);
    }
    else
    {
      int x = stoi(line.substr(5, line.length()-5));
      cycle++;
      checkCycle(cycle, x_register, result);
      cycle++;
      checkCycle(cycle, x_register, result);
      x_register += x;
    }

  }

  std::cout<<"Part 1: result: " << result <<"\n";

  file.close();
}

void DailyTask10::part2()
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_10_input.txt");
  std::string line;

  long cycle = 0;
  long x_register = 1;
  std::vector<char> output = {};

  while (std::getline(file, line))
  {
    if (line[0] == 'n')
    {
      cycle++;
      drawOutput(cycle, x_register, output);
    }
    else
    {
      int x = stoi(line.substr(5, line.length()-5));
      cycle++;
      drawOutput(cycle, x_register, output);
      cycle++;
      drawOutput(cycle, x_register, output);
      x_register += x;
    }

  }

  std::cout<<"Part 2: result: \n";

  for (int i = 0; i < 240; i++)
  {
    if (i%40 == 0)
    {
      std::cout<<'\n';
    }
    std::cout<<output[i];
  }

  file.close();
}

int main() {

  DailyTask10 dt10("--- Day 10: Cathode-Ray Tube ---");
  dt10.part1();
  dt10.part2();

  return 0;
}