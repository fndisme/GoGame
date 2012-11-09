/*
 * =====================================================================================
 *
 *       Filename:  GoAction.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月09日 16时06分38秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "GoAction.h"

GoAction::GoAction(GoActionPointer par, const GoPosition& pos, GoColor c) :
  m_parent(par),
  m_pos(pos),
  m_color(c) {}

GoActionPointer GoAction::makeRoot() {
  return GoActionPointer(new GoAction(nullptr, GoPosition(0,0), None)) ;
}

GoActionPointer GoAction::makeChild(const GoPosition& pos, GoColor c) {
  GoActionPointer newAction(new GoAction(shared_from_this(), pos, c)) ;

  size_t size = childrenSize() ;
  if(size == 0) m_children = newAction ;
  else if(size == 1) {
    buildRoom() ;
    appendChild(newAction) ;
  } else {
    appendChild(newAction) ;
  }
}

namespace {
  class ToPointer : public boost::static_visitor<GoActionPointer> {
    public:
      GoActionPointer operator()(GoActionPointer action) const {
        return action ;
      }

      template<typename T>
      GoActionPointer operator()(T&) const {
        return GoActionPointer() ;
      }
  } ;

  class AppendToGroup : public boost::static_visitor<> {
    public:
      void operator()(GoActionPointer) const {

      }

      void operator()(std::vector<GoActionPointer>& group) const {
        group.push_back(m_newAction) ;
      }

      explicit AppendToGroup(GoActionPointer newaction) :
      m_newAction(newaction) {}
      private:
      GoActionPointer m_newAction ;
  } ;

  class ChildrenSize : public boost::static_visitor<size_t> {
    public:
      size_t operator()(const GoActionPointer& action) const {
        if(action.get()) return 1 ;
        else return 0 ;
      }

      size_t operator()(const std::vector<GoActionPointer>& group) const {
        return group.size() ;
      }
  } ;
}

void GoAction::buildRoom() {
  auto firstChild = boost::apply_visitor(ToPointer(), m_children) ;
  std::vector<GoActionPointer> children ;
  children.push_back(firstChild) ;
  m_children = children ;
}

size_t GoAction::childrenSize() const {
  return boost::apply_visitor(ChildrenSize(), m_children) ;
}

void GoAction::appendChild(GoActionPointer newAction) {
  boost::apply_visitor(AppendToGroup(newAction), m_children) ;
}

