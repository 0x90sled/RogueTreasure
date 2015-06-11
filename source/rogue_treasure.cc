#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct POS {
    int x;
    int y;
};

void PrintMap(vector<string> &map) {
  for (int i = 0; i < 5; ++i) {
    cout << map[i] << endl;
  }
}

bool ValidLocation(vector<string> &map, POS &pos) {
  int x = pos.x;
  int y = pos.y;

  //Checks for out of bounds
  if (x < 0 || x > map[y].size() - 1) {
    return false;
  }
  else if (y < 0 || y > map.size() - 1) {
    return false;
  }

  //Check for a wall
  if (map[y][x] == '|') {
    return false;
  }

  return true;
}

void MoveCharacter(vector<string> &map, string action, POS &pos) {
  char action_char = tolower(action[0]);

  if (action_char == 'r') {
    POS nextPos;
    nextPos.x = pos.x + 1;
    nextPos.y = pos.y;

    if (!ValidLocation(map, nextPos)) {
      return;
    }

    map[pos.y][pos.x++] = ' ';
    map[pos.y][pos.x] = '@';
  } 
  else if (action_char == 'd') {
    POS nextPos;
    nextPos.x = pos.x;
    nextPos.y = pos.y + 1;

    if (!ValidLocation(map, nextPos)) {
      return;
    }

    map[pos.y++][pos.x] = ' ';
    map[pos.y][pos.x] = '@';
  } 
  else if (action_char == 'u') {
    POS nextPos;
    nextPos.x = pos.x;
    nextPos.y = pos.y - 1;

    if (!ValidLocation(map, nextPos)) {
      return;
    }

    map[pos.y--][pos.x] = ' ';
    map[pos.y][pos.x] = '@';
  }
  else if (action_char == 'l') {
    POS nextPos;
    nextPos.x = pos.x - 1;
    nextPos.y = pos.y;

    if (!ValidLocation(map, nextPos)) {
      return;
    }

    map[pos.y][pos.x--] = ' ';
    map[pos.y][pos.x] = '@';
  }
}

int main() {
  system("cls");

  POS pos;

  string map_raw[] = {
    "|@    |",
    "|     |",
    "|     |",
    "|     |",
    "|     |",
  };

  vector<string> map;
  for (int i = 0; i < 5; ++i) {
    map.push_back(map_raw[i]);
  }

  pos.x = 1;
  pos.y = 0;

  string action;

  do {
    PrintMap(map);
    cin >> action;
    MoveCharacter(map, action, pos);
    system("cls");
  } while (action != "quit");

  return 0;
}