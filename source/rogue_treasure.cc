#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

struct Point {
    int row;
    int column;
};

int board_size = 30;
Point player_point;

//Outputs the entire map
void PrintMap(vector<vector<string>> &map) {
  for (int i = 0; i < map.size(); ++i) {
    for (int j = 0; j < map[i].size(); ++j) {
      cout << map[i][j];
    }
    cout << endl;
  }
}

//Checks if the passed in location is a valid location to be in
//That is, checks for a wall or in the future, obstacles
bool ValidMove(vector<vector<string>> &map, Point &new_position) {
  string map_character = map[new_position.row][new_position.column];

  cout << map_character << endl;

  //Check for walls
  if (map_character == "|" || map_character == "-") {
    return false;
  }
  else if (map_character == "X") {
    return false;
  }
  
  return true;
}

bool MoveCharacter(vector<vector<string>> &map, string &action, Point &current_position) {
  //We control the acceptable vocabulary, we know directions won't have the same
  //first letter. So, we can just lowercase it and know it should be unique
  int action_letter = tolower(action[0]);

  //Coordinates for character's current position
  int current_column = current_position.column;
  int current_row = current_position.row;

  //Used to hold for next position
  Point next_position;
  next_position.column = current_column;
  next_position.row = current_row;

  //Grabs the current char representing a character
  string character_tile = map[current_row][current_column];
  string new_location_tile;

  //Update next_position based on movement action
  if (action_letter == 'a') {
    --next_position.column;
  }
  else if (action_letter == 'd') {
    ++next_position.column;
  }
  else if (action_letter == 'w') {
    --next_position.row;
  }
  else if (action_letter == 's') {
    ++next_position.row;
  }

  //Validate movement
  if (ValidMove(map, next_position)) {
    //Rename for cleanliness
    int next_row = next_position.row;
    int next_column = next_position.column;

    //Keep track of the next tile (could be a pickup)
    new_location_tile = map[next_row][next_column];

    new_location_tile = map[next_row][next_column];
    //Do replacement of characters
    map[current_row][current_column] = new_location_tile;
    map[next_row][next_column] = character_tile;

    //Update the current position
    current_position = next_position;

    //TODO: Stop using a global variable
    player_point = current_position;
  }

  if (new_location_tile == "X") {
    return true;
  }

  return false;
}

void CreateEnemies(vector<vector<string>> &map,
                      int enemyCount,
                      vector<Point> &monster_points) {
  srand(time(0));
  for (int i = 0; i < enemyCount; ++i) {
    Point monster_point;
    monster_point.row = rand() % board_size + 1;
    monster_point.column = rand() % board_size + 1;
    string generated_tile = map[monster_point.row][monster_point.column];

    if (generated_tile == "X") {
      --i;
    }
    else {
      map[monster_point.row][monster_point.column] = "M";
      monster_points.push_back(monster_point);
    }
  }
}

void MoveEnemies(vector<vector<string>> &map,
                    vector<Point> &monster_points) {
  for (int i = 0; i < monster_points.size(); ++i) {
    string current_monster = map[monster_points[i].row][monster_points[i].column];
    int monster_row = monster_points[i].row;
    int monster_column = monster_points[i].column;

    int row_delta = player_point.row - monster_row;
    int column_delta = player_point.column - monster_column;

    const int left = 0;
    const int right = 1;
    const int up = 2;
    const int down = 3;
    vector<int> movement_weights;

    //Player is above the monster
    if (row_delta < 0) {
      for (int i = 0; i < 70; ++i) {
        movement_weights.push_back(up);
      }
      for (int i = 0; i < 30; ++i) {
        movement_weights.push_back(down);
      }
    }

    //Player is below
    if (row_delta > 0) {
      for (int i = 0; i < 70; ++i) {
        movement_weights.push_back(down);
      }
      for (int i = 0; i < 30; ++i) {
        movement_weights.push_back(up);
      }
    }

    //Player is to the left
    if (column_delta < 0) {
      for (int i = 0; i < 70; ++i) {
        movement_weights.push_back(left);
      }
      for (int i = 0; i < 30; ++i) {
        movement_weights.push_back(right);
      }
    }

    //Player is to the right
    if (column_delta > 0) {
      for (int i = 0; i < 70; ++i) {
        movement_weights.push_back(right);
      }
      for (int i = 0; i < 30; ++i) {
        movement_weights.push_back(left);
      }
    }

    //TODO: Work on monster movement
    int direction = movement_weights[rand() % movement_weights.size()];

    if (direction == up) {
      map[monster_row][monster_column] = " ";
      --monster_row;
      map[monster_row][monster_column] = current_monster;
      monster_points[i].row = monster_row;
      monster_points[i].column = monster_column;
    }
    else if (direction == down) {
      map[monster_row][monster_column] = " ";
      ++monster_row;
      map[monster_row][monster_column] = current_monster;
      monster_points[i].row = monster_row;
      monster_points[i].column = monster_column;
    }
    else if (direction == left) {
      map[monster_row][monster_column] = " ";
      --monster_column;
      map[monster_row][monster_column] = current_monster;
      monster_points[i].row = monster_row;
      monster_points[i].column = monster_column;
    }
    else if (direction == right) {
      map[monster_row][monster_column] = " ";
      ++monster_column;
      map[monster_row][monster_column] = current_monster;
      monster_points[i].row = monster_row;
      monster_points[i].column = monster_column;
    }
  }
}

void CreateWinPoint(vector<vector<string>> &map) {
  //Give a seed for random generation
  srand(time(0));

  Point exit_point;
  exit_point.row = rand() % board_size + 1;
  exit_point.column = rand() % board_size + 1;

  map[exit_point.row][exit_point.column] = "X";
}

int main() {
  bool win = false;
  int current_level = 0;
  int max_level = 10;

  for (int i = current_level; i < max_level; ++i, ++current_level) {
    system("cls");
    cout << "Current Level: " << current_level + 1 << endl;

    Point pos;

    vector<vector<string>> map;
    vector<string> border_row;
    vector<string> map_row;
    vector<Point> monster_points;

    for (int i = 0; i < board_size + 2; ++i) {
      border_row.push_back("-");
    }

    map_row.push_back("|");
    for (int i = 0; i < board_size; ++i) {
      map_row.push_back(" ");
    }
    map_row.push_back("|");

    map.push_back(border_row);
    for (int i = 0; i < board_size; ++i) {
      map.push_back(map_row);
    }
    map.push_back(border_row);

    pos.column = 1;
    pos.row = 1;
    map[pos.row][pos.column] = "@";

    string action;

    CreateWinPoint(map);
    CreateEnemies(map, 5, monster_points);

    do {
      PrintMap(map);
      cin >> action;
      win = MoveCharacter(map, action, pos);
      MoveEnemies(map, monster_points);
      system("cls");
      cout << "Current Level: " << current_level + 1 << endl;
    } while (!win && action != "quit" && action != "exit");
  }

  system("cls");
  cout << "Congratulations, you beat the game!" << endl;

  return 0;
}