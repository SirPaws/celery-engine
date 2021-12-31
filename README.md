# 🥬 Celery Engine (0.8)
> a celery is a cultivated plant of the parsley family, 
> with closely packed succulent leaf stalks which are used as a salad or cooked vegetable.

But that's not what this is, though they may share a name their differences are vast.
This is Celery a small toolkit written in C99, inspired by the olc::PixelGameEngine[^1]
created by the youtuber javid9x and Processing[^2] first initiated by Ben Fry and Casey Reas.
at this moment it is still in development and has missing features.

[^1]: https://github.com/OneLoneCoder/olcPixelGameEngine
[^2]: https://processing.org

# Usage
As celery is inspired by Processing it has a similar interface to it

```c
#define CELERY_MAIN
#include "celery.h"

void setup(void) {
  ceSize(960, 540);
}

void draw(void) {
  const u32 width  = ceWidth();
  const u32 height = ceHeight();

  for (u32 y = 0; y < height; y++) {
    for (u32 x = 0; x < width; x++) {
      cePixel p = {.r= rand()%255,.g= rand()%255,.b= rand() % 255,.a= 255};
      ceDraw(x, y, p);
    }
  }
}
```  
this example is the minimal example, there are other functions that you can optionally define:
```c
void update(f64);
```
this function is meant for updating variables each frame
```c
void terminate(void);
```
and here's the one for termination of the program.
All of these functions are optional and will only be called if defined


# License (dual license: MIT or UNLICENSE)
this software is licensed under either MIT or UNLICENSE

## MIT License

Copyright (c) 2021 SirPaws

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

## UNLICENSE

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
