/*
 * =====================================================================================
 *
 *       Filename:  GoPassCurrentColorAction.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月21日 17时19分28秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_GOPASSCURRENTCOLORACTION_H
#define FND_GOPASSCURRENTCOLORACTION_H
#include "GoAction.h"
class GoPassCurrentColorAction : public GoAction {
  public:
    explicit GoPassCurrentColorAction(GoColor c) :
      m_color(c) {}
  private:
    pointer doClone() const { return pointer(new GoPassCurrentColorAction(m_color)) ;}
    pointer doRevertAction() const { return pointer(new GoPassCurrentColorAction(opponentColor(m_color))) ;}
    void doAction(GoBoard*) ;
    std::string doName() const { return "GoPassCurrentColorAction" ;}

    const GoColor m_color ;

} ;
#endif
