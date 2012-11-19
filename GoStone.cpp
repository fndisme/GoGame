/*
 * =====================================================================================
 *
 *       Filename:  GoStone.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月11日 13时19分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
//#include "GoGroup.h"
#include <iostream>
#include "GoStone.h"

void GoStone::bindGroup(int g) {
  assert(!hasGroup()) ;
  m_group_ref = g ;
}

void GoStone::unbindGroup() {
  assert(hasGroup()) ;
  m_group_ref =  -1;
  m_color = GoColor::None ;
}

void GoStone::debugInformaiton() const {
  std::string cdes ;
  if(m_color == GoColor::None) cdes = "None" ;
  if(m_color == GoColor::White) cdes = "White" ;
  if(m_color == GoColor::Black) cdes = "Black" ;
  std::cout << "P:(" << m_position.first << ","
    << m_position.second << ")C:" << cdes << " ";
  for(auto n : m_neighbour) {
    std::string ns ;
    
    if(std::get<0>(n) == NeighbourState::NotExistPos) ns = "NotExist" ;
    if(std::get<0>(n) == NeighbourState::None) ns = "None" ;
    if(std::get<0>(n) == NeighbourState::BlackColor) ns = "BlackColor" ;
    if(std::get<0>(n) == NeighbourState::WhiteColor) ns = "WhiteColor" ;
    std::cout << "N:" << ns << ":" << std::get<1>(n) << " " ; 
  }
  for(auto s : stoneNeighbourPosition(*this)) {
    std::cout << "NP:(" << s.first << "," << s.second << ")" ;
  }

  std::cout << std::endl ;

}


