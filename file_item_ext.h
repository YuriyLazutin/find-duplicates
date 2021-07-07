#ifndef FILE_ITEM_EXT_H
#define FILE_ITEM_EXT_H

#include "file_item.h"

class file_item_ext: public file_item
{
  char md5hash[32];
public:
  file_item_ext();
  file_item_ext(const int p_size, const char* p_md5hash, const char* p_path);
  //~file_item_ext():~file_item();
  file_item_ext &operator=(const file_item_ext &obj);
  int operator==(const file_item_ext &obj);
  int operator>(const file_item_ext &obj);
  int operator<(const file_item_ext &obj);
};

#endif // FILE_ITEM_EXT_H
