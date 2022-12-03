#ifndef DAILYTASK_H
#define DAILYTASK_H

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <unordered_map>
#include <sstream>
#include <regex>

class DailyTask
{
public:

    DailyTask(std::string task_description)
    {
        task_description_ = task_description;
    }

    virtual void part1() = 0;
    virtual void part2() = 0;

private:

    std::string task_description_;
};

#endif //DAILYTASK_H
