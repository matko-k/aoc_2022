#ifndef DAILY_TASK_19_H
#define DAILY_TASK_19_H

#include <DailyTask/DailyTask.h>

class DailyTask19 : DailyTask {
public:
  DailyTask19(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // DAILY_TASK_19_H
