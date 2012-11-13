/*
 * =====================================================================================
 *
 *       Filename:  GoAbandonRightAction.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月12日 15时20分57秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_GOABANDONRIGHTACTION_H
#define FND_GOABANDONRIGHTACTION_H
#include "GoAction.h"

class GoAbandonRightAction : public GoAction {
  public:
    explicit GoAbandonRightAction(GoColor c) :
      m_color(c) {}
  private:
    pointer doClone() const { return pointer(new GoAbandonRightAction(m_color)) ;}
    pointer doRevertAction() const { return doClone() ;}
    void doAction(GoBoard* board) ;

    GoColor m_color ;
} ;

#endif
