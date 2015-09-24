// RicochetRobots.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <set>
#include <cassert>

using namespace std;

typedef char Crd;
typedef int Conf;

int n, w, h, l;

int targetCrd;

typedef enum {R1 = 0, R2, R3, R4, Empty, Wall, Target} Cell;
typedef enum {Left, Right, Up, Down} Direction;

typedef std::vector<Cell> Map;

struct RobotState
{
  static RobotState SEmpty;
  RobotState() 
  {
    for( int i = 0 ; i < 4; ++i)
      state.indiv[i] = -1;
  }

  RobotState(RobotState& rs)
  {
    state.all = rs.state.all;
  }

  RobotState& operator=(const RobotState& that)
  {
    state.all = that.state.all;
  }

  bool operator<(const RobotState& that) const
  {
    return state.all < that.state.all;
  }
  
  union
  {
    Conf all;
    Crd indiv[4];
  } state;

  //StateImpl state

  Crd getPos(int rId) const { return state.indiv[rId];}
  void setPos(int rId, char pos) { state.indiv[rId] = pos;}
  Conf getVal() const {return state.all;}

  void clear()
  {
    this->operator=(SEmpty);
  }
};

RobotState RobotState::SEmpty = RobotState();

void applyStateToMap(Map& map, RobotState& state)
{
  for( int i = 0 ; i < 4 && state.state.indiv[i] != -1; ++i)
  {
    assert(map[state.getPos(i)] == Empty);
    map[state.getPos(i)] = (Cell)i;
  }
}

struct FullState
{
  FullState(Map _map, RobotState _state)
    : map(_map),
      state(_state)
  {
  }
  
  Map map;
  RobotState state;

  void apply(const RobotState& _state)
  {
    cancelState();
    state = _state;
    applyStateToMap(map, state);
  }

private:
  int nrOfRobots;

  void cancelState()
  {
    for( int i = 0 ; i < 4 && state.state.indiv[i] != -1; ++i)
    {
      assert( map[state.getPos(i)] == i);
      map[state.getPos(i)] = Empty;
    }
    state.clear();
  }
};

typedef std::set<RobotState> States;

template<class T>
void swapPos(T& i, T& j)
{
  T c = i;
  i = j;
  j = c;
}

int crd1(int row, int col)
{
  return row * w + col;
}

bool move(Map& map, RobotState& robots, int r, Direction d, bool alreadyMoved)
{
  Crd curPos = robots.getPos(r);
  
  int row = curPos / w;
  int col = curPos - row * w;

  Crd newPos = -1;

  switch (d)
  {
    case Left: if (col > 0) 
                  newPos = curPos - 1; 
               break;
    case Right: if (col < w - 1)
                  newPos = curPos + 1; 
                break;
    case Up: if ( row > 0)
                newPos = curPos - w;
             break;
    case Down: if ( row < h - 1)
                  newPos = curPos + w;
               break;
  }
  if ( newPos >= 0 )
  {
    if ( map[newPos] == Empty || map[newPos] == Target)
    {
      swapPos(map[curPos], map[newPos]);

      robots.setPos( r, newPos);

      return move(map, robots, r, d, true);
    }
  }

  return alreadyMoved;
}

bool isFinal(RobotState& state)
{
  return state.getPos(0) == targetCrd;
}

bool testcase()
{
  cin >> n >> w >> h >> l;

  Map map(h * w);
  RobotState state;
  States toTry, tried;

  for( auto it = map.begin() ; it != map.end() ; ++it )
  {
    char symb;
    cin >> symb;
    switch( symb )
    {
      case 'W': *it = Wall; break;
      case 'X': *it = Target; break;
      case '.': *it = Empty; break;
      default:  *it = (Cell)(symb - '0');
                state.setPos(*it, it - map.begin());
    }
  }

  FullState curState(map, state);

  toTry.insert(RobotState(state));

  while ( !toTry.empty() )
  {
    auto& cfg = toTry.begin();
    
  }

  return true;


}

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}
