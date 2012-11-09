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
#include <utility>
#include <vector>
enum GoColor { None, Black, White } ;
typedef std::pair<int,int> GoPosition ;
typedef std::pair<GoPosition, GoColor> StoneInfomation ;

inline bool
operator < (const GoPosition& lhs, const GoPosition& rhs) {
  return lhs.first < rhs.first ?
    true : lhs.right < rhs.right ;
}

#endif
