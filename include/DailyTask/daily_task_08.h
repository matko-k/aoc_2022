#ifndef DAILY_TASK_08_H
#define DAILY_TASK_08_H

#include <DailyTask/DailyTask.h>

class DailyTask08 : DailyTask {
public:
  DailyTask08(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // DAILY_TASK_08_H
