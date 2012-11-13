/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月09日 16时28分47秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <cassert>
#include <iostream>
#include "GoDef.h"
#include "GoAction.h"
#include "GoStone.h"
#include "GoBoard.h"

int main(int argc, char** argv) {

  GoStone stone(GoPosition(1,1), GoColor::White) ;

  GoBoard board(9,9) ;
  assert(board.canPlaceStone(GoPosition(0,0), GoColor::Black)) ;
  board.placeStone(GoPosition(0,0), GoColor::Black) ;
  board.placeStone(GoPosition(0,1), GoColor::White) ;
  //board.placeStone(GoPosition(0,2), GoColor::Black) ;
  //board.placeStone(GoPosition(1,0), GoColor::White) ;
  board.debugPrintCurrentBoard() ;
  return 0 ;
}
