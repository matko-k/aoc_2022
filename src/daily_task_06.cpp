#include <DailyTask/daily_task_06.h>

int findMarker(const std::string& input, int sequence_length)
{
  for (int i = 0; i < input.length(); i++)
  {
    std::string marker = "";
    for (int j = 0; j < sequence_length; j++)
    {
      if (marker.find(input[i+j]) == std::string::npos)
      {
        marker += input[i+j];
      }
      else
        break;

      if (marker.size() >= sequence_length)
      {
        return i + sequence_length;
      }
    }
  }
  return -1;
}

void DailyTask06::part1()
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_06_input.txt");
  std::string input;
  file >> input;
  file.close();

  int result = findMarker(input, 4);
  std::cout<<"Part 1: result: " << result <<"\n";
}

void DailyTask06::part2()
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_06_input.txt");
  std::string input;
  file >> input;
  file.close();

  int result = findMarker(input, 14);
  std::cout<<"Part 2: result: " << result <<"\n";
}

int main() {

  DailyTask06 dt06("--- Day 6: Tuning Trouble ---");
  dt06.part1();
  dt06.part2();

  return 0;
}