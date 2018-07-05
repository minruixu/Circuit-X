#include "gate.hpp"
Gate::Gate(Position position){
  position_ = position;
  left_in = new InInterface(position);
  right_in = new InInterface(position);
  out = new OutInterface;
}
Gate::~Gate(){
  if(right_in != NULL){
    delete right_in;
    right_in = NULL;
  }
  if(left_in != NULL){
    delete left_in;
    left_in = NULL;
  }
  if(out){
    delete out;
    out = NULL;
  }
}
/*bool Gate::setRightInput(bool r){
  if(right_in->occupied) return false;
  right_in->data = r;
  return true;
}
bool Gate::setLeftInput(bool l){
  if(left_in->occupied) return false;
  left_in->data = l;
  return true;
}*/
/*bool Gate::setRightInput(OutInterface* r){
  if(right_in->occupied) return false;
  else{
    r->next.insert(right_in);
    right_in->prev = r;
    right_in->occupied = true;
    right_in->data = r->data;
    return true;
  }
}
bool Gate::setLeftInput(OutInterface* l){
  if(left_in->occupied) return false;
  else{
    l->next.insert(left_in);
    left_in->prev = l;
    left_in->occupied = true;
    left_in->data = l->data;
    return true;
  }
}*/
/*bool Gate::disconnectRight(){
  if(right_in->occupied){
    right_in->prev->next.erase(right_in);
    right_in->occupied = false;
    right_in->data = 0;
    right_in->prev = NULL;
    return true;
  }
  else return false;
}
bool Gate::disconnectLeft(){
  if(left_in->occupied){
    left_in->prev->next.erase(right_in);
    left_in->occupied = false;
    left_in->data = 0;
    left_in->prev = NULL;
    return true;
  }
  else return false;
}*/
bool Gate::disconnect(Position position){
  int y = position.y-position_.y;
  if(y == 0){
    if(left_in->occupied){
      left_in->prev->next.erase(right_in);
      left_in->occupied = false;
      //left_in->data = 0;
      left_in->prev = NULL;
      return true;
    }
    else return false;
  }
  else if(y == 2){
    if(right_in->occupied){
      right_in->prev->next.erase(right_in);
      right_in->occupied = false;
      //right_in->data = 0;
      right_in->prev = NULL;
      return true;
    }
    else return false;
  }
  else return false;
}
bool Gate::freshData(){
  if(left_in->occupied){
    left_in->data = left_in->prev->data;
  }
  else return false;
  if(right_in->occupied)
  right_in->data = right_in->prev->data;
  else return false;
  return true;
}
bool Gate::inThisGate(Position position){
  int x = position.x-position_.x;
  int y = position.y-position_.y;
  return (x>=0&&x<=2)&&(y>=0&&y<=2);
}
/*bool Gate::setInInterface(Position position,int data){
  int y = position.y-position_.y;
  if(y == 0){
    if(left_in->occupied) return false;
    else{
      left_in->data = data;
      return true;
    }
  }
  else if(y == 2){
    if(right_in->occupied) return false;
    else{
      right_in->data = data;
      return true;
    }
  }
  else return false;
}*/
bool Gate::setInInterface(Position position,OutInterface* out){
  int y = position.y-position_.y;
  if(y == 0){
    if(left_in->occupied) return false;
    else{
      out->next.insert(left_in);
      left_in->prev = out;
      left_in->occupied = true;
      left_in->data = out->data;
      return true;
    }
  }
  else if(y == 2){
    if(right_in->occupied) return false;
    else{
      out->next.insert(right_in);
      right_in->prev = out;
      right_in->occupied = true;
      right_in->data = out->data;
      return true;
    }
  }
  else return false;
}

bool Orgate::run(){
  out->data = ((left_in->data+right_in->data)>0);
  return out->data;
}
bool Andgate::run(){
  out->data = ((left_in->data+right_in->data) == 2);
  return out->data;
}
bool Xorgate::run(){
  out->data = ((left_in->data+right_in->data) == 1);
  return out->data;
}

Inversegate::Inversegate(Position position){
  position_ = position;
  in = new InInterface(position);
  out = new OutInterface;
}
Inversegate::~Inversegate(){
  if(in) delete in;
  if(out) delete out;
}
/*bool Inversegate::setInput(bool i){
  if(in->occupied) return false;
  else{
    in->data = i;
    return true;
  }
}*/
bool Inversegate::setInput(OutInterface* o){
  if(in->occupied) return false;
  else{
    o->next.insert(in);
    in->prev = o;
    in->occupied = true;
    in->data = o->data;
    return true;
  }
}
bool Inversegate::freshData(){
  if(in->occupied){
    in->data = in->prev->data;
    return true;
  }
  else return false;
}
bool Inversegate::run(){
  out->data = !in->data;
  return out->data;
}
bool Inversegate::disconnect(){
  if(in->occupied){
    in->prev->next.erase(in);
    in->occupied = false;
    //in->data = 0;
    in->prev = NULL;
    return true;
  }
  else return false;
}
bool Inversegate::inThisGate(Position position){
  int x = position.x- position_.x;
  int y = position.y - position_.y;
  return (x>=0&&x<=2)&&(y==0);
}

Bitdisplay::Bitdisplay(Position position){
  position_ = position;
  in = new InInterface(position);
}
bool Bitdisplay::inThisDisplay(Position position){
  int x = position.x-position_.x;
  int y = position.y - position_.y;
  return (x>=0&&x<=2)&&(y>=0&&y<=2);
}
Bitdisplay::~Bitdisplay(){
  if(in) delete in;
}
bool Bitdisplay::disconnect(){
  if(in->occupied){
    in->prev->next.erase(in);
    in->occupied = false;
    //in->data = 0;
    in->prev = NULL;
    return true;
  }
  else return false;
}
bool Bitdisplay::freshData(){
  if(in->occupied){
    in->data = in->prev->data;
    return true;
  }
  else return false;
}
/*bool Bitdisplay::setInput(bool i){
  if(in->occupied) return false;
  else{
    in->data = i;
    return true;
  }
}*/
bool Bitdisplay::setInput(OutInterface* o){
  if(in->occupied) return false;
  else{
    o->next.insert(in);
    in->prev = o;
    in->occupied = true;
    in->data = o->data;
    return true;
  }
}

Bytedisplay::Bytedisplay(Position position){
  position_ = position;
  for(int i = 0;i<8;i++) in[i] = new InInterface(position);
}
Bytedisplay::~Bytedisplay(){
  for(int i =0;i<8;i++){
    if(in[i]) delete in[i];
  }
}
bool Bytedisplay::disconnect(Position position){
  int y = position.y-position_.y - 1;
  if(y>=0 && y<=7){
    if(in[y]->occupied){
      in[y]->prev->next.erase(in[y]);
      in[y]->occupied = false;
      //in->data = 0;
      in[y]->prev = NULL;
      return true;
    }
    else return false;
  }
  return false;
}
bool Bytedisplay::freshData(){
  for(int i = 0;i<8;i++){
    if(in[i]->occupied){
      in[i]->data = in[i]->prev->data;
    }
  }
  return true;
}
bool Bytedisplay::inThisDisplay(Position position){
  int x = position.x - position_.x;
  int y = position.y - position_.y;
  return (x>=0&&x<=2)&&(y>=0&&y<=10);
}
/*bool Bytedisplay::setInput(Position position,bool i){
  int y = position.y - position_.y -1;
  if(y>=0 && y<=7){
    if(in[y]->occupied) return false;
    else{
      in[y]->data = i;
      return true;
    }
  }
  return false;
}*/
bool Bytedisplay::setInput(Position position,OutInterface* o){
  int no = position.y - position_.y-1;
  if(no<0||no>=8) return false;
  if(in[no]->occupied) return false;
  else{
    o->next.insert(in[no]);
    in[no]->prev = o;
    in[no]->occupied = true;
    in[no]->data = o->data;
    return true;
  }
}
