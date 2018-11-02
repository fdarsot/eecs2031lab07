#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "doOperator.h"
#include "tokenStack.h"
#include "lexical.h"

static int op_quit(struct tokenStack *stack);
static int op_print(struct tokenStack *stack);
static int op_dump(struct tokenStack *stack);
static int op_add(struct tokenStack *stack);
static int popInt(struct tokenStack *s);

/*MY FUNCTIONS-----------------------------------*/
static int op_diff(struct tokenStack *s);
static int op_product(struct tokenStack *s);
static int op_quotient(struct tokenStack *s);
static int op_gt(struct tokenStack *s);
static int op_lt(struct tokenStack *s);
static int op_ge(struct tokenStack *s);
static int op_le(struct tokenStack *s);
static int op_eq(struct tokenStack *s);
static int op_drop(struct tokenStack *s);
static int op_s(struct tokenStack *s);
/*MY FUNCTIONS-----------------------------------*/

static struct operator_struct {
  char *name;
  int (*fn_ptr)(struct tokenStack *);
} ops[] = {
  {"quit", op_quit},
  {"print", op_print},
  {"dump", op_dump},
  {"-", op_diff},
  {"*", op_product},
  {"/", op_quotient},
  {"gt", op_gt},
  {"lt", op_lt},
  {"ge", op_ge},
  {"le", op_le},
  {"eq", op_eq},
  {"drop", op_drop},
  {"s", op_s},
  {"+", op_add},  
  {(char *)NULL, (int(*)(struct tokenStack *)) NULL}
};


/* YOU WRITE THIS */
static int popInt(struct tokenStack *s)
{
  struct lexToken *t = popTokenStack(s);
	
  int temp = atoi(t->symbol); /* convert the char symbol to int */
   
  /* 
   printf("this is symbol the token is %d \n", temp);
  	  */
  	  
  freeToken(t);   
  return temp;
}

/* YOU WRITE THIS */
static void pushInt(struct tokenStack *s, int v)
{
	/* 
   		-given a stack and an int, push the int onto the stack,
   		-need to turn int into char to push onto stack
   		-once char is achieved, need to put it in a lexToken (encode) to push onto stack
   		-call pushTokenStack and pass stack and lextoken
  	  */
  struct lexToken *t = allocToken();
  
  char str[MAX_SYMBOL_LENGTH]; 
  sprintf(str,"%d", v);  /*turn int v into char and put in array*/
  
  /*char temp = (char) (v + '0');  convert the int to char symbol  
  printf("this is  pushing  %s \n", str); */
  
  /* place char into the lextoken at symbol[0] */
    t->kind = LEX_TOKEN_NUMBER;  
    
    strncpy(t->symbol, str, MAX_SYMBOL_LENGTH);   /* copy all of new string array into t->symbol */
    
  /*  t->symbol[1]= temp;*/
    
  /*  t->symbol = '\0';
    printf("this is t->symbol  %s \n", t->symbol); */

   /*  then push lextoken onto the stack*/
 pushTokenStack(s,t);
}




int doOperator(struct tokenStack *stack, char *o) 
{
  struct operator_struct *op = ops;
  for(op=ops;op->name != (char *)NULL; op++) {
    if(!strcmp(op->name, o))
      return op->fn_ptr(stack);
  }
  return(-1);
}

/*ARGSUSED*/
static int op_quit(struct tokenStack *stack)
{
  printf("[quit]\n");
  exit(0);
  /*NOTREACHED*/
}

static int op_print(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  printToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_dump(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  dumpToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_add(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);  
  v2 = popInt(stack);
  	  
 /* printf("this is after add  %d \n", v1+v2);  
  	  */
  pushInt(stack, v1+v2);
  return(0);
}

/*MY FUNCTIONS-----------------------------------------------------------*/
static int op_diff(struct tokenStack *stack)
{
  int n1, n2;
  n2 = popInt(stack);  
  n1 = popInt(stack); 	 /*bigger number*/
  pushInt(stack, n1-n2);
  return(0);  
}



static int op_product(struct tokenStack *stack)
{
  int n1, n2;
  n2 = popInt(stack);  
  n1 = popInt(stack); 	 
  pushInt(stack, n1*n2);
  return(0);  
}


static int op_quotient(struct tokenStack *stack)
{
  int n1, n2;
  n2 = popInt(stack);  
  n1 = popInt(stack); 	 /*bigger number*/
  pushInt(stack, n1/n2);
  return(0);  
}

static int op_gt(struct tokenStack *stack)
{
  int n1, n2;
  n2 = popInt(stack);  
  n1 = popInt(stack); 	 
  
  if(n1>n2)
  {
  	  pushInt(stack,1);
  }
  else
  {
  	  pushInt(stack,0);
  }
  return(0);  
}


static int op_lt(struct tokenStack *stack)
{
  int n1, n2;
  n2 = popInt(stack);  
  n1 = popInt(stack);  /*bigger number*/
  
  if(n1<n2)
  {
  	  pushInt(stack,1);
  }
  else
  {
  	  pushInt(stack,0);
  }
  return(0);  
}


static int op_ge(struct tokenStack *stack)
{
  int n1, n2;
  n2 = popInt(stack);  
  n1 = popInt(stack);  /*bigger number*/
  
  if(n1>=n2)
  {
  	  pushInt(stack,1);
  }
  else
  {
  	  pushInt(stack,0);
  }
  return(0);  
}



static int op_le(struct tokenStack *stack)
{
  int n1, n2;
  n2 = popInt(stack);  
  n1 = popInt(stack);  /*bigger number*/
  
  if(n1<=n2)
  {
  	  pushInt(stack,1);
  }
  else
  {
  	  pushInt(stack,0);
  }
  return(0);  
}


static int op_eq(struct tokenStack *stack)
{
  int n1, n2;
  n2 = popInt(stack);  
  n1 = popInt(stack);  /*bigger number*/
  
  if(n1==n2)
  {
  	  pushInt(stack,1);
  }
  else
  {
  	  pushInt(stack,0);
  }
  return(0);  
}

static int op_drop(struct tokenStack *stack)
{
  popInt(stack);  
  return(0);  
}


static int op_s(struct tokenStack *stack)
{
  int i;
     
    if(emptyTokenStack())
    {
        printf("Stack is empty! \n");
    }
    else
    {
        printf("Stack elements are: \n");


			for(i=0;i<(stack->top);++i)
			{
				struct lexToken *t= stack->e[i];
				printToken(stdout, t);
			}
        
    }
  return(0);  
}














