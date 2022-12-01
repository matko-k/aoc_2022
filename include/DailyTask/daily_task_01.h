#ifndef AOC2021_DAILY_TASK_01_H
#define AOC2021_DAILY_TASK_01_H

#include <DailyTask/DailyTask.h>

class DailyTask01 : DailyTask {
public:
  DailyTask01(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // AOC2021_DAILY_TASK_01_H
