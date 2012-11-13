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
#include "GoAbandonRightAction.h"
#include "GoSequenceAction.h"
#include "GoNewGroupAction.h"
#include "GoAddGroupMember.h"
#include "GoRemoveGroupAction.h"
#include "GoCombineGroupAction.h"

#include <iostream>

namespace {
  GoPosition InvalidPostion(-1,-1) ;
}


void GoBoard::debugPrintCurrentBoard() const {
  for(int x = 0 ; x < m_maxX ; ++x) {
    for(int y = 0 ; y < m_maxY ; ++y) {
        auto& s = stone(GoPosition(x,y)) ;
        if(s.color() == GoColor::None) std::cout << "." ;
        else if(s.color() == GoColor::Black) std::cout << "b" ;
        else std::cout << "w" ;
    }
    std::cout << std::endl ;
  }

  for(auto s : m_stones) {
    if(s.color() != GoColor::None) s.debugInformaiton() ;
  }
}
bool hasForbiddenPosition(GoBoard const& b) {
  return b.forbiddenPosition() != InvalidPostion ;
}

void GoBoard::removeForbbinPosition() {
  m_forbiddenPosition = InvalidPostion ;
}

GoBoard::pointer GoBoard::clone() {
  pointer board(new GoBoard(m_maxX, m_maxY)) ;
  board->m_currentColor = m_currentColor ;
  board->m_group = m_group ;
  board->m_stones = m_stones ;
  board->m_forbiddenPosition = m_forbiddenPosition ;
  board->m_nextGroupId = m_nextGroupId ;
  for(const auto& a : m_actions) board->m_actions.push_back(a->clone()) ;
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
          stone.neighbourState(GoStone::POS_LEFT,
              GoStone::NeighbourState::NotExistPos) ; 
        if(x == m_maxX - 1)
          stone.neighbourState(GoStone::POS_RIGHT,
              GoStone::NeighbourState::NotExistPos) ;
        if(y == 0)
          stone.neighbourState(GoStone::POS_DOWN,
              GoStone::NeighbourState::NotExistPos) ;
        if(y == m_maxY -1)
          stone.neighbourState(GoStone::POS_UP,
              GoStone::NeighbourState::NotExistPos) ;
        m_stones.push_back(stone) ;
      }
  }

void GoBoard::removeStone(const GoPosition& pos) {
  assert(canPlaceStone(pos, GoColor::None)) ;

}

void GoBoard::abandonCurrentRight() {
  GoAction::pointer act(new GoAbandonRightAction(m_currentColor)) ;
  act->action(this) ;
  m_actions.push_back(std::move(act)) ;
}



bool GoBoard::canPlaceStone(const GoPosition& pos, GoColor c) const {
  if(pos.first < 0 ||
      pos.first >= m_maxX ||
      pos.second < 0 ||
      pos.second >= m_maxY) return false ;
  if(stone(pos).color() == c) return false ;

  if(c == GoColor::None) return true ; // remove stone
  if(stone(pos).color() != GoColor::None) return false ; // place position must has no

  if(!isCurrentBoardColor(*this, c)) return false ;

  if(isForbiddenPosition(*this, pos)) return false ;
  return true ;
//  if(isRemoveOpponentGroup(pos, c) || isCombineGroupAndAlive(pos, c)) return true ;
//  //if(isRemoveSelfGroup(pos, c)) return false ;
//
//  // last result
//  /*  if(isMakeNewGroup(pos, c)) */
//  return true ;
}

GoBoard::GroupType GoBoard::removedOpponentGroup(const GoPosition& pos, GoColor c) const {
  assert(hasStonePosition(pos)) ;
  GoColor opponentColor ;
  if(c == GoColor::Black) opponentColor = GoColor::White ;
  if(c == GoColor::White) opponentColor = GoColor::Black ;
  assert(opponentColor == GoColor::White ||
      opponentColor == GoColor::Black) ;
  auto opponentsGroup = stone(pos).colorGroup(opponentColor) ;
  //if(opponentsGroup.empty()) return false ;

  GroupType groups ;
  for(auto g : opponentsGroup) {
    if(m_group.at(g).isDeadIfRemoveQi(pos)) groups.insert(g);
  }

  return groups ;
}

std::vector<GoPosition> stoneQiPositionInBoard(GoPosition const& pos,
    GoBoard const& board) {
  auto neighbourPosGroup = stoneNeighbourPosition(board.stone(pos)) ;
  std::vector<GoPosition> qis ;

  for(const auto& neighbourPos : neighbourPosGroup) {
    const auto& s = board.stone(neighbourPos) ;
    if(isQi(s)) qis.push_back(neighbourPos) ;
  }
  return qis ;
}

GoBoard::GroupType
GoBoard::combinedGroupAndAlive(const GoPosition& pos, GoColor c) const {
  auto friendgroup = stone(pos).colorGroup(c) ;
  GroupType groups ;

  if(friendgroup.empty()) return groups ;
  auto qis = stoneQiPositionInBoard(pos, *this) ;
  bool hasQi = !qis.empty() ;
  if(!hasQi) {
    for(auto g : friendgroup)
      if(!m_group.at(g).isDeadIfRemoveQi(pos)) {
        hasQi = true ;
        break ;
    }
  }

  if(hasQi) {
    for(auto g : friendgroup) groups.insert(g) ;
  }

  return groups;
}

void GoBoard::placeStone(GoPosition const& pos, GoColor c) {
  assert(c == GoColor::Black || c == GoColor::White) ;
  assert(canPlaceStone(pos, c)) ;


  std::vector<GoAction::pointer> seqs ;
  auto removed(removedOpponentGroup(pos, c)) ;
  if(!removed.empty()) {
    GoRemoveGroupAction::RemoveGroupType gs ;
    for(auto groupid : removed)
      gs.push_back(std::make_pair(groupid, m_group.at(groupid))) ;
    seqs.push_back(GoAction::pointer(new GoRemoveGroupAction(gs))) ;
  } 


  auto combined(combinedGroupAndAlive(pos, c)) ;


  int start = m_nextGroupId ;

  if(!combined.empty()) {
    start = *(combined.begin()) ;

    GoCombineGroupAction::Groups gs ;
    for(auto gid : combined) 
      gs.push_back(std::make_pair(gid, m_group.at(gid))) ;
    seqs.push_back(GoAction::pointer(new GoCombineGroupAction(gs))) ;
  }

  if(start == m_nextGroupId) {
    // new group
    GoGroup newGroup(c) ;
    newGroup.addMember(pos, stoneQiPositionInBoard(pos, *this)) ;
    seqs.push_back(GoAction::pointer(new GoNewGroupAction(start, newGroup))) ;
  } else {
    seqs.push_back(GoAction::pointer(new GoAddGroupMember(pos, stoneQiPositionInBoard(pos, *this), start))) ;
  }



  GoAction::pointer seqAction(new GoSequenceAction(std::move(seqs))) ;
  seqAction->action(this) ;
  m_actions.push_back(std::move(seqAction)) ;
}

void GoBoard::addNewGroup(int groupid, GoGroup const& group) {
  assert(!hasGroup(groupid)) ;
  m_group.insert(std::make_pair(groupid, group)) ;
  assert(group.member().size() == 1) ;
  for(auto s : group.member()) {
    setStoneAsSolid(s, group.color()) ;
    for(auto qi : group.qi()) updateStoneStateAsQi(qi, s, groupid) ;
  }
  for(auto s : group.member()) updateStoneStateAsSolid(s, groupid) ;

  passToRivalColor(group.color()) ;
  m_nextGroupId ++ ;
}

void GoBoard::updateStoneStateAsSolid(const GoPosition& pos, int groupid) {
  auto& s = stone(pos) ;
  for(auto sp : stoneNeighbourPosition(s)) {
    auto& neighbourStone = stone(sp) ;
    int direction = stoneDirection(s, neighbourStone) ;
    s.setNeighbourColor(direction, neighbourStone.groupId(), neighbourStone.color()) ;
  }
}

void GoBoard::updateStoneStateAsQi(const GoPosition& pos, const GoPosition& ori, int groupid) {
  if(hasDirectConnection(pos, ori)) {
    GoColor c = m_group.at(groupid).color() ;

    int direction = stoneDirection(stone(pos), stone(ori)) ;
    std::cout << "set pos " << pos.first << " : " << pos.second << " : " << groupid << std::endl ;
    stone(pos).setNeighbourColor(direction, groupid, c) ;
  }
}

void GoBoard::setStoneAsSolid(const GoPosition& pos, GoColor c) {
  auto& s = stone(pos) ;
  s.color(c) ;
}

void GoBoard::removeSingleGroup(int groupid) {
  assert(hasGroup(groupid)) ;
  auto& group = m_group.at(groupid) ;
  assert(group.member().size() == 1) ;

  //auto qi = m_group.

}

