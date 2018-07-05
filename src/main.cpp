#include <iostream>
#include <ncurses.h>
#include <curses.h>
#include <vector>
#include <queue>
#include <string>
#include "position.hpp"
#include "circuit.hpp"
#include "window.hpp"
#include "parser.hpp"
using namespace std;
//const int max_width = 132;
//const int max_height = 40;
int main(){
  //用显示器显示输出
  string command;
  bool on = true;
  Window *window = Window::GetInstance();
  Parser *parser = Parser::GetInstance(window);
  Circuit *circuit = Circuit::GetInstance();
  window->print("Please read the manual first!");
  window->freshWindow(circuit);
  while(on){
    command = window->input();
    on = parser->HandleCommand(circuit,command);
    window->freshWindow(circuit);
  }
  Parser::DeleteInstance();
  Window::DeleteInstance();
  Circuit::DeleteInstance();
}
