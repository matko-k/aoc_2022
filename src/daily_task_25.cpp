#include <DailyTask/daily_task_25.h>

long snafu_to_dec(const std::string& snafu_num)
{
  long result = 0;
  long base = 1;
  for (int i = snafu_num.length() - 1; i >= 0; i--)
  {
    if (snafu_num[i] == '=')
      result += -2L*base;
    else if (snafu_num[i] == '-')
      result += -1L*base;
    else
      result += (long)(snafu_num[i] - '0')*base;
    base *= 5;
  }

  return result;
}

std::map<int, char> snafu_digits = {{0, '0'}, {1, '1'}, {2, '2'}, {3, '='}, {4, '-'}};

std::string dec_to_snafu(const long dec)
{
  std::string snafu = "";
  long current = dec;

  while (current > 0)
  {
    long quotient = current / 5L;
    long remainder = current % 5L;
    long carry = (remainder > 2) ? 1L : 0L;
    current = quotient + carry;
    snafu = snafu_digits[remainder] + snafu;
  }

  return snafu;
}

void DailyTask25::part1()
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_25_input.txt");
  std::string line;

  long result = 0;

  while (std::getline(file, line))
    result += snafu_to_dec(line);

  file.close();

  std::unordered_map<long, bool> explored;
  std::string snafu_result = dec_to_snafu(result);

  std::cout<<"Part 1: result: "<< snafu_result <<"\n";
}

void DailyTask25::part2()
{
}

int main() {

  DailyTask25 dt25("--- Day 25: Full of Hot Air ---");
  dt25.part1();
  dt25.part2();

  return 0;
}