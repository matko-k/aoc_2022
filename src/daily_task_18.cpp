#include <DailyTask/daily_task_18.h>

struct Cube
{
  int x;
  int y;
  int z;

  std::string to_string()
  {
    return std::to_string(x) + "|"
    + std::to_string(y) + "|"
    + std::to_string(z);
  }

  int adjacent = 0;
};

void expand(const std::unordered_map<std::string, Cube>& cubes,
            std::unordered_map<std::string, Cube>& expanded,
            Cube& current,
            const Cube& low_limit,
            const Cube& up_limit)
{
  expanded[current.to_string()] = current;

  Cube test_cube = current;
  test_cube.x--;
  if (test_cube.x > low_limit.x &&
  cubes.find(test_cube.to_string()) == cubes.end() &&
  expanded.find(test_cube.to_string()) == expanded.end())
    expand(cubes, expanded, test_cube, low_limit, up_limit);

  test_cube = current;
  test_cube.x++;
  if (test_cube.x < up_limit.x &&
      cubes.find(test_cube.to_string()) == cubes.end() &&
      expanded.find(test_cube.to_string()) == expanded.end())
    expand(cubes, expanded, test_cube, low_limit, up_limit);

  test_cube = current;
  test_cube.y--;
  if (test_cube.y > low_limit.y &&
      cubes.find(test_cube.to_string()) == cubes.end() &&
      expanded.find(test_cube.to_string()) == expanded.end())
    expand(cubes, expanded, test_cube, low_limit, up_limit);

  test_cube = current;
  test_cube.y++;
  if (test_cube.y < up_limit.y &&
      cubes.find(test_cube.to_string()) == cubes.end() &&
      expanded.find(test_cube.to_string()) == expanded.end())
    expand(cubes, expanded, test_cube, low_limit, up_limit);

  test_cube = current;
  test_cube.z--;
  if (test_cube.z > low_limit.z &&
      cubes.find(test_cube.to_string()) == cubes.end() &&
      expanded.find(test_cube.to_string()) == expanded.end())
    expand(cubes, expanded, test_cube, low_limit, up_limit);

  test_cube = current;
  test_cube.z++;
  if (test_cube.z < up_limit.z &&
      cubes.find(test_cube.to_string()) == cubes.end() &&
      expanded.find(test_cube.to_string()) == expanded.end())
    expand(cubes, expanded, test_cube, low_limit, up_limit);

}

void DailyTask18::part1()
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_18_input.txt");

  std::unordered_map<std::string, Cube> cubes = {};
  std::string buffer;

  while(std::getline(file, buffer, ','))
  {
    Cube cube;
    cube.x = stoi(buffer);
    std::getline(file, buffer, ',');
    cube.y = stoi(buffer);
    std::getline(file, buffer);
    cube.z = stoi(buffer);

    cubes[cube.to_string()] = cube;
  }

  file.close();

  int result = 0;

  for (auto& c : cubes)
  {
    Cube& cube = c.second;
    Cube adjacent_cube = cube;
    adjacent_cube.x++;
    if (cubes.find(adjacent_cube.to_string()) != cubes.end())
      cube.adjacent++;
    adjacent_cube.x -= 2;
    if (cubes.find(adjacent_cube.to_string()) != cubes.end())
      cube.adjacent++;

    adjacent_cube.x++;
    adjacent_cube.y++;
    if (cubes.find(adjacent_cube.to_string()) != cubes.end())
      cube.adjacent++;
    adjacent_cube.y -= 2;
    if (cubes.find(adjacent_cube.to_string()) != cubes.end())
      cube.adjacent++;

    adjacent_cube.y++;
    adjacent_cube.z++;
    if (cubes.find(adjacent_cube.to_string()) != cubes.end())
      cube.adjacent++;
    adjacent_cube.z -= 2;
    if (cubes.find(adjacent_cube.to_string()) != cubes.end())
      cube.adjacent++;

    result += 6-cube.adjacent;
  }

  std::cout<<"Part 1: result: "<< result <<"\n";

}

void DailyTask18::part2()
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_18_input.txt");

  std::unordered_map<std::string, Cube> cubes = {};
  Cube up_limit;
  Cube low_limit;
  up_limit.x = 0;
  up_limit.y = 0;
  up_limit.z = 0;
  low_limit.x = std::numeric_limits<int>::max();
  low_limit.y = std::numeric_limits<int>::max();
  low_limit.z = std::numeric_limits<int>::max();

  std::string buffer;

  while(std::getline(file, buffer, ','))
  {
    Cube cube;
    cube.x = stoi(buffer);
    std::getline(file, buffer, ',');
    cube.y = stoi(buffer);
    std::getline(file, buffer);
    cube.z = stoi(buffer);

    up_limit.x = std::max(up_limit.x, cube.x);
    up_limit.y = std::max(up_limit.y, cube.y);
    up_limit.z = std::max(up_limit.z, cube.z);
    low_limit.x = std::min(low_limit.x, cube.x);
    low_limit.y = std::min(low_limit.y, cube.y);
    low_limit.z = std::min(low_limit.z, cube.z);

    cubes[cube.to_string()] = cube;
  }

  file.close();

  Cube lower_limit = low_limit;
  lower_limit.x -= 2;
  lower_limit.y -= 2;
  lower_limit.z -= 2;

  Cube upper_limit = up_limit;
  upper_limit.x += 2;
  upper_limit.y += 2;
  upper_limit.z += 2;

  Cube start = low_limit;
  start.x--;
  start.y--;
  start.z--;

  std::unordered_map<std::string, Cube> outer_cubes = {};
  expand(cubes, outer_cubes, start, lower_limit, upper_limit);

  int result = 0;

  for (auto& c : outer_cubes)
  {
    Cube& cube = c.second;
    Cube adjacent_cube = cube;
    adjacent_cube.x++;
    if (outer_cubes.find(adjacent_cube.to_string()) != outer_cubes.end())
      cube.adjacent++;
    adjacent_cube.x -= 2;
    if (outer_cubes.find(adjacent_cube.to_string()) != outer_cubes.end())
      cube.adjacent++;

    adjacent_cube.x++;
    adjacent_cube.y++;
    if (outer_cubes.find(adjacent_cube.to_string()) != outer_cubes.end())
      cube.adjacent++;
    adjacent_cube.y -= 2;
    if (outer_cubes.find(adjacent_cube.to_string()) != outer_cubes.end())
      cube.adjacent++;

    adjacent_cube.y++;
    adjacent_cube.z++;
    if (outer_cubes.find(adjacent_cube.to_string()) != outer_cubes.end())
      cube.adjacent++;
    adjacent_cube.z -= 2;
    if (outer_cubes.find(adjacent_cube.to_string()) != outer_cubes.end())
      cube.adjacent++;

    result += 6-cube.adjacent;
  }

  result -= 2*(upper_limit.x - lower_limit.x - 1)*(upper_limit.y - lower_limit.y - 1)
      + 2*(upper_limit.y - lower_limit.y - 1)*(upper_limit.z - lower_limit.z - 1)
      + 2*(upper_limit.x - lower_limit.x - 1)*(upper_limit.z - lower_limit.z - 1);

  std::cout<<"Part 2: result: "<< result <<"\n";
}

int main() {

  DailyTask18 dt18("--- Day 18: Boiling Boulders ---");
  dt18.part1();
  dt18.part2();

  return 0;
}