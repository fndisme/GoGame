/*
 * =====================================================================================
 *
 *       Filename:  GoAction.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月09日 15时34分21秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_GOACTION_H
#define FND_GOACTION_H
#include <vector>
#include <memory>
#include <boost/variant.hpp>
#include "GoDef.h"
typedef boost::variant<
    GoActionPointer,
    std::vector<GoActionPointer>
  > GoPointerTree ;

class GoAction : public std::enable_shared_from_this<GoAction>{
  private:
    GoPosition m_pos ;
    GoColor m_color ;
    GoActionWeakPointer m_parent ;
    GoPointerTree m_children ;

    GoAction(GoActionPointer parent, const GoPosition& pos, GoColor) ;
    void appendChild(GoActionPointer child);
    void buildRoom() ;
  public:
    bool isRoot() const { return !m_parent.lock().get();}
    size_t childrenSize() const ;
    const GoPosition& position() const { return m_pos ;}
    GoColor color() const { return m_color ;}
    GoActionPointer makeChild(const GoPosition& pos, GoColor) ;
    static 
      GoActionPointer makeRoot() ;

} ;
#endif
