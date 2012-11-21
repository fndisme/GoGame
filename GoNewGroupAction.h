/*
 * =====================================================================================
 *
 *       Filename:  GoNewGroupAction.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月12日 19时34分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_GONEWGROUPACTION_H
#define FND_GONEWGROUPACTION_H
#include "GoAction.h"
#include "GoGroup.h"
class GoNewGroupAction : public GoAction {
  public:
    GoNewGroupAction(int groupid, const GoGroup& group) :
      m_group_id(groupid),
      m_group(group) {}
    GoNewGroupAction(const GoNewGroupAction&) = default ;

  private:
    void doAction(GoBoard* board) ;
    pointer doClone() const ;
    pointer doRevertAction() const ;
    std::string doName() const { return "GoNewGroupAction" ;}

    int m_group_id ;
    GoGroup m_group ;

} ;

class GoRemoveSingleStoneGroupAction : public GoAction {
  public:
    GoRemoveSingleStoneGroupAction(int groupid, GoGroup const& group) :
      m_group_id(groupid),
      m_group(group) {}

    GoRemoveSingleStoneGroupAction(const GoRemoveSingleStoneGroupAction&) = default ;

  private:
    void doAction(GoBoard* board) ;
    pointer doClone() const ;
    pointer doRevertAction() const ;
    std::string doName() const { return "GoRemoveSingleStoneGroupAction" ;}

    int m_group_id ;
    GoGroup m_group ;
} ;
#endif
