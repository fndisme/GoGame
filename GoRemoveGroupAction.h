/*
 * =====================================================================================
 *
 *       Filename:  GoRemoveGroupAction.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月12日 21时12分40秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_GOREMOVEGROUPACTION_H
#define FND_GOREMOVEGROUPACTION_H
#include "GoAction.h"
#include "GoGroup.h"
class GoRemoveGroupAction : public GoAction {
  public:
    typedef std::pair<int, GoGroup> GroupValue ;
    typedef std::vector<GroupValue> RemoveGroupType ;
    explicit GoRemoveGroupAction(RemoveGroupType const& removedGroup) :
      m_removedGroup(removedGroup) {}
  private:
    RemoveGroupType m_removedGroup ;
    pointer doClone() const { return pointer(new GoRemoveGroupAction(m_removedGroup));}
    pointer doRevertAction() const ;
    void doAction(GoBoard*) ;
    std::string doName() const { return "GoRemoveGroupAction" ;}
} ;

class GoRecreateGroupAction : public GoAction {

  public:
    typedef GoRemoveGroupAction::GroupValue GroupValue ;
    typedef GoRemoveGroupAction::RemoveGroupType RecreateGroupType;

    explicit GoRecreateGroupAction(RecreateGroupType const& createGroup) : 
      m_recreateGroup(createGroup) {}
  private:
    RecreateGroupType m_recreateGroup ;
    pointer doClone() const { return pointer(new GoRecreateGroupAction(m_recreateGroup)) ;}
    pointer doRevertAction() const ;
    void doAction(GoBoard*) ;
    std::string doName() const { return "GoRecreateGroupAction" ;}
} ;
#endif
