/****************************************************/
/* File: util.c                                     */
/* Utility function implementation                  */
/* for the TINY compiler                            */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "util.h"
#include "y.tab.h"

/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void printToken( TokenType token, const char* tokenString )
{ switch (token)
  { case IF:
    case ELSE:
    case WHILE:
    case RETURN:
    case INT:
    case VOID:
      fprintf(listing,
         "reserved word: %s\n",tokenString);
      break;
    case ASSIGN: fprintf(listing,"=\n"); break;
    case EQ: fprintf(listing,"==\n"); break;
    case NE: fprintf(listing,"!=\n"); break;
    case LT: fprintf(listing,"<\n"); break;
    case LE: fprintf(listing, "<=\n"); break;
    case GT: fprintf(listing, ">\n"); break;
    case GE: fprintf(listing, ">=\n"); break;
    case LPAREN: fprintf(listing,"(\n"); break;
    case RPAREN: fprintf(listing,")\n"); break;
    case LBRACE: fprintf(listing, "[\n"); break;
    case RBRACE: fprintf(listing, "]\n"); break;
    case LCURLY: fprintf(listing, "{\n"); break;
    case RCURLY: fprintf(listing, "}\n"); break;
    case SEMI: fprintf(listing,";\n"); break;
    case COMMA: fprintf(listing, ",\n"); break;
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

void printExpType(ExpType token)
{ switch(token)
  { case Void:
      fprintf(listing,"void");
      break;
    case Integer:
      fprintf(listing,"int");
      break;
    case Boolean:
      fprintf(listing,"bool");
      break;
    default:
      fprintf(listing,"unknown");
      break;
  }
}

/* Function newDeclNode creates a new declaration
 * node for syntax tree construction
 */
TreeNode * newDeclNode(DeclKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = DeclK;
    t->kind.decl = kind;
    t->lineno = lineno;
  }
  return t;
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

//proj2
/* Function newOpNode creates a new operation
 * node for syntax tree construction
 */
TreeNode * newOpNode(TokenType optype)
{ TreeNode * t = newExpNode(OpK);
  if (t != NULL)
    t->attr.op = optype;
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

//proj2
static int printDeclVar(TreeNode * tree)
{ int flag = 1;
  fprintf(listing,"%s \n\tType : ",tree->attr.name);
  printExpType(tree->type);
  if (tree->child[0] != NULL) {
    if (tree->child[0]->attr.val != -1)
      fprintf(listing,"[%d]",tree->child[0]->attr.val);
    else
      fprintf(listing, "[]");
    flag = 0;
  }
  fprintf(listing,"\n");
  return flag;
}

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree( TreeNode * tree )
{ int i, flag; //
  INDENT;
  while (tree != NULL) {
    printSpaces();
    flag = 1;
    if (tree->nodekind ==DeclK)
    { switch (tree->kind.decl) {
        case ParamK:
          fprintf(listing,"\n\tParameter : ");
          //fprintf(listing,"\n\tSingle parameter, ");
          flag = printDeclVar(tree);
          break;
        case VarK:
          fprintf(listing,"\n\tVariable Declare : ");
          //fprintf(listing,"\n\tVariable Declare: ");
          flag = printDeclVar(tree);
          break;
        case FnK:
          fprintf(listing,"\nFunction Declare: %s\n\tType : ",tree->attr.name);
          printExpType(tree->type);
          fprintf(listing,"\n");
          break;
        default:
          fprintf(listing,"Unknown DeclNode kind\n");
          break;
      }
    }
    else if (tree->nodekind==StmtK)
    { switch (tree->kind.stmt) {
          case CompK:
            fprintf(listing,"Compound Statement :\n");
            break;
          case IfK:
            fprintf(listing,"If");
            /*if (tree->child[2] != NULL)
              fprintf(listing,"Else"); */
            fprintf(listing,"\n");
            break;
          case WhileK:
            fprintf(listing,"While\n");
            break;
          case ReturnK:
            fprintf(listing,"Return : \n");
            break;
        default:
          fprintf(listing,"Unknown StmtNode kind\n");
          break;
      }
    }
    else if (tree->nodekind==ExpK)
    { switch (tree->kind.exp) {
          case AssignK:
            fprintf(listing,"Assign : = \n");
            break;
          case OpK:
            fprintf(listing,"Operator : ");
            printToken(tree->attr.op,"\0");
            break;
          case ConstK:
            fprintf(listing,"Constant : %d\n",tree->attr.val);
            break;
          case IdK:
            fprintf(listing,"Variable : %s\n",tree->attr.name);
            break;
          case CallK:
            fprintf(listing,"Call, name : %s, with arguments below\n",tree->attr.name);
            break;
          case IdxK:
            fprintf(listing,"Indexing : (expression)\n");
            break;
          case SimpleExpK:
            fprintf(listing,"Simple Expression\n");
            break;
        default:
          fprintf(listing,"Unknown ExpNode kind\n");
          break;
      }
    }
    else fprintf(listing,"Unknown node kind\n");
  if(flag)
    for (i=0;i<MAXCHILDREN;i++)
         printTree(tree->child[i]);
    tree = tree->sibling;
  }
  UNINDENT;
}
