/*
 * =====================================================================================
 *
 *       Filename:  GoCombineGroupAction.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月13日 15时57分27秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "GoBoard.h"
#include "GoCombineGroupAction.h"

GoAction::pointer GoCombineGroupAction::doRevertAction() const {
  return pointer(new GoBreakGroupAction(m_groups)) ;
}

void GoCombineGroupAction::doAction(GoBoard* board) {
  board->combineGroups(m_groups) ;
}

void GoBreakGroupAction::doAction(GoBoard* board) {
  assert(false) ;
}

