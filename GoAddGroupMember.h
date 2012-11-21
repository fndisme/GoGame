/*
 * =====================================================================================
 *
 *       Filename:  GoAddGroupMember.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月12日 20时51分00秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_GOADDGROUPMEMBER_H
#define FND_GOADDGROUPMEMBER_H
#include "GoAction.h"
class GoAddGroupMember : public GoAction {
  public:
    GoAddGroupMember(const GoPosition& pos,
        const std::vector<GoPosition>& qis,
        int group) :
      m_position(pos),
      m_maybeAddedQi(qis),
      m_group(group) {}

  private:
    const GoPosition m_position ; // not changed
    const std::vector<GoPosition> m_maybeAddedQi; // not changed
    const int m_group ;

    pointer doClone() const { return pointer(new GoAddGroupMember(m_position, m_maybeAddedQi, m_group)) ;}
    pointer doRevertAction() const ;
    void doAction(GoBoard*) ;
    std::string doName() const { return "GoAddGroupMember" ;}
} ;


class GoRemoveGroupMemberAction : public GoAction {
  public:
    GoRemoveGroupMemberAction(const GoPosition& pos,
        const std::vector<GoPosition>& qis,
        int group) :
      m_position(pos),
      m_maybeRemovedQi(qis),
      m_group(group) {}

  private:
    const GoPosition m_position ;
    const std::vector<GoPosition> m_maybeRemovedQi ;
    const int m_group ;

    pointer doClone() const { return pointer(new GoRemoveGroupMemberAction(m_position, m_maybeRemovedQi, m_group)) ;}
    pointer doRevertAction() const ;
    void doAction(GoBoard*) ;
    std::string doName() const { return "GoRemoveGroupMemberAction" ;}

} ;
#endif
