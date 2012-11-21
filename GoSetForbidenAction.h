/*
 * =====================================================================================
 *
 *       Filename:  GoSetFormbidenAction.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月21日 14时20分02秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_GOSETFORBINDENACTION_H
#define FND_GOSETFORBINDENACTION_H
#include "GoAction.h"

class GoSetForbidenAction : public GoAction {
  public:
    GoSetForbidenAction(const ForbiddenGroup& lhs, const ForbiddenGroup& rhs) :
      m_lhs(lhs),
      m_rhs(rhs) {}
  private:
    GoSetForbidenAction(const GoSetForbidenAction& o) :
      m_lhs(o.m_lhs),
      m_rhs(o.m_rhs) {}
    pointer doClone() const { return pointer(new GoSetForbidenAction(*this)) ;}
    pointer doRevertAction() const { return pointer(new GoSetForbidenAction(m_rhs, m_lhs)) ;}
    void doAction(GoBoard*) ;
    const ForbiddenGroup m_lhs ;
    const ForbiddenGroup m_rhs ;
    std::string doName() const { return "GoSetForbidenAction" ;}


} ;
#endif

