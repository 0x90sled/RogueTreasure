#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Point {
    int row;
    int column;
};

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
  
  return true;
}

void MoveCharacter(vector<vector<string>> &map, string &action, Point &current_position) {
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
  if (action_letter == 'l') {
    --next_position.column;
  }
  else if (action_letter == 'r') {
    ++next_position.column;
  }
  else if (action_letter == 'u') {
    --next_position.row;
  }
  else if (action_letter == 'd') {
    ++next_position.row;
  }

  //Validate movement
  if (ValidMove(map, next_position)) {
    int next_row = next_position.row;
    int next_column = next_position.column;

    new_location_tile = map[next_row][next_column];
    map[current_row][current_column] = new_location_tile;
    map[next_row][next_column] = character_tile;
    current_position = next_position;
  }
}


int main() {
  const unsigned int size = 10;
  system("cls");

  Point pos;

  vector<vector<string>> map;
  vector<string> border_row;
  vector<string> map_row;

  for (int i = 0; i < size + 2; ++i) {
    border_row.push_back("-");
  }

  map_row.push_back("|");
  for (int i = 0; i < size; ++i) {
    map_row.push_back(" ");
  }
  map_row.push_back("|");

  map.push_back(border_row);
  for (int i = 0; i < size; ++i) {
    map.push_back(map_row);
  }
  map.push_back(border_row);

  pos.column = 1;
  pos.row = 1;
  map[pos.row][pos.column] = "@";

  string action;

  do {
    PrintMap(map);
    cin >> action;
    MoveCharacter(map, action, pos);
    //system("cls");
  } while (action != "quit" && action != "exit");

  return 0;
}