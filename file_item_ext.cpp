#include "file_item_ext.h"
#include <cstring>
#include <cstdio>
#include <cstdlib>

file_item_ext::file_item_ext()
{
  for (int i = 0; i < 32; i++)
      md5hash[i] = '\0';
}

file_item_ext::file_item_ext(const int p_size, const char* p_md5hash, const char* p_path) : file_item(p_size, p_path)
{
  memcpy(md5hash, p_md5hash, 32);
};

file_item_ext::file_item_ext(const file_item_ext &obj) : file_item((file_item)obj)
{
  memcpy(md5hash, obj.md5hash, 32);
}

file_item_ext& file_item_ext::operator = (const file_item_ext &obj)
{
  /* size = obj.size;
  int path_len = strlen(obj.path);
  if (path != nullptr)
    delete [] path;
  path = new char [path_len + 1];
  if (!path)
  {
    fprintf(stderr, "Error during memory allocation\n");
    exit(1);
  }
  for (int i=0; i < path_len + 1; i++)
    path[i] = obj.path[i];
  */

  this->file_item::operator = ((file_item)obj);
  memcpy(md5hash, obj.md5hash, 32);

  return *this;
}

int file_item_ext::operator == (const file_item_ext &obj) const
{
  if (memcmp(md5hash, obj.md5hash, 32) == 0)
    return true;
  return false;
};

int file_item_ext::operator > (const file_item_ext &obj) const
{
  if (memcmp(md5hash, obj.md5hash, 32) > 0)
    return true;
  return false;
};

int file_item_ext::operator < (const file_item_ext &obj) const
{
  if (memcmp(md5hash, obj.md5hash, 32) < 0)
    return true;
  return false;
};

std::ostream& operator << (std::ostream &os, const file_item_ext &obj)
{
  os << obj.size << ' ' << obj.path << '\n';
  return os;
};
