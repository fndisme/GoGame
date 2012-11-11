/*
 * =====================================================================================
 *
 *       Filename:  GoStone.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月11日 13时19分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
//#include "GoGroup.h"
#include "GoStone.h"

void GoStone::unbindGroup() {
  assert(hasGroup()) ;
  m_group_ref =  -1;
}



