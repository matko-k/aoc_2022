#ifndef DAILY_TASK_10_H
#define DAILY_TASK_10_H

#include <DailyTask/DailyTask.h>

class DailyTask10 : DailyTask {
public:
  DailyTask10(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // DAILY_TASK_10_H
