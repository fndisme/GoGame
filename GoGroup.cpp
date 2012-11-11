/*
 * =====================================================================================
 *
 *       Filename:  GoGroup.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月09日 18时42分27秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "GoGroup.h"

void GoGroup::addMember(GoPosition const& pos,
    const std::vector<GoPosition>& q) {
  assert(!hasMember(pos)) ;
  m_member.insert(pos) ;
  m_qi.insert(q.begin(), q.end()) ;
}


