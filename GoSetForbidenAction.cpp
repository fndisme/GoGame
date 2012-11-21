/*
 * =====================================================================================
 *
 *       Filename:  GoSetForbindenAction.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月21日 14时25分52秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "GoSetForbidenAction.h"
#include "GoBoard.h"

void GoSetForbidenAction::doAction(GoBoard* board) {
  board->resetForbidenPositions(m_lhs) ;
}

