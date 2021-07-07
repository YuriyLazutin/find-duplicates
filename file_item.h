#ifndef FILE_ITEM_H
#define FILE_ITEM_H

class file_item
{
  int size;
  char* path;

public:
  file_item() { size = 0; path = nullptr; };
  file_item(const int p_size, const char* p_path);
  file_item(const file_item &obj);
  ~file_item();
  file_item &operator=(const file_item &obj);
  int operator==(const file_item &obj) { return size == obj.size; };
  int operator>(const file_item &obj) { return size > obj.size; };
  int operator<(const file_item &obj) { return size < obj.size; };
};

#endif // FILE_ITEM_H
