#ifndef DAILY_TASK_03_H
#define DAILY_TASK_03_H

#include <DailyTask/DailyTask.h>

class DailyTask03 : DailyTask {
public:
  DailyTask03(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // DAILY_TASK_03_H
