#ifndef DAILY_TASK_22_H
#define DAILY_TASK_22_H

#include <DailyTask/DailyTask.h>

const int cube_size = 50;

//std::vector<std::pair<int, int>> limits_row =
//    {{8, 11},
//     {8, 11},
//     {12, 15},
//     {0, 3},
//     {4, 7},
//     {8, 11}};
//std::vector<std::pair<int, int>> limits_col =
//    {{0, 3},
//     {4, 7},
//     {8, 11},
//     {4, 7},
//     {4, 7},
//     {8, 11}};

std::vector<std::pair<int, int>> limits_row =
    {{50, 99},
     {50, 99},
     {100, 149},
     {0, 49},
     {0, 49},
     {50, 99}};
std::vector<std::pair<int, int>> limits_col =
    {{0, 49},
     {50, 99},
     {0, 49},
     {150, 199},
     {100, 149},
     {100, 149}};


class DailyTask22 : DailyTask {
public:
  DailyTask22(std::string task_name) : DailyTask(task_name){};

  virtual void part1();
  virtual void part2();
};

#endif // DAILY_TASK_22_H
