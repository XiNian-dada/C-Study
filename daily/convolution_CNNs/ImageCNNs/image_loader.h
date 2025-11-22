#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include "stb_image.h"
#include <stdlib.h>
#include <stdio.h>

#define INPUT_H 64
#define INPUT_W 64

// 双线性插值缩放
float **resize_gray(float **src, int src_h, int src_w, int dst_h, int dst_w) {
    float **dst = (float**)malloc(dst_h * sizeof(float*));
    for (int i = 0; i < dst_h; i++)
        dst[i] = (float*)malloc(dst_w * sizeof(float));

    for (int dy = 0; dy < dst_h; dy++) {
        for (int dx = 0; dx < dst_w; dx++) {

            float gx = (dx / (float)dst_w) * src_w;
            float gy = (dy / (float)dst_h) * src_h;

            int gxi = (int)gx;
            int gyi = (int)gy;

            float c00 = src[gyi][gxi];
            float c10 = src[gyi][gxi+1 < src_w ? gxi+1 : gxi];
            float c01 = src[gyi+1 < src_h ? gyi+1 : gyi][gxi];
            float c11 = src[gyi+1 < src_h ? gyi+1 : gyi][gxi+1 < src_w ? gxi+1 : gxi];

            float tx = gx - gxi;
            float ty = gy - gyi;

            float c0 = c00*(1-tx) + c10*tx;
            float c1 = c01*(1-tx) + c11*tx;

            dst[dy][dx] = (c0*(1-ty) + c1*ty);
        }
    }
    return dst;
}

// 读取图片 → 输出 64×64 单通道
float **load_image_64(const char *filename) {

    int w, h, c;
    unsigned char *img = stbi_load(filename, &w, &h, &c, 3);
    if (!img) {
        printf("无法读取图片: %s\n", filename);
        return NULL;
    }

    float **gray = (float**)malloc(h * sizeof(float*));
    for (int i = 0; i < h; i++)
        gray[i] = (float*)malloc(w * sizeof(float));

    // RGB → 灰度
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int idx = (y*w + x)*3;
            float r = img[idx] / 255.0f;
            float g = img[idx+1] / 255.0f;
            float b = img[idx+2] / 255.0f;

            gray[y][x] = 0.299*r + 0.587*g + 0.114*b;
        }
    }

    stbi_image_free(img);

    float **res = resize_gray(gray, h, w, INPUT_H, INPUT_W);

    for (int i = 0; i < h; i++) free(gray[i]);
    free(gray);

    return res;
}

#endif
