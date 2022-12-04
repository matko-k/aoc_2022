#ifndef DAILY_TASK_04_H
#define DAILY_TASK_04_H

#include <DailyTask/DailyTask.h>

class DailyTask04 : DailyTask {
public:
  DailyTask04(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // DAILY_TASK_04_H
