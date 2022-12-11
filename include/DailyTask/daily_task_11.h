#ifndef DAILY_TASK_11_H
#define DAILY_TASK_11_H

#include <DailyTask/DailyTask.h>

class DailyTask11 : DailyTask {
public:
  DailyTask11(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // DAILY_TASK_11_H
