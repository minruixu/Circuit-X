#include <string>
#include <vector>
#include <ncurses.h>
#include <curses.h>
#include "parser.hpp"
#include "position.hpp"
#include "circuit.hpp"
#include "gate.hpp"
using namespace std;
Parser::Parser(Window *window){
  window_ = window;
}
Parser::~Parser(){
}
bool Parser::HandleCommand(Circuit* circuit,string command){
  all_command.push_back(command);
  if(command[0]=='N'){//new a gate
    vector<string> com = split(command);
    vector <int> xy = getxy(com[2]);
    if(circuit->newGate(com,xy[0],xy[1]))
    window_->print("New gate succesfully");
    else window_->print("New gate fail");
  }
  else if(command[0] == 'C'){//connect 2 interface
    vector<string> com = split(command);
    int x1 = getxy(com[1])[0];
    int y1 = getxy(com[1])[1];
    int x2 = getxy(com[2])[0];
    int y2 = getxy(com[2])[1];
    if(circuit->connect(Position(x1,y1),Position(x2,y2)))
      window_->print("Connect succesfully");
    else window_->print("Connect fail");
  }
  /*else if(command[0] == 'M'){//move interface's data
    vector<string> com = split(command);
    int x1 = com[1][0] - '0';
    int y1 = com[1][2] - '0';
    bool data = com[2][0] - '0';
    circuit->moveData(Position(x1,y1),data);
  }*/
  else if(command[0] == 'D'){//disconnect two interface
    vector<string> com = split(command);
    int x1 = getxy(com[2])[0];
    int y1 = getxy(com[2])[1];
    if(circuit->disconnect(Position(x1,y1))){
      window_->print("Disconnect succesfully");
    }
    else window_->print("Disconnect fail");
  }
  else if(command[0] == 'L'){//list all
    window_->listCommand(all_command);
  }
  else if(command[0] == 'S'){//save command as a file
  }
  else if(command[0] == 'R'){//run the circuit
    window_->print("start to run");
    try{
      int i = 0;
      i = circuit->run();
      if(i == 1) throw 1;
      else if(i == 0) throw 'c';
    }
    catch(int){
      window_->print("环异常");
    }
    catch(...){
      window_->print("Run succesfully");
    }
    //window_->print("end");
  }
  else if(command[0] == 'Q'){
    return false;
  }
  else if(command[0] =='/'){
    
  }
  return true;
}
vector<string> Parser::split(string command){
  vector <string> str;
  string s;
  for(int i = 0;i<command.length();i++){
    if((command[i] == ' '||command[i]=='\n')&&s!=""){
      str.push_back(s);
      s.erase();
    }
    else {
      s += command[i];
    }
  }
  if(s.length()) str.push_back(s);
  return str;
}
vector<int> Parser::getxy(string pos){
  string s;
  vector <int> xy;
  for(int i = 0;i<=pos.length();i++){
    if(pos[i] == ','||pos[i]=='\n'||i==pos.length()){
      try {
		    xy.push_back(stoi(s));
	    }
	    catch (std::invalid_argument&){
		    window_->print("invalid position");
	    }
	    catch (std::out_of_range&){
		    cout << "Out of range" << endl;
	    }
	    catch (...) {
		    cout << "Something else" << endl;
	    }
      s.erase();
    }
    else{
      s+=pos[i];
    }
  }
  //xy.push_back(stoi(s));
  return xy;
}
Parser* Parser::instance_ = NULL;
