/*
 * =====================================================================================
 *
 *       Filename:  GoAddGroupMember.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月12日 21时00分39秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "GoAddGroupMember.h"

GoAction::pointer GoAddGroupMember::doRevertAction() const {
  return pointer(new GoRemoveGroupMemberAction(m_position, m_maybeAddedQi, m_group)) ;
}

GoAction::pointer GoRemoveGroupMemberAction::doRevertAction() const {
  return pointer(new GoAddGroupMember(m_position, m_maybeRemovedQi, m_group)) ;
}

void GoAddGroupMember::doAction(GoBoard* board) {
assert(false) ;
}

void GoRemoveGroupMemberAction::doAction(GoBoard* board) {
assert(false) ;
}


