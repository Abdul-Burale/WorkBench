#include "util.h"
#include "slp.h"

#include <stdlib.h>


/* Statements */
A_stm A_CompoundStm(A_stm stm1, A_stm stm2){
  A_stm s = checked_malloc(sizeof(*s));
  s->Kind = A_compoundStm;
  s->u.compound.stm1 = stm1;
  s->u.compound.stm2 = stm2;
  return s;
}

A_stm A_AssignStm(string id, A_exp exp){
  A_stm s = checked_malloc(sizeof(*s));
  s->Kind = A_assignStm;
  s->u.assign.id = id;
  s->u.assign.exp = exp;
  return s;
}

A_stm A_PrintStm(A_expList exps){
  A_stm s = checked_malloc(sizeof(*s));
  s->Kind = A_printStm;
  s->u.print.exps = exps;
  return s;
}

/* Expressions */

A_exp A_IdExp(string id){
  A_exp e = checked_malloc(sizeof(*e));
  e->Kind = A_idExp;
  e->u.id = id;

  return e;
}

A_exp A_NumExp(int num){
  A_exp e = checked_malloc(sizeof(*e));
  e->Kind = A_numExp;
  e->u.num = num;
  return e;
}

A_exp A_OpExp(A_exp left, A_binop oper, A_exp right){
  A_exp e = checked_malloc(sizeof(*e));
  e->Kind = A_opExp;
  e->u.op.left = left;
  e->u.op.oper = oper;
  e->u.op.right = right;
  return e;
}

A_exp A_EseqExp(A_stm stm, A_exp exp){
  A_exp e = checked_malloc(sizeof(*e));
  e->Kind = A_eseqExp;
  e->u.eseq.stm = stm;
  e->u.eseq.exp = exp;
  return e;
}


/*Expression List */

A_expList A_PairExpList(A_exp head, A_expList tail){
  A_expList e = checked_malloc(sizeof(*e));
  e->Kind = A_pairExpList;
  e->u.pair.head = head;
  e->u.pair.tail = tail;
  return e;
}

A_expList A_LastExpList(A_exp last){
  A_expList e = checked_malloc(sizeof(*e));
  e->Kind = A_lastExpList;
  e->u.last = last;
  return e;
}
