/*
 * =====================================================================================
 *
 *       Filename:  GoDef.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月09日 15时56分02秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_GODEF_H
#define FND_GODEF_H
#include <cassert>
#include <utility>
#include <vector>
#include <set>
#include <memory>
enum class GoColor {None, Black, White} ;
typedef std::pair<int,int> GoPosition ;
typedef std::pair<GoPosition, GoColor> StoneInfomation ;

inline bool
operator < (const GoPosition& lhs, const GoPosition& rhs) {
  return lhs.first < rhs.first ?
    true : lhs.second < rhs.second ;
}

class GoGroup ;
class GoBoard ;

class GoAction ;
//typedef std::shared_ptr<GoAction> GoActionPointer ;
//typedef std::weak_ptr<GoAction> GoActionWeakPointer ;

inline bool hasDirectConnection(GoPosition const& lhs, GoPosition const& rhs) {
  if(lhs.first == rhs.first && ((lhs.second - rhs.second == 1) || 
        (lhs.second - rhs.second == -1))) return true ;
  if(lhs.second == rhs.second && ((lhs.first - rhs.first == 1) || 
        (lhs.first - rhs.first == -1))) return true ;
  return false ;
}



#endif
