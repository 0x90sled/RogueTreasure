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

void MoveCharacter(vector<string> &map, string action, POS &pos) {
  char action_char = tolower(action[0]);
  if (action_char == 'r') {
    map[pos.y][pos.x++] = ' ';
    map[pos.y][pos.x] = '@';
  } 
  else if (action_char == 'd') {
    map[pos.y++][pos.x] = ' ';
    map[pos.y][pos.x] = '@';
  } 
  else if (action_char == 'u') {
    map[pos.y--][pos.x] = ' ';
    map[pos.y][pos.x] = '@';
  }
  else if (action_char == 'l') {
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