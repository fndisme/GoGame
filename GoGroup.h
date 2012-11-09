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
class GoGroup {
  typedef std::set<GoPosition> QiGroup ;
  std::set<GoPosition> m_member ;
  std::set<GoPosition> m_qi ;
  const GoColor m_color ;

  public:
    explicit GoGroup(GoColor c) ;
    GoColor color() const { return m_color ;}
    void addMember(GoPosition const& pos, const std::vector<GoPosition>& qi) ;
    const QiGroup& qi() const { return m_qi;}
    const QiGroup& member() const { return m_member ;}
} ;

bool is_can_combine(const GoGroup& lhs, const GoGroup& rhs) ;
bool is_can_combine(const GoGroup& lhs, const GoGroup& rhs, GoPosition const& qi) ;
bool is_can_combine(const GoGroup& lhs, const GoGroup& rhs, GoPosition const& qi,
    std::vector<GoPosition>& combineQi) ;


#endif

