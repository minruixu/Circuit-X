#ifndef WINDOW_H_
#define WINDOW_H_
#include <string>
#include <ncurses.h>
#include <curses.h>
#include <string>
#include <vector>
#include "circuit.hpp"
using namespace std;
class Window{
private:
  int x,y;
  static Window* instance_;
  string logg;
  Window();
  ~Window();
public:
  static Window* GetInstance();
  static void DeleteInstance();
  string input();
  void freshWindow(Circuit* circuit);
  void print(string str);
  void listCommand(vector<string> command);
};
#endif
