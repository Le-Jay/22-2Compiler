/****************************************************/
/* File: tiny.l                                     */
/* Lex specification for TINY                       */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

%{
#include "globals.h"
#include "util.h"
#include "scan.h"
/* lexeme of identifier or reserved word */
char tokenString[MAXTOKENLEN+1];
%}

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}+{number}*
newline     \n
whitespace  [ \t]+

%%

"return"        {return RETURN;}
","		          {return COMMA;}
"/*"	        	{return COMMENTB;}
"*/"	        	{return COMMENTE;}
"int"           {return INT;}
"if"            {return IF;}
"while"         {return WHILE;}
"then"          {return THEN;}
"else"          {return ELSE;}
"end"           {return END;}
"repeat"        {return REPEAT;}
"until"         {return UNTIL;}
"read"          {return READ;}
"write"         {return WRITE;}
":="            {return ASSIGN;}
"="             {return EQ;}
"<"             {return LT;}
"+"             {return PLUS;}
"-"             {return MINUS;}
"*"             {return TIMES;}
"/"             {return OVER;}
"("             {return LPAREN;}
")"             {return RPAREN;}
"["			      	{return LBRACKET;}
"]"			      	{return RBRACKET;}
"{"             {return LBRACE;}
"}"			      	{return RBRACE;}
";"             {return SEMI;}
{number}        {return NUM;}
{identifier}    {return ID;}
{newline}       {lineno++;}
{whitespace}    {/* skip whitespace */}
"{"             { char c;
                  do
                  { c = input();
                    if (c == EOF) break;
                    if (c == '\n') lineno++;
                  } while (c != '}');
                }
.               {return ERROR;}

%%

TokenType getToken(void)
{ static int firstTime = TRUE;
  TokenType currentToken;
  if (firstTime)
  { firstTime = FALSE;
    lineno++;
    yyin = source;
    yyout = listing;
  }
  currentToken = yylex();
  strncpy(tokenString,yytext,MAXTOKENLEN);

  if (TraceScan)
  {
    if(currentToken == COMMENTB)
    {
      TraceScan = FALSE;
    }
    else if(currentToken == COMMENTE)
    {
      fprintf(listing, "\t%d:", lineno);
      printToken(ERROR, "Comment Error");
      printToText(ERROR, "Comment Error");
    }
    if(TraceScan)
    {
    fprintf(listing,"\t%d: ",lineno);
    printToken(currentToken,tokenString);
    printToText(currentToken, tokenString);
    }
  }
  else
  {
    if(currentToken == COMMENTE)
    {
      TraceScan = TRUE;
    }
    else if(currentToken == ENDFILE)
    {
      fprintf(listing, "\t%d:", lineno);
      printToken(ERROR, "Comment Error");
      printToText(ERROR, "Comment Error");

      fprintf(listing,"\t%d: ",lineno);
      printToken(currentToken,tokenString);
      printToText(currentToken, tokenString);
    }
  }
  return currentToken;
}

