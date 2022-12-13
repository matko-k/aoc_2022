#include <DailyTask/daily_task_13.h>

struct List
{
  typedef std::shared_ptr<List> ListPtr;
  ListPtr parent;
  std::vector<ListPtr> sublists = {};
  bool isNumber;
  int value;
};

using ListPtr = List::ListPtr;

void readLine(const std::string& line, ListPtr& top_list)
{
  std::vector<ListPtr> list_stack = {};
  top_list.reset();

  for (int i = 0; i < line.size(); i++)
  {
    if (line[i] == ',') continue;

    if (line[i] == '[')
    {
      ListPtr new_list = std::make_shared<List>();
      if (!list_stack.empty())
      {
        new_list->parent = list_stack.back();
        list_stack.back()->sublists.push_back(new_list);
      }
      list_stack.push_back(new_list);
      continue;
    }
    if (line[i] == ']')
    {
      top_list = list_stack.back();
      list_stack.pop_back();
      continue;
    }

    std::string value = "";
    while (line[i] != ',' && line[i] != ']')
    {
      value += line[i++];
    }
    i--;

    ListPtr new_list = std::make_shared<List>();
    new_list->isNumber = true;
    new_list->value = stoi(value);
    list_stack.back()->sublists.push_back(new_list);

  }
};

void readInput(std::vector<std::pair<ListPtr, ListPtr>>& signal)
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_13_input.txt");

  std::string line;
  ListPtr first;
  ListPtr second;

  while (std::getline(file, line))
  {
    if (line.empty())
    {
      auto list_pair = std::make_pair(first, second);
      signal.push_back(list_pair);
      continue;
    }

    readLine(line, first);
    std::getline(file, line);
    readLine(line, second);
  }
  auto list_pair = std::make_pair(first, second);
  signal.push_back(list_pair);

  file.close();
}

int compareValues(const ListPtr& left, const ListPtr& right)
{
  if (left->isNumber && right->isNumber)
  {
    if (left->value != right->value)
      return left->value < right->value ? 1 : 0;
    return -1;
  }

  if (!left->isNumber && !right->isNumber)
  {
    for (int i = 0; ; i++)
    {
      if (i == left->sublists.size() && i == right->sublists.size())
        return -1;

      if (i == left->sublists.size() && i < right->sublists.size())
        return 1;

      if (i < left->sublists.size() && i == right->sublists.size())
        return 0;

      int result = compareValues(left->sublists[i], right->sublists[i]);
      if (result >= 0)
        return result;
    }
  }

  if (left->isNumber)
  {
    ListPtr l = std::make_shared<List>();
    l->value = left->value;
    l->isNumber = true;
    left->isNumber = false;
    left->sublists.push_back(l);
    return compareValues(left, right);

  }

  if (right->isNumber)
  {
    ListPtr l = std::make_shared<List>();
    l->value = right->value;
    l->isNumber = true;
    right->isNumber = false;
    right->sublists.push_back(l);
    return compareValues(left, right);

  }
  return -1;
}

void DailyTask13::part1()
{
  std::vector<std::pair<ListPtr, ListPtr>> signal;
  readInput(signal);
  int count = 0;
  for (int i = 0; i < signal.size(); i++)
  {
    int result = compareValues(signal[i].first, signal[i].second);

    if (result == 1)
      count += i+1;
  }

  std::cout<<"Part 1: result: " << count <<"\n";

}

struct list_comparator
{
  inline bool operator() (const ListPtr& l1, const ListPtr& l2)
  {
    return compareValues(l1, l2);
  }
};

void DailyTask13::part2()
{
  std::vector<std::pair<ListPtr, ListPtr>> signal;
  readInput(signal);
  std::vector<ListPtr> all_values = {};

  for (const auto& l : signal)
  {
    all_values.push_back(l.first);
    all_values.push_back(l.second);
  }
  ListPtr outer_two = std::make_shared<List>();
  ListPtr two = std::make_shared<List>();
  two->isNumber = true;
  two->value = 2;
  outer_two->sublists.push_back(two);

  ListPtr outer_six = std::make_shared<List>();
  ListPtr six = std::make_shared<List>();
  six->isNumber = true;
  six->value = 6;
  outer_six->sublists.push_back(six);

  all_values.push_back(outer_two);
  all_values.push_back(outer_six);
  std::sort(all_values.begin(), all_values.end(), list_comparator());

  int result = 1;
  for (int i = 0; i < all_values.size(); i++)
  {
    if (compareValues(all_values[i], outer_two) == -1)
      result *= i+1;
    if (compareValues(all_values[i], outer_six) == -1)
      result *= i+1;
  }

  std::cout<<"Part 2: result: " << result <<"\n";
}

int main() {

  DailyTask13 dt13("--- Day 13: Distress Signal ---");
  dt13.part1();
  dt13.part2();

  return 0;
}