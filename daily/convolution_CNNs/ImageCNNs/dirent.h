#ifndef DIRENT_H
#define DIRENT_H

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct DIR {
    HANDLE hFind;
    WIN32_FIND_DATAA data;
    char pattern[MAX_PATH];
    int first_read;
} DIR;

struct dirent {
    char d_name[MAX_PATH];
};

DIR* opendir(const char* name) {
    DIR* dir = (DIR*)malloc(sizeof(DIR));
    if (!dir) return NULL;

    snprintf(dir->pattern, MAX_PATH, "%s\\*.*", name);

    dir->hFind = FindFirstFileA(dir->pattern, &dir->data);

    if (dir->hFind == INVALID_HANDLE_VALUE) {
        free(dir);
        return NULL;
    }

    dir->first_read = 1;
    return dir;
}

struct dirent* readdir(DIR* dir) {
    static struct dirent entry;

    if (dir->first_read) {
        dir->first_read = 0;
    } else {
        if (!FindNextFileA(dir->hFind, &dir->data))
            return NULL;
    }

    strcpy(entry.d_name, dir->data.cFileName);
    return &entry;
}

int closedir(DIR* dir) {
    if (!dir) return -1;
    FindClose(dir->hFind);
    free(dir);
    return 0;
}

#endif
