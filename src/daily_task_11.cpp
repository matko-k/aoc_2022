#include <DailyTask/daily_task_11.h>

struct Monkey
{
  std::vector<long> items_;
  std::function<long(long)> inspect_;
  std::function<long(double)> relax_ = [](long item) { return item/3;};
  long test_;
  long true_dest_;
  long false_dest_;
  long inspections_;

  Monkey(const std::vector<long>& items, std::function<long(long)> inspect, long test, long true_dest, long false_dest)
  : items_(items), inspect_(inspect), test_(test), true_dest_(true_dest), false_dest_(false_dest), inspections_(0)
  {};
};

const std::vector<Monkey> start_monkeys = {
    {{56, 56, 92, 65, 71, 61, 79}, [](long item) { return item * 7;}, 3, 3, 7}, // Monkey 0
    {{61, 85}, [](long item) { return item + 5;}, 11, 6, 4}, // Monkey 1
    {{54, 96, 82, 78, 69}, [](long item) { return item * item;}, 7, 0, 7}, // Monkey 2
    {{57, 59, 65, 95}, [](long item) { return item + 4;}, 2, 5, 1}, // Monkey 3
    {{62, 67, 80}, [](long item) { return item * 17;}, 19, 2, 6}, // Monkey 4
    {{91}, [](long item) { return item + 7;}, 5, 1, 4}, // Monkey 5
    {{79, 83, 64, 52, 77, 56, 63, 92}, [](long item) { return item + 6;}, 17, 2, 0}, // Monkey 6
    {{50, 97, 76, 96, 80, 56}, [](long item) { return item + 3;}, 13, 3, 5}, // Monkey 7
};

void playARound(std::vector<Monkey>& monkeys)
{
  for (Monkey& monkey : monkeys)
  {
    while (!monkey.items_.empty())
    {
      long current_item = monkey.items_.back();
      monkey.items_.pop_back();
      current_item = monkey.inspect_(current_item);
      monkey.inspections_++;
      current_item = monkey.relax_(current_item);
      if (current_item % monkey.test_ == 0)
      {
        monkeys[monkey.true_dest_].items_.push_back(current_item);
        continue;
      }
      monkeys[monkey.false_dest_].items_.push_back(current_item);
    }
  }
}

void playARound2(std::vector<Monkey>& monkeys, long common_div)
{
  for (Monkey& monkey : monkeys)
  {
    while (!monkey.items_.empty())
    {
      long current_item = monkey.items_.back();
      monkey.items_.pop_back();
      current_item = monkey.inspect_(current_item);
      monkey.inspections_++;
      current_item %= common_div;
      if (current_item % monkey.test_ == 0)
      {
        monkeys[monkey.true_dest_].items_.push_back(current_item);
        continue;
      }
      monkeys[monkey.false_dest_].items_.push_back(current_item);
    }
  }
}

void DailyTask11::part1()
{
  std::vector<Monkey> monkeys = start_monkeys;
  int rounds = 20;
  while (rounds > 0)
  {
    playARound(monkeys);
    rounds--;
  }

  std::vector<long> inspections = {};
  for (const Monkey& m : monkeys)
  {
    inspections.push_back(m.inspections_);
  }

  std::sort(inspections.begin(), inspections.end(), std::greater());
  std::cout<<"Part 1: result: " << inspections[0]*inspections[1] <<"\n";
}

void DailyTask11::part2()
{
  std::vector<Monkey> monkeys = start_monkeys;
  int rounds = 10000;

  long common_div = 1;

  for (const Monkey& m : monkeys)
  {
    common_div *= m.test_;
  }

  while (rounds > 0)
  {
    playARound2(monkeys, common_div);
    rounds--;
  }

  std::vector<long> inspections = {};
  for (const Monkey& m : monkeys)
  {
    inspections.push_back(m.inspections_);
  }

  std::sort(inspections.begin(), inspections.end(), std::greater());
  std::cout<<"Part 2: result: " << inspections[0]*inspections[1] <<"\n";
}

int main() {

  DailyTask11 dt11("--- Day 11: Monkey in the Middle ---");
  dt11.part1();
  dt11.part2();

  return 0;
}