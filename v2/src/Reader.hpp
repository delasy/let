#ifndef SRC_READER_HPP
#define SRC_READER_HPP

#include <fstream>

enum ReaderCursorToken {
  READER_CURSOR_UNKNOWN,
  READER_CURSOR_MAIN,
  READER_CURSOR_PRIMARY,
  READER_CURSOR_SECONDARY
};

class ReaderCursor {
 public:
  unsigned int charIdx = 1;
  bool isEOF = false;
  std::string line;
  unsigned int lineLen = 0;
  unsigned int lineNum = 1;
  ReaderCursorToken token = READER_CURSOR_UNKNOWN;

  unsigned char getChar() const;
};

class Reader {
 public:
  ReaderCursor cursor1;
  ReaderCursor cursor2;
  ReaderCursor cursor3;
  std::filesystem::path filePath;

  explicit Reader(const std::filesystem::path &);

  std::string getFileLine(unsigned int);
  unsigned char nextToken();
  void prevToken();
  void restoreCursor(ReaderCursorToken);
  void saveCursor(ReaderCursorToken);

 private:
  std::fstream _file;
  unsigned int _fileLen;
};

#endif
