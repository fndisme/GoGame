/*
 * =====================================================================================
 *
 *       Filename:  GoBoard.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月11日 13时48分25秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "GoBoard.h"

namespace {
  GoPosition InvalidPostion(-1,-1) ;
}

bool hasForbiddenPosition(GoBoard const& b) {
  return b.forbiddenPosition() != InvalidPostion ;
}

GoBoard::pointer GoBoard::clone() {
  pointer board(new GoBoard(*this)) ;
  return board ;
}

GoBoard::GoBoard(int mx, int my) : m_maxX(mx),
  m_maxY(my),
  m_forbiddenPosition(InvalidPostion),
  m_currentColor(GoColor::Black){
    assert(mx > 0) ;
    assert(my > 0) ;
    m_stones.reserve(mx * my) ;
    for(int x = 0 ; x < m_maxX ; ++x)
      for(int y = 0 ; y < m_maxY ; ++y) {
        GoStone stone(GoPosition(x,y)) ;
        if(x == 0)
          stone.neighbourState(GoStone::POS_DOWN,
              GoStone::NeighbourState::NotExistPos) ; 
        if(x == m_maxX - 1)
          stone.neighbourState(GoStone::POS_UP,
              GoStone::NeighbourState::NotExistPos) ;
        if(y == 0)
          stone.neighbourState(GoStone::POS_LEFT,
              GoStone::NeighbourState::NotExistPos) ;
        if(y == m_maxY -1)
          stone.neighbourState(GoStone::POS_RIGHT,
              GoStone::NeighbourState::NotExistPos) ;
        m_stones.push_back(stone) ;
      }
  }



bool GoBoard::canPlaceStone(const GoPosition& pos, GoColor c) const {
  if(pos.first < 0 ||
      pos.first >= m_maxX ||
      pos.second < 0 ||
      pos.second >= m_maxY) return false ;
  if(stone(pos).color() == c) return false ;

  if(c == GoColor::None) return true ; // remove stone

  if(isCurrentBoardColor(*this, c)) return false ;

  if(isForbiddenPosition(*this, pos)) return false ;
  if(isRemoveOpponentGroup(pos, c)) return true ;
  if(isRemoveSelfGroup(pos, c)) return false ;
  if(isCombineGroup(pos, c)) return true ;

  // last result
  /*  if(isMakeNewGroup(pos, c)) */
  return true ;
}

bool GoBoard::isRemoveOpponentGroup(const GoPosition& pos, GoColor c) const {
  assert(!hasStonePosition(pos)) ;
  auto opponentsGroup = m_stones[pos.first * m_maxY + pos.second].opponentGroups() ;
  if(opponentsGroup.empty()) return false ;

  for(auto g : opponentsGroup) {
    if(m_group.at(g).isDeadIfRemoveQi(pos)) return true ;
  }
  return false ;
}

bool GoBoard::isRemoveSelfGroup(const GoPosition& pos, GoColor c) const {
  assert(false) ;
  return false ;
}

bool GoBoard::isCombineGroup(const GoPosition& pos, GoColor c) const {
  assert(false) ;
  return false ;
}




