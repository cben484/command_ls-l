#include <cstdio>
#include <cstring>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#define PATH_LEN 128

// 用于显示文件权限的函数
void print_permissions(mode_t mode) {
  char perms[11];
  perms[0] = (S_ISDIR(mode)) ? 'd' : (S_ISLNK(mode)) ? 'l' : '-'; // 文件类型
  perms[1] = (mode & S_IRUSR) ? 'r' : '-'; // 用户权限
  perms[2] = (mode & S_IWUSR) ? 'w' : '-';
  perms[3] = (mode & S_IXUSR) ? 'x' : '-';
  perms[4] = (mode & S_IRGRP) ? 'r' : '-'; // 群组权限
  perms[5] = (mode & S_IWGRP) ? 'w' : '-';
  perms[6] = (mode & S_IXGRP) ? 'x' : '-';
  perms[7] = (mode & S_IROTH) ? 'r' : '-'; // 其他权限
  perms[8] = (mode & S_IWOTH) ? 'w' : '-';
  perms[9] = (mode & S_IXOTH) ? 'x' : '-';
  perms[10] = '\0'; // 结束符

  printf("%s ", perms);
}

int main(int argc, char *argv[]) {
  char path[PATH_LEN];

  // 如果有传递路径参数，则使用它，否则获取当前程序的路径
  if (argv[1]) {
    strcpy(path, argv[1]);
  } else {
    ssize_t len = readlink("/proc/self/exe", path, sizeof(path) - 1);
    if (len == -1) {
      perror("readlink error");
      return 1;
    }
    // 确保字符串终止
    path[len] = '\0';

    char *last_slash = strrchr(path, '/');
    if (last_slash) {
      *last_slash = '\0'; // 截断路径
    }
  }

  // 打开目录
  DIR *Dirp = opendir(path);
  if (!Dirp) {
    perror("opendir error");
    return 1;
  }

  struct dirent *direntp = NULL;
  struct stat file_stat;

  // 遍历目录中的文件
  while ((direntp = readdir(Dirp)) != NULL) {
    // 跳过 "." 开头的文件
    if (direntp->d_name[0] == '.')
      continue;

    // 构建完整的文件路径
    char full_path[PATH_LEN];
    snprintf(full_path, sizeof(full_path), "%s/%s", path, direntp->d_name);

    // 获取文件的stat信息
    if (lstat(full_path, &file_stat) == -1) {
      perror("lstat error");
      continue;
    }

    // 打印文件权限
    print_permissions(file_stat.st_mode);

    // 打印硬链接数
    printf("%lu ", file_stat.st_nlink);

    // 打印文件所有者和群组
    struct passwd *pw = getpwuid(file_stat.st_uid);
    struct group *gr = getgrgid(file_stat.st_gid);
    printf("%s %s ", pw ? pw->pw_name : "unknown",
           gr ? gr->gr_name : "unknown");

    // 打印文件大小
    printf("%lld ", (long long)file_stat.st_size);

    // 打印修改时间
    char time_buff[128];
    strftime(time_buff, sizeof(time_buff), "%b %d %H:%M",
             localtime(&file_stat.st_mtime));
    printf("%s ", time_buff);

    // 打印文件名
    printf("%s\n", direntp->d_name);
  }

  closedir(Dirp);
  return 0;
}
