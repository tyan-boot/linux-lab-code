#include <dirent.h>
#include <cstdio>
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <array>

using std::vector;
using std::array;

static bool list_all = false;
static bool list_recursive = false;
static bool list_long = false;

void walk_dir(const char *path)
{
    DIR *dir = opendir(path);
    dirent *de;
    struct stat st{};
    vector<array<char, PATH_MAX + 1>> dirs{};

    if (!dir)
    {
        perror("Unknown path");
        exit(1);
    }

    chdir(path);

    char buff[PATH_MAX + 1];
    char timebuff[32];

    while ((de = readdir(dir)) != nullptr)
    {
        if (de->d_name[0] == '.' && !list_all) continue;

        if (de->d_type == DT_DIR && list_recursive)
        {
            realpath(de->d_name, buff);
            array<char, PATH_MAX + 1> tmp{};

            strcpy(tmp.data(), buff);
            dirs.push_back(tmp);

            continue;
        }

        if (!list_long)
        {
            printf("%s\n", de->d_name);
        } else
        {
            realpath(de->d_name, buff);
            lstat(buff, &st);

            auto ptm = localtime(&st.st_mtime);
            strftime(timebuff, 32, "%a %d %H:%M", ptm);

            auto u_pwd = getpwuid(st.st_uid);
            auto g_pwd = getpwuid(st.st_gid);

            printf("%s %s %ld %s %s\n", u_pwd->pw_name, g_pwd->pw_name, st.st_size, timebuff, buff);
        }
    }

    if (list_recursive)
    {
        for (auto dir_to_walk: dirs)
        {
            printf("%s:\n", dir_to_walk.data());
            walk_dir(dir_to_walk.data());
        }
    }
    chdir("..");
}

int main(int argc, char *argv[])
{
    int opt;

    while ((opt = getopt(argc, argv, ":aRl")) != -1)
    {
        switch (opt)
        {
            case 'a':
                list_all = true;
                break;
            case 'R':
                list_recursive = true;
                break;
            case 'l':
                list_long = true;
                break;
            default:
                break;
        }
    }

    if (optind >= argc)
    {
        printf("must provide path\n");
        exit(1);
    }

    walk_dir(argv[optind]);
}
