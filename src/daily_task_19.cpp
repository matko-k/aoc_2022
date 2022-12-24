#include <DailyTask/daily_task_19.h>
#include <unordered_set>

struct OreRobot
{
  int ore_cost;
};

struct ClayRobot
{
  int ore_cost;
};

struct ObsidianRobot
{
  int ore_cost;
  int clay_cost;
};

struct GeodeRobot
{
  int ore_cost;
  int obsidian_cost;
};

struct Blueprint
{
  int id;
  OreRobot ore_robot;
  ClayRobot clay_robot;
  ObsidianRobot obsidian_robot;
  GeodeRobot geode_robot;
};

struct Production
{
  int ore_robots = 0;
  int clay_robots = 0;
  int obs_robots = 0;
  int geo_robots = 0;
};

struct Materials
{
  int ore = 0;
  int clay = 0;
  int obsidian = 0;
  int geode = 0;
};

void readInput(std::vector<Blueprint>& blueprints)
{
  std::ifstream file;
  file.open("../daily_inputs/daily_task_19_input.txt");
  std::string line;

  int count = 1;

  while (std::getline(file, line))
  {
    Blueprint blueprint;
    blueprint.id = count++;
    std::stringstream ss(line);
    std::string buffer;
    while (ss >> buffer)
      if (buffer == "costs")
        break;
    ss>>buffer;
    blueprint.ore_robot.ore_cost = stoi(buffer);
    while (ss >> buffer)
      if (buffer == "costs")
        break;
    ss>>buffer;
    blueprint.clay_robot.ore_cost = stoi(buffer);
    while (ss >> buffer)
      if (buffer == "costs")
        break;
    ss>>buffer;
    blueprint.obsidian_robot.ore_cost = stoi(buffer);
    ss>>buffer;ss>>buffer;ss>>buffer;
    blueprint.obsidian_robot.clay_cost = stoi(buffer);
    while (ss >> buffer)
      if (buffer == "costs")
        break;
    ss>>buffer;
    blueprint.geode_robot.ore_cost = stoi(buffer);
    ss>>buffer;ss>>buffer;ss>>buffer;
    blueprint.geode_robot.obsidian_cost = stoi(buffer);
    blueprints.push_back(blueprint);
    continue;
  }

  file.close();

}

std::string to_string(const Production& prod, const Materials& mater, int minutes)
{
  return std::to_string(prod.ore_robots) + "|"
   + std::to_string(prod.clay_robots) + "|"
   + std::to_string(prod.obs_robots) + "|"
   + std::to_string(prod.geo_robots) + "|"
   + std::to_string(mater.ore) + "|"
   + std::to_string(mater.clay) + "|"
   + std::to_string(mater.obsidian) + "|"
   + std::to_string(mater.geode) + "|"
   + std::to_string(minutes);
}

bool canBuildGeoRobot(const Blueprint& blueprint, const Materials& mater)
{
  return mater.obsidian >= blueprint.geode_robot.obsidian_cost &&
         mater.ore >= blueprint.geode_robot.ore_cost;
}

bool canBuildObsRobot(const Blueprint& blueprint, const Materials& mater)
{
  return mater.clay >= blueprint.obsidian_robot.clay_cost &&
         mater.ore >= blueprint.obsidian_robot.ore_cost;
}

bool canBuildClayRobot(const Blueprint& blueprint, const Materials& mater)
{
  return mater.ore >= blueprint.clay_robot.ore_cost;
}

bool canBuildOreRobot(const Blueprint& blueprint, const Materials& mater)
{
  return mater.ore >= blueprint.ore_robot.ore_cost;
}


bool shouldBuildOreRobot(const Production& prod, const Blueprint& blueprint)
{
  int max_ore = 0;
  max_ore = std::max(max_ore, blueprint.ore_robot.ore_cost);
  max_ore = std::max(max_ore, blueprint.clay_robot.ore_cost);
  max_ore = std::max(max_ore, blueprint.obsidian_robot.ore_cost);
  max_ore = std::max(max_ore, blueprint.geode_robot.ore_cost);

  return prod.ore_robots < max_ore;
}

bool shouldBuildClayRobot(const Production& prod, const Blueprint& blueprint)
{
  return prod.clay_robots < blueprint.obsidian_robot.clay_cost;
}

bool shouldBuildObsRobot(const Production& prod, const Blueprint& blueprint)
{
  return prod.obs_robots < blueprint.geode_robot.obsidian_cost;
}

bool shouldWait(const Materials& materials, const Blueprint& blueprint)
{
  int max_ore = 0;
  max_ore = std::max(max_ore, blueprint.ore_robot.ore_cost);
  max_ore = std::max(max_ore, blueprint.clay_robot.ore_cost);
  max_ore = std::max(max_ore, blueprint.obsidian_robot.ore_cost);
  max_ore = std::max(max_ore, blueprint.geode_robot.ore_cost);

  return !(max_ore < materials.ore &&
  blueprint.obsidian_robot.clay_cost < materials.clay &&
  blueprint.geode_robot.obsidian_cost < materials.obsidian);

}

void doProduction(const Production& prod, Materials& mater)
{
  mater.ore += prod.ore_robots;
  mater.clay += prod.clay_robots;
  mater.obsidian += prod.obs_robots;
  mater.geode += prod.geo_robots;
}

int maxGeodesPossible(int minutes, int production)
{
  int total = 0;
  while (minutes > 0)
  {
    minutes--;
    total += production;
    production++;
  }
  return total;
}

void maximizeGeodes(std::unordered_set<std::string>& explored_states, const Blueprint& blueprint, int minutes_remaining,
                   const Production& production, const Materials& materials, int& max_geodes)
{
  if (explored_states.find(to_string(production, materials, minutes_remaining)) != explored_states.end())
    return;

  if (minutes_remaining <= 0)
    return;

  if (max_geodes > materials.geode + maxGeodesPossible(minutes_remaining, production.geo_robots))
    return;

  explored_states.insert(to_string(production, materials, minutes_remaining));

  if (shouldWait(materials, blueprint))
  {
    Materials new_materials = materials;
    doProduction(production, new_materials);
    max_geodes = std::max(max_geodes, new_materials.geode);

    maximizeGeodes(explored_states, blueprint, minutes_remaining - 1, production, new_materials, max_geodes);
  }

  if (shouldBuildOreRobot(production, blueprint) &&
      canBuildOreRobot(blueprint, materials))
  {
    Materials new_materials = materials;
    Production new_production = production;
    new_materials.ore -= blueprint.ore_robot.ore_cost;
    doProduction(new_production, new_materials);
    max_geodes = std::max(max_geodes, new_materials.geode);
    new_production.ore_robots++;
    maximizeGeodes(explored_states, blueprint, minutes_remaining - 1, new_production, new_materials, max_geodes);
  }

  if (shouldBuildClayRobot(production, blueprint) &&
      canBuildClayRobot(blueprint, materials))
  {
    Materials new_materials = materials;
    Production new_production = production;
    new_materials.ore -= blueprint.clay_robot.ore_cost;
    doProduction(new_production, new_materials);
    max_geodes = std::max(max_geodes, new_materials.geode);
    new_production.clay_robots++;
    maximizeGeodes(explored_states, blueprint, minutes_remaining - 1, new_production, new_materials, max_geodes);
  }

  if (canBuildObsRobot(blueprint, materials)
      && !canBuildGeoRobot(blueprint, materials)) {
    Materials new_materials = materials;
    Production new_production = production;
    new_materials.clay -= blueprint.obsidian_robot.clay_cost;
    new_materials.ore -= blueprint.obsidian_robot.ore_cost;
    doProduction(new_production, new_materials);
    max_geodes = std::max(max_geodes, new_materials.geode);
    new_production.obs_robots++;
    maximizeGeodes(explored_states, blueprint, minutes_remaining - 1, new_production, new_materials, max_geodes);
  }
  if (canBuildGeoRobot(blueprint, materials))
  {
    Materials new_materials = materials;
    Production new_production = production;
    new_materials.obsidian -= blueprint.geode_robot.obsidian_cost;
    new_materials.ore -= blueprint.geode_robot.ore_cost;
    doProduction(new_production, new_materials);
    max_geodes = std::max(max_geodes, new_materials.geode);
    new_production.geo_robots++;
    maximizeGeodes(explored_states, blueprint, minutes_remaining - 1, new_production, new_materials, max_geodes);
  }
}

void DailyTask19::part1()
{
  std::vector<Blueprint> blueprints;
  readInput(blueprints);
  int result = 0;
  for (const Blueprint& blueprint : blueprints)
  {
    int minutes_remaining = 24;

    Production production;
    Materials materials;
    production.ore_robots = 1;
    materials.ore = 1;
    std::unordered_set<std::string> explored_states = {};
    int max_geode = -1;

    maximizeGeodes(explored_states, blueprint, minutes_remaining - 1, production, materials, max_geode);

    std::cout<<blueprint.id <<": "<<max_geode<<"\n";
    result += max_geode * blueprint.id;
  }

  std::cout<<"Part 1: result: "<< result <<"\n";
}

void DailyTask19::part2()
{
  std::vector<Blueprint> blueprints;
  readInput(blueprints);
  long result = 1;
  for (int i = 0; i < 3; i++)
  {
    Blueprint& blueprint = blueprints[i];
    int minutes_remaining = 32;

    Production production;
    Materials materials;
    production.ore_robots = 1;
    materials.ore = 1;
    std::unordered_set<std::string> explored_states = {};
    int max_geode = -1;

    maximizeGeodes(explored_states, blueprint, minutes_remaining - 1, production, materials, max_geode);

    std::cout<<blueprint.id <<": "<<max_geode<<"\n";
    result *= max_geode;
  }

  std::cout<<"Part 2: result: "<< result <<"\n";
}

int main() {

  DailyTask19 dt19("--- Day 19: Not Enough Minerals ---");
  dt19.part1();
  dt19.part2();

  return 0;
}