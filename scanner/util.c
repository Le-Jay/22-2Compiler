/****************************************************/
/* File: util.c                                     */
/* Utility function implementation                  */
/* for the TINY compiler                            */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "util.h"

/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void printToken( TokenType token, const char* tokenString )
{ switch (token)
  { 
    case INT: fprintf(listing,"INT\t%s\n",tokenString); break;
    case RETURN: fprintf(listing,"RETURN\t%s\n",tokenString); break;
    case WHILE: fprintf(listing,"WHILE\t%s\n",tokenString); break;
    case COMMA: fprintf(listing,",\t%s\n",tokenString); break;
    case IF: fprintf(listing,"IF\t%s\n",tokenString); break;
    case THEN: fprintf(listing,"THEN\t%s\n",tokenString); break;
    case ELSE: fprintf(listing,"ELSE\t%s\n",tokenString); break;
    case END: fprintf(listing,"END\t%s\n",tokenString); break;
    case REPEAT: fprintf(listing,"REPEAT\t%s\n",tokenString); break;
    case LBRACE: fprintf(listing,"{\t%s\n",tokenString); break;
    case RBRACE: fprintf(listing,"}\t%s\n",tokenString); break;
    case LBRACKET: fprintf(listing,"[\t%s\n",tokenString); break;
    case RBRACKET: fprintf(listing,"]\t%s\n",tokenString); break;
    case UNTIL: fprintf(listing,"UNTIL\t%s\n",tokenString); break;
    case READ: fprintf(listing,"READ\t%s\n",tokenString); break;
    case WRITE:
      fprintf(listing,
         "reserved word: %s\n",tokenString);
      break;
    case ASSIGN: fprintf(listing,":=\n"); break;
    case LT: fprintf(listing,"<\n"); break;
    case EQ: fprintf(listing,"=\n"); break;
    case LPAREN: fprintf(listing,"(\n"); break;
    case RPAREN: fprintf(listing,")\n"); break;
    case SEMI: fprintf(listing,";\n"); break;
    case PLUS: fprintf(listing,"+\n"); break;
    case MINUS: fprintf(listing,"-\n"); break;
    case TIMES: fprintf(listing,"*\n"); break;
    case OVER: fprintf(listing,"/\n"); break;
    case ENDFILE: fprintf(listing,"EOF\n"); break;
    case NUM:
      fprintf(listing,
          "NUM, val= %s\n",tokenString);
      break;
    case ID:
      fprintf(listing,
          "ID, name= %s\n",tokenString);
      break;
    case ERROR:
      fprintf(listing,
          "ERROR: %s\n",tokenString);
      break;
    default: /* should never happen */
      fprintf(listing,"Unknown token: %d\n",token);
  }
}

void printToText( TokenType token, const char* tokenString )
{ switch (token)
  { 
    case INT: fprintf(txt,"\t%d\t\t\tINT\t\t\t%s\n",lineno, tokenString); break;
    case RETURN: fprintf(txt,"\t%d\t\t\tRETURN\t\t\t%s\n",lineno, tokenString); break;
    case WHILE: fprintf(txt,"\t%d\t\t\tWHILE\t\t\t%s\n",lineno, tokenString); break;
    case COMMA: fprintf(txt,"\t%d\t\t\t,\t\t\t%s\n",lineno, tokenString); break;
    case IF: fprintf(txt,"\t%d\t\t\tIF\t\t\t%s\n",lineno, tokenString); break;
    case THEN: fprintf(txt,"\t%d\t\t\tTHEN\t\t\t%s\n",lineno, tokenString); break;
    case ELSE: fprintf(txt,"\t%d\t\t\tELSE\t\t\t%s\n",lineno, tokenString); break;
    case END: fprintf(txt,"\t%d\t\t\tEND\t\t\t%s\n",lineno, tokenString); break;
    case REPEAT: fprintf(txt,"\t%d\t\t\tREPEAT\t\t\t%s\n",lineno, tokenString); break;
    case UNTIL: fprintf(txt,"\t%d\t\t\tUNTIL\t\t\t%s\n",lineno, tokenString); break;
    case READ: fprintf(txt,"\t%d\t\t\tREAD\t\t\t%s\n",lineno, tokenString); break;
    case WRITE:
      fprintf(listing,
         "reserved word: %s\n",tokenString);
      break;
    case ASSIGN: fprintf(txt,"\t%d\t\t\t:=\t\t\t%s\n",lineno, tokenString); break;
    case LT: fprintf(txt,"\t%d\t\t\t<\t\t\t%s\n",lineno, tokenString); break;
    case EQ: fprintf(txt,"\t%d\t\t\t=\t\t\t%s\n",lineno, tokenString); break;
    case LPAREN: fprintf(txt,"\t%d\t\t\t(\t\t\t%s\n",lineno, tokenString); break;
    case RPAREN: fprintf(txt,"\t%d\t\t\t)\t\t\t%s\n",lineno, tokenString); break;
    case LBRACE: fprintf(txt,"\t%d\t\t\t{\t\t\t%s\n",lineno, tokenString); break;
    case RBRACE: fprintf(txt,"\t%d\t\t\t}\t\t\t%s\n",lineno, tokenString); break;
    case LBRACKET: fprintf(txt,"\t%d\t\t\t[\t\t\t%s\n",lineno, tokenString); break;
    case RBRACKET: fprintf(txt,"\t%d\t\t\t]\t\t\t%s\n",lineno, tokenString); break;
    case SEMI: fprintf(txt,"\t%d\t\t\t;\t\t\t%s\n", lineno, tokenString); break;
    case PLUS: fprintf(txt,"\t%d\t\t\t+\t\t\t%s\n",lineno, tokenString); break;
    case MINUS: fprintf(txt,"\t%d\t\t\t-\t\t\t%s\n",lineno, tokenString); break;
    case TIMES: fprintf(txt,"\t%d\t\t\t*\t\t\t%s\n",lineno, tokenString); break;
    case OVER: fprintf(txt,"\t%d\t\t\t/\t\t\t%s\n",lineno, tokenString); break;
    case NUM: fprintf(txt,"\t%d\t\t\tNUM\t\t\t%s\n",lineno,tokenString); break;
    case ID: fprintf(txt,"\t%d\t\t\tID\t\t\t%s\n",lineno,tokenString); break;
    case ERROR: fprintf(txt,"\t%d\t\t\tERROR\t\t\t%s\n",lineno,tokenString); break;
    case ENDFILE: fprintf(txt,"\t%d\t\t\tEOF\n",lineno); break;
    default: /* should never happen */
      fprintf(txt,"\t%d\t\t\tUnknown token\t\t\t%s\n",lineno,tokenString); break;
  }
}

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode * newStmtNode(StmtKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = StmtK;
    t->kind.stmt = kind;
    t->lineno = lineno;
  }
  return t;
}

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
TreeNode * newExpNode(ExpKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = ExpK;
    t->kind.exp = kind;
    t->lineno = lineno;
    t->type = Void;
  }
  return t;
}

/* Function copyString allocates and makes a new
 * copy of an existing string
 */
char * copyString(char * s)
{ int n;
  char * t;
  if (s==NULL) return NULL;
  n = strlen(s)+1;
  t = malloc(n);
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else strcpy(t,s);
  return t;
}

/* Variable indentno is used by printTree to
 * store current number of spaces to indent
 */
static indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno+=2
#define UNINDENT indentno-=2

/* printSpaces indents by printing spaces */
static void printSpaces(void)
{ int i;
  for (i=0;i<indentno;i++)
    fprintf(listing," ");
}

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree( TreeNode * tree )
{ int i;
  INDENT;
  while (tree != NULL) {
    printSpaces();
    if (tree->nodekind==StmtK)
    { switch (tree->kind.stmt) {
        case IfK:
          fprintf(listing,"If\n");
          break;
        case RepeatK:
          fprintf(listing,"Repeat\n");
          break;
        case AssignK:
          fprintf(listing,"Assign to: %s\n",tree->attr.name);
          break;
        case ReadK:
          fprintf(listing,"Read: %s\n",tree->attr.name);
          break;
        case WriteK:
          fprintf(listing,"Write\n");
          break;
        default:
          fprintf(listing,"Unknown ExpNode kind\n");
          break;
      }
    }
    else if (tree->nodekind==ExpK)
    { switch (tree->kind.exp) {
        case OpK:
          fprintf(listing,"Op: ");
          printToken(tree->attr.op,"\0");
          break;
        case ConstK:
          fprintf(listing,"Const: %d\n",tree->attr.val);
          break;
        case IdK:
          fprintf(listing,"Id: %s\n",tree->attr.name);
          break;
        default:
          fprintf(listing,"Unknown ExpNode kind\n");
          break;
      }
    }
    else fprintf(listing,"Unknown node kind\n");
    for (i=0;i<MAXCHILDREN;i++)
         printTree(tree->child[i]);
    tree = tree->sibling;
  }
  UNINDENT;
}
