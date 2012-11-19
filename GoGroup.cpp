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
#include <iostream>
#include "GoGroup.h"

void GoGroup::addMember(GoPosition const& pos,
    const std::vector<GoPosition>& q) {
  assert(!hasMember(pos)) ;
  m_member.insert(pos) ;
  m_qi.insert(q.begin(), q.end()) ;
}

void GoGroup::debugInformaiton() const {
  std::cout << "M:" ;
  for(const auto& m : m_member) 
    std::cout << "N:(" << m.first << ":" << m.second << ")" ;
  std::cout << std::endl ;

  for(const auto& q : m_qi)
    std::cout << "Q:(" << q.first << ":" << q.second << ")" ;
  std::cout << std::endl ;

}


