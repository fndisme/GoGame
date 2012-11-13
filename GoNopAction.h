/*
 * =====================================================================================
 *
 *       Filename:  GoNopAction.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月12日 14时46分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_GONOPACTION_H
#define FND_GONOPACTION_H
#include "GoAction.h"

class GoNopAction : public GoAction {
  private:
    pointer doClone() const { return pointer(new GoNopAction()) ;}
    void doAction(GoBoard*) { }
    pointer doRevertAction() const { return doClone() ;}
} ;

#endif
