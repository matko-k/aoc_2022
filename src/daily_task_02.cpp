#include <DailyTask/daily_task_02.h>

void DailyTask02::part1()
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_02_input.txt");

  std::vector<char> opponents_plays;
  std::vector<char> my_plays;
  char op_play;
  char my_play;

  while (file >> op_play >> my_play)
  {
    opponents_plays.push_back(op_play);
    my_plays.push_back(my_play);
  }

  long score = 0;
  for (int i = 0; i < opponents_plays.size(); i++)
  {
    score += getPlayScore(my_plays[i]);
    score += getResult(opponents_plays[i], my_plays[i]);
  }

  std::cout<<"Part 1: " << score <<"\n";
}

void DailyTask02::part2()
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_02_input.txt");
  char op_play;
  char result;
  long score = 0;
  while (file >> op_play >> result)
  {
    score += (result - 'X') * 3;
    score += getPlayBasedOnResult(op_play, result);
  }

  std::cout<<"Part 2: " << score <<"\n";
}

int main() {

  DailyTask02 dt02("--- Day 2: Rock Paper Scissors ---");
  dt02.part1();
  dt02.part2();

  return 0;
}