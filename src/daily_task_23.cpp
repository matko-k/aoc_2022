#include <DailyTask/daily_task_23.h>
enum class Movement
{
  NO_MOVE, N, NW, NE, S, SW, SE, W, E
};

void getMovement(Movement mov, long& dx, long& dy)
{
  switch (mov)
  {
    case Movement::NO_MOVE:
      dx = 0;
      dy = 0;
      break;
    case Movement::N:
      dx = 0;
      dy = -1;
      break;
    case Movement::NW:
      dx = -1;
      dy = -1;
      break;
    case Movement::NE:
      dx = 1;
      dy = -1;
      break;
    case Movement::S:
      dx = 0;
      dy = 1;
      break;
    case Movement::SW:
      dx = -1;
      dy = 1;
      break;
    case Movement::SE:
      dx = 1;
      dy = 1;
      break;
    case Movement::W:
      dx = -1;
      dy = 0;
      break;
    case Movement::E:
      dx = 1;
      dy = 0;
      break;
  }
}

struct Elf
{
  long x;
  long y;
  Movement move = Movement::NO_MOVE;

  std::string to_string()
  {
    return std::to_string(x) + "|" + std::to_string(y);
  }

  void applyMove()
  {
    long dx,dy;
    getMovement(move, dx, dy);
    x += dx;
    y += dy;
  }
};

struct DirectionGetter
{
  std::function<Movement(const std::unordered_map<std::string, Elf>&, const Elf&)> checkNorth =
      [](const std::unordered_map<std::string, Elf>& elves, const Elf& elf)
      {
        Elf test_elf = elf;
        test_elf.y -= 1;
        if (elves.find(test_elf.to_string()) != elves.end())
          return Movement::NO_MOVE;
        test_elf.x -= 1;
        if (elves.find(test_elf.to_string()) != elves.end())
          return Movement::NO_MOVE;
        test_elf.x += 2;
        if (elves.find(test_elf.to_string()) != elves.end())
          return Movement::NO_MOVE;

        return Movement::N;
      };

  std::function<Movement(const std::unordered_map<std::string, Elf>&, const Elf&)> checkSouth =
      [](const std::unordered_map<std::string, Elf>& elves, const Elf& elf)
      {
        Elf test_elf = elf;
        test_elf.y += 1;
        if (elves.find(test_elf.to_string()) != elves.end())
          return Movement::NO_MOVE;
        test_elf.x -= 1;
        if (elves.find(test_elf.to_string()) != elves.end())
          return Movement::NO_MOVE;
        test_elf.x += 2;
        if (elves.find(test_elf.to_string()) != elves.end())
          return Movement::NO_MOVE;

        return Movement::S;
      };

  std::function<Movement(const std::unordered_map<std::string, Elf>&, const Elf&)> checkWest =
      [](const std::unordered_map<std::string, Elf>& elves, const Elf& elf)
      {
        Elf test_elf = elf;
        test_elf.x -= 1;
        if (elves.find(test_elf.to_string()) != elves.end())
          return Movement::NO_MOVE;
        test_elf.y -= 1;
        if (elves.find(test_elf.to_string()) != elves.end())
          return Movement::NO_MOVE;
        test_elf.y += 2;
        if (elves.find(test_elf.to_string()) != elves.end())
          return Movement::NO_MOVE;

        return Movement::W;
      };

  std::function<Movement(const std::unordered_map<std::string, Elf>&, const Elf&)> checkEast =
      [](const std::unordered_map<std::string, Elf>& elves, const Elf& elf)
      {
        Elf test_elf = elf;
        test_elf.x += 1;
        if (elves.find(test_elf.to_string()) != elves.end())
          return Movement::NO_MOVE;
        test_elf.y -= 1;
        if (elves.find(test_elf.to_string()) != elves.end())
          return Movement::NO_MOVE;
        test_elf.y += 2;
        if (elves.find(test_elf.to_string()) != elves.end())
          return Movement::NO_MOVE;

        return Movement::E;
      };
  std::vector<std::function<Movement(const std::unordered_map<std::string, Elf>&, const Elf&)>> direction_getters = {checkNorth,
                                                                                                                     checkSouth,
                                                                                                                     checkWest,
                                                                                                                     checkEast};

  Movement getNextMove(const std::unordered_map<std::string, Elf>& elves, const Elf& elf) const
  {
    std::vector<Movement> results;
    results.push_back(direction_getters[0](elves, elf));
    results.push_back(direction_getters[1](elves, elf));
    results.push_back(direction_getters[2](elves, elf));
    results.push_back(direction_getters[3](elves, elf));

    bool all_clear = true;
    for (const Movement& res : results)
    {
      if (res == Movement::NO_MOVE)
      {
        all_clear = false;
        break;
      }
    }
    if (all_clear)
      return Movement::NO_MOVE;

    for (const Movement& res : results)
    {
      if (res != Movement::NO_MOVE)
      {
        return res;
      }
    }
    return Movement::NO_MOVE;
  };
};

struct Reservation
{
  long x;
  long y;
  std::vector<Elf> reservers;
  std::string to_string()
  {
    return std::to_string(x) + "|" + std::to_string(y);
  }
};

void readInput(std::unordered_map<std::string, Elf>& elves)
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_23_input.txt");
  std::string line;
  int y = 0;
  while (getline(file, line))
  {
    for (int i = 0; i < line.size(); i++)
    {
      if (line[i] == '#')
      {
        Elf elf;
        elf.x = i;
        elf.y = y;
        elves[elf.to_string()] = elf;
      }
    }
    y++;
  }
  file.close();
}



void doReservations(const DirectionGetter& dir_getter, std::unordered_map<std::string, Elf>& elves, std::unordered_map<std::string, Reservation>& reservations)
{
  for (auto& e : elves)
  {
    Elf& elf = e.second;
    Movement move = dir_getter.getNextMove(elves, elf);
    if (move == Movement::NO_MOVE)
      continue;

    elf.move = move;

    Reservation res;
    Elf test_elf = elf;
    test_elf.applyMove();
    res.x = test_elf.x;
    res.y = test_elf.y;

    if (reservations.find(res.to_string()) == reservations.end())
      reservations[res.to_string()] = res;

    reservations[res.to_string()].reservers.push_back(elf);
  }
}

void checkReservations(std::unordered_map<std::string, Reservation>& reservations)
{
  for (auto& res : reservations)
  {
    if (res.second.reservers.size() > 1)
      reservations.erase(res.second.to_string());
  }
}

void applyMovements(std::unordered_map<std::string, Elf>& elves, std::unordered_map<std::string, Reservation>& reservations)
{
  for (const auto& res : reservations)
  {
    Elf test_elf = res.second.reservers.back();
    elves.erase(test_elf.to_string());
    test_elf.applyMove();
    elves[test_elf.to_string()] = test_elf;
  }
}

void DailyTask23::part1()
{
  std::unordered_map<std::string, Elf> elves;
  readInput(elves);

  int steps = 10;

  DirectionGetter dir_getter;

  while (steps > 0)
  {
    steps--;

    std::unordered_map<std::string, Reservation> reservations;
    doReservations(dir_getter,elves, reservations);

    std::rotate(dir_getter.direction_getters.begin(),
                dir_getter.direction_getters.begin() + 1,
                dir_getter.direction_getters.end());

    checkReservations(reservations);

    applyMovements(elves, reservations);

  }

  long min_x = std::numeric_limits<long>::max();
  long max_x = -std::numeric_limits<long>::max();
  long min_y = min_x;
  long max_y = max_x;

  for (const auto& el : elves)
  {
    const Elf& elf = el.second;
    min_x = std::min(elf.x, min_x);
    max_x = std::max(elf.x, max_x);
    min_y = std::min(elf.y, min_y);
    max_y = std::max(elf.y, max_y);
  }

  int result = 0;
  for (long i = min_x; i <= max_x; i++)
    for (long j = min_y; j <= max_y; j++)
    {
      std::string hash = std::to_string(i) + "|" + std::to_string(j);
      if (elves.find(hash) == elves.end())
        result++;
    }

    std::cout<<"Part 1: result: " <<result<< "\n";
}

void DailyTask23::part2()
{
  std::unordered_map<std::string, Elf> elves;
  readInput(elves);

  long steps = 0;

  DirectionGetter dir_getter;

  while (true)
  {
    steps++;

    std::unordered_map<std::string, Reservation> reservations;
    doReservations(dir_getter,elves, reservations);

    std::rotate(dir_getter.direction_getters.begin(),
                dir_getter.direction_getters.begin() + 1,
                dir_getter.direction_getters.end());

    checkReservations(reservations);

    if (reservations.empty())
      break;

    applyMovements(elves, reservations);

  }

  std::cout<<"Part 1: result: " <<steps - 1<< "\n";
}

int main() {

  DailyTask23 dt23("--- Day 23: Unstable Diffusion ---");
  dt23.part1();
  dt23.part2();

  return 0;
}