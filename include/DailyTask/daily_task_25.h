#ifndef DAILY_TASK_25_H
#define DAILY_TASK_25_H

#include <DailyTask/DailyTask.h>

class DailyTask25 : DailyTask {
public:
  DailyTask25(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // DAILY_TASK_25_H
