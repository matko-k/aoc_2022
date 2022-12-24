#ifndef DAILY_TASK_24_H
#define DAILY_TASK_24_H

#include <DailyTask/DailyTask.h>

class DailyTask24 : DailyTask {
public:
  DailyTask24(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // DAILY_TASK_24_H
