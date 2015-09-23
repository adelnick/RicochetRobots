// RicochetRobots.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef enum {R1 = 1, R2, R3, R4, Empty, Wall, Target} Cell;
typedef enum {Left, Right, Up, Down} Direction;

typedef vector<Cell> Map;
typedef vector<int> Robots;

typedef map<Robots, int> Configs;

int n, w, h, l;

template<class T>
void swapPos(T& i, T& j)
{
  T c = i;
  i = j;
  j = c;
}

bool move(Map& map, Robots& robots, int r, Direction d, bool alreadyMoved)
{
  int curPos = robots[r], newPos = -1;
  switch (d)
  {
    case Left: if (curPos > 0) 
                  newPos = curPos - 1; 
               break;
    case Right: if (curPos < w - 1)
                  newPos = curPos + 1; 
                break;
    case Up: if ( (curPos % w) < h - 1)
                newPos = curPos + w;
             break;
    case Down: if ( curPos >= w)
                  newPos = curPos - w;
               break;
  }
  if ( newPos >= 0 )
  {
    if ( map[newPos] == Empty || map[newPos] == Target)
    {
      swapPos(map[curPos], map[newPos]);

      robots[r] = newPos;

      return move(map, robots, r, d, true);
    }
  }

  return alreadyMoved;
}

bool testcase()
{
  cin >> n >> w >> h >> l;

  Map map(h * w);
  Robots robots(n);
  Configs configs;

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
                robots[*it] = it - map.begin();               
    }
  }

  configs.insert({Robots(robots), 0});

  while ( !configs.empty() )
  {
    auto& cfg = *configs.begin();
    auto rbs = cfg.first;
    auto steps = cfg.second;

    for ( int i = 1; i <= 4; ++i)
    {
      if (move(map, rbs, i, Left, false))
      {
        auto it = configs.find(rbs);

        if ( it != configs.end() ) 
        {
          if ( it->second > steps + 1 )
          {
            it->second = steps;
          }
        }
      }
    }
    

  }

  return true;


}

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}
