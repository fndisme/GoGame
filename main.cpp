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
  board.placeStone(GoPosition(0,2), GoColor::Black) ;
  board.placeStone(GoPosition(1,0), GoColor::White) ;
  board.placeStone(GoPosition(3,3), GoColor::Black) ;
  board.placeStone(GoPosition(1,1), GoColor::White) ;
  board.placeStone(GoPosition(4,4), GoColor::Black) ;
  board.placeStone(GoPosition(2,3), GoColor::White) ;
  board.placeStone(GoPosition(3,5), GoColor::Black) ;
  board.placeStone(GoPosition(2,5), GoColor::White) ;
  board.placeStone(GoPosition(2,4), GoColor::Black) ;
  board.placeStone(GoPosition(1,4), GoColor::White) ;
  board.placeStone(GoPosition(5,5), GoColor::Black) ;
  board.placeStone(GoPosition(3,4), GoColor::White) ;
  assert(!board.canPlaceStone(GoPosition(2,4), GoColor::Black)) ;

  assert(board.canTakeBack()) ;
  board.takeBackOneHand() ;
  board.debugPrintCurrentBoard() ;
  return 0 ;
}
