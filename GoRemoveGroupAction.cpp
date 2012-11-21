/*
 * =====================================================================================
 *
 *       Filename:  GoRemoveGroupAction.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月12日 21时32分54秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "GoRemoveGroupAction.h"
#include "GoBoard.h"

void GoRemoveGroupAction::doAction(GoBoard* b) {
  for(const auto& g : m_removedGroup)
    b->removeGroup(g.first) ;
}

GoAction::pointer GoRemoveGroupAction::doRevertAction() const{
  return pointer(new GoRecreateGroupAction(m_removedGroup)) ;
}

void GoRecreateGroupAction::doAction(GoBoard* b) {
  for(const auto& g : m_recreateGroup) 
    b->recreateGroup(g.first, g.second) ;
}

GoAction::pointer GoRecreateGroupAction::doRevertAction() const {
  return pointer(new GoRemoveGroupAction(m_recreateGroup)) ;
}

