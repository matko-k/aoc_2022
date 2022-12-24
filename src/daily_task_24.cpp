#include <DailyTask/daily_task_24.h>
#include <queue>
#include <unordered_set>
#include <numeric>

struct Expedition
{
  int x;
  int y;
  int time = std::numeric_limits<int>::max();

  int h = std::numeric_limits<int>::max();

  std::string to_string(int bliz_cycle)
  {
    return std::to_string(x) + '|' + std::to_string(y) + '|' + std::to_string(time % bliz_cycle);
  }
};

struct Blizzard
{
  int x;
  int y;
  char dir;

  void move(int limit_x, int limit_y)
  {
    if (dir == '>')
    {
      if (x + 1 > limit_x-1)
        x = 1;
      else
        x++;
    }
    if (dir == '<')
    {
      if (x - 1 < 1)
        x = limit_x-1;
      else
        x--;
    }
    if (dir == '^')
    {
      if (y - 1 < 1)
        y = limit_y-1;
      else
        y--;
    }
    if (dir == 'v')
    {
      if (y + 1 > limit_y-1)
        y = 1;
      else
        y++;
    }
  }
};

struct CompareExpeditions
{
  bool operator() (const Expedition& lhs, const Expedition& rhs)
  {
    return lhs.h + lhs.time > rhs.h + rhs.time;
  }
};

void readInput(std::vector<std::string>& map, std::vector<Blizzard>& blizzards)
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_24_input.txt");
  std::string line;
  int lines = 0;
  while (std::getline(file, line))
  {
    map.push_back(line);
    for (int i = 1; i < line.size(); i++)
    {
      Blizzard bliz;
      if (line[i] == '>' || line[i] == '<' || line[i] == '^' || line[i] == 'v')
      {
        bliz.x = i;
        bliz.y = lines;
        bliz.dir = line[i];
        blizzards.push_back(bliz);
      }
    }
    lines++;
  }

  file.close();
}

int getHCost(const Expedition& current, const Expedition& goal)
{
  return abs(goal.x - current.x) + abs(goal.y - current.y);
}

std::vector<std::string> getStateFromBlizzards(const std::vector<Blizzard>& blizzards, const Expedition& start, const Expedition& goal, int row_size, int column_size)
{
  std::string line(row_size, '.');
  std::vector<std::string> out;
  out.resize(column_size, line);

  for (const Blizzard& bliz : blizzards)
  {
    out[bliz.y][bliz.x] = bliz.dir;
  }
  std::string border(row_size, '#');
  out[0] = border;
  out[column_size-1] = border;
  for (int i = 0; i < column_size; i++)
  {
    out[i][0] = '#';
    out[i][row_size-1] = '#';
  }
  out[start.y][start.x] = '.';
  out[goal.y][goal.x] = '.';
  return out;
}

void getNextBlizzards(std::vector<Blizzard>& blizzards, int limit_x, int limit_y)
{
  for (Blizzard& bliz : blizzards)
    bliz.move(limit_x, limit_y);
}

std::vector<Expedition> getNeighborStates(const Expedition& current, const std::vector<std::string>& next_state)
{
  int row_size = next_state[0].size();
  int column_size = next_state.size();
  Expedition test;
  test.x = current.x;
  test.y = current.y;
  std::vector<Expedition> neighborhood = {};
  if (next_state[test.y][test.x] == '.') neighborhood.push_back(test);
  test.x++;
  if (test.x < row_size && next_state[test.y][test.x] == '.') neighborhood.push_back(test);
  test.x -= 2;
  if (test.x >= 0 && next_state[test.y][test.x] == '.') neighborhood.push_back(test);
  test.x++;
  test.y++;
  if (test.y < column_size && next_state[test.y][test.x] == '.') neighborhood.push_back(test);
  test.y -= 2;
  if (test.y >= 0 && next_state[test.y][test.x] == '.') neighborhood.push_back(test);

  return neighborhood;
}

void prepareBlizzards(std::unordered_map<int, std::vector<Blizzard>>& all_blizzards, int cycle, int row_size, int column_size)
{
  std::vector<Blizzard> current = all_blizzards[0];
  for (int i = 1; i < cycle; i++)
  {
    getNextBlizzards(current, row_size-1, column_size-1);
    all_blizzards[i] = current;
  }
}

int findPath(std::unordered_map<int, std::vector<Blizzard>>& blizzard_states,
             int row_size, int column_size,
             const Expedition& start, const Expedition& goal)
{
  std::priority_queue<Expedition, std::vector<Expedition>, CompareExpeditions> open_set;
  open_set.push(start);

  int blizzard_cycle = blizzard_states.size();

  std::vector<bool> visited = {};
  visited.resize(row_size*column_size*blizzard_cycle, false);

  while (!open_set.empty())
  {
    Expedition current = open_set.top();
    open_set.pop();

    if (current.x == goal.x && current.y == goal.y)
      return current.time;


    int new_time = current.time+1;

    std::vector<std::string> next_state = getStateFromBlizzards(blizzard_states[new_time % blizzard_cycle], start, goal, row_size, column_size);
    std::vector<Expedition> neighborhood = getNeighborStates(current, next_state);

    for (Expedition neighbor : neighborhood)
    {
      neighbor.time = new_time;
      bool skip = visited[neighbor.x + neighbor.y*row_size + (new_time%blizzard_cycle)*row_size*column_size];
      visited[neighbor.x + neighbor.y*row_size + (new_time%blizzard_cycle)*row_size*column_size] = true;
      if (skip)
        continue;
      neighbor.h = getHCost(neighbor, goal);
      open_set.push(neighbor);
    }
  }
  return -1;
}

void DailyTask24::part1()
{
  std::vector<std::string> start_map_state;
  std::vector<Blizzard> blizzards;
  readInput(start_map_state, blizzards);
  int row_size = start_map_state[0].size();
  int column_size = start_map_state.size();
  std::unordered_map<int, std::vector<Blizzard>> blizzard_states;
  blizzard_states[0] = blizzards;
  int blizzard_cycle = std::lcm(row_size-2, column_size-2);
  prepareBlizzards(blizzard_states, blizzard_cycle, row_size, column_size);

  Expedition start, goal;
  start.x = 1;
  start.y = 0;
  goal.x = row_size-2;
  goal.y = column_size-1;
  start.time = 0;
  start.h = getHCost(start, goal);
  int result = findPath(blizzard_states, row_size, column_size, start, goal);

  std::cout<<"Part 1: result: "<< result <<"\n";
}

void DailyTask24::part2()
{
  std::vector<std::string> start_map_state;
  std::vector<Blizzard> blizzards;
  readInput(start_map_state, blizzards);
  int row_size = start_map_state[0].size();
  int column_size = start_map_state.size();
  std::unordered_map<int, std::vector<Blizzard>> blizzard_states;
  blizzard_states[0] = blizzards;
  int blizzard_cycle = std::lcm(row_size-2, column_size-2);
  prepareBlizzards(blizzard_states, blizzard_cycle, row_size, column_size);

  Expedition start, goal;
  start.x = 1;
  start.y = 0;
  goal.x = row_size - 2;
  goal.y = column_size - 1;
  start.time = 0;
  start.h = getHCost(start, goal);
  int result1 = findPath(blizzard_states, row_size, column_size, start, goal);

  start.x = row_size - 2;
  start.y = column_size - 1;
  start.time = result1;
  goal.x = 1;
  goal.y = 0;
  start.h = getHCost(start, goal);
  int result2 = findPath(blizzard_states, row_size, column_size, start, goal);

  start.x = 1;
  start.y = 0;
  start.time = result2;
  goal.x = row_size - 2;
  goal.y = column_size - 1;
  start.h = getHCost(start, goal);
  int result3 = findPath(blizzard_states, row_size, column_size, start, goal);

  std::cout<<"Part 2: result: "<< result3 <<"\n";
}

int main() {

  DailyTask24 dt24("--- Day 24: Blizzard Basin ---");
  dt24.part1();
  dt24.part2();

  return 0;
}