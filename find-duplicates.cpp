#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

class file_item
{
  int size;
  char md5hash[32];
  char* path;

public:
  file_item(const int p_size, const char* p_md5hash, const char* p_path);
  ~file_item();
};

file_item::file_item(const int p_size, const char* p_md5hash, const char* p_path)
{
  size = p_size;
  memcpy(md5hash, p_md5hash, 32);
  int path_len = strlen(p_path);
  path = (char*)malloc((path_len + 1) * sizeof(char));
  for (int i=0; i < path_len + 1; i++)
    path[i] = p_path[i];
  //strncpy(entry_path, dir_path, sizeof(entry_path));
}

file_item::~file_item()
{
  free (path);
}

void scan_directory(const char* p_dir_path, const int p_fd);

int main(int argcnt, char** argval)
{
  const char* const short_options = "hvc";
  const struct option long_options[] =
  {
    { "help", no_argument, NULL, 'h' },
    { "verbose", no_argument, NULL, 'v' },
    { "compare", no_argument, NULL, 'c' },
    { NULL, 0, NULL, 0 }
  };

  int next_option;
  int verbose = 0;
  int compare = 0;

  do
  {
    next_option = getopt_long(argcnt, argval, short_options, long_options, NULL);
    switch (next_option)
    {
      case 'h': /* -h or --help */
                fprintf(stdout, "Usage: find-duplicates [ options ] /path/to/directory\n"
                                "\t-h\t--help\t\t\t\tWill show help and exit.\n"
                                "\t-v\t--verbose\t\t\tThe program will show extended messages\n"
                                "\t-c\t--compare\t\t\tDuplicate candidates will be compared pairwise.\n"
                       );
                exit(0);
      case 'v': /* -v or --verbose */
                verbose = 1;
                break;
      case 'c': /* -c or --compare */
                compare = 1;
                break;
      case '?': /* Incorrect option. */
                fprintf(stderr, "Incorrect option %c\n", next_option);
                exit(1);
      case -1: /* No options anymore */
               break;
      default: /* Some problem occurs */
               abort();
    }
  } while (next_option != -1);

  // Create log file
  int fd = open("find-duplicates.log", O_WRONLY | O_CREAT | O_APPEND, 0666);

  if (argcnt == optind)
  {
    if (verbose)
      printf("Path № %d: %s\n", 1, ".");
    scan_directory(".", fd);
  }
  else
    for (int i = optind; i < argcnt; i++)
    {
      if (verbose)
        printf("Path № %d: %s\n", i - optind + 1, argval[i]);
      scan_directory(argval[i], fd);
    }

  close(fd);
  return 0;
}

void scan_directory(const char* p_dir_path, const int p_fd)
{
  char v_file[PATH_MAX];
  const char* ptr = p_dir_path;
  int v_len = 0, save_len;
  while (*ptr != '\0' && v_len < PATH_MAX - 1)
    v_file[v_len++] = *ptr++;
  v_file[v_len] = '\0';

  // Add '/' if it absent in directory name
  if (v_file[v_len - 1] != '/' && v_len < PATH_MAX - 2)
  {
    v_file[v_len++] = '/';
    v_file[v_len] = '\0';
  }

  struct dirent* vp_entry;
  DIR* vp_dir = opendir(p_dir_path);
  save_len = v_len;
  struct stat st;

  while ((vp_entry = readdir(vp_dir)) != NULL)
  {
    if (!strcmp(vp_entry->d_name, "..") || !strcmp(vp_entry->d_name, "."))
      continue;

    ptr = vp_entry->d_name;
    while (*ptr != '\0' && v_len < PATH_MAX - 1)
      v_file[v_len++] = *ptr++;
    v_file[v_len] = '\0';

    lstat(v_file, &st);
    if (S_ISREG(st.st_mode)) // regular file
    {
      char buf[PATH_MAX + 256];
      sprintf(buf, "%ld %s\n", st.st_size, v_file);
      write(p_fd, buf, strlen(buf));
    }
    else if (S_ISDIR(st.st_mode)) // directory
      scan_directory(v_file, p_fd);
    ;
    v_file[save_len] = '\0';
    v_len = save_len;
  }

  closedir(vp_dir);
}
