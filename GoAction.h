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
#include <string>
//#include <boost/variant.hpp>
#include "GoDef.h"

class GoAction {
  public:
    typedef std::unique_ptr<GoAction> pointer ;
    pointer clone() const { return doClone() ;}
    virtual ~GoAction() {}
    pointer revertAction() const { return doRevertAction() ;}
    void action(GoBoard* board) { doAction(board) ;}
    std::string name() const { return doName() ;} // for debug

  private:
    virtual pointer doClone()const = 0 ;
    virtual pointer doRevertAction() const= 0 ;
    virtual void doAction(GoBoard*) = 0 ;
    virtual std::string doName() const = 0 ;
    
} ;
#endif
