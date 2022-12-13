#ifndef DAILY_TASK_13_H
#define DAILY_TASK_13_H

#include <DailyTask/DailyTask.h>

class DailyTask13 : DailyTask {
public:
  DailyTask13(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // DAILY_TASK_13_H
