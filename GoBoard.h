/*
 * =====================================================================================
 *
 *       Filename:  GoBoard.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月09日 15时18分16秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_GOBOARD_H
#define FND_GOBOARD_H
#include <map>
#include "GoAction.h"

typedef std::vector<StoneInfomation> GoBoardSnap ;
class GoGroup ;
class GoQi ;
class GoBoard {
  public:
    GoBoard(int mx, int my) ;
    ~GoBoard() ;
    bool canPlaceStone(const GoPosition& pos, GoColor) const ;
    void goAction(const GoPosition& pos, GoColor) ;
    void undoLastGoAction() ;
    void toAction(int step, int forkPos = 0) ;
    void addFork(int step) ;
    GoBoardSnap snap(int step) const ;

  private:
    GoActionPointer m_current_action ;
    int m_maxX ;
    int m_maxY ;

    // this must recaculate
    // FIXME
    std::map<int, GoGroup> m_group ;
    std::map<GoPosition, int> m_group_ids ; 



} ;
#endif
