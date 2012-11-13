/*
 * =====================================================================================
 *
 *       Filename:  GoAbandonRightAction.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月12日 15时36分25秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "GoAbandonRightAction.h"
#include "GoBoard.h"

void GoAbandonRightAction::doAction(GoBoard* board) {
  board->passToRivalColor(m_color) ;
}
