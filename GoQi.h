/*
 * =====================================================================================
 *
 *       Filename:  GoQi.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月09日 17时52分12秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "GoDef.h"
#include <cassert>
#include <memory>
#include <set>
#include <functional>
class GoGroup ;
class GoQi {
  // FIXME max is 4 in GoGame
  std::set<GoGroup*> m_ref_group ;

  GoPosition m_position ;
  typedef std::function<void (GoGroup*, GoQi*)> AddRefFunction ;
  typedef AddRefFunction RemoveRefFunction ;
  typedef AddRefFunction MainAddRefFunction ;
  typedef AddRefFunction MainRemoveRefFunction ;

  
  void notifyAllAddRef() {
    for(auto g : m_ref_group) notifyAddRef(g, this) ; 
  }
  void notifyAllRemoveRef() {
    for(auto g : m_ref_group) notifyRemoveRef(g, this) ;
  }


  public:
    explicit GoQi(GoPosition const& pos) : m_position(pos) {}
    const GoPosition& position() const { return m_position ;}
    bool hasRef(GoGroup* group) const { return m_ref_group.count(group) ;}

    void addRef(GoGroup* group) { 
      assert(!hasRef(group)) ;
      mainAddRef(group, this) ;
      notifyAllAddRef() ;
      m_ref_group.insert(group) ;}

    void removeRef(GoGroup* group) {
      assert(hasRef(group)) ;
      mainRemoveRef(group, this) ;
      m_ref_group.erase(group) ; notifyAllRemoveRef() ;
    }

    size_t refCount() const { return m_ref_group.size() ;}

    static AddRefFunction notifyAddRef ;
    static RemoveRefFunction notifyRemoveRef ;
    static MainAddRefFunction mainAddRef ;
    static MainRemoveRefFunction mainRemoveRef ;
} ;
