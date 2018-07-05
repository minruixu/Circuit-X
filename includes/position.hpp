#ifndef POSITION_H_
#define POSITION_H_
struct Position{
  int x;
  int y;
  Position(int x_ = -1,int y_ = -1):x(x_),y(y_){}
  ~Position(){
    x = -1;
    y = -1;
  }
  operator bool() const{
        if (x == -1 && y == -1)
            return false;
        else
            return true;
  }
  bool operator=(const Position &other){
    x = other.x;
    y = other.y;
    return true;
  }
  bool operator==(const Position &other)const{
    return (x==other.x)&&(y == other.y);
  }
};
#endif
