/*
 * =====================================================================================
 *
 *       Filename:  GoStone.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月11日 13时09分31秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_GOSTONE_H
#define FND_GOSTONE_H
#include <tuple>
#include <array>
#include <algorithm>
#include "GoDef.h"
class GoStone {
  public:
    enum {
      POS_UP,
      POS_RIGHT,
      POS_DOWN,
      POS_LEFT,
      NeighbourMax
    } ;
    enum class NeighbourState {
      NotExistPos,
      None,
      BlackColor,
      WhiteColor,
    } ;

    typedef std::tuple<NeighbourState, int> Neighbour ;

    
    explicit GoStone(const GoPosition& pos, GoColor c = GoColor::None) :
      m_position(pos),
      m_color(c),
      m_group_ref(-1){
        m_neighbour.fill(std::make_tuple(NeighbourState::None, 0)) ;
      }
    const GoPosition& position() const { return m_position ;}
    GoColor color() const { return m_color ;}
    void color(GoColor c) { m_color = c ;}
    void bindGroup(int group) ;
    void unbindGroup() ;
    void debugInformaiton() const ;
    bool hasGroup() const { return m_group_ref != -1;}
    GoStone(GoStone const&) = default ;
    GoStone& operator = (const GoStone&) = default ;
    void neighbourState(int neighbourPos, NeighbourState s) {
      assert(s == NeighbourState::NotExistPos||
          s == NeighbourState::None) ;
      m_neighbour.at(neighbourPos) = std::make_tuple(s, 0) ;
    }

    int groupId() const { return m_group_ref ;}

    void setNeighbourColor(int neighbourPos, int groupId, GoColor c) {
      if(c == GoColor::Black)
        m_neighbour.at(neighbourPos) = std::make_tuple(NeighbourState::BlackColor, groupId) ;
      else if(c == GoColor::White)
        m_neighbour.at(neighbourPos) = std::make_tuple(NeighbourState::WhiteColor, groupId) ;
      else
        m_neighbour.at(neighbourPos) = std::make_tuple(NeighbourState::None, 0) ;
    }


    bool hasNeighbour(int direction) const {
      return direction >= 0 && direction < NeighbourMax &&
        std::get<0>(m_neighbour.at(direction)) != NeighbourState::NotExistPos ;
    }

    GoPosition neighbourPosition(int direction) const {
      assert(hasNeighbour(direction)) ;
      if(direction == POS_UP) return GoPosition(m_position.first, m_position.second + 1) ;
      if(direction == POS_DOWN) return GoPosition(m_position.first, m_position.second -1) ;
      if(direction == POS_LEFT) return GoPosition(m_position.first -1, m_position.second) ;
      return GoPosition(m_position.first +1 , m_position.second) ;
    }

    std::vector<int> colorGroup(GoColor c) const {
      std::vector<int> groups ;
      NeighbourState b(NeighbourState::BlackColor) ;
      if(c == GoColor::White) b = NeighbourState::WhiteColor ;
      if(c == GoColor::None) b = NeighbourState::None ;
      for(const auto& g : m_neighbour) {
        if(std::get<0>(g) == b) {
          if(std::find(groups.begin(), groups.end(), std::get<1>(g)) == groups.end())
            groups.push_back(std::get<1>(g)) ;
        }
      }
      return groups ;
    }

  private:
    GoPosition m_position ;
    GoColor m_color ;
    int m_group_ref ;  
    std::array<Neighbour, NeighbourMax> m_neighbour ;
    
} ;

inline 
std::vector<GoPosition> stoneNeighbourPosition(GoStone const& stone) {
  std::vector<GoPosition> positions ;
  if(stone.hasNeighbour(GoStone::POS_UP))
    positions.push_back(stone.neighbourPosition(GoStone::POS_UP)) ;
  if(stone.hasNeighbour(GoStone::POS_DOWN))
    positions.push_back(stone.neighbourPosition(GoStone::POS_DOWN)) ;
  if(stone.hasNeighbour(GoStone::POS_LEFT))
    positions.push_back(stone.neighbourPosition(GoStone::POS_LEFT)) ;
  if(stone.hasNeighbour(GoStone::POS_RIGHT))
    positions.push_back(stone.neighbourPosition(GoStone::POS_RIGHT)) ;
  return positions ;
}

inline bool isQi(GoStone const& stone) {
  return stone.color() == GoColor::None ;
}

inline bool isWhiteStone(const GoStone& stone) {
  return stone.color() == GoColor::White ;
}

inline bool isBlackStone(const GoStone& stone) {
  return stone.color() == GoColor::Black ;
}

inline int stoneDirection(const GoStone& slhs,
    const GoStone& srhs) {
  const auto& lhs = slhs.position() ;
  const auto& rhs = srhs.position() ;
  if((lhs.first - rhs.first) == 1) return GoStone::POS_LEFT ;
  if((lhs.first - rhs.first) == -1) return GoStone::POS_RIGHT ;
  if((lhs.second - rhs.second) == 1) return GoStone::POS_DOWN ;
  if((lhs.second - rhs.second) == -1) return GoStone::POS_UP ;
  assert(false) ;
  return GoStone::POS_LEFT ;
}




#endif
