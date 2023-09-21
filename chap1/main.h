#include "prog1.h"

typedef struct table *Table_;
typedef struct IntAndTable *IntAndTable_;

struct table {
  string id;
  int value;
  Table_ tail;
};

struct IntAndTable {
  int i;
  Table_ t;

};


struct IntAndTable interpExp(A_exp e, Table_ t);

Table_ Table(string id, int val, struct table *tail);
Table_ interpStm(A_stm s, Table_ t);
Table_ Update(Table_ t, string key, int value);

IntAndTable_ intAndtable(int val, Table_ t);

int maxargs(A_stm);
int lookup(Table_ t, string key);
