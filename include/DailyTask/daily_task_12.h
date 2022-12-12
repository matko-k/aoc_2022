#ifndef DAILY_TASK_12_H
#define DAILY_TASK_12_H

#include <DailyTask/DailyTask.h>

class DailyTask12 : DailyTask {
public:
  DailyTask12(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // DAILY_TASK_12_H
