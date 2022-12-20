#include <DailyTask/daily_task_20.h>

struct Number
{
  typedef std::shared_ptr<Number> NumberPtr;
  long value;
  NumberPtr left;
  NumberPtr right;
};

using NumberPtr = Number::NumberPtr;

void readInput(std::unordered_map<long, NumberPtr>& numbers, std::vector<NumberPtr>& number_order)
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_20_input.txt");

  std::string line;
  while (std::getline(file, line))
  {
    NumberPtr number = std::make_shared<Number>();
    number->value = stoi(line);
    if (!number_order.empty())
    {
      number->left = number_order.back();
      number_order.back()->right = number;
    }
    number_order.push_back(number);
    numbers[number->value] = number;
  }
  number_order.back()->right = number_order.front();
  number_order.front()->left = number_order.back();

  file.close();
}

void DailyTask20::part1()
{
  std::unordered_map<long, NumberPtr> numbers;
  std::vector<NumberPtr> number_order;
  readInput(numbers, number_order);

  std::reverse(number_order.begin(), number_order.end());

  while (!number_order.empty())
  {
    NumberPtr current_saved = number_order.back();
    number_order.pop_back();

    long cycles = abs(current_saved->value);
    int dir = current_saved->value > 0 ? 1 : -1;
    while (cycles > 0)
    {
      NumberPtr current = current_saved;
      if (dir > 0)
      {
        NumberPtr temp_right = current->right;
        NumberPtr temp_left = current->left;
        current->right = temp_right->right;
        current->left = temp_right;

        temp_left->right = temp_right;
        temp_right->left = temp_left;
        temp_right->right = current;
        current->right->left = current;
        cycles--;
        continue;
      }
      NumberPtr temp_right = current->right;
      NumberPtr temp_left = current->left;
      current->left = temp_left->left;
      current->right = temp_left;

      temp_right->left = temp_left;
      temp_left->right = temp_right;
      temp_left->left = current;
      current->left->right = current;
      cycles--;
    }
  }

  long result = 0;
  NumberPtr current = numbers[0];
  for (int i = 0; i < 1000 ; i++)
    current = current->right;
  result += current->value;

  current = numbers[0];
  for (int i = 0; i < 2000 ; i++)
    current = current->right;
  result += current->value;

  current = numbers[0];
  for (int i = 0; i < 3000 ; i++)
    current = current->right;
  result += current->value;

  std::cout<<"Part 1: result: "<< result <<"\n";

}

void DailyTask20::part2()
{
  std::unordered_map<long, NumberPtr> numbers;
  std::vector<NumberPtr> number_order;
  readInput(numbers, number_order);

  std::reverse(number_order.begin(), number_order.end());

  std::vector<NumberPtr> saved = number_order;

  int x = 10;
  while (x > 0)
  {
    x--;
    std::vector<NumberPtr> number_ordered = saved;

    while (!number_ordered.empty())
    {
      NumberPtr current_saved = number_ordered.back();
      number_ordered.pop_back();

      long cycles = abs(current_saved->value * 811589153L);
      long size = saved.size() - 1;
      cycles = cycles % size;
      int dir = current_saved->value > 0 ? 1 : -1;
      while (cycles > 0)
      {
        NumberPtr current = current_saved;
        if (dir > 0)
        {
          NumberPtr temp_right = current->right;
          NumberPtr temp_left = current->left;
          current->right = temp_right->right;
          current->left = temp_right;

          temp_left->right = temp_right;
          temp_right->left = temp_left;
          temp_right->right = current;
          current->right->left = current;
          cycles--;
          continue;
        }
        NumberPtr temp_right = current->right;
        NumberPtr temp_left = current->left;
        current->left = temp_left->left;
        current->right = temp_left;

        temp_right->left = temp_left;
        temp_left->right = temp_right;
        temp_left->left = current;
        current->left->right = current;
        cycles--;
      }
    }
  }

  long result = 0;
  NumberPtr current = numbers[0];
  for (int i = 0; i < 1000 % numbers.size(); i++)
    current = current->right;
  result += current->value;

  current = numbers[0];
  for (int i = 0; i < 2000 % numbers.size(); i++)
    current = current->right;
  result += current->value;

  current = numbers[0];
  for (int i = 0; i < 3000 % numbers.size(); i++)
    current = current->right;
  result += current->value;

  std::cout<<"Part 2: result: "<< result * 811589153L <<"\n";
}

int main() {

  DailyTask20 dt20("--- Day 20: Grove Positioning System ---");
  dt20.part1();
  dt20.part2();

  return 0;
}