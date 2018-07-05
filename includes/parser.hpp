#ifndef PARSER_H_
#define PARSER_H_
#include <iostream>
#include <string>
#include "position.hpp"
#include "circuit.hpp"
#include "window.hpp"
#include "gate.hpp"
using namespace std;
class Parser{
private:
  Parser(Window* window);
  ~Parser();
  Window * window_;
  vector<string> all_command;
  static Parser* instance_;
public:
  static Parser* GetInstance(Window* window){
    if(instance_ != NULL) return instance_;
    else{
      instance_ = new Parser(window);
      return instance_;
    }
  }
  static void DeleteInstance(){
    if(instance_ != NULL) {
      delete instance_;
      instance_ = NULL;
    }
  }
  bool HandleCommand(Circuit* circuit,string command);
  vector<string> split(string command);
  vector<int> getxy(string pos);
};
#endif
