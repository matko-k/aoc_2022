#ifndef DAILY_TASK_20_H
#define DAILY_TASK_20_H

#include <DailyTask/DailyTask.h>

class DailyTask20 : DailyTask {
public:
  DailyTask20(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // DAILY_TASK_20_H
