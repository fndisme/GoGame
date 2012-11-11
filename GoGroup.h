/*
 * =====================================================================================
 *
 *       Filename:  GoGroup.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月09日 17时35分43秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_GOGROUP_H
#define FND_GOGROUP_H
#include "GoDef.h"
class GoQi ;
typedef std::shared_ptr<GoQi> QiType ;
class GoGroup {
  typedef std::set<GoPosition> PositionGroup;
  PositionGroup m_member ;
  typedef std::set<GoPosition> QiGroup ;
  QiGroup m_qi ;
  const GoColor m_color ;

  public:
    explicit GoGroup(GoColor c) : m_color(c) {}
    GoColor color() const { return m_color ;}
    void addMember(GoPosition const& pos, const std::vector<GoPosition>& qi) ;
    const QiGroup& qi() const { return m_qi;}
    const PositionGroup& member() const { return m_member ;}
    bool hasMember(GoPosition const& pos) const { return m_member.count(pos) ;}

    bool isDead() const { return m_qi.empty() ;}
    bool isDeadIfRemoveQi(GoPosition const& pos) const {
      return m_qi.size() == 1 && m_qi.count(pos) == 1 ;
    }
} ;

//bool is_can_combine(const GoGroup& lhs, const GoGroup& rhs) ;
//bool is_can_combine(const GoGroup& lhs, const GoGroup& rhs,  QiType qiPos) ;
//bool is_dead_if_combine(const GoGroup& lhs, const GoGroup& rhs, QiType qiPos) ;


#endif

