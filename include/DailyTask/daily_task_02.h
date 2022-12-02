#ifndef AOC2021_DAILY_TASK_02_H
#define AOC2021_DAILY_TASK_02_H

#include <DailyTask/DailyTask.h>

class DailyTask02 : DailyTask {
public:
  DailyTask02(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();

private:
  int getPlayScore(char my_play)
  {
    return my_play - 'X' + 1;
  }

  int getResult(char op_play, char my_play) const
  {
    switch (op_play)
    {
      case 'A':
      {
        if (my_play == 'X')
          return 3;
        if (my_play == 'Y')
          return 6;
        return 0;
      }
      case 'B':
      {
        if (my_play == 'X')
          return 0;
        if (my_play == 'Y')
          return 3;
        return 6;
      }
      case 'C':
      {
        if (my_play == 'X')
          return 6;
        if (my_play == 'Y')
          return 0;
        return 3;
      }
    }
  }

  int getPlayBasedOnResult(char op_play, char result) const
  {
    switch (op_play)
    {
      case 'A':
      {
        if (result == 'X')
          return 3;
        if (result == 'Y')
          return 1;
        return 2;
      }
      case 'B':
      {
        if (result == 'X')
          return 1;
        if (result == 'Y')
          return 2;
        return 3;
      }
      case 'C':
      {
        if (result == 'X')
          return 2;
        if (result == 'Y')
          return 3;
        return 1;
      }
    }
  }
};

#endif // AOC2021_DAILY_TASK_02_H
