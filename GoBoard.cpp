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
#include <algorithm>
#include "GoBoard.h"
#include "GoSequenceAction.h"
#include "GoNewGroupAction.h"
#include "GoSetNewGroupIdAction.h"
#include "GoPassCurrentColorAction.h"
#include "GoAddGroupMember.h"
#include "GoRemoveGroupAction.h"
#include "GoCombineGroupAction.h"
#include "GoSetForbidenAction.h"

#include <iostream>

namespace {
  GoPosition InvalidPostion(-1,-1) ;
}


void GoBoard::debugPrintCurrentBoard() const {
  for(int y = 0 ; y < m_maxY ; ++y) {
    for(int x = 0 ; x < m_maxX ; ++x) {
        auto& s = stone(GoPosition(x,y)) ;
        if(s.color() == GoColor::None) std::cout << "." ;
        else if(s.color() == GoColor::Black) std::cout << "b" ;
        else std::cout << "w" ;
    }
    std::cout << std::endl ;
  }

  for(const auto& s : m_stones) {
    if(s.color() != GoColor::None) s.debugInformaiton() ;
  }

  for(const auto& g : m_group) {
    std::cout << "Group:" << g.first << std::endl ;
    g.second.debugInformaiton() ;
  }
}
bool hasForbiddenPosition(GoBoard const& b) {
  return b.forbiddenPositions().empty() ;
}

void GoBoard::removeForbbinPosition() {
  m_forbiddenPositions.clear() ;
}

GoBoard::pointer GoBoard::clone(int step) {
  assert(step < m_actions.size()) ;
  pointer board(new GoBoard(m_maxX, m_maxY)) ;
  for(int i = 0 ;i < step ; ++i) {
    board->m_actions.push_back(m_actions[i]->clone()) ;
  }
  for(auto& action : board->m_actions) action->action(board.get()) ;
  return board ;
}

void GoBoard::takeBackOneHand() {
  assert(canTakeBack()) ;
  auto action = m_actions.back()->revertAction() ;
  m_actions.pop_back() ;
  action->action(this) ;
}

GoBoard::GoBoard(int mx, int my) : m_maxX(mx),
  m_maxY(my),
  m_currentColor(GoColor::Black){
    assert(mx > 0) ;
    assert(my > 0) ;
    m_stones.reserve(mx * my) ;
    for(int x = 0 ; x < m_maxX ; ++x)
      for(int y = 0 ; y < m_maxY ; ++y) {
        GoStone s(GoPosition(x,y)) ;
        if(x == 0)
          s.neighbourState(GoStone::POS_LEFT,
              GoStone::NeighbourState::NotExistPos) ; 
        if(x == m_maxX - 1)
          s.neighbourState(GoStone::POS_RIGHT,
              GoStone::NeighbourState::NotExistPos) ;
        if(y == 0)
          s.neighbourState(GoStone::POS_DOWN,
              GoStone::NeighbourState::NotExistPos) ;
        if(y == m_maxY -1)
          s.neighbourState(GoStone::POS_UP,
              GoStone::NeighbourState::NotExistPos) ;
        m_stones.push_back(s) ;
      }
  }

void GoBoard::removeStone(const GoPosition& pos) {
  assert(canPlaceStone(pos, GoColor::None)) ;

}

void GoBoard::abandonCurrentRight() {
  GoAction::pointer act(new GoPassCurrentColorAction(opponentColor(m_currentColor))) ;
  act->action(this) ;
  m_actions.push_back(std::move(act)) ;
}

bool GoBoard::hasColorGroupDeadIfPlaceStone(const GoPosition& pos, GoColor c) const {
  return std::any_of(m_group.begin(), m_group.end(),
        [&pos, c](ColorGroupType::const_reference v) -> bool {
       return v.second.color() == c && v.second.isDeadIfRemoveQi(pos) ;
      }) ;
}

bool GoBoard::canPlaceStone(const GoPosition& pos, GoColor c) const {
  if(pos.first < 0 ||
      pos.first >= m_maxX ||
      pos.second < 0 ||
      pos.second >= m_maxY) return false ;
  if(stone(pos).color() == c) return false ;

  if(c == GoColor::None) return true ;

  if(stone(pos).color() != GoColor::None) return false ; // place position must has no color

  if(isForbiddenPosition(*this, pos)) return false ;

  if(hasColorGroupDeadIfPlaceStone(pos, opponentColor(c))) return true ;

  if(stone(pos).allNeighbourIsRival(opponentColor(c))) return false ;

  if(!isCurrentBoardColor(*this, c)) return false ;

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

  ForbiddenGroup newGroup ; 
  if(!removed.empty()) {
    GoRemoveGroupAction::RemoveGroupType gs ;
    for(auto groupid : removed) {
      gs.push_back(std::make_pair(groupid, m_group.at(groupid))) ;
      if(m_group.at(groupid).member().size() == 1) {
        newGroup.insert(*(m_group.at(groupid).member().begin())) ;
      }
    }
    seqs.push_back(GoAction::pointer(new GoRemoveGroupAction(gs))) ;
  } 

  // set fordin
  if(!newGroup.empty() || !m_forbiddenPositions.empty()) {
    std::cout << "add forbiden........." ;
    seqs.push_back(GoAction::pointer(new GoSetForbidenAction(m_forbiddenPositions, newGroup))) ;
  }


  auto combined(combinedGroupAndAlive(pos, c)) ;


  int start = m_nextGroupId ;

  if(!combined.empty()) {
    start = *(combined.begin()) ;

    Groups gs ;
    for(auto gid : combined) 
      gs.push_back(std::make_pair(gid, m_group.at(gid))) ;
    seqs.push_back(GoAction::pointer(new GoCombineGroupAction(gs))) ;
  }

  if(start == m_nextGroupId) {
    // new group
    GoGroup newGroup(c) ;
    newGroup.addMember(pos, stoneQiPositionInBoard(pos, *this)) ;
    seqs.push_back(GoAction::pointer(new GoNewGroupAction(start, newGroup))) ;
    seqs.push_back(GoAction::pointer(new GoPassCurrentColorAction(opponentColor(m_currentColor)))) ;
    seqs.push_back(GoAction::pointer(new GoSetNewGroupIdAction(m_nextGroupId + 1, m_nextGroupId))) ;
  } else {
    seqs.push_back(GoAction::pointer(new GoAddGroupMember(pos, stoneQiPositionInBoard(pos, *this), start))) ;
    seqs.push_back(GoAction::pointer(new GoPassCurrentColorAction(opponentColor(m_currentColor)))) ;
  }

  GoAction::pointer seqAction(new GoSequenceAction(std::move(seqs))) ;
  seqAction->action(this) ;
  m_actions.push_back(std::move(seqAction)) ;
}

void GoBoard::combineGroups(const Groups& groups) {
  assert(groups.size() >= 1) ;
  int newGroupId = groups[0].first ;
  auto& g = m_group.at(newGroupId) ;
  for(size_t i = 1 ; i < groups.size() ; ++i) {
    const auto& ogroup = m_group.at(groups[i].first) ;
    for(const auto& pos : ogroup.member()) {
      setStoneAsSolid(pos, newGroupId) ;
    }
    g.addMember(ogroup.member()) ;
    g.addQi(ogroup.qi()) ;
    m_group.erase(groups[i].first) ;
  }
}

void GoBoard::addGroupMember(const GoPosition& pos,
    const std::vector<GoPosition>& qis, 
    int groupid) {
  m_group.at(groupid).addMember(pos, qis) ;
  setStoneAsSolid(pos, groupid) ;
  //passToRivalColor(m_group.at(groupid).color()) ;
}

void GoBoard::addNewGroup(int groupid, GoGroup const& group) {
  assert(!hasGroup(groupid)) ;
  m_group.insert(std::make_pair(groupid, group)) ;
  assert(group.member().size() == 1) ;
  GoPosition newPos = *group.member().begin() ;
  setStoneAsSolid(newPos, groupid) ;
  //updateStoneNeighbourNeighbour(newPos, groupid, group.color()) ;
//  for(auto s : group.member()) {
//    setStoneAsSolid(s, group.color()) ;
//    for(auto qi : group.qi()) updateStoneStateAsQi(qi, s, groupid) ;
//  }
//  for(auto s : group.member()) updateStoneStateAsSolid(s, groupid) ;
//
  //passToRivalColor(group.color()) ;
}

/* 
void GoBoard::updateStoneStateAsSolid(const GoPosition& pos, int groupid) {
  auto& s = stone(pos) ;
  for(auto sp : stoneNeighbourPosition(s)) {
    auto& neighbourStone = stone(sp) ;
    int direction = stoneDirection(s, neighbourStone) ;
    s.setNeighbourColor(direction, neighbourStone.groupId(), neighbourStone.color()) ;
  }
}
*/

/*  
void GoBoard::updateStoneStateAsQi(const GoPosition& pos, const GoPosition& ori, int groupid) {
  if(hasDirectConnection(pos, ori)) {
    GoColor c = m_group.at(groupid).color() ;

    int direction = stoneDirection(stone(pos), stone(ori)) ;
    std::cout << "set pos " << pos.first << " : " << pos.second << " : " << groupid << std::endl ;
    stone(pos).setNeighbourColor(direction, groupid, c) ;
  }
}
*/

void GoBoard::setStoneAsSolid(const GoPosition& pos, int groupid) {
  auto& g = m_group.at(groupid) ;
  assert(g.color() != GoColor::None) ;
  auto& s = stone(pos) ;
  bindColorGroup(s, g.color(), groupid) ;
  assert(s.color() != GoColor::None) ;

  for(auto neighbourPos : stoneNeighbourPosition(s)) {
    auto& neighbour = stone(neighbourPos) ;
    updateStoneRelation(s, neighbour) ;

    if(isRival(s, neighbour)) {
      m_group.at(neighbour.groupId()).removeQi(s.position()) ;
    }
  }
}

void GoBoard::removeGroup(int groupId) {
  //assert(false) ;
  auto& group = m_group.at(groupId) ;
  for(const auto& pos : group.member()) 
    setStoneAsNone(pos) ;
  m_group.erase(groupId) ;
}

void GoBoard::recreateGroup(int groupId, const GoGroup& g) {
  if(m_group.count(groupId)) {
    removeGroup(groupId) ;
  }

  m_group.insert(std::make_pair(groupId,g)) ;
  for(const auto& pos : g.member()) {
    setStoneAsSolid(pos, groupId) ;
  }
  
}

void GoBoard::setStoneAsNone(const GoPosition& pos) {
  auto& s = stone(pos) ;
  auto rivalgroup = rivalColorGroup(s) ;
  s.unbindGroup() ;

  for(const auto& spos : stoneNeighbourPosition(s)) {
    updateStoneRelation(s, stone(spos)) ;
  }

  for(auto g : rivalgroup) {
    m_group.at(g).addQi(s.position()) ;
  }
}

void GoBoard::removeSingleGroup(int groupid) {
  assert(hasGroup(groupid)) ;
  auto& group = m_group.at(groupid) ;
  assert(group.member().size() == 1) ;

  for(const auto& pos : group.member()) {
    setStoneAsNone(pos) ;
  }

  m_group.erase(groupid) ;

  //auto qi = m_group.

}

