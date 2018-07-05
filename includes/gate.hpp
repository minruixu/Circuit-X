#ifndef GATE_H_
#define GATE_H_
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include "position.hpp"
using namespace std;
struct InInterface;
struct OutInterface;
struct InInterface{//in接口只有一个输入
  bool occupied;
  Position position_;
  OutInterface* prev;
  bool data;
  InInterface(Position position):occupied(false),data(false){
    position_ = position;
  }
  bool operator||(InInterface l){
    return data||l.data;
  }
  bool operator&&(InInterface l){
    return data&&l.data;
  }
};
struct OutInterface{
  bool occupied;
  set <InInterface*> next;
  bool data;
  OutInterface():occupied(false),data(false){}
};
class Source_true{
 public:
  Position position_;
  OutInterface *out;
  Source_true(Position position){
    position_ = position;
    out = new OutInterface;
    out->data = 1;
  }
  ~Source_true(){
    if(out) delete out;
  }
};
class Source_false{
 public:
   Position position_;
  OutInterface *out;
  Source_false(Position position){
    position_ = position;
    out = new OutInterface;
    out->data = 0;
  }
  ~Source_false(){
    if(out) delete out;
  }
};
class Gate{
 protected:
  InInterface *left_in,*right_in;
  Position position_;
 public:
  OutInterface *out;
  Gate(Position position);
  virtual ~Gate();
  //bool setRightInput(bool r);
  //bool setLeftInput(bool l);
  //bool setRightInput(OutInterface* r);
  //bool setLeftInput(OutInterface* l);
  //bool disconnectRight();
  //bool disconnectLeft();
  bool disconnect(Position position);
  bool freshData();
  virtual bool run() = 0;
  bool inThisGate(Position position);
  bool setInInterface(Position position,OutInterface* out);
  //bool setInInterface(Position position,int data);
};
class Orgate:public Gate{
 public:
  Orgate(Position position):Gate(position){}
  ~Orgate(){}
  virtual bool run();
};
class Andgate:public Gate{
 public:
  Andgate(Position position):Gate(position){}
  ~Andgate(){}
  virtual bool run();
};
class Xorgate:public Gate{
 public:
  Xorgate(Position position):Gate(position){}
  ~Xorgate(){}
  virtual bool run();
};
class Inversegate{
 protected:
  InInterface* in;
  Position position_;
 public:
  OutInterface* out;
  Inversegate(Position position);
  ~Inversegate();
  //bool setInput(bool i);
  bool setInput(OutInterface* o);
  bool disconnect();
  bool freshData();
  bool run();
  bool inThisGate(Position position);
};
class Bitdisplay{
 protected:
  InInterface* in;
  Position position_;
 public:
  Bitdisplay(Position position);
  ~Bitdisplay();
  bool disconnect();
  //bool setInput(bool i);
  bool setInput(OutInterface* o);
  bool freshData();
  bool display(){return in->data;}
  bool inThisDisplay(Position position);
  Position getPosition(){return position_;}
};
class Bytedisplay{
 protected:
  Position position_;
  InInterface* in[8];
 public:
  Bytedisplay(Position position);
  ~Bytedisplay();
  bool disconnect(Position position);
  bool freshData();
  bool display(int i){return in[i]->data;}
  //bool setInput(Position position,bool data);
  bool setInput(Position position,OutInterface* o);
  bool inThisDisplay(Position position);
  Position getPosition(){return position_;}
};
#endif
