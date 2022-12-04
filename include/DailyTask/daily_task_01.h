#ifndef DAILY_TASK_01_H
#define DAILY_TASK_01_H

#include <DailyTask/DailyTask.h>

class DailyTask01 : DailyTask {
public:
  DailyTask01(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // DAILY_TASK_01_H
