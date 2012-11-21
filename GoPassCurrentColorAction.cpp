/*
 * =====================================================================================
 *
 *       Filename:  GoPassCurrentColorAction.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月21日 17时22分01秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "GoBoard.h"
#include "GoPassCurrentColorAction.h"

void GoPassCurrentColorAction::doAction(GoBoard* board) {
  board->passHandToColor(m_color) ;
}
