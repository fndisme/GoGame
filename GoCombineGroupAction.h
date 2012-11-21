/*
 * =====================================================================================
 *
 *       Filename:  GoCombineGroupAction.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月13日 15时05分36秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_GOCOMBINEGROUPACTION_H
#define FND_GOCOMBINEGROUPACTION_H
#include "GoAction.h"
#include "GoGroup.h"

class GoCombineGroupAction : public GoAction {
  public:
  explicit GoCombineGroupAction(const Groups& groups) :
    m_groups(groups) {}
  private:
  const Groups m_groups ;
  pointer doClone() const { return pointer(new GoCombineGroupAction(m_groups)) ;}
  pointer doRevertAction() const ;
  void doAction(GoBoard*) ;
  std::string doName() const { return "GoCombineGroupAction" ;}
} ;

class GoBreakGroupAction : public GoAction {
  public:
    explicit GoBreakGroupAction(const Groups& groups) :
      m_groups(groups) {}
  private:
    const Groups m_groups ;
    pointer doClone() const { return pointer(new GoBreakGroupAction(m_groups)) ;}
    pointer doRevertAction() const { return pointer(new GoCombineGroupAction(m_groups)) ;}
    void doAction(GoBoard*) ;
    std::string doName() const { return "GoBreakGroupAction" ;}

} ;
#endif

