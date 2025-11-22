#ifndef DATASET_LOADER_H
#define DATASET_LOADER_H

#include "dirent.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char **paths;
    int *labels;
    int count;
} Dataset;

// 读取目录中的所有图片
Dataset load_dataset(const char *cat_dir, const char *dog_dir) {

    Dataset ds;
    ds.paths = malloc(5000 * sizeof(char*));
    ds.labels = malloc(5000 * sizeof(int));
    ds.count = 0;

    struct dirent *p;
    DIR *d;

    // cats = label 0
    d = opendir(cat_dir);
    if (d) {
        while ((p = readdir(d))) {
            if (strstr(p->d_name, ".jpg") || strstr(p->d_name, ".png")) {
                char *buf = malloc(300);
                sprintf(buf, "%s/%s", cat_dir, p->d_name);
                ds.paths[ds.count] = buf;
                ds.labels[ds.count] = 0;
                ds.count++;
            }
        }
        closedir(d);
    } else {
        printf("无法打开目录: %s\n", cat_dir);
    }

    // dogs = label 1
    d = opendir(dog_dir);
    if (d) {
        while ((p = readdir(d))) {
            if (strstr(p->d_name, ".jpg") || strstr(p->d_name, ".png")) {
                char *buf = malloc(300);
                sprintf(buf, "%s/%s", dog_dir, p->d_name);
                ds.paths[ds.count] = buf;
                ds.labels[ds.count] = 1;
                ds.count++;
            }
        }
        closedir(d);
    } else {
        printf("无法打开目录: %s\n", dog_dir);
    }

    printf("数据集加载完成，总图片数: %d\n", ds.count);

    return ds;
}

#endif