#ifndef DAILY_TASK_09_H
#define DAILY_TASK_09_H

#include <DailyTask/DailyTask.h>

class DailyTask09 : DailyTask {
public:
  DailyTask09(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // DAILY_TASK_09_H
