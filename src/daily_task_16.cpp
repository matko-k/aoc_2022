#include <DailyTask/daily_task_16.h>

struct Valve
{
  std::string ID;
  int flow;
  int opened_timestamp = -1;

  std::vector<std::string> connections = {};
};

void readInput(std::unordered_map<std::string, Valve>& valves)
{
  std::ifstream file;
  std::string line;
  file.open("../daily_inputs/daily_task_16_input.txt");

  while (std::getline(file, line))
  {
    Valve valve;
    std::string buffer;
    std::stringstream ss(line);
    ss >> buffer; ss >> buffer;
    valve.ID = buffer;

    ss >> buffer; ss >> buffer; ss >> buffer;
    valve.flow = stoi(buffer.substr(buffer.find('=') + 1, buffer.length()));

    ss >> buffer; ss >> buffer; ss >> buffer; ss >> buffer;
    while (ss >> buffer)
    {
      if (buffer.back() == ',')
        buffer = buffer.substr(0, buffer.length()-1);
      valve.connections.push_back(buffer);
    }

    valves[valve.ID] = valve;
  }

  file.close();

}

std::string getStateID(const std::unordered_map<std::string, Valve>& valves, const std::string& current, int minutes, bool elephant)
{
  std::string out = "";
  for (const auto& valve : valves)
  {
    out += valve.first + "|" + std::to_string(valve.second.opened_timestamp > 0) + '|';
  }
  out += '|' + current;
  out += '|' + std::to_string(minutes);
  out += '|' + std::to_string(elephant);

  return out;
}

int getMaxFlow(std::unordered_map<std::string, Valve> valves, std::unordered_map<std::string, int>& saved_max_states,
               const std::string& current, int minutes, bool elephant)
{
  if (minutes <= 0)
  {
    if (!elephant)
      return 0;

    return getMaxFlow(valves, saved_max_states, "AA", 26, false);
  }

  Valve& current_valve = valves[current];

  std::string state_id = getStateID(valves, current, minutes, elephant);
  if (saved_max_states.find(state_id) != saved_max_states.end())
    return saved_max_states[state_id];

  int max = 0;
  if (current_valve.opened_timestamp < 0 && current_valve.flow > 0)
  {
    current_valve.opened_timestamp = minutes;
    max = std::max(max, (current_valve.opened_timestamp-1)*current_valve.flow +
                        getMaxFlow(valves, saved_max_states, current, minutes-1, elephant));
  }

  for (const std::string& next : current_valve.connections)
  {
    max = std::max(max, getMaxFlow(valves, saved_max_states, next, minutes-1, elephant));
  }

  saved_max_states[state_id] = max;
  return max;
}

void DailyTask16::part1()
{
  std::unordered_map<std::string, Valve> valves;
  readInput(valves);

  std::unordered_map<std::string, int> saved_max_states = {};
  int minutes = 30;

  int result = getMaxFlow(valves, saved_max_states, "AA", minutes, false);

  std::cout<<"Part 1: result: "<< result <<"\n";
}

void DailyTask16::part2()
{
  std::unordered_map<std::string, Valve> valves;
  readInput(valves);

  std::unordered_map<std::string, int> saved_max_states = {};
  int minutes = 26;

  int result = getMaxFlow(valves, saved_max_states, "AA", minutes, true);

  std::cout<<"Part 2: result: "<< result <<"\n";
}

int main() {

  DailyTask16 dt16("--- Day 16: Proboscidea Volcanium ---");
  dt16.part1();
  dt16.part2();

  return 0;
}