#include "circuit.hpp"
#include "position.hpp"
#include "gate.hpp"
#include <string>
using namespace std;
Circuit::Circuit(){
  for(int i = 0;i<max_height;i++){
    for(int j = 0;j<max_width;j++){
      map_[i][j] = '\0';
      picture_[i][j] = ' ';
    }
  }
  circuit_false_ = new Source_false(Position(0,0));
  map_[0][0] = 'o';
  picture_[0][0] = '-';
  circuit_true_ = new Source_true(Position(0,1));
  map_[1][0] = 'o';
  picture_[1][0] = '+';
}
Circuit::~Circuit(){
  for(auto &it : andgate_){
    if(it){
      delete it;
      it = NULL;
    }
  }
  for(auto &it : orgate_){
    if(it){
      delete it;
      it = NULL;
    }
  }
  for(auto &it : xorgate_){
    if(it){
      delete it;
      it = NULL;
    }
  }
  for(auto &it : inversegate_){
    if(it){
      delete it;
      it = NULL;
    }
  }
  for(auto &it : bitdisplay_){
    if(it){
      delete it;
      it = NULL;
    }
  }
  for(auto &it : bytedisplay_){
    if(it){
      delete it;
      it = NULL;
    }
  }
  andgate_.clear();
  orgate_.clear();
  xorgate_.clear();
  inversegate_.clear();
  bitdisplay_.clear();
  bytedisplay_.clear();
  delete circuit_true_;
  delete circuit_false_;
}
Circuit* Circuit::GetInstance(){
  if(instance_!=NULL) return instance_;
  else{
    instance_ = new Circuit;
    return instance_;
  }
}
void Circuit::DeleteInstance(){
  if(instance_!=NULL){
     delete instance_;
     instance_ = NULL;
  }
}
//new command
bool Circuit::newGate(vector <string> command,int _x,int _y){
  int x = _x;
  int y = _y;
  if(command[1][0] == 'A'){
    return newAnd(x,y);
  }
  else if(command[1][0] == 'O'){
    return newOr(x,y);
  }
  else if(command[1][0] == 'X'){
    return newXor(x,y);
  }
  else if(command[1][0] == 'I'){
    return newInverse(x,y);
  }
  else if(command[1][0] == 'B'&& command[1][1] == 'I'){
    return newBitdisplay(x,y);
  }
  else if(command[1][0] == 'B'&& command[1][1] == 'Y'){
    return newBytedisplay(x,y);
  }
  else return false;
}
bool Circuit::newAnd(int x,int y){//在(x,y)处 new 一个3*3的们
  //check setable
  for(int i = y;i<y+3;i++){
    for(int j = x;j<x+3;j++){
      if(map_[i][j]!='\0') return false;
    }
  }
  //draw the gate
  for(int i = y;i<y+3;i++){
    for(int j = x;j<x+3;j++){
      map_[i][j] = '1';
    }
  }
  picture_[y][x] = '-';map_[y][x] = 'i';
  picture_[y+2][x] = '-';map_[y+2][x] = 'i';
  picture_[y+1][x+1] = '&';
  picture_[y+1][x+2] = '-';map_[y+1][x+2] = 'o';
  Andgate *andgate = new Andgate(Position(x,y));
  andgate_.push_back(andgate);
  return true;
}
bool Circuit::newOr(int x,int y){
  for(int i = y;i<y+3;i++){
    for(int j = x;j<x+3;j++){
      if(map_[i][j]!='\0') return false;
    }
  }
  //draw the gate
  for(int i = y;i<y+3;i++){
    for(int j = x;j<x+3;j++){
      map_[i][j] = '1';
    }
  }
  picture_[y][x] = '-';map_[y][x] = 'i';
  picture_[y+2][x] = '-';map_[y+2][x] = 'i';
  picture_[y+1][x+1] = '|';
  picture_[y+1][x+2] = '-';map_[y+1][x+2] = 'o';
  Orgate *orgate = new Orgate(Position(x,y));
  orgate_.push_back(orgate);
  return true;
}
bool Circuit::newXor(int x,int y){
  for(int i = y;i<y+3;i++){
    for(int j = x;j<x+3;j++){
      if(map_[i][j]!='\0') return false;
    }
  }
  //draw the gate
  for(int i = y;i<y+3;i++){
    for(int j = x;j<x+3;j++){
      map_[i][j] = '1';
    }
  }
  picture_[y][x] = '-';map_[y][x] = 'i';
  picture_[y+2][x] = '-';map_[y+2][x] = 'i';
  picture_[y+1][x+1] = '^';
  picture_[y+1][x+2] = '-';map_[y+1][x+2] = 'o';
  Xorgate *xorgate = new Xorgate(Position(x,y));
  xorgate_.push_back(xorgate);
  return true;
}
bool Circuit::newInverse(int x,int y){
  for(int i = x;i<x+3;i++){
    if(map_[y][i]!='\0') return false;
  }
  for(int i = x;i<x+3;i++){
    map_[y][i] = '1';
  }
  picture_[y][x] = '-';map_[y][x] = 'i';
  picture_[y][x+1] = '>';
  picture_[y][x+2] = '-';map_[y][x+2] = 'o';
  Inversegate *inversegate = new Inversegate(Position(x,y));
  inversegate_.push_back(inversegate);
  return true;
}
bool Circuit::newBitdisplay(int x,int y){
  for(int i = y;i<y+3;i++){
    for(int j = x;j<x+3;j++){
      if(map_[i][j]!='\0') return false;
    }
  }
  for(int i = y;i<y+3;i++){
    for(int j = x;j<x+3;j++){
      map_[i][j] = '1';
    }
  }
  picture_[y][x+1] = '-';
  picture_[y][x+2] = '|';
  picture_[y+1][x] = '-';map_[y+1][x] = 'i';
  picture_[y+1][x+2] = '|';
  picture_[y+2][x+1] = '-';
  picture_[y+2][x+2] = '|';
  Bitdisplay *bitdisplay = new Bitdisplay(Position(x,y));
  bitdisplay_.push_back(bitdisplay);
  return true;
}
bool Circuit::newBytedisplay(int x,int y){
  for(int i = y;i<y+10;i++){
    for(int j = x;j<x+3;j++){
      if(map_[i][j]!='\0') return false;
    }
  }
  for(int i = y;i<y+10;i++){
    for(int j = x;j<x+3;j++){
      map_[i][j] = '1';
    }
  }
  for(int i = 0;i<10;i++){
    picture_[y+i][x+2] = '|';
  }
  for(int i = 1;i<9;i++){
    picture_[y+i][x] = '-';
    map_[y+i][x] = 'i';
  }
  picture_[y][x+1] = '-';
  picture_[y+9][x+1] = '-';
  Bytedisplay *bytedisplay = new Bytedisplay(Position(x,y));
  bytedisplay_.push_back(bytedisplay);
  return true;
}
//connect command
bool Circuit::connect(Position out,Position in){
  if(map_[out.y][out.x]!='o'||map_[in.y][in.x]!='i'){
    return false;
  }
  //connect two interface of two gate
  OutInterface* out_interface;
  if(out==Position(0,0)){
    out_interface = circuit_false_->out;
  }
  else if(out == Position(0,1)){
    out_interface = circuit_true_->out;
  }
  else {out_interface = findInterfaceViaOut(out);}

  for(auto &it : andgate_){
    if(it->inThisGate(in)) return it->setInInterface(in,out_interface);
  }
  for(auto &it : orgate_){
    if(it->inThisGate(in)) return it->setInInterface(in,out_interface);
  }
  for(auto &it : xorgate_){
    if(it->inThisGate(in)) return it->setInInterface(in,out_interface);
  }
  for(auto &it : inversegate_){
    if(it->inThisGate(in)) return it->setInput(out_interface);
  }
  for(auto &it : bitdisplay_){
    if(it->inThisDisplay(in)) return it->setInput(out_interface);
  }
  for(auto &it : bytedisplay_){
    if(it->inThisDisplay(in)) return it->setInput(in,out_interface);
  }
  return false;
}
/*bool Circuit::setGateViaOut(Position position,OutInterface* out){
  for(set<Andgate>::iterator it : andgate_){
    if(it->inThisGate(position)) return it->setInInterface(position,out);
  }
  for(set<Orgate>::iterator it : orgate_){
    if(it->inThisGate(position)) return it->setInInterface(position,out);
  }
  for(set<Xorgate>::iterator it : xorgate_){
    if(it->inThisGate(position)) return it->setInInterface(position,out);
  }
  for(set<Inversegate>::iterator it : inversegate_){
    if(it->inThisGate(position)) return it->setInput(out);
  }
  for(set<Bitdisplay>::iterator it : bitdisplay_){
    if(it->inThisGate(position)) return it->setInput(out);
  }
  for(set<Bytedisplay>::iterator it : bytedisplay_){
    if(it->inThisGate(position)) return it->setInput(position,out);
  }
  return false;
}*/
OutInterface* Circuit::findInterfaceViaOut(Position position){
  //get the gate
  OutInterface *result;
  for(auto &it : andgate_){
    if(it->inThisGate(position)) return it->out;
  }
  for(auto &it : orgate_){
    if(it->inThisGate(position)) return it->out;
  }
  for(auto &it : xorgate_){
    if(it->inThisGate(position)) return it->out;
  }
  for(auto &it : inversegate_){
    if(it->inThisGate(position)) return it->out;
  }
  return result;
}
//move command
/*bool Circuit::moveData(Position in,bool data){
  if(map_[in.x][in.y]!= 'i'){
    return false;
  }
  //connect two interface of two gate
  for(auto &it : andgate_){
    if(it->inThisGate(in)) return it->setInInterface(in,data);
  }
  for(auto &it : orgate_){
    if(it->inThisGate(in)) return it->setInInterface(in,data);
  }
  for(auto &it : xorgate_){
    if(it->inThisGate(in)) return it->setInInterface(in,data);
  }
  for(auto &it : inversegate_){
    if(it->inThisGate(in)) return it->setInput(data);
  }
  for(auto &it : bitdisplay_){
    if(it->inThisDisplay(in)) return it->setInput(data);
  }
  for(auto &it : bytedisplay_){
    if(it->inThisDisplay(in)) return it->setInput(in,data);
  }
  return false;
}*/
//disconnect command
bool Circuit::disconnect(Position in){
  if(map_[in.y][in.x]!= 'i'){
    return false;
  }
  for(auto &it : andgate_){
    if(it->inThisGate(in)) return it->disconnect(in);
  }
  for(auto &it : orgate_){
    if(it->inThisGate(in)) return it->disconnect(in);
  }
  for(auto &it : xorgate_){
    if(it->inThisGate(in)) return it->disconnect(in);
  }
  for(auto &it : inversegate_){
    if(it->inThisGate(in)) return it->disconnect();
  }
  for(auto &it : bitdisplay_){
    if(it->inThisDisplay(in)) return it->disconnect();
  }
  for(auto &it : bytedisplay_){
    if(it->inThisDisplay(in)) return it->disconnect(in);
  }
  return false;
}
//run the circuit
bool Circuit::checkCircle(){
  queue <OutInterface*> all_out;
  for(auto &it : andgate_){
    all_out.push(it->out);
  }
  for(auto &it : orgate_){
    all_out.push(it->out);
  }
  for(auto &it : xorgate_){
    all_out.push(it->out);
  }
  for(auto &it : inversegate_){
    all_out.push(it->out);
  }
  while(!all_out.empty()){
    if(!testOut(all_out.front())) return true;
    all_out.pop();
  }
  return false;
}
bool Circuit::testOut(OutInterface *out){
  int to_out = 0;
  int to_self = 0;
  queue <OutInterface*> out_q;
  queue <InInterface*> in_q;
  out_q.push(out);
  while(!out_q.empty()){
    for(auto & it : out_q.front()->next){
      in_q.push(it);
    }
    while(!in_q.empty()){
      for(auto &it : andgate_){
        if(it->inThisGate(in_q.front()->position_)) {
          if(it->out == out) to_self = true;
          else out_q.push(it->out);
        }
      }
      for(auto &it : orgate_){
        if(it->inThisGate(in_q.front()->position_)) {
          out_q.push(it->out);
          if(it->out == out) return false;
        }
      }
      for(auto &it : xorgate_){
        if(it->inThisGate(in_q.front()->position_)) {
          out_q.push(it->out);
          if(it->out == out) return false;
        }
      }
      for(auto &it : inversegate_){
        if(it->inThisGate(in_q.front()->position_)) {
          out_q.push(it->out);
          if(it->out == out) return false;
        }
      }
      in_q.pop();
    }
    out_q.pop();
  }
  return to_out&&to_self;
}
int Circuit::run(){
  //if(checkCircle()) return 1;
  //从连接的 source 开始，遍历Interface们，直到到输出口没有为止
  //在display展示出来
  //set<InInterface*> s_in;
  set<OutInterface*> s_out;
  queue<InInterface*> in;
  queue<OutInterface*> out;
  out.push(circuit_true_->out);
  out.push(circuit_false_->out);
  while(!out.empty()){
    /*while(!out.empty()){
      for(auto &it : out.front()->next){
        if(!s_in.count(it)){
          s_in.insert(it);
          in.push(it);
        }
      }
      out.pop();
    }*/
    for(auto &it : out.front()->next){
        in.push(it);
    }
    out.pop();
    while(!in.empty()){
      InInterface* temp = in.front();
      for(auto &it : andgate_){
        if(it->inThisGate(temp->position_)){
          it->freshData();
          it->run();
          if(!s_out.count(it->out)){
            out.push(it->out);
            s_out.insert(it->out);
          }
        }
      }
      for(auto &it : orgate_){
        if(it->inThisGate(temp->position_)){
          it->freshData();
          it->run();
          if(!s_out.count(it->out)){
            out.push(it->out);
            s_out.insert(it->out);
          }
        }
      }
      for(auto &it : xorgate_){
        if(it->inThisGate(temp->position_)){
          it->freshData();
          it->run();
          if(!s_out.count(it->out)){
            out.push(it->out);
            s_out.insert(it->out);
          }
        }
      }
      for(auto &it : inversegate_){
        if(it->inThisGate(temp->position_)){
          it->freshData();
          it->run();
          if(!s_out.count(it->out)){
            out.push(it->out);
            s_out.insert(it->out);
          }
        }
      }
      in.pop();
    }
  }
  runBitdisplay();
  runBytedisplay();
  return 0;
}
bool Circuit::runBitdisplay(){
  for(auto &it : bitdisplay_){
    int x = it->getPosition().x;
    int y = it->getPosition().y;
    it->freshData();
    picture_[y+1][x+1] = it->display()+'0';
  }
  return true;
}
bool Circuit::runBytedisplay(){
  for(auto &it : bytedisplay_){
    int x = it->getPosition().x;
    int y = it->getPosition().y;
    it->freshData();
    for(int i = 0;i<8;i++){
      picture_[y+1+i][x+1] = it->display(i)+'0';
    }
  }
  return true;
}
Circuit *Circuit::instance_ = NULL;
