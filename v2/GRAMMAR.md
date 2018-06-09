# Grammar
The syntax is specified using Extended Backus-Naur Form (EBNF) [edited by W3C](https://www.w3.org/TR/xml/#sec-notation).

## Syntax

```txt
Syntax ::= (_ Statement)* _
Statement ::= AssignExpr | CallExpr

AssignExpr ::= ID _ EQUAL _ Expr
CallExpr ::= ID _ LPAR _ ArgList _ RPAR

ArgList ::= Expr (_ COMMA _ Expr)*

Expr ::= Id | Literal
Id ::= ID
Literal ::= BOOLEAN_LITERAL | NIL_LITERAL | NUMBER_LITERAL | STRING_LITERAL
```

## Skippable

```txt
_ ::= (WS | BLOCK_COMMENT | LINE_COMMENT)*
```

## Tokens

```txt
WS ::= (BS | CR | FF | LF | SPACE | TAB | VT)+

LBRACE ::= '{'
RBRACE ::= '}'
LPAR ::= '('
RPAR ::= ')'
LBRACK ::= '['
RBRACK ::= ']'

BLOCK_COMMENT ::= "/*" (ANY_CHAR - "*/")* "*/"
LINE_COMMENT ::= "//" (ANY_CHAR - NL)*

ID ::= [a-zA-Z_$][a-zA-Z0-9_$]+

RETURN ::= "return"

BOOLEAN_LITERAL ::= "false" | "true"
NIL_LITERAL ::= "nil"
NUMBER_LITERAL ::= [0-9]+
STRING_LITERAL ::= STRING_LITERAL_DQ | STRING_LITERAL_SQ
STRING_LITERAL_DQ ::= '"' (ANY_CHAR - '"')* '"'
STRING_LITERAL_SQ ::= '\'' (ANY_CHAR - '\'')* '\''

COMMA ::= ','
EXCL ::= '!'

EQUAL ::= '='
MINUS ::= '-'
PLUS ::= '+'
TILDE ::= '~'
```

## Primitives

```txt
ANY_CHAR ::= [#x0-#x10FFFF]+
BS ::= #x8
CR ::= #xD
FF ::= #xC
LF ::= #xA
SPACE ::= #x20
TAB ::= #x9
VT ::= #xB
```
