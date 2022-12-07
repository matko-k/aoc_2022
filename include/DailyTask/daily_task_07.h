#ifndef DAILY_TASK_07_H
#define DAILY_TASK_07_H

#include <DailyTask/DailyTask.h>

class DailyTask07 : DailyTask {
public:
  DailyTask07(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // DAILY_TASK_07_H
