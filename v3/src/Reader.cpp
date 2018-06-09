#include "Reader.hpp"
#include "Error.hpp"

std::string getStoreKey(ReaderStoreToken token) {
  return token == READER_STORE_LEXER ? "lexer" : "parser";
}

Reader::Reader(const std::filesystem::path &filePath) {
  this->_filePath = filePath;

  this->_file.open(this->_filePath.c_str());
  this->_fileSize = std::filesystem::file_size(this->_filePath);

  this->_line = this->_getLine(1);
  this->_lineLen = this->_line.length();

  this->_isEOF = this->_line.empty();
}

unsigned char Reader::getChar() const {
  if (this->isEOF()) {
    throw Error("Error reading char");
  }

  return this->_line[this->charIdx - 1];
}

bool Reader::isEOF() const {
  return this->_isEOF;
}

unsigned char Reader::next() {
  if (this->_isEOF) {
    throw Error("Error reading next char");
  }

  unsigned char ch = this->getChar();

  if (this->charIdx >= this->_lineLen) {
    std::string line = this->_getLine(this->lineNum + 1);

    if (line.empty()) {
      this->_isEOF = true;

      if (ch == '\n') {
        this->_line = "";
        this->_lineLen = 0;

        this->charIdx = 1;
        this->lineNum += 1;
      }

      return ch;
    }

    this->_line = line;
    this->_lineLen = this->_line.length();

    this->charIdx = 1;
    this->lineNum += 1;
  } else {
    this->charIdx += 1;
  }

  return ch;
}

unsigned char Reader::prev() {
  unsigned char ch = this->getChar();

  if (this->charIdx == 1) {
    if (this->lineNum - 1 == 0) {
      throw Error("Error reading prev char");
    }

    std::string line = this->_getLine(this->lineNum - 1);

    this->_line = line;
    this->_lineLen = this->_line.length();

    this->charIdx = this->_lineLen;
    this->lineNum -= 1;
  } else {
    this->charIdx -= 1;
  }

  return ch;
}

std::string Reader::_getLine(unsigned int searchLineNum) {
  unsigned int currFileSize = 0;
  unsigned int currLineNum = 1;
  std::string searchLine;

  this->_file.seekg(0);

  for (
    std::string currLine;
    std::getline(this->_file, currLine);
    currLineNum++
  ) {
    currFileSize += currLine.length();

    if (currLineNum == searchLineNum) {
      searchLine = currLine;

      if (currFileSize + 1 <= this->_fileSize) {
        searchLine += '\n';
      }

      break;
    }

    currFileSize += 1;
  }

  return searchLine;
}

void Reader::restore(ReaderStoreToken token) {
  std::string key = getStoreKey(token);
  ReaderStoreItem item = this->_store[key];

  this->charIdx = item.charIdx;
  this->lineNum = item.lineNum;

  this->_line = this->_getLine(this->lineNum);
  this->_lineLen = this->_line.length();

  this->_store.erase(key);
}

void Reader::save(ReaderStoreToken token) {
  this->_store.erase(getStoreKey(token));
}

void Reader::store(ReaderStoreToken token) {
  this->_store[getStoreKey(token)] = {
    .charIdx = this->charIdx,
    .lineNum = this->lineNum
  };
}
