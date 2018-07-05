#include <ncurses.h>
#include <curses.h>
#include <string>
#include "window.hpp"
#include "circuit.hpp"
using namespace std;
Window::Window(){
  x = 0;
  y = 0;
  initscr();
  echo();
  //raw();
  cbreak();
  keypad(stdscr,TRUE);
}
Window::~Window(){
  erase();
  endwin();
}
Window* Window::GetInstance(){
  if(instance_ != NULL) return instance_;
  else{
    instance_ = new Window;
    return instance_;
  }
}
void Window::DeleteInstance(){
  if(instance_!=NULL) {
    delete instance_;
    instance_ = NULL;
  }
}
string Window::input(){
  string str;
  char c[20];
  mvprintw(42,0,"%s","Input command:");
  refresh();
  move(42,14);
  /*do{
    c = getch();
    str+= c;
    refresh();
  }while(c!='\n');*/
  getstr(c);
  str = c;
  //refresh();
  return str;
}
void Window::freshWindow(Circuit* circuit){
  erase();
  for(int i = 0;i<40;i++){
    for(int j = 0;j<132;j++){
      mvaddch(i,j,circuit->picture_[i][j]);
    }
  }
  print(logg);
  //mvprintw(42,0,"%s","Input command:");
  refresh();
  //getch();
}
void Window::listCommand(vector<string> command){
  erase();
  for(int i = 0;i<command.size();i++){
    mvaddstr(i,0,command[i].c_str());
  }
  refresh();
  getch();
}
void Window::print(string str){
  logg = str;
  mvaddstr(40,0,logg.c_str());
  refresh();
}
Window* Window::instance_ = NULL;
