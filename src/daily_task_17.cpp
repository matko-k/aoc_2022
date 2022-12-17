#include <DailyTask/daily_task_17.h>

struct Pose
{
  long x;
  long y;
  Pose(){};
  Pose(long x, long y): x(x), y(y){};
};

struct Block
{
  Pose pose;
  char id;
  std::vector<Pose> shape = {};
  int length;
  std::vector<int> height_profile = {};


  Block(char ID) : id(ID)
  {
    if (ID == '-')
    {
      shape = {{0,0}, {1,0}, {2,0}, {3,0}};
      length = 4;
      height_profile = {1,1,1,1};
    }
    else if (ID == '+')
    {
      shape = {{1,0}, {0,1}, {1,1}, {2,1}, {1,2}};
      length = 3;
      height_profile = {2,3,2};
    }
    else if (ID == 'L')
    {
      shape = {{0,0}, {1,0}, {2,0}, {2,1}, {2,2}};
      length = 3;
      height_profile = {1,1,3};
    }
    else if (ID == 'I')
    {
      shape = {{0,0},{0,1},{0,2},{0,3}};
      length = 1;
      height_profile = {4};
    }
    else if (ID == 'O')
    {
      shape = {{0,0},{1,0},{0,1},{1,1}};
      length = 2;
      height_profile = {2,2};
    }
  }
};

struct BlockGetter
{
  const std::unordered_map<int, Block> blocks = {
      {0, Block('-')},
      {1, Block('+')},
      {2 , Block('L')},
      {3 , Block('I')},
      {4 , Block('O')},
  };

  int current = 0;

  Block getNext()
  {
    Block block = blocks.at(current);
    current++;
    if (current > 4)
      current = 0;
    return block;
  }
};

struct Field
{
  std::array<long, 7> topmost = {0,0,0,0,0,0,0};
  std::vector<std::array<char, 7>> field;

  long getMax() const
  {
    long max = 0;
    for (int i = 0; i < topmost.size(); i++)
    {
      if (topmost[i] > max)
        max = topmost[i];
    }
    return max;
  }

  long getMin() const
  {
    long min = std::numeric_limits<long>::max();
    for (int i = 0; i < topmost.size(); i++)
    {
      if (topmost[i] < min)
        min = topmost[i];
    }
    return min;
  }
};

bool inCollision(const Field& field, const Block& block, long x, long y)
{
  Block test_block = block;
  test_block.pose.x += x;
  test_block.pose.y += y;
  for (const Pose& p : test_block.shape)
  {
    if (field.field[test_block.pose.y + p.y][test_block.pose.x + p.x] != '.')
      return true;
  }
  return false;
}

void fixateBlock(Field& field, const Block& block)
{
  for (int i = 0; i < block.height_profile.size(); i++)
  {
    if (block.id == 'L')
      std::cout<<"";

    field.topmost[block.pose.x + i] = std::max(field.topmost[block.pose.x + i],
                                               block.pose.y + block.height_profile[i]-1);
  }
  for (const Pose& p : block.shape)
  {
    field.field[block.pose.y + p.y][block.pose.x + p.x] = '#';
  }
}

bool simulateStep(Field& field, const std::string& commands, int& command_count, Block& block)
{
  int cmd = -1;
  if (commands[command_count] == '>')
    cmd = +1;

  command_count++;
  if (command_count >= commands.size())
    command_count = 0;

  if (block.pose.x + cmd >= 0 && block.pose.x + cmd + block.length -1 < field.topmost.size())
  {
    if (!inCollision(field, block, cmd, 0))
    {
      block.pose.x += cmd;
    }
  }

  if (inCollision(field, block, 0, -1))
  {
    fixateBlock(field, block);
    return false;
  }

  block.pose.y += -1;
  return true;
}

void expandField(Field& field, int height)
{
  for (int i = 1; i <= height; i++)
  {
    field.field.push_back({'.', '.', '.', '.', '.', '.', '.'});
  }
}

std::string getCurrentState(const Field& field, const Block& block, int current_command)
{
  std::string field_state = "";
  long min_top = field.getMin();
  for (int i = 0; i < field.topmost.size(); i++)
  {
    for (long j = min_top; j < field.topmost[i]; j++)
    {
      field_state += field.field[j][i];
    }
  }

  return field_state + block.id + std::to_string(current_command);
}

void DailyTask17::part1()
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_17_input.txt");
  std::string commands;
  std::getline(file, commands);
  file.close();

  int command_count = 0;
  BlockGetter block_getter;
  Field field;
  field.field.push_back({'#', '#', '#', '#', '#', '#', '#'});
  int turns = 2022;

  while (turns > 0)
  {
    Block block = block_getter.getNext();
    block.pose.x = 2;
    block.pose.y = field.getMax() + 4;
    expandField(field, 4);

    while (simulateStep(field, commands, command_count, block));

    turns--;
  }

  std::cout<<"Part 1: result: "<< field.getMax() <<"\n";

}

void DailyTask17::part2()
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_17_input.txt");
  std::string commands;
  std::getline(file, commands);
  file.close();

  int command_count = 0;
  BlockGetter block_getter;
  Field field;
  field.field.push_back({'#', '#', '#', '#', '#', '#', '#'});
  std::unordered_map<std::string, std::pair<long, long>> states = {};
  long cycle_height;
  long cycle_period;
  long long turns = 1000000000000L;

  while (turns > 0)
  {
    Block block = block_getter.getNext();
    block.pose.x = 2;
    block.pose.y = field.getMax() + 4;
    expandField(field, 4);

    while (simulateStep(field, commands, command_count, block));

    std::string current_state = getCurrentState(field, block, command_count);
    if (states.find(current_state) != states.end())
    {
      cycle_height = field.getMax() - states[current_state].first;
      cycle_period = states[current_state].second - turns;
      break;
    }

    states[current_state] = std::make_pair(field.getMax(), turns);
    turns--;
  }

  long height = turns/cycle_period * cycle_height;
  turns %= cycle_period;

  while (turns > 0)
  {
    Block block = block_getter.getNext();
    block.pose.x = 2;
    block.pose.y = field.getMax() + 4;
    expandField(field, 4);

    while (simulateStep(field, commands, command_count, block));

    std::string current_state = getCurrentState(field, block, command_count);

    turns--;
  }

  height += field.getMax();

  std::cout<<"Part 2: result: "<< height-1 <<"\n";

}

int main() {

  DailyTask17 dt17("--- Day 17: Pyroclastic Flow ---");
  dt17.part1();
  dt17.part2();

  return 0;
}