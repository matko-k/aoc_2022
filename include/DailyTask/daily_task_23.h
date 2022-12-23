#ifndef DAILY_TASK_23_H
#define DAILY_TASK_23_H

#include <DailyTask/DailyTask.h>

class DailyTask23 : DailyTask {
public:
  DailyTask23(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // DAILY_TASK_23_H
