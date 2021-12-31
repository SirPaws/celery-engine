#define CELERY_MAIN
#include "celery.h"

void setup() {
    ceSize(960, 540);
}

void draw() {
    const u32 width  = ceWidth();
    const u32 height = ceHeight();

    for (u32 y = 0; y < height; y++) {
        for (u32 x = 0; x < width; x++) {
            cePixel p = {.r= rand()%255,.g= rand()%255,.b= rand() % 255,.a= 255};
            ceDraw(x, y, p);
        }
    }
}


