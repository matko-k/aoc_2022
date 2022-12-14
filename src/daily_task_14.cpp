#include <DailyTask/daily_task_14.h>

struct Point
{
  int x;
  int y;
  Point(){};
  Point(int X, int Y):x(X), y(Y){};
};

void readInput(std::vector<std::vector<char>>& map, int& highest)
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_14_input.txt");

  std::string line;
  highest = 0;

  while (std::getline(file, line))
  {
    std::string buffer;
    std::stringstream ss(line);
    Point first;
    Point second;
    bool first_point = true;
    while (ss >> buffer)
    {
      if (buffer == "->")
        continue;

      int x = stoi(buffer.substr(0, buffer.find(',')));
      int y = stoi(buffer.substr(buffer.find(',') + 1, buffer.size()));
      if (first_point)
      {
        first_point = false;
        second = {x, y};
        continue;
      }
      first = second;
      second = {x, y};
      int x_low = std::min(first.x, second.x);
      int x_high = std::max(first.x, second.x);
      int y_low = std::min(first.y, second.y);
      int y_high = std::max(first.y, second.y);

      for (int i = y_low; i <= y_high; i++)
        for (int j = x_low; j <= x_high; j++)
          map[i][j] = '#';

      highest = std::max(highest, y_high);
    }
  }

  file.close();
}

bool simulateSand(int highest, std::vector<std::vector<char>>& map, Point& current, long& count)
{
  if (current.y >= highest)
    return false;

  if (map[current.y + 1][current.x] == '.')
  {
    current.y++;
    return simulateSand(highest, map, current, count);
  }

  if (map[current.y + 1][current.x - 1] == '.')
  {
    current.x--;
    current.y++;
    return simulateSand(highest, map, current, count);
  }

  if (map[current.y + 1][current.x + 1] == '.')
  {
    current.x++;
    current.y++;
    return simulateSand(highest, map, current, count);
  }

  map[current.y][current.x] = 'O';
  count++;
  return true;

}

bool simulateSand2(int highest, std::vector<std::vector<char>>& map, Point& current, long& count)
{
  if (map[current.y + 1][current.x] == '.')
  {
    current.y++;
    return simulateSand2(highest, map, current, count);
  }

  if (map[current.y + 1][current.x - 1] == '.')
  {
    current.x--;
    current.y++;
    return simulateSand2(highest, map, current, count);
  }

  if (map[current.y + 1][current.x + 1] == '.')
  {
    current.x++;
    current.y++;
    return simulateSand2(highest, map, current, count);
  }

  if (current.x == 500 && current.y == 0)
    return false;

  map[current.y][current.x] = 'O';
  count++;
  return true;

}

void DailyTask14::part1()
{
  std::vector<std::vector<char>> map;
  map.resize(1000);
  for (auto& row : map)
  {
    row.resize(1000, '.');
  }

  int highest;
  readInput(map, highest);

  long count = 0;
  Point start = {500, 0};

  Point fresh_start = start;
  bool there_is_space = true;

  while (there_is_space)
  {
    there_is_space = simulateSand(highest, map, fresh_start, count);
    fresh_start = start;
  }

  std::cout<<"Part 1: result: " << count <<"\n";

}

void DailyTask14::part2()
{
  std::vector<std::vector<char>> map;
  map.resize(1000);
  for (auto& row : map)
  {
    row.resize(1000, '.');
  }

  int highest;
  readInput(map, highest);
  highest += 2;

  for (int i = 0; i < map[highest].size(); i++)
    map[highest][i] = '#';

  long count = 0;
  Point start = {500, 0};

  Point fresh_start = start;
  bool there_is_space = true;

  while (there_is_space)
  {
    there_is_space = simulateSand2(highest, map, fresh_start, count);
    fresh_start = start;
  }

  std::cout<<"Part 2: result: " << count+1 <<"\n";
}

int main() {

  DailyTask14 dt14("--- Day 14: Regolith Reservoir ---");
  dt14.part1();
  dt14.part2();

  return 0;
}