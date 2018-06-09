# Grammar
The syntax is specified using Extended Backus-Naur Form (EBNF) [edited by W3C](https://www.w3.org/TR/xml/#sec-notation).

## Syntax

```txt
Syntax ::= (_ Statement)* _
Statement ::= AssignExpr | CallExpr

AssignExpr ::= ID _ EQUAL _ Expr
CallExpr ::= ID _ LPAR _ ArgList _ RPAR

ArgList ::= Expr (_ COMMA _ Expr)*

Expr ::= Literal | Id
Id ::= ID
Literal ::= BOOLEAN_LITERAL | NIL_LITERAL | NUMBER_LITERAL | STRING_LITERAL
```

## Skippable

```txt
_ ::= (WS | BLOCK_COMMENT | LINE_COMMENT)*
```

## Tokens

```txt
WS ::= (HTAB | NL | CR | SPACE)+

LBRACE ::= '{'
RBRACE ::= '}'
LPAR ::= '('
RPAR ::= ')'
LBRACK ::= '['
RBRACK ::= ']'

BLOCK_COMMENT ::= "/*" (ANY_CHAR - "*/")* "*/"
LINE_COMMENT ::= "//" (ANY_CHAR - NL)*

ID ::= [a-zA-Z_]+

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
CR ::= #xD
HTAB ::= #x9
NL ::= #xA
SPACE ::= #x20
```
