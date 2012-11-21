/*
 * =====================================================================================
 *
 *       Filename:  GoSetNewGroupIdAction.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月21日 17时11分18秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_GOSETNEWGROUPACTION_H
#define FND_GOSETNEWGROUPACTION_H
#include "GoAction.h"
class GoSetNewGroupIdAction : public GoAction {
  public:
    GoSetNewGroupIdAction(int newId, int oldId) :
      m_newId(newId),
      m_oldId(oldId) {}
  private:
    std::string doName() const { return "GoSetNewGroupAction" ;}
    pointer doClone() const { return pointer(new GoSetNewGroupIdAction(m_newId, m_oldId)) ;}
    pointer doRevertAction() const {
      return pointer(new GoSetNewGroupIdAction(m_oldId, m_newId)) ;
    }

    void doAction(GoBoard* board) ;
    const int m_newId ;
    const int m_oldId ;
} ;
#endif
