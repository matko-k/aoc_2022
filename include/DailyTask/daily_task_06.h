#ifndef DAILY_TASK_06_H
#define DAILY_TASK_06_H

#include <DailyTask/DailyTask.h>

class DailyTask06 : DailyTask {
public:
  DailyTask06(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // DAILY_TASK_06_H
