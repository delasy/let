#ifndef SRC_READER_HPP
#define SRC_READER_HPP

#include <fstream>
#include <map>

struct ReaderStoreItem {
  unsigned int charIdx = 1;
  unsigned int lineNum = 1;
};

enum ReaderStoreToken {
  READER_STORE_LEXER,
  READER_STORE_PARSER
};

class Reader {
 public:
  unsigned int charIdx = 1;
  unsigned int lineNum = 1;

  explicit Reader(const std::filesystem::path &);

  unsigned char getChar() const;
  bool isEOF() const;
  unsigned char next();
  unsigned char prev();
  void restore(ReaderStoreToken);
  void save(ReaderStoreToken);
  void store(ReaderStoreToken);

 private:
  std::fstream _file;
  std::filesystem::path _filePath;
  unsigned int _fileSize;
  bool _isEOF;
  std::string _line;
  unsigned int _lineLen;
  std::map<std::string, ReaderStoreItem> _store;

  std::string _getLine(unsigned int);
};

#endif
