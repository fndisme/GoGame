/*
 * =====================================================================================
 *
 *       Filename:  GoSetNewGroupIdAction.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月21日 17时16分59秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "GoBoard.h"
#include "GoSetNewGroupIdAction.h"

void GoSetNewGroupIdAction::doAction(GoBoard* board) {
  board->setNewGroupId(m_newId) ;
}

