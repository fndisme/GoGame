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

int main(int argc, char** argv) {
  auto root = GoAction::makeRoot() ;
  assert(root->isRoot()) ;

  GoStone stone(GoPosition(1,1), GoColor::White) ;
  return 0 ;
}
