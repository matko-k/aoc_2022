#include <DailyTask/daily_task_22.h>

struct MapRow
{
  std::string fields;
  int start_pos;
  int end_pos;
};

enum class Direction
{
  RIGHT, UP, LEFT, DOWN
};

int getDirValue(Direction dir)
{
  if (dir == Direction::RIGHT)
    return 0;
  if (dir == Direction::DOWN)
    return 1;
  if (dir == Direction::LEFT)
    return 2;
  return 3;
}

struct Coordinates
{
  int x;
  int y;
  Direction dir;
  int side_id;

  void moveRight3d(Coordinates& current)
  {
    int side_from = current.side_id;

    if (side_from == 2)
    {
      //go to side 5
      current.side_id = 5;
      current.dir = Direction::LEFT;
      current.x = limits_row[5].second;
      current.y = limits_col[5].second - (current.y - limits_col[side_from].first);
      return;
    }
    if (side_from == 1)
    {
      //go to side 2
      current.side_id = 2;
      current.dir = Direction::UP;
      current.x = limits_row[2].first + (current.y - limits_col[side_from].first);
      current.y = limits_col[2].second;
      return;
    }
    if (side_from == 5)
    {
      //go to side 2
      current.side_id = 2;
      current.dir = Direction::LEFT;
      current.x = limits_row[2].second;
      current.y = limits_col[2].second - (current.y - limits_col[side_from].first);
      return;
    }
    if (side_from == 3)
    {
      //go to side 5
      current.side_id = 5;
      current.dir = Direction::UP;
      current.x = limits_row[5].first + (current.y - limits_col[side_from].first);;
      current.y = limits_col[5].second;
      return;
    }
  }

  void moveLeft3d(Coordinates& current)
  {
    int side_from = current.side_id;

    if (side_from == 0)
    {
      //go to side 4
      current.side_id = 4;
      current.dir = Direction::RIGHT;
      current.x = limits_row[4].first;
      current.y = limits_col[4].second - (current.y - limits_col[side_from].first);
      return;
    }
    if (side_from == 1)
    {
      //go to side 4
      current.side_id = 4;
      current.dir = Direction::DOWN;
      current.x = limits_row[4].first + (current.y - limits_col[side_from].first);
      current.y = limits_col[4].first;
      return;
    }
    if (side_from == 4)
    {
      //go to side 0
      current.side_id = 0;
      current.dir = Direction::RIGHT;
      current.x = limits_row[0].first;
      current.y = limits_col[0].second - (current.y - limits_col[side_from].first);
      return;
    }
    if (side_from == 3)
    {
      //go to side 0
      current.side_id = 0;
      current.dir = Direction::DOWN;
      current.x = limits_row[0].first + (current.y - limits_col[side_from].first);
      current.y = limits_col[0].first;
      return;
    }
  }
  void moveUp3d(Coordinates& current)
  {
    int side_from = current.side_id;

    if (side_from == 4)
    {
      //go to side 1
      current.side_id = 1;
      current.dir = Direction::RIGHT;
      current.x = limits_row[1].first;
      current.y = limits_col[1].first + (current.x - limits_row[side_from].first);
      return;
    }
    if (side_from == 0)
    {
      //go to side 3
      current.side_id = 3;
      current.dir = Direction::RIGHT;
      current.x = limits_row[3].first;
      current.y = limits_col[3].first + (current.x - limits_row[side_from].first);
      return;
    }
    if (side_from == 2)
    {
      //go to side 3
      current.side_id = 3;
      current.dir = Direction::UP;
      current.x = limits_row[3].first + (current.x - limits_row[side_from].first);
      current.y = limits_col[3].second;
      return;
    }
  }

  void moveDown3d(Coordinates& current)
  {
    int side_from = current.side_id;

    if (side_from == 3)
    {
      //go to side 2
      current.side_id = 2;
      current.dir = Direction::DOWN;
      current.x = limits_row[2].first + (current.x - limits_row[side_from].first);
      current.y = limits_col[2].first;
      return;
    }
    if (side_from == 5)
    {
      //go to side 3
      current.side_id = 3;
      current.dir = Direction::LEFT;
      current.x = limits_row[3].second;
      current.y = limits_col[3].first + (current.x - limits_row[side_from].first);
      return;
    }
    if (side_from == 2)
    {
      //go to side 1
      current.side_id = 1;
      current.dir = Direction::LEFT;
      current.x = limits_row[1].second;
      current.y = limits_col[1].first + (current.x - limits_row[side_from].first);
      return;
    }
  }

  void moveHorizontal3D(const std::vector<MapRow>& map_rows,
                        const std::vector<MapRow>& map_columns,
                        int length)
  {
    MapRow current_map_row = map_rows[y];
    int dx = dir == Direction::RIGHT ? 1 : -1;

    for (int i = 1; i <= length; i++)
    {
      Coordinates test_coord = *this;
      test_coord.x += dx;
      if (test_coord.x < current_map_row.start_pos)
        moveLeft3d(test_coord);
      else if (test_coord.x > current_map_row.end_pos)
        moveRight3d(test_coord);
      if (map_rows[test_coord.y].fields[test_coord.x] == '#')
        break;

      bool side_change = side_id != test_coord.side_id;
      *this = test_coord;
      if (side_change)
      {
        if (dir == Direction::RIGHT || dir == Direction::LEFT)
        {
          moveHorizontal3D(map_rows, map_columns, length - i);
        }
        else
        {
          moveVertical3D(map_rows, map_columns, length - i);
        }
        break;
      }
    }
  }

  void moveVertical3D(const std::vector<MapRow>& map_rows,
                      const std::vector<MapRow>& map_columns,
                      int length)
  {
    MapRow current_map_col = map_columns[x];
    int dy = dir == Direction::DOWN ? 1 : -1;

    for (int i = 1; i <= length; i++)
    {
      Coordinates test_coord = *this;
      test_coord.y += dy;
      if (test_coord.y < current_map_col.start_pos)
        moveUp3d(test_coord);
      else if (test_coord.y > current_map_col.end_pos)
        moveDown3d(test_coord);
      if (map_rows[test_coord.y].fields[test_coord.x] == '#')
        break;

      bool side_change = side_id != test_coord.side_id;
      *this = test_coord;
      if (side_change)
      {
        if (dir == Direction::RIGHT || dir == Direction::LEFT)
        {
          moveHorizontal3D(map_rows, map_columns, length - i);
        }
        else
        {
          moveVertical3D(map_rows, map_columns, length - i);
        }
        break;
      }
    }
  }

  void moveHorizontal(const MapRow& map_row, int length)
  {
    int dx = dir == Direction::RIGHT ? 1 : -1;

    for (int i = 1; i <= length; i++)
    {
      int test_x = x+dx;
      if (test_x < map_row.start_pos)
        test_x = map_row.end_pos;
      if (test_x > map_row.end_pos)
        test_x = map_row.start_pos;
      if (map_row.fields[test_x] == '#')
        break;
     x = test_x;
    }
  }

  void moveVertical(const MapRow& map_row, int length)
  {
    int dy = dir == Direction::DOWN ? 1 : -1;

    for (int i = 1; i <= length; i++)
    {
      int test_y = y+dy;
      if (test_y < map_row.start_pos)
        test_y = map_row.end_pos;
      if (test_y > map_row.end_pos)
        test_y = map_row.start_pos;
      if (map_row.fields[test_y] == '#')
        break;
      y = test_y;
    }
  }

  void rotate(char c)
  {
    if (c == 'L')
      if (dir == Direction::RIGHT)
        dir = Direction::UP;
      else if (dir == Direction::UP)
        dir = Direction::LEFT;
      else if (dir == Direction::LEFT)
        dir = Direction::DOWN;
      else
        dir = Direction::RIGHT;
    else
    if (dir == Direction::RIGHT)
      dir = Direction::DOWN;
    else if (dir == Direction::DOWN)
      dir = Direction::LEFT;
    else if (dir == Direction::LEFT)
      dir = Direction::UP;
    else
      dir = Direction::RIGHT;
  }

  void updateSideID()
  {
    for (int i = 0; i < 6; i++)
    {
      if (x >= limits_row[i].first && x <= limits_row[i].second &&
          y >= limits_col[i].first && y <= limits_col[i].second)
      {
        side_id = i;
        break;
      }
    }
  }
};

void getMapRowsAndColumns(const std::vector<std::string>& map, std::vector<MapRow>& map_rows, std::vector<MapRow>& map_columns)
{
  for (const std::string& mr : map)
  {
    MapRow map_row;
    bool first_non_empty = false;
    map_row.fields = mr;
    for (int i = 0; i < mr.size(); i++)
    {
      if (mr[i] == 32)
      {
        if (first_non_empty)
        {
          map_row.end_pos = i - 1;
          first_non_empty = false;
          break;
        }
        continue;
      }
      if (!first_non_empty)
      {
        first_non_empty = true;
        map_row.start_pos = i;
      }
    }
    if (first_non_empty)
      map_row.end_pos = mr.size()-1;

    map_rows.push_back(map_row);
  }

  for (int i = 0; i < map[0].size(); i++)
  {
    MapRow map_row;
    bool first_non_empty = false;
    std::string column = "";
    for (int j = 0; j < map.size(); j++)
    {
      column += map[j][i];
      if (map[j][i] == 32)
      {
        if (first_non_empty)
        {
          map_row.end_pos = j - 1;
          first_non_empty = false;
          break;
        }
        continue;
      }
      if (!first_non_empty)
      {
        first_non_empty = true;
        map_row.start_pos = j;
      }
    }
    if (first_non_empty)
      map_row.end_pos = map.size()-1;
    map_row.fields = column;
    map_columns.push_back(map_row);
  }
}

void readInput(std::vector<std::string>& map,
               std::vector<int>& movements,
               std::vector<char>& rotations)
{
  std::string filepath = "../daily_inputs/daily_task_22_input.txt";
  int size = 0;
  std::ifstream file;
  file.open(filepath);
  std::string line;

  while (std::getline(file, line))
  {
    size = std::max(size, (int)line.size());
  }
  file.close();

  file.open(filepath);
  while (std::getline(file, line))
  {
    if (line.empty())
      break;
    if (line.size() < size)
    {
      for (int i = line.size(); i < size; i++)
      {
        line += 32;
      }
    }
    map.push_back(line);
  }

  std::getline(file, line);
  std::string move_buffer = "";
  for (char c : line)
  {
    if (!std::isdigit(c))
    {
      int move = stoi(move_buffer);
      move_buffer = "";
      movements.push_back(move);
      rotations.push_back(c);
      continue;
    }
    move_buffer += c;
  }
  if (!move_buffer.empty())
  {
    int move = stoi(move_buffer);
    movements.push_back(move);
  }
  file.close();
}

void DailyTask22::part1()
{
  std::vector<std::string> map;
  std::vector<int> movements;
  std::vector<char> rotations;

  readInput(map, movements, rotations);
  std::reverse(movements.begin(), movements.end());
  std::reverse(rotations.begin(), rotations.end());

  std::vector<MapRow> map_rows;
  std::vector<MapRow> map_columns;

  getMapRowsAndColumns(map, map_rows, map_columns);

  Coordinates current;
  current.x = map_rows.front().start_pos;
  current.y = map_columns[current.x].start_pos;
  current.dir = Direction::RIGHT;

  while (!movements.empty())
  {
    int move = movements.back();
    movements.pop_back();
    if (current.dir == Direction::RIGHT || current.dir == Direction::LEFT)
      current.moveHorizontal(map_rows[current.y], move);
    else
      current.moveVertical(map_columns[current.x], move);

    if (rotations.empty())
      continue;
    char rot = rotations.back();
    rotations.pop_back();
    current.rotate(rot);
  }

  int result = (current.x+1) * 4 + (current.y+1)*1000 + getDirValue(current.dir);

  std::cout<<"Part 1: result: " << result << "\n";
}

void DailyTask22::part2()
{
  std::vector<std::string> map;
  std::vector<int> movements;
  std::vector<char> rotations;

  readInput(map, movements, rotations);
  std::reverse(movements.begin(), movements.end());
  std::reverse(rotations.begin(), rotations.end());

  std::vector<MapRow> map_rows;
  std::vector<MapRow> map_columns;

  getMapRowsAndColumns(map, map_rows, map_columns);

  Coordinates current;
  current.x = map_rows.front().start_pos;
  current.y = map_columns[current.x].start_pos;
  current.dir = Direction::RIGHT;
  current.updateSideID();

  while (!movements.empty())
  {
    int move = movements.back();
    movements.pop_back();

    if (current.dir == Direction::RIGHT || current.dir == Direction::LEFT)
      current.moveHorizontal3D(map_rows, map_columns, move);
    else
      current.moveVertical3D(map_rows, map_columns, move);

    current.updateSideID();

    if (rotations.empty())
      continue;
    char rot = rotations.back();
    rotations.pop_back();
    current.rotate(rot);
  }

  int result = (current.x+1) * 4 + (current.y+1)*1000 + getDirValue(current.dir);


  std::cout<<"Part 2: result: " << result << "\n";
}

int main() {

  DailyTask22 dt22("--- Day 22: Monkey Map ---");
  dt22.part1();
  dt22.part2();

  return 0;
}