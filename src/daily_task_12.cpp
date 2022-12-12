#include <DailyTask/daily_task_12.h>
#include <queue>

struct Field
{
  char value;
  int x;
  int y;
  int g = std::numeric_limits<int>::max();
  int h = std::numeric_limits<int>::max();
  Field* came_from;

  Field(int X, int Y, char Value) : x(X), y(Y), value(Value){};
  Field(){};
};

void readInput(std::vector<std::vector<Field>>& map, Field& start, Field& goal)
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_12_input.txt");

  std::string line;
  int i = 0;

  while (std::getline(file, line))
  {
    std::vector<Field> field_line = {};
    for (int j = 0; j < line.size(); j++)
    {
      if (line[j] == 'S')
      {
        start = {j, i, 'a'};
        line[j] = 'a';
      }
      if (line[j] == 'E')
      {
        goal = {j, i , 'z'};
        line[j] = 'z';
      }
      field_line.push_back({j, i, line[j]});
    }
    map.emplace_back(field_line);
    i++;
  }

  file.close();
}

struct CompareFields
{
  bool operator() (Field* lhs, Field* rhs)
  {
    return lhs->h + lhs->g > rhs->h + rhs->g;
  }
};

int getHCost(const Field& current, const Field& goal)
{
  return abs(goal.x - current.x) + abs(goal.y - current.y);
}

void findPath(std::vector<std::vector<Field>>& map,
              std::vector<Field>& shortest_path,
              Field* start,
              Field* goal)
{
  const int row_size = map[0].size();
  const int column_size = map.size();

  std::priority_queue<Field*, std::vector<Field*>, CompareFields> open_set;
  start->g = 0;
  start->h = getHCost(*start, *goal);
  start->came_from = nullptr;
  open_set.push(start);

  while (!open_set.empty())
  {
    Field* next = open_set.top();
    open_set.pop();

    if (next->x == goal->x && next->y == goal->y)
    {
      while (next != nullptr)
      {
        shortest_path.push_back(*next);
        next = next->came_from;
      }
      return;
    }

    std::vector<Field*> neighborhood;
    if (next->x < row_size-1 && map[next->y][next->x + 1].value - next->value <= 1) neighborhood.push_back(&map[next->y][next->x + 1]);
    if (next->x > 0 && map[next->y][next->x - 1].value - next->value <= 1) neighborhood.push_back(&map[next->y][next->x - 1]);
    if (next->y > 0 && map[next->y - 1][next->x].value - next->value <= 1) neighborhood.push_back(&map[next->y - 1][next->x]);
    if (next->y < column_size-1 && map[next->y + 1][next->x].value - next->value <= 1) neighborhood.push_back(&map[next->y + 1][next->x]);

    for (Field* neighbor : neighborhood)
    {
      int new_score = next->g + 1;
      if (new_score < neighbor->g)
      {
        neighbor->came_from = next;
        neighbor->g = new_score;
        neighbor->h = getHCost(*neighbor, *goal);
        open_set.push(neighbor);
      }
    }
  }
}

void DailyTask12::part1()
{
  std::vector<std::vector<Field>> map = {};
  Field start, goal;
  readInput(map, start, goal);
  std::vector<Field> shortest_path;

  findPath(map, shortest_path, &start, &goal);
  std::cout<<"Part 1: result: "<< shortest_path.size() -1 <<"\n";
}

void DailyTask12::part2()
{
  std::vector<std::vector<Field>> map = {};
  Field start, goal;
  readInput(map, start, goal);

  std::vector<Field> possible_starts;
  for (const auto& field_row : map)
  {
    for (const auto& f : field_row)
    {
      if (f.value == 'a')
        possible_starts.push_back(f);
    }
  }

  int shortest_shortest_path_size = std::numeric_limits<int>::max();

  for (Field f_start : possible_starts)
  {
    auto fresh_map = map;
    auto fresh_goal = goal;
    std::vector<Field> shortest_path;
    findPath(fresh_map, shortest_path, &f_start, &fresh_goal);

    int current_size = shortest_path.size();
    if (current_size == 0)
      continue;
    shortest_shortest_path_size = std::min(current_size, shortest_shortest_path_size);
  }

  std::cout<<"Part 2: result: "<< shortest_shortest_path_size - 1 <<"\n";
}

int main() {

  DailyTask12 dt12("--- Day 12: Hill Climbing Algorithm ---");
  dt12.part1();
  dt12.part2();

  return 0;
}