#ifndef CIRCUIT_H_
#define CIRCUIT_H_
#include "gate.hpp"
#include "position.hpp"
#include <string>
#include <vector>
#include <set>
#include <queue>
using namespace std;
const int max_width = 132;
const int max_height = 40;
class Circuit{
private:
  static Circuit* instance_;
  char map_[max_height][max_width];
  vector <Andgate*> andgate_;
  vector <Orgate*> orgate_;
  vector <Xorgate*> xorgate_;
  vector <Inversegate*> inversegate_;
  vector <Bitdisplay*> bitdisplay_;
  vector <Bytedisplay*> bytedisplay_;
  Source_true* circuit_true_;
  Source_false* circuit_false_;
  Circuit();
  ~Circuit();
  bool newAnd(int x,int y);
  bool newOr(int x,int y);
  bool newXor(int x,int y);
  bool newInverse(int x,int y);
  bool newBitdisplay(int x,int y);
  bool newBytedisplay(int x,int y);
  bool checkCircle();
  bool testOut(OutInterface* out);
public:
  char picture_[max_height][max_width];
  static Circuit* GetInstance();
  static void DeleteInstance();
  bool newGate(vector<string> command,int _x,int _y);
  bool connect(Position out,Position in);
  //bool setGateViaOut(Position position,OutInterface* out);
  OutInterface* findInterfaceViaOut(Position position);
  //bool moveData(Position in,bool data);
  bool disconnect(Position in);
  int run();
  bool runBitdisplay();
  bool runBytedisplay();
};
#endif
