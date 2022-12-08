#include <DailyTask/daily_task_08.h>

typedef std::vector<u_int8_t> Forrest_row;
typedef std::vector<Forrest_row> Forrest;

void readInput(Forrest& forrest)
{
  forrest.clear();
  std::ifstream file;
  file.open("../daily_inputs/daily_task_08_input.txt");
  std::string line;
  while(std::getline(file, line))
  {
    Forrest_row forrest_row = {};
    for (char c : line)
    {
      forrest_row.push_back((u_int8_t) c - '0');
    }
    forrest.push_back(forrest_row);
  }
  file.close();
}

bool isVisible(const Forrest& forrest, int i, int j)
{
  u_int8_t current_tree = forrest[i][j];
  int current_i = i;
  int current_j = j;

  while (true)
  {
    if (current_i == 0)
      return true;
    current_i--;
    if (forrest[current_i][current_j] >= current_tree)
      break;
  }

  current_i = i;
  current_j = j;
  while (true)
  {
    if (current_j == 0)
      return true;
    current_j--;
    if (forrest[current_i][current_j] >= current_tree)
      break;
  }

  current_i = i;
  current_j = j;
  while (true)
  {
    if (current_i == forrest.size()-1)
      return true;
    current_i++;
    if (forrest[current_i][current_j] >= current_tree)
      break;
  }

  current_i = i;
  current_j = j;
  while (true)
  {
    if (current_j == forrest[0].size()-1)
      return true;
    current_j++;
    if (forrest[current_i][current_j] >= current_tree)
      break;
  }
  return false;
}

long getScore(const Forrest& forrest, int i, int j)
{
  u_int8_t current_tree = forrest[i][j];
  int current_i = i;
  int current_j = j;

  long score_up = 0;
  long score_left = 0;
  long score_down = 0;
  long score_right = 0;

  while (true)
  {
    if (current_i == 0)
      break;
    current_i--;
    score_up++;
    if (forrest[current_i][current_j] >= current_tree)
      break;
  }

  current_i = i;
  current_j = j;
  while (true)
  {
    if (current_j == 0)
      break;
    current_j--;
    score_left++;
    if (forrest[current_i][current_j] >= current_tree)
      break;
  }

  current_i = i;
  current_j = j;
  while (true)
  {
    if (current_i == forrest.size()-1)
      break;
    score_down++;
    current_i++;
    if (forrest[current_i][current_j] >= current_tree)
      break;
  }

  current_i = i;
  current_j = j;
  while (true)
  {
    if (current_j == forrest[0].size()-1)
      break;
    current_j++;
    score_right++;
    if (forrest[current_i][current_j] >= current_tree)
      break;
  }
  return score_down*score_left*score_up*score_right;
}

void DailyTask08::part1()
{
  Forrest forrest = {};
  readInput(forrest);
  long visible = 0;

  for (int i = 1; i < forrest.size() - 1; i++)
  {
    for (int j = 1; j < forrest[i].size() - 1; j++)
    {
      if (isVisible(forrest, i, j))
        visible++;
    }
  }
  visible += 2*(forrest.size() + forrest[0].size() - 2);

  std::cout<<"Part 1: result: " << visible <<"\n";
}

void DailyTask08::part2()
{
  Forrest forrest = {};
  readInput(forrest);
  long high_score = 0;
  for (int i = 0; i < forrest.size(); i++)
  {
    for (int j = 0; j < forrest[i].size(); j++)
    {
      long score = getScore(forrest, i, j);
      high_score = std::max(score, high_score);
    }
  }

  std::cout<<"Part 2: result: " << high_score <<"\n";
}

int main() {

  DailyTask08 dt08("--- Day 8: Treetop Tree House ---");
  dt08.part1();
  dt08.part2();

  return 0;
}