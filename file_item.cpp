#include "file_item.h"
#include <cstring>
#include <cstdio>
#include <cstdlib>

file_item::file_item(const int p_size, const char* p_path)
{
  size = p_size;
  int path_len = strlen(p_path);
  path = new char [path_len + 1];
  if (!path)
  {
      fprintf(stderr, "Error during memory allocation\n");
      exit(1);
  }

  for (int i=0; i < path_len + 1; i++)
    path[i] = p_path[i];
  //strncpy(entry_path, dir_path, sizeof(entry_path));
}

file_item::file_item(const file_item &obj)
{
  size = obj.size;
  int path_len = strlen(obj.path);
  path = new char [path_len + 1];
  if (!path)
  {
      fprintf(stderr, "Error during memory allocation\n");
      exit(1);
  }
  for (int i=0; i < path_len + 1; i++)
    path[i] = obj.path[i];
}

file_item::~file_item()
{
  delete [] path;
}

file_item &file_item::operator=(const file_item &obj)
{
  size = obj.size;
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

  return *this;
}
