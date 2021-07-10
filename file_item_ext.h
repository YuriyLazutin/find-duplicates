#ifndef FILE_ITEM_EXT_H
#define FILE_ITEM_EXT_H

#include <ostream>
#include "file_item.h"

class file_item_ext: protected file_item
{
  protected:
    char md5hash[32];
  public:
    explicit file_item_ext();
    explicit file_item_ext(const int p_size, const char* p_md5hash, const char* p_path);
    explicit file_item_ext(const file_item_ext &obj);
    //~file_item_ext():~file_item();
    file_item_ext& operator = (const file_item_ext &obj);
    //using file_item:: operator =;
    int operator == (const file_item_ext &obj) const;
    int operator > (const file_item_ext &obj) const;
    int operator < (const file_item_ext &obj) const;
    friend std::ostream& operator << (std::ostream &os, const file_item_ext &obj);
};

std::ostream& operator << (std::ostream &os, const file_item_ext &obj);

#endif // FILE_ITEM_EXT_H
