/*
 * =====================================================================================
 *
 *       Filename:  GoBinaryAction.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月12日 17时39分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_GOSEQUENCEACTION_H
#define FND_GOSEQUENCEACTION_H
#include <algorithm>
#include <iostream>
#include "GoAction.h"

class GoSequenceAction : public GoAction {
  public:
    typedef std::vector<pointer> Sequence ;
    explicit GoSequenceAction(Sequence&& seq) : m_sequence(std::move(seq)) {}

  private:
    void doAction(GoBoard* b) {
      std::cout << "action size is " << m_sequence.size() << std::endl ;
      for(auto& v : m_sequence) {
        std::cout << v->name() << std::endl ;
        v->action(b) ;

      }
    }
    pointer doRevertAction() const { 
      Sequence seqs ;
      std::for_each(m_sequence.rbegin(), m_sequence.rend(), [&seqs](Sequence::const_reference v) {
          seqs.push_back(v->revertAction()) ;
          }) ;
      
      return pointer(new GoSequenceAction(std::move(seqs))) ;
    }

    pointer doClone() const {
      Sequence seqs ;
      for(const auto& v : m_sequence) seqs.push_back(v->clone()) ;
      return pointer(new GoSequenceAction(std::move(seqs))) ;
    }

    Sequence m_sequence ;

    std::string doName() const { return "GoSequenceAction" ;}
} ;

#endif
