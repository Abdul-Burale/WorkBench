#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"


int maxargs(A_stm stm){
  int Count = 0;

  if(stm->Kind == A_compoundStm)    // Compound Statement
    {
      return maxargs(stm->u.compound.stm1) + maxargs(stm->u.compound.stm2);
    }
  else if(stm->Kind == A_assignStm) // Assisgn Statement
    {
      if(stm->u.assign.exp->Kind == A_eseqExp)
        {
          return maxargs(stm->u.assign.exp->u.eseq.stm);
        }
    }
  else   // Print Statement
    {
      Count++;
      // PairExpList. Head & Tail || Head ==> Exp Could Be eseq with A Print Stm Tail is another ExpList
      A_expList expList = stm->u.print.exps;

      while(expList->Kind == A_pairExpList)
        {
          A_exp exp = expList->u.pair.head;

          if(exp->Kind == A_eseqExp)
            {
              Count += maxargs(exp->u.eseq.stm);
            }

          expList = expList->u.pair.tail;
        }
    }


  return Count;
}

IntAndTable_ intAndtable(int val, Table_ t)
{
  IntAndTable_ iAt = malloc(sizeof(*iAt));
  if (iAt == NULL)
    {printf("Failed to init IntAndTable struct.\n");}

  iAt->i = val;
  iAt->t = t;
  return iAt;
}


struct IntAndTable interpExp(A_exp e, Table_ t)
{
  if(e->Kind == A_idExp)
    {
      return *intAndtable(lookup(t, e->u.id), t);
    }
  else if(e->Kind == A_numExp)
    {
      return *intAndtable(e->u.num, t);
    }
  else if(e->Kind == A_opExp)
    {
      int Left_ = interpExp(e->u.op.left, t).i;
      int Right_ = interpExp(e->u.op.right, t).i;
      int Ans = 0;

      if (e->u.op.oper == A_plus)
      {
       Ans = Left_ + Right_;
      }
      else if (e->u.op.oper == A_minus)
      {
        Ans = Left_ - Right_;
      }
      else if (e->u.op.oper == A_times)
      {
        Ans = Left_ * Right_;
      }
      else {
        Ans = Left_ / Right_;
      }
      return *intAndtable(Ans, t);
    }

  else
    {
      interpStm(e->u.eseq.stm, t);
      return interpExp(e->u.eseq.exp, t);
    }
}

int lookup(Table_ t, string key)
{
  if(t == NULL)
    {
      printf("Table is invalid(NULL)... \tEmpty Linked List.\n");
      return 1;
    }

  if(strcmp(key, t->id) == 0) return t->value;
  else return lookup(t->tail, key);
}

Table_ Update(Table_ t, string key, int value)
{
  return Table(key, value, t);
}

Table_ interpStm(A_stm s, Table_ t)
{

  if(s->Kind == A_compoundStm)
    {
     // Recursion
     t = interpStm(s->u.compound.stm1, t);
     t = interpStm(s->u.compound.stm2, t);
    }
  else if (s->Kind == A_assignStm) //Update
  {
    t = Update(t, s->u.assign.id, interpExp(s->u.assign.exp, t).i);
  }
  else // Print
  {
    if(s->u.print.exps->Kind == A_pairExpList)
      {
        A_expList eList = s->u.print.exps;

        while(eList->Kind == A_pairExpList)
          {
            A_exp e = eList->u.pair.head;
            printf("%d\n", interpExp(e, t).i);
            eList = eList->u.pair.tail;
          }
        printf("%d\n", interpExp(eList->u.last, t).i);
      }
    else
      {
        printf("%d\n", interpExp(s->u.print.exps->u.last, t).i);
      }
  }


  return t;
}

Table_ Table(string id, int value, struct table *tail)
{
  Table_ t = malloc(sizeof(*t));
  t->id = id;
  t->value = value;
  t->tail = tail;
  return t;
}

int main(int argc, char *argv[]) {
  A_stm programAST = prog();
  Table_ tab = NULL;

  int maxArguments = maxargs(programAST);
  printf("\nMax arguments of Prog ==>\t %d\n\n\n", maxArguments);

  interpStm(programAST, tab);

  /*

  printf("Argument Count ==> \t%d\nArg(0) ==> \t%s\n", argc, argv[0]);
  printf("\nMax arguments of Prog ==>\t %d\n", maxArguments);
  */
  return 0;

}
