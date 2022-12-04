#ifndef DAILY_TASK_XX_H
#define DAILY_TASK_XX_H

#include <DailyTask/DailyTask.h>

class DailyTaskXX : DailyTask {
public:
  DailyTaskXX(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // DAILY_TASK_XX_H
