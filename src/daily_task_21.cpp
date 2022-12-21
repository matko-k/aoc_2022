#include <DailyTask/daily_task_21.h>

struct Operation
{
  char id;
  std::function<long(long, long)> calculate;
};
struct Monkey
{
  std::string name;
  bool is_number;
  long value = -1;

  Operation operation;
  std::string number1;
  std::string number2;
};

using Tribe = std::unordered_map<std::string, Monkey>;

Operation getMonkeyOperation(char op)
{
  Operation operation;
  operation.id = op;
  if (op == '+')
    operation.calculate = [](long x, long y){return x+y;};
  if (op == '-')
    operation.calculate = [](long x, long y){return x-y;};
  if (op == '*')
    operation.calculate = [](long x, long y){return x*y;};
  if (op == '/')
    operation.calculate = [](long x, long y){return x/y;};

  return operation;
}

void readInput(Tribe& unprocessed_monkeys, Tribe& known_monkeys)
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_21_input.txt");
  std::string line;

  while (std::getline(file, line))
  {
    std::stringstream ss(line);
    std::string buffer;

    Monkey monkey;
    ss >> buffer;
    monkey.name = buffer.substr(0, buffer.length()-1);
    ss >> buffer;
    if (std::isdigit(buffer[0]))
    {
      monkey.is_number = true;
      monkey.value = stoi(buffer);
      known_monkeys[monkey.name] = monkey;
      continue;
    }
    monkey.is_number = false;
    monkey.number1 = buffer;
    ss>>buffer;
    monkey.operation = getMonkeyOperation(buffer[0]);
    ss>>buffer;
    monkey.number2 = buffer;
    unprocessed_monkeys[monkey.name] = monkey;
  }

  file.close();

}

void findHumnNumber(Tribe& unprocessed_monkeys, Tribe& known_monkeys, std::string current, long& current_number)
{
  Monkey& monkey = unprocessed_monkeys[current];

  bool found1 = known_monkeys.find(monkey.number1) != known_monkeys.end();
  std::string unknown = found1 ? monkey.number2 : monkey.number1;
  std::string known = found1 ? monkey.number1 : monkey.number2;

  if (monkey.operation.id == '+')
  {
    current_number -= known_monkeys[known].value;
  }
  if (monkey.operation.id == '-')
  {
    if (found1)
      current_number = known_monkeys[known].value - current_number;
    else
      current_number += known_monkeys[known].value;
  }
  if (monkey.operation.id == '*')
  {
    current_number /= known_monkeys[known].value;
  }

  if (monkey.operation.id == '/')
  {
    if (found1)
      current_number = known_monkeys[known].value / current_number;
    else
      current_number *= known_monkeys[known].value;
  }

  if (unknown == "humn")
    return;

  findHumnNumber(unprocessed_monkeys, known_monkeys, unknown, current_number);
}

void DailyTask21::part1()
{
  Tribe unprocessed_monkeys;
  Tribe known_monkeys;

  readInput(unprocessed_monkeys, known_monkeys);

  int iteration = 0;
  while (!unprocessed_monkeys.empty())
  {
    iteration++;
    for (auto& monkey : unprocessed_monkeys)
    {
      Monkey& current = monkey.second;

      bool found1 = known_monkeys.find(current.number1) != known_monkeys.end();
      bool found2 = known_monkeys.find(current.number2) != known_monkeys.end();
      if (found1 && found2)
      {
        current.is_number = true;
        current.value = current.operation.calculate(known_monkeys[current.number1].value,
                                                    known_monkeys[current.number2].value);
        known_monkeys[current.name] = current;
        unprocessed_monkeys.erase(current.name);
      }
    }
  }

  std::cout<<"Part 1: result: "<< known_monkeys["root"].value << ", found in " << iteration << " iterations\n";

}

void DailyTask21::part2()
{
  Tribe unprocessed_monkeys;
  Tribe known_monkeys;

  readInput(unprocessed_monkeys, known_monkeys);

  std::string interesting_monkey1 = unprocessed_monkeys["root"].number1;
  std::string interesting_monkey2 = unprocessed_monkeys["root"].number2;
  std::string unknown_root = "";
  std::string known_root = "";
  known_monkeys.erase("humn");
  int size_previous = -1;
  while (!unprocessed_monkeys.empty())
  {
    if (size_previous == unprocessed_monkeys.size())
      break;

    size_previous = unprocessed_monkeys.size();

    bool found_interesting1 = known_monkeys.find(interesting_monkey1) != known_monkeys.end();
    bool found_interesting2 = known_monkeys.find(interesting_monkey2) != known_monkeys.end();
    if (known_root == "" && (found_interesting1 || found_interesting2))
    {
      unknown_root = found_interesting2 ? interesting_monkey1 : interesting_monkey2;
      known_root= found_interesting2 ? interesting_monkey2 : interesting_monkey1;
    }

    for (auto& monkey : unprocessed_monkeys)
    {
      Monkey& current = monkey.second;

      bool found1 = known_monkeys.find(current.number1) != known_monkeys.end();
      bool found2 = known_monkeys.find(current.number2) != known_monkeys.end();
      if (found1 && found2)
      {
        current.is_number = true;
        current.value = current.operation.calculate(known_monkeys[current.number1].value,
                                                    known_monkeys[current.number2].value);
        known_monkeys[current.name] = current;
        unprocessed_monkeys.erase(current.name);
      }
    }
  }

  long number = known_monkeys[known_root].value;
  findHumnNumber(unprocessed_monkeys, known_monkeys, unknown_root, number);

  std::cout<<"Part 2: result: "<< number << "\n";
}

int main() {

  DailyTask21 dt21("");
  dt21.part1();
  dt21.part2();

  return 0;
}