#ifndef DAILY_TASK_14_H
#define DAILY_TASK_14_H

#include <DailyTask/DailyTask.h>

class DailyTask14 : DailyTask {
public:
  DailyTask14(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // DAILY_TASK_14_H
