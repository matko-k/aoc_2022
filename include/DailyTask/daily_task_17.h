#ifndef DAILY_TASK_17_H
#define DAILY_TASK_17_H

#include <DailyTask/DailyTask.h>

class DailyTask17 : DailyTask {
public:
  DailyTask17(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // DAILY_TASK_17_H
