/*
 * =====================================================================================
 *
 *       Filename:  GoNewGroupAction.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月12日 19时40分07秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "GoBoard.h"
#include "GoNewGroupAction.h"

GoAction::pointer GoNewGroupAction::doClone() const {
  return pointer(new GoNewGroupAction(*this)) ;
}

void GoNewGroupAction::doAction(GoBoard* board) {
  board->addNewGroup(m_group_id, m_group) ;
}

GoAction::pointer GoNewGroupAction::doRevertAction() const {
  return pointer(new GoRemoveSingleStoneGroupAction(m_group_id, m_group)) ;
}

GoAction::pointer GoRemoveSingleStoneGroupAction::doClone() const {
  return pointer(new GoRemoveSingleStoneGroupAction(*this)) ;
}

void GoRemoveSingleStoneGroupAction::doAction(GoBoard* board) {
  board->removeSingleGroup(m_group_id) ;
}

GoAction::pointer GoRemoveSingleStoneGroupAction::doRevertAction() const {
  return pointer(new GoNewGroupAction(m_group_id, m_group)) ;
}




