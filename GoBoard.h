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
#include "GoStone.h"
#include "GoGroup.h"

typedef std::vector<StoneInfomation> GoBoardSnap ;

class GoBoard {
  public:
    GoBoard(int mx, int my) ;
    typedef std::unique_ptr<GoBoard> pointer ;
    bool canPlaceStone(const GoPosition& pos, GoColor) const ;
    //void goAction(const GoPosition& pos, GoColor) ;
    //void undoLastGoAction() ;
    //void toAction(int step, int forkPos = 0) ;
    //void addFork(int step) ;
    //GoBoardSnap snap(int step) const ;
    pointer clone(int step) ;
    const ForbiddenGroup& forbiddenPositions() const { return m_forbiddenPositions;}

    GoColor currentColor() const { return m_currentColor ;}

    typedef std::set<int> GroupType ;
    GroupType removedOpponentGroup(GoPosition const& pos, GoColor c) const ;
    void removeStone(GoPosition const& pos) ;
    void placeStone(GoPosition const& pos) ; // not set color because must be current color
    //bool isRemoveSelfGroup(GoPosition const& pos, GoColor c) const ;
    GroupType combinedGroupAndAlive(GoPosition const& pos, GoColor c) const ;
    bool hasStonePosition(GoPosition const& pos) const {
      return pos.first >= 0 && pos.second >= 0 &&
        pos.first < m_maxX && pos.second < m_maxY ;
    }

    void resetForbidenPositions(const ForbiddenGroup& group) {
      assert(!group.empty() || m_forbiddenPositions.empty()) ;
      m_forbiddenPositions = group ;
    }

    //GoBoard(const GoBoard& board) ;

    void abandonCurrentRight() ;
    void passHandToColor(GoColor c) {
      m_currentColor = c ;
    }

    void setNewGroupId(int groupId) { m_nextGroupId = groupId ;}

    void combineGroups(const Groups& groups) ; 
    void addGroupMember(const GoPosition& pos,
        const std::vector<GoPosition>& qis,
        int group) ;
        

    void placeStone(GoPosition const& pos, GoColor c) ;

    const GoStone& stone(const GoPosition& pos) const
    { return m_stones.at(pos.first * m_maxY + pos.second) ;}

    void addNewGroup(int groupid, GoGroup const& group) ; 
    void removeSingleGroup(int groupid) ; 
    void removeGroup(int groupid) ;
    void setStoneAsNone(const GoPosition& pos) ;

    void debugPrintCurrentBoard() const ;
    bool canTakeBack() const { return !m_actions.empty() ;}
    void takeBackOneHand() ;
    void recreateGroup(int groupid, const GoGroup& g) ;

  private:
    //GoActionPointer m_current_action ;
    typedef std::unique_ptr<GoAction> ActionPointer ;
    int m_maxX ;
    int m_maxY ;

    // this must recaculate
    // FIXME
    typedef std::map<int, GoGroup> ColorGroupType ;
    ColorGroupType m_group ;
    std::vector<GoStone> m_stones; 
    std::vector<ActionPointer> m_actions ;

    ForbiddenGroup m_forbiddenPositions ;
    GoColor m_currentColor ;
    int m_nextGroupId = 0;

    GoStone& stone(const GoPosition& pos)
    { return m_stones.at(pos.first * m_maxY + pos.second) ;}
    
    void removeForbbinPosition() ;

    bool hasGroup(int groupid) const { return m_group.count(groupid) ;}
    void setStoneAsSolid(const GoPosition& pos, int c) ;
    bool hasColorGroupDeadIfPlaceStone(const GoPosition& pos, GoColor c) const ;
    //void updateStoneStateAsQi(const GoPosition& pos, const GoPosition& ori, int groupId) ;
    //void updateStoneStateAsSolid(const GoPosition& pos, int groupId) ;
} ;

inline bool isCurrentBoardColor(GoBoard const& b, GoColor c) {
  return c == b.currentColor() ;
}


inline bool isForbiddenPosition(GoBoard const& b, const GoPosition& pos) {
  return b.forbiddenPositions().count(pos);
} 

bool hasForbiddenPosition(GoBoard const& b) ;

std::vector<GoPosition> stoneQiPositionInBoard(const GoPosition& pos, const GoBoard&) ;

#endif
