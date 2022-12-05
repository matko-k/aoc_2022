#ifndef DAILY_TASK_05_H
#define DAILY_TASK_05_H

#include <DailyTask/DailyTask.h>

class DailyTask05 : DailyTask {
public:
  DailyTask05(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // DAILY_TASK_05_H
