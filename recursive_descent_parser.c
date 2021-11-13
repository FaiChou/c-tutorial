#include <stdio.h>
#include <stdlib.h>

/*
<expr> ::= <term> + <expr>
         | <term> - <expr>
         | <term>

<term> ::= <factor> * <term> 
         | <factor> / <term>
         | <factor>

<factor> ::= ( <expr> ) | Num
*/

enum {
  Num
};

int token;
int token_val;
char* line = NULL;
char* src = NULL;
int expr();
void next();

int factor() {
  int v = 0;
  if (token == '(') {
    next();
    v = expr();
    next();
  } else {
    v = token_val;
    next();
  }
  return v;
}

int term() {
  int lvalue = factor();
  if (token == '*') {
    next();
    return lvalue * term();
  } else if (token == '/') {
    next();
    return lvalue / term();
  } else {
    return lvalue;
  }
}

int expr() {
  int lvalue = term();
  if (token == '+') {
    next();
    return lvalue + expr();
  } else if (token == '-') {
    next();
    return lvalue - expr();
  } else {
    return lvalue;
  }
}
void next() {
  // skip white space
  while (*src == ' ' || *src == '\t') {
    src++;
  }
  // printf("%c\n", *src);
  token = *src++;

  if (token >= '0' && token <= '9') {
    token_val = token - '0';
    token = Num;

    while (*src >= '0' && *src <= '9') {
      token_val = token_val * 10 + *src - '0';
      src++;
    }
    return;
  }
}

int main(int argc, char* argv[])
{
  size_t linecap = 0;
  ssize_t linelen;
  while ((linelen = getline(&line, &linecap, stdin)) > 0) {
    src = line;
    next();
    printf("%d\n", expr());
  }
  return 0;
}