#include "Reader.hpp"
#include "Exception.hpp"

Reader::Reader(const std::filesystem::path &path) {
  this->_file.open(path.c_str());
  this->_file.seekg(0, this->_file.end);

  this->_fileLen = this->_file.tellg();
  this->filePath = path;

  std::string line = this->getFileLine(1);

  this->cursor1.token = READER_CURSOR_MAIN;
  this->cursor2.token = READER_CURSOR_PRIMARY;
  this->cursor3.token = READER_CURSOR_SECONDARY;

  this->cursor1.isEOF = line.empty();
  this->cursor2.isEOF = line.empty();
  this->cursor3.isEOF = line.empty();

  this->cursor1.line = line;
  this->cursor2.line = line;
  this->cursor3.line = line;

  this->cursor1.lineLen = line.length();
  this->cursor2.lineLen = line.length();
  this->cursor3.lineLen = line.length();
}

std::string Reader::getFileLine(unsigned int lineNum) {
  this->_file.seekg(0, this->_file.beg);

  unsigned int currFileLen = 0;
  unsigned int currLineNum = 1;
  std::string line;

  for (std::string currLine; getline(this->_file, currLine); currLineNum++) {
    currFileLen += currLine.length();

    if (currLineNum == lineNum) {
      line = currLine;

      if (currFileLen + 1 <= this->_fileLen) {
        line += '\n';
      }

      break;
    }

    currFileLen += 1;
  }

  return line;
}

unsigned char Reader::nextToken() {
  unsigned char ch = this->cursor3.getChar();

  if (this->cursor3.charIdx >= this->cursor3.lineLen) {
    std::string line = this->getFileLine(this->cursor3.lineNum + 1);

    if (line.empty()) {
      this->cursor3.isEOF = true;

      if (ch == '\n') {
        this->cursor3.line = "";
        this->cursor3.lineLen = 0;
        this->cursor3.charIdx = 1;
        this->cursor3.lineNum += 1;
      }

      return ch;
    }

    this->cursor3.line = line;
    this->cursor3.lineLen = this->cursor3.line.length();
    this->cursor3.charIdx = 1;
    this->cursor3.lineNum += 1;
  } else {
    this->cursor3.charIdx += 1;
  }

  return ch;
}

void Reader::prevToken() {
  if (this->cursor3.charIdx <= 1) {
    if (this->cursor3.lineNum - 1 <= 0) {
      throw Exception("Tried to read non-existing line");
    }

    std::string line = this->getFileLine(this->cursor3.lineNum - 1);

    this->cursor3.line = line;
    this->cursor3.lineLen = this->cursor3.line.length();
    this->cursor3.charIdx = this->cursor3.lineLen;
    this->cursor3.lineNum -= 1;
  } else {
    this->cursor3.charIdx -= 1;
  }
}

void Reader::restoreCursor(ReaderCursorToken token) {
  ReaderCursor *targetCursor;
  ReaderCursor copyCursor;

  switch (token) {
    case READER_CURSOR_PRIMARY: {
      targetCursor = &this->cursor2;
      copyCursor = this->cursor1;

      break;
    }
    case READER_CURSOR_SECONDARY: {
      targetCursor = &this->cursor3;
      copyCursor = this->cursor2;

      break;
    }
    default: {
      return;
    }
  }

  targetCursor->isEOF = copyCursor.isEOF;
  targetCursor->line = copyCursor.line;
  targetCursor->lineLen = copyCursor.lineLen;
  targetCursor->charIdx = copyCursor.charIdx;
  targetCursor->lineNum = copyCursor.lineNum;

  if (token == READER_CURSOR_PRIMARY) {
    this->restoreCursor(READER_CURSOR_SECONDARY);
  }
}

void Reader::saveCursor(ReaderCursorToken token) {
  if (token == READER_CURSOR_MAIN) {
    this->saveCursor(READER_CURSOR_PRIMARY);
  }

  ReaderCursor *targetCursor;
  ReaderCursor saveCursor;

  switch (token) {
    case READER_CURSOR_MAIN: {
      targetCursor = &this->cursor1;
      saveCursor = this->cursor2;

      break;
    }
    case READER_CURSOR_PRIMARY: {
      targetCursor = &this->cursor2;
      saveCursor = this->cursor3;

      break;
    }
    default: {
      return;
    }
  }

  targetCursor->isEOF = saveCursor.isEOF;
  targetCursor->line = saveCursor.line;
  targetCursor->lineLen = saveCursor.lineLen;
  targetCursor->charIdx = saveCursor.charIdx;
  targetCursor->lineNum = saveCursor.lineNum;
}

unsigned char ReaderCursor::getChar() const {
  if (this->isEOF) {
    throw Exception("Tried to read non-existing char");
  }

  return this->line[this->charIdx - 1];
}
