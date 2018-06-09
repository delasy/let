#include "Parser.hpp"
#include "Exception.hpp"

Parser::Parser(Reader &reader) {
  ParserSkippable parserSkippable(reader);

  if (parserSkippable.isInitialized()) {
    this->skippable = parserSkippable;
    this->token = PARSER_SKIPPABLE;

    reader.saveCursor(READER_CURSOR_MAIN);
    return;
  }

  reader.restoreCursor(READER_CURSOR_PRIMARY);
  ParserAssignExpr parserAssignExpr(reader);

  if (parserAssignExpr.isInitialized()) {
    this->assignExpr = parserAssignExpr;
    this->token = PARSER_ASSIGN_EXPR;

    reader.saveCursor(READER_CURSOR_MAIN);
    return;
  }

  reader.restoreCursor(READER_CURSOR_PRIMARY);
  ParserCallExpr parserCallExpr(reader);

  if (parserCallExpr.isInitialized()) {
    this->callExpr = parserCallExpr;
    this->token = PARSER_CALL_EXPR;

    reader.saveCursor(READER_CURSOR_MAIN);
    return;
  }

  reader.restoreCursor(READER_CURSOR_PRIMARY);
  std::string errorMessage;

  errorMessage += "Unexpected statement '";
  errorMessage += reader.cursor3.getChar();
  errorMessage += "'";

  throw Exception(errorMessage, reader);
}

ParserArgList::ParserArgList(Reader &reader) {
  Lexer lexer(reader);
  reader.restoreCursor(READER_CURSOR_SECONDARY);

  while (lexer.token != LEXER_RPAR) {
    ParserExpr parserExpr(reader);

    if (!parserExpr.isInitialized()) {
      std::string errorMessage;

      errorMessage += "Unexpected token '";
      errorMessage += reader.cursor3.getChar();
      errorMessage += "', expected expression";

      throw Exception(errorMessage, reader);
    }

    this->exprs.push_back(parserExpr);
    ParserSkippable _1(reader);

    lexer = Lexer(reader);

    if (lexer.token == LEXER_COMMA) {
      reader.saveCursor(READER_CURSOR_PRIMARY);
      ParserSkippable _2(reader);

      continue;
    }

    reader.restoreCursor(READER_CURSOR_SECONDARY);

    if (lexer.token != LEXER_RPAR) {
      std::string errorMessage;

      errorMessage += "Unexpected token '";
      errorMessage += reader.cursor3.getChar();
      errorMessage += "', expected comma or right parenthesis";

      throw Exception(errorMessage, reader);
    }
  }

  this->_initialize();
}

ParserAssignExpr::ParserAssignExpr(Reader &reader) {
  this->id = ParserId(reader);

  if (!this->id.isInitialized()) {
    return;
  }

  ParserSkippable _1(reader);
  Lexer lexerEqual(reader);

  if (lexerEqual.token != LEXER_EQUAL) {
    reader.restoreCursor(READER_CURSOR_SECONDARY);
    return;
  }

  reader.saveCursor(READER_CURSOR_PRIMARY);

  ParserSkippable _2(reader);
  this->expr = ParserExpr(reader);

  if (!this->expr.isInitialized()) {
    return;
  }

  this->_initialize();
}

bool ParserBase::isInitialized() const {
  return this->_isInitialized;
}

void ParserBase::_initialize() {
  this->_isInitialized = true;
}

ParserCallExpr::ParserCallExpr(Reader &reader) {
  this->id = ParserId(reader);

  if (!this->id.isInitialized()) {
    return;
  }

  ParserSkippable _1(reader);
  Lexer lexerLPar(reader);

  if (lexerLPar.token != LEXER_LPAR) {
    reader.restoreCursor(READER_CURSOR_SECONDARY);
    return;
  }

  reader.saveCursor(READER_CURSOR_PRIMARY);

  ParserSkippable _2(reader);
  this->argList = ParserArgList(reader);

  if (!this->argList.isInitialized()) {
    return;
  }

  ParserSkippable _3(reader);
  Lexer lexerRPar(reader);

  if (lexerRPar.token != LEXER_RPAR) {
    reader.restoreCursor(READER_CURSOR_SECONDARY);
    return;
  }

  reader.saveCursor(READER_CURSOR_PRIMARY);
  this->_initialize();
}

ParserExpr::ParserExpr(Reader &reader) {
  ParserId parserId(reader);

  if (!parserId.isInitialized()) {
    ParserLiteral parserLiteral(reader);

    if (!parserLiteral.isInitialized()) {
      return;
    }

    this->literal = parserLiteral;
    this->token = PARSER_EXPR_LITERAL;
  } else {
    this->id = parserId;
    this->token = PARSER_EXPR_ID;
  }

  reader.saveCursor(READER_CURSOR_PRIMARY);
  this->_initialize();
}

ParserId::ParserId(Reader &reader) {
  this->l = Lexer(reader);

  if (this->l.token != LEXER_ID) {
    reader.restoreCursor(READER_CURSOR_SECONDARY);
    return;
  }

  reader.saveCursor(READER_CURSOR_PRIMARY);
  this->_initialize();
}

ParserLiteral::ParserLiteral(Reader &reader) {
  this->l = Lexer(reader);

  if (!this->l.isLiteral()) {
    reader.restoreCursor(READER_CURSOR_SECONDARY);
    return;
  }

  reader.saveCursor(READER_CURSOR_PRIMARY);
  this->_initialize();
}

ParserSkippable::ParserSkippable(Reader &reader) {
  for (unsigned int i = 0; !reader.cursor2.isEOF; i++) {
    Lexer lexer(reader);

    if (!lexer.isSkippable()) {
      reader.restoreCursor(READER_CURSOR_SECONDARY);

      if (i == 0) {
        return;
      } else {
        break;
      }
    }

    reader.saveCursor(READER_CURSOR_PRIMARY);
    this->lexers.push_back(lexer);
  }

  this->_initialize();
}
