#include <DailyTask/daily_task_15.h>

struct Point
{
  int x;
  int y;
  Point(){};
  Point(int X, int Y):x(X), y(Y){};
};

struct Sensor
{
  Point location;
  Point closest_beacon;
  int range;

  bool isInRange(const Point& point) const
  {
    if ((abs(location.x - point.x)
         + abs(location.y - point.y)) > range)
      return false;
    return true;
  }
};

void readInput(std::vector<Sensor>& sensors, int& leftmost, int& rightmost)
{
  sensors.clear();
  leftmost = std::numeric_limits<int>::max();
  rightmost = -std::numeric_limits<int>::max();

  std::ifstream file;
  file.open("../daily_inputs/daily_task_15_input.txt");

  std::string line;

  while (std::getline(file, line))
  {
    std::string buffer;
    std::stringstream ss(line);
    bool reading_sensor = true;
    Sensor sensor;
    while (ss >> buffer)
    {
      if (buffer.find("x=") != std::string::npos)
      {
        if (reading_sensor)
        {
          int x = stoi(buffer.substr(2, buffer.find(',')));
          ss >> buffer;
          int y = stoi(buffer.substr(2, buffer.find(':')));
          sensor.location = {x, y};
          reading_sensor = false;
          continue;
        }
        int x = stoi(buffer.substr(2, buffer.find(',')));
        ss >> buffer;
        int y = stoi(buffer.substr(2, buffer.length()));
        sensor.closest_beacon = {x, y};
      }
    }
    sensor.range = (abs(sensor.location.x - sensor.closest_beacon.x)
        + abs(sensor.location.y - sensor.closest_beacon.y));
    leftmost = std::min(leftmost, sensor.location.x - sensor.range);
    rightmost = std::max(rightmost, sensor.location.x + sensor.range);
    sensors.push_back(sensor);
  }
  file.close();
}

void DailyTask15::part1()
{
  std::vector<Sensor> sensors;
  int leftmost_point;
  int rightmost_point;
  readInput(sensors, leftmost_point, rightmost_point);

  long count = 0;
  int inspection_row = 2000000;


  for (int i = leftmost_point; i <= rightmost_point; i++)
  {
    for (const Sensor &sensor: sensors)
    {
      if (sensor.isInRange({i, inspection_row}))
      {
        count++;
        break;
      }
    }
  }

  std::cout<<"Part 1: result: "<< count -1 <<"\n";
}

void addIfWithinLimit(std::vector<Point>& points, const Point& p, int low_limit, int up_limit)
{
  if (p.x < low_limit || p.x > up_limit
   || p.y < low_limit || p.y > up_limit)
    return;

  points.push_back({p.x, p.y});
}

void DailyTask15::part2()
{
  int limit = 4000000;
  std::vector<Sensor> sensors;
  int leftmost_point;
  int rightmost_point;
  readInput(sensors, leftmost_point, rightmost_point);

  std::vector<Point> possible_targets = {};

  for (const Sensor& sensor : sensors)
  {
    //start with right_most
    Point current = {sensor.location.x + sensor.range, sensor.location.y};

    int dir_x = -1;
    int dir_y = -1;
    while (current.x != sensor.location.x)
    {
      addIfWithinLimit(possible_targets, {current.x + 1, current.y}, 0, limit);

      current.x += dir_x;
      current.y += dir_y;
    }
    addIfWithinLimit(possible_targets, {current.x, current.y - 1}, 0, limit);

    dir_x = -1;
    dir_y = +1;
    while (current.y != sensor.location.y)
    {
      addIfWithinLimit(possible_targets, {current.x - 1, current.y}, 0, limit);
      current.x += dir_x;
      current.y += dir_y;
    }
    addIfWithinLimit(possible_targets, {current.x - 1, current.y}, 0, limit);

    dir_x = +1;
    dir_y = +1;
    while (current.x != sensor.location.x)
    {
      addIfWithinLimit(possible_targets, {current.x - 1, current.y}, 0, limit);
      current.x += dir_x;
      current.y += dir_y;
    }
    addIfWithinLimit(possible_targets, {current.x, current.y + 1}, 0, limit);

    dir_x = +1;
    dir_y = -1;
    while (current.y != sensor.location.y)
    {
      addIfWithinLimit(possible_targets, {current.x + 1, current.y}, 0, limit);
      current.x += dir_x;
      current.y += dir_y;
    }
    addIfWithinLimit(possible_targets, {current.x + 1, current.y}, 0, limit);

  }

  long long freq = -1;

  for (const Point& p : possible_targets)
  {
    int in_range = false;
    for (const Sensor& s : sensors)
    {
      if (s.isInRange(p))
      {
        in_range = true;
        break;
      }
    }
    if (!in_range)
    {
      freq = p.x*4'000'000L + p.y;
      break;
    }
  }

  std::cout<<"Part 2: result: "<< freq <<"\n";
}

int main() {

  DailyTask15 dt15("--- Day 15: Beacon Exclusion Zone ---");
  dt15.part1();
  dt15.part2();

  return 0;
}