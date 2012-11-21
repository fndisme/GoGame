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
#include <vector>
#include <string>
#include "GoDef.h"
class GoGroup {
  typedef std::set<GoPosition> PositionGroup;
  PositionGroup m_member ;
  typedef std::set<GoPosition> QiGroup ;
  QiGroup m_qi ;
  GoColor m_color ;

  public:
    explicit GoGroup(GoColor c) : m_color(c) {}
    GoGroup(GoGroup const& g) : 
      m_member(g.m_member),
      m_qi(g.m_qi),
      m_color(g.m_color) {}
    GoGroup& operator = (const GoGroup& g) {
      m_member = g.m_member ;
      m_qi = g.m_qi ;
      m_color = g.m_color ;
      return *this ;
    }

    GoColor color() const { return m_color ;}
    void addMember(GoPosition const& pos, const std::vector<GoPosition>& qi) ;
    void addMember(const PositionGroup& mems) { m_member.insert(mems.begin(), mems.end()) ;}
    const QiGroup& qi() const { return m_qi;}
    const PositionGroup& member() const { return m_member ;}
    bool hasMember(GoPosition const& pos) const { return m_member.count(pos) ;}

    bool isDead() const { return m_qi.empty() ;}
    bool isDeadIfRemoveQi(GoPosition const& pos) const {
      return m_qi.size() == 1 && m_qi.count(pos) == 1 ;
    }
    void removeQi(const GoPosition& q) { m_qi.erase(q) ;}
    void addQi(const GoPosition& q) { m_qi.insert(q) ;}
    template<typename T>
      void addQi(const T& qiGroup) {
        m_qi.insert(qiGroup.begin(), qiGroup.end()) ;
      }
    void debugInformaiton() const ;
} ;


typedef std::vector<std::pair<int, GoGroup>> Groups ;

//bool is_can_combine(const GoGroup& lhs, const GoGroup& rhs) ;
//bool is_can_combine(const GoGroup& lhs, const GoGroup& rhs,  QiType qiPos) ;
//bool is_dead_if_combine(const GoGroup& lhs, const GoGroup& rhs, QiType qiPos) ;


#endif

