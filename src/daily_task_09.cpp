#include <DailyTask/daily_task_09.h>
#include <unordered_set>

struct Pose
{
  int x;
  int y;

  Pose(int X, int Y) : x(X), y(Y){};

  std::string toString() const
  {
    return std::to_string(x) + "," + std::to_string(y);
  }

  void moveByOne(char dir)
  {
    switch (dir)
    {
      case 'R' :
        x++;
        break;
      case 'L':
        x--;
        break;
      case 'U':
        y++;
        break;
      case 'D':
        y--;
        break;
    }
  }

};

void moveTail(const Pose& head, Pose& tail)
{
  if (head.x > tail.x)
    tail.moveByOne('R');
  if (head.x < tail.x)
    tail.moveByOne('L');
  if (head.y > tail.y)
    tail.moveByOne('U');
  if (head.y < tail.y)
    tail.moveByOne('D');
}

void DailyTask09::part1()
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_09_input.txt");

  char dir;
  int dist;
  std::unordered_set<std::string> visited;
  Pose head (0,0);
  Pose tail = head;

  visited.insert(tail.toString());

  while (file >> dir >> dist)
  {
    for (int i = 0; i < dist; i++)
    {
      head.moveByOne(dir);
      if (abs(head.x - tail.x) > 1 || abs(head.y - tail.y) > 1)
      {
        moveTail(head, tail);
        visited.insert(tail.toString());
      }
    }
  }

  file.close();

  std::cout<<"Part 1: result: " << visited.size() <<"\n";
}

void DailyTask09::part2()
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_09_input.txt");

  char dir;
  int dist;
  std::unordered_set<std::string> visited;
  Pose start (0,0);
  std::vector<Pose> rope;
  rope.resize(10, start);
  Pose& head = rope.front();
  Pose& tail = rope.back();

  visited.insert(tail.toString());

  while (file >> dir >> dist)
  {
    for (int i = 0; i < dist; i++)
    {
      head.moveByOne(dir);
      for (int j = 1; j<rope.size(); j++)
      {
        if (abs(rope[j-1].x - rope[j].x) > 1 || abs(rope[j-1].y - rope[j].y) > 1)
        {
          moveTail(rope[j-1], rope[j]);
        }
      }
      visited.insert(tail.toString());
    }
  }

  file.close();

  std::cout<<"Part 2: result: " << visited.size() <<"\n";
}

int main() {

  DailyTask09 dt09("--- Day 9: Rope Bridge ---");
  dt09.part1();
  dt09.part2();

  return 0;
}