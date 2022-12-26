#ifndef DAILY_TASK_16_H
#define DAILY_TASK_16_H

#include <DailyTask/DailyTask.h>

class DailyTask16 : DailyTask {
public:
  DailyTask16(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // DAILY_TASK_16_H
