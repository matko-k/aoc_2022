#ifndef DAILY_TASK_21_H
#define DAILY_TASK_21_H

#include <DailyTask/DailyTask.h>

class DailyTask21 : DailyTask {
public:
  DailyTask21(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // DAILY_TASK_21_H
