#ifndef DAILY_TASK_18_H
#define DAILY_TASK_18_H

#include <DailyTask/DailyTask.h>

class DailyTask18 : DailyTask {
public:
  DailyTask18(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // DAILY_TASK_18_H
