/*
   celery.h

   |~~~~~~~~~~~~~~~~~~~~~~|
   |CELERY ENGINE (v: 0.8)|
   |~~~~~~~~~~~~~~~~~~~~~~|

   What is this?
   ~~~~~~~~~~~~~
    Celery is a cultivated plant of the parsley family, 
    with closely packed succulent leaf stalks which are used as a salad or cooked vegetable.
    But that's not what this is, though they may share a name their differences are vast.
    This is Celery a small toolkit written in C99, inspired by the olc::PixelGameEngine*
    created by the youtuber javid9x and Processing** first initiated by Ben Fry and Casey Reas.
    at this moment it is still in development and has missing features.

    *  https://github.com/OneLoneCoder/olcPixelGameEngine
    ** https://processing.org
   License 
   ~~~~~~~
    this software is licensed under either MIT or UNLICENSE
    -----------------------------------------------------------------------------
    MIT License
    
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
    -----------------------------------------------------------------------------
    UNLICENSE
    
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

   Roadmap 
   ~~~~~~~
    [] Image loading and saving
    [] Audio support through miniaudio
    [] support for linux and mac

   Interface 
   ~~~~~~~~~
    when you use celery it checks whether 4 functions are defined
    - void setup(void)
    - void update(f64)
    - void draw(void)
    - void terminate(void)

*/
/*
// A simple 'hello world' example
#define CELERY_MAIN
#include "release/celery.h"

void setup() {
    ceSize(960, 540);   // sets up the window
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
*/
#ifndef CELERY_HEADER
#define CELERY_HEADER
#if defined(CELERY_ALL)
#define CELERY_STB_IMAGE
#define CELERY_QOI
#define CELERY_GIF
#endif

#if !defined(CELERY_INCLUDE_PSTD)
#if defined(__EMSCRIPTEN__)
#   define PSTD_WASM
#elif defined(_WIN32) || defined(_WIN64)
#    define PSTD_WINDOWS
#elif defined(__linux__) || defined(__unix__)
#    define PSTD_LINUX
#elif defined(__APPLE__)
#    define PSTD_MACOS
#else
#   error platform not supported
#endif

#if _WIN32 || _WIN64
    #if _WIN64
        #define PSTD_64
    #else
        #define PSTD_32
    #endif
#elif __GNUC__
    #if __x86_64__ || __ppc64__
        #define PSTD_64
    #else
        #define PSTD_32
    #endif
#elif UINTPTR_MAX > UINT_MAX
    #define PSTD_64
#else
    #define PSTD_32
#endif

#if !(defined(_MSC_FULL_VER) && !defined(__clang__)) // not an msvc compiler
#   define PSTD_GNU_COMPATIBLE 1
#else
#   define PSTD_MSVC 1
#endif
#if defined(__cplusplus) && !defined(PSTD_I_KNOW_WHAT_IM_DOING)
#   if defined(PSTD_MSVC)
#       pragma message pstd was written with c in mind so c++ might not work as intended. Please run your compiler in c mode
#   else
#       warning pstd was written with c in mind so c++ might not work as intended. Please run your compiler in c mode
#   endif
#endif

#if defined(__STDC_VERSION__)
#   if __STDC_VERSION__ == 199901
#      define PSTD_C99 1
#      define PSTD_C89 1
#   elif __STDC_VERSION__ == 201112
#      define PSTD_C11 1
#      define PSTD_C99 1
#      define PSTD_C89 1
#   elif __STDC_VERSION__ == 201710
#      define PSTD_C18 1
#      define PSTD_C17 1
#      define PSTD_C11 1
#      define PSTD_C99 1
#      define PSTD_C89 1
#   endif
#elif defined(__STDC__)
#       define PSTD_C89 1
#endif

#if defined(__STDC_NO_VLA__)
#   define PSTD_HAS_VLA 0
#elif defined(PSTD_C11) && !defined(PSTD_MSVC)
#   define PSTD_HAS_VLA 1
#else
#   define PSTD_HAS_VLA 0
#endif

#if defined(__has_c_attribute)
#   define PSTD_HAS_ATTRIBUTE __has_c_attribute
#   if __STDC_VERSION__ >= 201710 
#       define PSTD_C23 1
#   endif 
#else
#   define PSTD_HAS_ATTRIBUTE(x) 0
#endif


#if PSTD_HAS_ATTRIBUTE(maybe_unused)
#define PSTD_UNUSED [[maybe_unused]]
#elif defined(PSTD_GNU_COMPATIBLE)
#define PSTD_UNUSED __attribute__((unused))
#else
#define PSTD_UNUSED
#endif

#if defined(PSTD_MSVC) && (defined(_MSVC_TRADITIONAL) && _MSVC_TRADITIONAL)
#pragma message("Warning: the traditional msvc preprocessor does not support 'complicated' macros use /Zc:preprocessor") 
#define PSTD_HAS_SECOND(...) 0
#else
#define PSTD_HAS_SECOND_TEST__(_0, _1, _2, ...) _2
#define PSTD_HAS_SECOND_TRIGGER(...) ,
#define PSTD_HAS_SECOND_TEST_(...) PSTD_HAS_SECOND_TEST__(__VA_ARGS__)
#define PSTD_HAS_SECOND_TEST(...)  PSTD_HAS_SECOND_TEST_(PSTD_HAS_SECOND_TRIGGER __VA_ARGS__ (), 0, 1, 0) 
#define PSTD_HAS_SECOND(a, ...)    PSTD_HAS_SECOND_TEST(__VA_ARGS__)
#endif

#define PSTD_CONCAT_( a, b ) a##b
#define PSTD_CONCAT( a, b ) PSTD_CONCAT_( a, b )

#define PSTD_STRINGIFY_(x) #x
#define PSTD_STRINGIFY(x) PSTD_STRINGIFY_(x)

#ifndef countof
#define countof(x) (sizeof((x))/sizeof((x)[0]))
#endif

#if defined(PSTD_GNU_COMPATIBLE)
#define PSTD_ASSUME(x) __builtin_assume((x))
#define PSTD_EXPECT(cond, expected_result) __builtin_expect((cond), (expected_result))
#else
#define PSTD_ASSUME(x) __assume((x))
#define PSTD_EXPECT(cond, expected_result) (cond)
#define register __register
#endif

#if defined(PSTD_GNU_COMPATIBLE)
#   ifndef pallocate
#      define pallocate(size) malloc(size)
#   endif // pAllocate
#   ifndef pzero_allocate
#      define pzero_allocate(size) ({ void *_tmp_ = malloc(size); memset(_tmp_, 0, (size));})
#   endif // pzeroallocate
#   ifndef preallocate
#      define preallocate(size, buffer) realloc(buffer, size)
#   endif // pReallocate
#   ifndef pfree
#      define pfree(buffer) free(buffer)
#   endif // pfree
#   ifndef psized_free
#      define psized_free(size, buffer) free(buffer)
#   endif // psizedfree
#else
#   ifndef pallocate
#      define pallocate(size) malloc(size)
#   endif // pAllocate
#   ifndef pzero_allocate
#      define pzero_allocate(size) pzero_allocate_implementation(size)
#   endif // pZeroAllocate
#   ifndef pReallocate
#      define preallocate(size, buffer) realloc(buffer, size)
#   endif // pReallocate
#   ifndef pFree
#      define pfree(buffer) free(buffer)
#   endif // pFree
#   ifndef pSized_Free
#      define psized_free(size, buffer) free(buffer)
#   endif // pFree
#endif

#define PSTD_TIME_MILI    1000000
#define PSTD_TIME_SECONDS 1000000000
#define pprintf printf
#endif

#define CE_PI (3.141592653589793)

// includes ---------------------------------------------------------------------------------------

#if defined(CELERY_INCLUDE_PSTD)
#include <general.h>
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#endif

#if defined(CELERY_STB_IMAGE)
#include "stb_image.h"
#endif
#if defined(CELERY_QOI)
#include "qoi.h"
#endif
#if defined(CELERY_GIF)
#include "msf_gif.h"
#endif

#if defined(PSTD_WINDOWS)
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Gdi32.lib")
#pragma comment(lib, "Opengl32.lib")
#endif


// enums ------------------------------------------------------------------------------------------
enum ceMode {
    CE_BACKGROUND =  0,
    CE_FOREGROUND =  1,
    CE_ENTITY_0   =  2,
    CE_ENTITY_1   =  3,
    CE_ENTITY_2   =  4,
    CE_ENTITY_3   =  5,
    CE_ENTITY_4   =  6,
    CE_ENTITY_5   =  7,
    CE_ENTITY_6   =  8,
    CE_ENTITY_7   =  9,
    CE_ENTITY_8   = 10,
    CE_ENTITY_9   = 11,
    CE_ENTITY_10  = 12,
    CE_ENTITY_11  = 13,
    CE_ENTITY_12  = 14,
    CE_ENTITY_13  = 15,
    CE_ENTITY_14  = 16,
    CE_ENTITY_15  = 17,
    CE_ENTITY_16  = 18,
    CE_ENTITY_17  = 19,
    CE_ENTITY_18  = 20,
    CE_ENTITY_19  = 21,
    CE_ENTITY_20  = 22,
    CE_ENTITY_21  = 23,
    CE_ENTITY_22  = 24,
    CE_ENTITY_23  = 25,
    CE_ENTITY_24  = 26,
    CE_ENTITY_25  = 27,
    CE_ENTITY_26  = 28,
    CE_ENTITY_27  = 29,
    CE_ENTITY_28  = 30,
    CE_ENTITY_29  = 31,
    CE_ENTITY_30  = 32,
    CE_ENTITY_31  = 33,
    CE_ENTITY_32  = 34,
    // the maximum value for entities is 255, please note this is experimental and might be removed 
    // in future releases
};
typedef enum ceMode ceMode;


enum ceKeyCode {
    CE_KEY_UNKNOWN      = -1,

    CE_KEY_SPACE         = ' ',
    CE_KEY_APOSTROPHE    = '\'',
    CE_KEY_COMMA         = ',',
    CE_KEY_MINUS         = '-',
    CE_KEY_PERIOD        = '.',
    CE_KEY_SLASH         = '/',
    CE_KEY_0             = '0',
    CE_KEY_1             = '1',
    CE_KEY_2             = '2',
    CE_KEY_3             = '3',
    CE_KEY_4             = '4',
    CE_KEY_5             = '5',
    CE_KEY_6             = '6',
    CE_KEY_7             = '7',
    CE_KEY_8             = '8',
    CE_KEY_9             = '9',
    CE_KEY_SEMICOLON     = ';',
    CE_KEY_EQUAL         = '=',
    CE_KEY_A             = 'A', /* note: 'a' also works */
    CE_KEY_B             = 'B', /* note: 'b' also works */
    CE_KEY_C             = 'C', /* note: 'c' also works */
    CE_KEY_D             = 'D', /* note: 'd' also works */
    CE_KEY_E             = 'E', /* note: 'e' also works */
    CE_KEY_F             = 'F', /* note: 'f' also works */
    CE_KEY_G             = 'G', /* note: 'g' also works */
    CE_KEY_H             = 'H', /* note: 'h' also works */
    CE_KEY_I             = 'I', /* note: 'i' also works */
    CE_KEY_J             = 'J', /* note: 'j' also works */
    CE_KEY_K             = 'K', /* note: 'k' also works */
    CE_KEY_L             = 'L', /* note: 'l' also works */
    CE_KEY_M             = 'M', /* note: 'm' also works */
    CE_KEY_N             = 'N', /* note: 'n' also works */
    CE_KEY_O             = 'O', /* note: 'o' also works */
    CE_KEY_P             = 'P', /* note: 'p' also works */
    CE_KEY_Q             = 'Q', /* note: 'q' also works */
    CE_KEY_R             = 'R', /* note: 'r' also works */
    CE_KEY_S             = 'S', /* note: 's' also works */
    CE_KEY_T             = 'T', /* note: 't' also works */
    CE_KEY_U             = 'U', /* note: 'u' also works */
    CE_KEY_V             = 'V', /* note: 'v' also works */
    CE_KEY_W             = 'W', /* note: 'w' also works */
    CE_KEY_X             = 'X', /* note: 'x' also works */
    CE_KEY_Y             = 'Y', /* note: 'y' also works */
    CE_KEY_Z             = 'Z', /* note: 'z' also works */
    CE_KEY_LEFT_BRACKET  = '[',
    CE_KEY_BACKSLASH     = '\\',
    CE_KEY_RIGHT_BRACKET = ']',
    CE_KEY_GRAVE_ACCENT  = '`',
    CE_KEY_WORLD_1       = 161, /* non-US #1 */
    CE_KEY_WORLD_2       = 162, /* non-US #2 */
    
    CE_KEY_ESCAPE        = 256,
    CE_KEY_ENTER         = 257,
    CE_KEY_TAB           = 258,
    CE_KEY_BACKSPACE     = 259,
    CE_KEY_INSERT        = 260,
    CE_KEY_DELETE        = 261,
    CE_KEY_RIGHT         = 262,
    CE_KEY_LEFT          = 263,
    CE_KEY_DOWN          = 264,
    CE_KEY_UP            = 265,
    CE_KEY_PAGE_UP       = 266,
    CE_KEY_PAGE_DOWN     = 267,
    CE_KEY_HOME          = 268,
    CE_KEY_END           = 269,
    CE_KEY_CAPS_LOCK     = 280,
    CE_KEY_SCROLL_LOCK   = 281,
    CE_KEY_NUM_LOCK      = 282,
    CE_KEY_PRINT_SCREEN  = 283,
    CE_KEY_PAUSE         = 284,
    CE_KEY_F1            = 290,
    CE_KEY_F2            = 291,
    CE_KEY_F3            = 292,
    CE_KEY_F4            = 293,
    CE_KEY_F5            = 294,
    CE_KEY_F6            = 295,
    CE_KEY_F7            = 296,
    CE_KEY_F8            = 297,
    CE_KEY_F9            = 298,
    CE_KEY_F10           = 299,
    CE_KEY_F11           = 300,
    CE_KEY_F12           = 301,
    CE_KEY_F13           = 302,
    CE_KEY_F14           = 303,
    CE_KEY_F15           = 304,
    CE_KEY_F16           = 305,
    CE_KEY_F17           = 306,
    CE_KEY_F18           = 307,
    CE_KEY_F19           = 308,
    CE_KEY_F20           = 309,
    CE_KEY_F21           = 310,
    CE_KEY_F22           = 311,
    CE_KEY_F23           = 312,
    CE_KEY_F24           = 313,
    CE_KEY_F25           = 314,
    CE_KEY_KP_0          = 320,
    CE_KEY_KP_1          = 321,
    CE_KEY_KP_2          = 322,
    CE_KEY_KP_3          = 323,
    CE_KEY_KP_4          = 324,
    CE_KEY_KP_5          = 325,
    CE_KEY_KP_6          = 326,
    CE_KEY_KP_7          = 327,
    CE_KEY_KP_8          = 328,
    CE_KEY_KP_9          = 329,
    CE_KEY_KP_DECIMAL    = 330,
    CE_KEY_KP_DIVIDE     = 331,
    CE_KEY_KP_MULTIPLY   = 332,
    CE_KEY_KP_SUBTRACT   = 333,
    CE_KEY_KP_ADD        = 334,
    CE_KEY_KP_ENTER      = 335,
    CE_KEY_KP_EQUAL      = 336,
    CE_KEY_LEFT_SHIFT    = 340,
    CE_KEY_LEFT_CONTROL  = 341,
    CE_KEY_LEFT_ALT      = 342,
    CE_KEY_LEFT_SUPER    = 343,
    CE_KEY_RIGHT_SHIFT   = 344,
    CE_KEY_RIGHT_CONTROL = 345,
    CE_KEY_RIGHT_ALT     = 346,
    CE_KEY_RIGHT_SUPER   = 347,
    CE_KEY_MENU          = 348,
};
typedef enum ceKeyCode ceKeyCode;

enum ceMouseButton {
    CE_MOUSE_1, CE_MOUSE_2, CE_MOUSE_3, CE_MOUSE_4, CE_MOUSE_5,

    CE_MOUSE_BUTTON_COUNT,
    CE_MOUSE_LEFT   = CE_MOUSE_1,
    CE_MOUSE_RIGHT  = CE_MOUSE_2,
    CE_MOUSE_MIDDLE = CE_MOUSE_3,
};
typedef enum ceMouseButton ceMouseButton;

enum ceModifier {
    CE_MOD_SHIFT     = 0b000001,
    CE_MOD_CONTROL   = 0b000010,
    CE_MOD_ALT       = 0b000100,
    CE_MOD_SUPER     = 0b001000,
    CE_MOD_CAPS_LOCK = 0b010000,
    CE_MOD_NUM_LOCK  = 0b100000,
};
typedef enum ceModifier ceModifier;

// typedefs ---------------------------------------------------------------------------------------
#if !defined(CELERY_INCLUDE_PSTD)
typedef int8_t    i8;
typedef int16_t   i16;
typedef int32_t   i32;
typedef int64_t   i64;

typedef int8_t    s8;
typedef int16_t   s16;
typedef int32_t   s32;
typedef int64_t   s64;

typedef uint8_t   u8;
typedef uint16_t  u16;
typedef uint32_t  u32;
typedef uint64_t  u64;

typedef ptrdiff_t isize;
typedef ptrdiff_t ssize;

typedef size_t    usize;

typedef float     f32;
typedef double    f64;

#if !defined(__cplusplus)
#   if defined(PSTD_C99)
        enum { false, true };
        typedef _Bool pbool_t;
#   else
        enum pbool_t { false, true };
        typedef enum pbool_t pbool_t;
#   endif
#else
    using p_bool = pbool_t;
#endif

typedef s64 ptimepoint_t;

enum pclocktype_t {
    PSTD_STEADY_CLOCK,
    PSTD_HIGH_RESOLUTION_CLOCK,
    PSTD_SYSTEM_CLOCK
};

ptimepoint_t pget_tick(enum pclocktype_t);
#endif
// structs ----------------------------------------------------------------------------------------
typedef struct cePixel cePixel;
struct cePixel {
    union { 
        struct { u8 r, g, b, a; };
        struct { u8 red, green, blue, alpha; };
        struct { u8 R, G, B, A; };
        struct { u8 RED, GREEN, BLUE, ALPHA; };
        u32 hex;
    };
};

typedef struct ceVec2f ceVec2f;
struct ceVec2f {
    union { 
        struct { f32 x, y; };
        struct { f32 X, Y; };
        struct { f32 width, height; };
        struct { f32 WIDTH, HEIGHT; };
        f32 data[2];
    };
};

typedef struct ceVec2d ceVec2d;
struct ceVec2d {
    union { 
        struct { f64 x, y; };
        struct { f64 X, Y; };
        struct { f64 width, height; };
        struct { f64 WIDTH, HEIGHT; };
        f64 data[2];
    };
};

#if defined(CE_VEC2_DEFAULT_DOUBLE)
typedef ceVec2d ceVec2;
#else
typedef ceVec2f ceVec2;
#endif

typedef struct ceSprite ceSprite;
struct ceSprite {
    pbool_t is_valid;
    u32 width, height;
    cePixel *data;
};

typedef struct ceShadedArea ceShadedArea;
struct ceShadedArea {
    ceVec2  p0, p1, p2;
    cePixel c0, c1, c2;
};

#if defined(CELERY_GIF)
typedef struct ceGifState ceGifState;
struct ceGifState {
    pbool_t is_valid;
    MsfGifState state;
};
#endif

typedef struct ceInputState ceInputState; 
struct ceInputState { 
    pbool_t held, pressed, released;
};

typedef struct ceMouse ceMouse;
struct ceMouse {
    ceInputState buttons[5];
    ceVec2d      pos;
    ceVec2d      wheel;
};


// functions --------------------------------------------------------------------------------------
#if defined(CELERY_STB_IMAGE)
// this function loads an image and creates a sprite through stb_image
// please note that it is only defined if stb_image is available
ceSprite ceLoadImageSTB(const char *filepath);
#endif
#if defined(CELERY_QOI)
// this function loads an image in the qoi format and creates a sprite
ceSprite ceLoadImageQOI(const char *filepath);

// this function saves a sprite as a qoi image
void ceSaveSpriteQOI(ceSprite *spr, const char *filepath);
#endif

#if defined(CELERY_GIF)
// initialises the gif 'renderer', this should be done in the 'setup' function
ceGifState ceBeginGIF(void);

// cleans up the ceGifState should be perfomed when the gif 'renderer' is no longer needed
void ceEndGif(ceGifState *s);

// saves the current window frame in the gif, equivalent to ceRecordFrameAdv(&state, 5, 16)
void ceRecordFrame(ceGifState *);

// saves the current window frame in the gif, 
// i have no idea what centi_seconds_per_frame or bit_depth is about, ask notnull.
void ceRecordFrameAdv(ceGifState *, u32 centi_seconds_per_frame, u32 bit_depth);

// saves the gif to a file, this should always be done before calling 'ceEndGif'
void ceSaveGif(ceGifState *s, const char *filepath);
#endif

#if !defined(CELERY_INCLUDE_PSTD)
PSTD_UNUSED
static inline f64 pget_time_seconds_d(ptimepoint_t timepoint) { 
    return (f64)timepoint  / (f64) PSTD_TIME_SECONDS; 
}

PSTD_UNUSED
static inline void *pzero_allocate_implementation(usize size) {
    void *tmp = malloc(size);
    memset(tmp, 0, size);
    return tmp;
}
#endif

// i can't be bothered to explain this properly. we use alpha as a collision mask
void ceSetMode(ceMode);
pbool_t ceHasCollided(void);

// gets the current state of a key
ceInputState ceGetKey(ceKeyCode code);
// gets the current state of a mouse button
ceInputState ceGetMouseButton(ceMouseButton button);
// gets the current state of a mouse
ceMouse      ceGetMouse(void);
// gets the position of the mouse
ceVec2d      ceGetMousePos(void);
// gets the state of the mouse wheel
ceVec2d      ceGetMouseWheel(void);
// gets current modifier keys held at the moment
ceModifier   ceGetModifiers(void);


// (WIP) this function does not work it is a stub
ceSprite ceLoadImage(const char *filepath);
// (WIP) this function does not work it is a stub
void ceSaveSprite(ceSprite *spr, const char *filepath);

// gets the current window frame as a sprite
ceSprite ceGetFrameAsSprite(void);

// frees the current sprite
void ceFreeSprite(ceSprite *spr);

// pixel scale would mean the screen space would be width/scale, height/scale
void ceScale(u32 scale);
// first time this function is called, it will create a window.
// successive calls will resize the window
void ceSize(u32 width, u32 height);

// gets the window width in pixels
u32 ceWidth(void);
// gets the window height in pixels
u32 ceHeight(void);
// gets the window width and height in pixels
ceVec2 ceBounds(void);

// sets the window title
void ceSetTitle(const char *title);

// draws a sprite at x, y
void ceDrawSprite(ceSprite *spr, u32 x, u32 y);

// draws part of a sprite at x, y. this is useful for spritesheets
void ceDrawPartialSprite(ceSprite *spr, u32 _xoff, u32 _yoff, u32 width, u32 height, u32 x, u32 y);

// draws a single pixel
void ceDraw(u32 x, u32 y, cePixel color);

// draws a filled in rectangle
void ceRectangle(u32 x, u32 y, u32 width, u32 height, cePixel color);

// draws a filled in triangle
void ceTriangle(u32 x0, u32 y0, u32 x1, u32 y1, u32 x2, u32 y2, cePixel color);

// draws a filled in ellipse
void ceEllipse(u32 x, u32 y, f64 x_radius, f64 y_radius, cePixel color);

// draws a filled in circle
void ceCircle(u32 x, u32 y, f64 radius, cePixel color);

// draws a line
void ceLine(u32 x, u32 y, u32 x1, u32 y1, cePixel color);

// draws a shaded ellipse that will have one colour at the center and 
// will interpolate towards the edge color 
void ceEllipseShaded(u32 x, u32 y, f64 x_radius, f64 y_radius, cePixel center, cePixel edge);
// draws a shaded circle that will have one colour at the center and 
// will interpolate towards the edge color 
void ceCircleShaded(u32 x, u32 y, f64 radius, cePixel center, cePixel edge);

// draws a shaded line that starts with the color c0 and interpolates towards c1 
void ceLineShaded(u32 x0, u32 y0, u32 x1, u32 y1, cePixel c0, cePixel c1);

// draws a shaded triangle 
void ceTriangleShaded(ceShadedArea);
#endif // CELERY_HEADER
#if defined(CELERY_MAIN)
#if defined(PSTD_WINDOWS)
// defines ----------------------------------------------------------------------------------------
#define CEPRIVATE_INIT_PLATFORM              ceprivate_win32_init
#define CEPRIVATE_PLATFORM_GET_PROC_ADDRESS  ceprivate_win32_get_proc_address
#define CEPRIVATE_SHUTDOWN_PLATFORM          ceprivate_win32_shutdown

#define CEPRIVATE_CREATE_WINDOW ceprivate_win32_create_window
#define CEPRIVATE_RESIZE_WINDOW ceprivate_win32_resize_window
        
#define CEPRIVATE_PLATFORM_POLL_EVENTS  ceprivate_win32_poll_events
#define CEPRIVATE_PLATFORM_SWAP_BUFFERS ceprivate_win32_swap_buffers

#define CEPRIVATE_PLATFORM_CLEAR ceprivate_win32_clear

#define CEPRIVATE_PLATFORM_DRAW ceprivate_win32_update_surface

#define CEPRIVATE_PLATFORM_TITLE ceprivate_win32_title

#define CEPRIVATE_PLATFORM_GLOBALS ceWin32 win32
#define CEPRIVATE_PLATFORM_INIT_KEYS ceprivate_win32_init_keys

#if defined(PSTD_MSVC)
#pragma warning(push)
#pragma warning(disable : 4113 4244 4098)
#endif

// includes ---------------------------------------------------------------------------------------
#include <windows.h>
#include <gl/GL.h>
// enums ----------------------------------------------------------------------------------------
// typedefs ----------------------------------------------------------------------------------------
typedef void ceProcFunc();
// structs ----------------------------------------------------------------------------------------
typedef struct ceWin32 ceWin32;
struct ceWin32 {
    HMODULE  module;
    HWND     handle;
    HDC      dc;
    HGLRC    gl;
    u32      id;
};
// functions --------------------------------------------------------------------------------------
LRESULT CALLBACK ceprivate_win32_winproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

void ceprivate_win32_title(const char *);
void ceprivate_win32_scale(u32 s);

void ceprivate_win32_init(void);
void ceprivate_win32_init_keys(void);
void ceprivate_win32_shutdown(void);

s32 ceprivate_win32_create_surface(u32 width, u32 height, void *buf);

void ceprivate_win32_create_window(u32 width, u32 height);
void ceprivate_win32_resize_window(u32 width, u32 height);

void ceprivate_win32_poll_events(void);
void ceprivate_win32_swap_buffers(void);

void ceprivate_win32_clear(void);

void ceprivate_win32_update_surface(u32 x, u32 y, cePixel p);

void (*ceprivate_win32_get_proc_address(const char *))();
#else
#error platform not supported yet!
#endif
// enums ----------------------------------------------------------------------------------------
// typedefs ----------------------------------------------------------------------------------------
// structs ----------------------------------------------------------------------------------------
typedef struct ceEnvironment ceEnvironment;
struct ceEnvironment {
    int count;
    const char **arguments;
    const char **environment;
};

typedef struct ceApp ceApp;
struct ceApp {
    ceEnvironment env;
    volatile pbool_t is_running;
    pbool_t has_app;
    u32 width, height;
    const char *title;

    ceKeyCode    keycodes[512];
    ceKeyCode    scancodes[512];
    ceInputState keys[512];
    ceMouse      mouse;
    ceModifier   mods;

    pbool_t collision_flag;
    ceMode mode;

    u32 scale;
    u32 image_width, image_height;
    struct cePixel *image_buffer;

    CEPRIVATE_PLATFORM_GLOBALS;
};
// functions --------------------------------------------------------------------------------------
void ceInit(void);
void ceShutdown(void);
//-------------------------------------------------------------------------------------------------
// implementation ---------------------------------------------------------------------------------
// main -------------------------------------------------------------------------------------------
#if !defined(CELERY_INCLUDE_PSTD)
// ported from _Xtime_get_ticks: https://github.com/microsoft/STL/blob/master/stl/src/xtime.cpp
ptimepoint_t psystem_time(void) {
#if defined(PSTD_WINDOWS)
#define COMBINE(high, low) (((s64)(high) << 32) | (s64)(low))
    static const long long PSTD_EPOCH = 0x19DB1DED53E8000LL; 
    FILETIME ft;
    GetSystemTimePreciseAsFileTime(&ft);
    return COMBINE(ft.dwHighDateTime,ft.dwLowDateTime) - PSTD_EPOCH;
#undef COMBINE
#else
    struct timespec tp;
    clock_gettime(CLOCK_REALTIME, &tp);
    return tp.tv_sec * PSTD_TIME_SECONDS + tp.tv_nsec;
#endif
}

// these clocks are taken from MSVC-STL
// the only edit is the names of the variables have been changed to all lowercase
// because the _Ugly syntax is reserved.
// Can be found here https://github.com/microsoft/STL  (2021)
ptimepoint_t pget_tick(enum pclocktype_t type) {
#if defined(PSTD_WINDOWS)
    if (PSTD_EXPECT(type != PSTD_SYSTEM_CLOCK, 1)) {
        const s64 _freq; QueryPerformanceFrequency((void *)&_freq); // doesn't change after system boot
        const s64 _ctr;  QueryPerformanceCounter((void*)&_ctr);
        // Instead of just having "(_Ctr * period::den) / _Freq",
        // the algorithm below prevents overflow when _Ctr is sufficiently large.
        // It assumes that _Freq * period::den does not overflow, which is currently true for nano period.
        // It is not realistic for _Ctr to accumulate to large values from zero with this assumption,
        // but the initial value of _Ctr could be large.
        const s64 _whole = (_ctr / _freq) * 1000000000;
        const s64 _part = (_ctr % _freq) * 1000000000 / _freq;
        return _whole + _part;
    } else {
        return psystem_time();
    }
#elif defined(PSTD_LINUX) || defined(PSTD_WASM)
    struct timespec tp; 
    switch (type) {
    case PSTD_STEADY_CLOCK: {
            clock_gettime(CLOCK_MONOTONIC, &tp);
            return tp.tv_sec * PSTD_TIME_SECONDS + tp.tv_nsec;
        }
    case PSTD_SYSTEM_CLOCK:
    case PSTD_HIGH_RESOLUTION_CLOCK: return psystem_time();
    }
#else
    return 0;
#endif
}

void *pmemexpand(void *dst, const void *src, usize dstsize, usize srcsize) {
    if (!dst || !src || !dstsize) return NULL;

    if (dstsize < srcsize)
        return memcpy(dst, src, dstsize);
    
    if (PSTD_EXPECT(srcsize % sizeof(usize) == 0, 1)) { 
        u8 *dstptr = dst;
        const usize *srcptr = src;
        usize offset = 0;
        while (dstsize) {
            if (dstsize < sizeof(usize)) break;
            srcptr = src;
            for (usize i = 0; i < srcsize; i += sizeof(usize)) {
                if (dstsize < sizeof(usize)) break;
                *((usize *)(dstptr + offset)) = *srcptr++;
                dstsize -= sizeof(usize); offset += sizeof(usize);
            }
        }
        if (dstsize != 0) memcpy(dstptr + offset, srcptr, dstsize);
    }
    else if (PSTD_EXPECT(srcsize % sizeof(u32) == 0, 1)) { 
        u8 *dstptr = dst;
        const u32 *srcptr = src;
        usize offset = 0;
        while (dstsize) {
            if (dstsize < sizeof(u32)) break;
            srcptr = src;
            for (usize i = 0; i < srcsize; i += sizeof(u32)) {
                if (dstsize < sizeof(u32)) break;
                *((u32 *)(dstptr + offset)) = *srcptr++;
                dstsize -= sizeof(u32); offset += sizeof(u32);
            }
        }
        if (dstsize != 0) memcpy(dstptr + offset, srcptr, dstsize);
    }
    else {
        u8 *dstptr = dst;
        const u8 *srcptr = src;
        usize offset = 0;
        while (dstsize) {
            if (dstsize < srcsize) break;
            srcptr = src;
            for (usize i = 0; i < srcsize; i++) {
                if (dstsize < srcsize) break;
                dstptr[offset++] = *srcptr++;
                dstsize--;
            }
        }
        if (srcptr + dstsize > (u8 *)src + srcsize) {
            const u8 *begin = srcptr; 
            const u8 *end = ((const u8*)src) + srcsize;  
            memcpy(dstptr + offset, srcptr, end - begin);
            srcptr = src; dstsize -= end - begin;
            offset += end - begin;
        }
        memcpy(dstptr + offset, srcptr, dstsize);
    }

    return dst;
}

#endif
static ceApp CEPRIVATE_GLOBAL = {0};

extern __declspec(dllexport) void setup(void);
extern __declspec(dllexport) void update(f64);   
extern __declspec(dllexport) void draw(void);   
extern __declspec(dllexport) void terminate(void);

int main(int argc, const char *argv[], const char **envp) {
    CEPRIVATE_GLOBAL = (ceApp){.env={argc, argv, envp}};
    
    typedef void cUserfunc(void), cUserUpdateFunc(f64);

    cUserfunc *setup, *draw, *terminate;
    cUserUpdateFunc *update;

    ceInit();

    setup     = CEPRIVATE_PLATFORM_GET_PROC_ADDRESS("setup");
    update    = CEPRIVATE_PLATFORM_GET_PROC_ADDRESS("update");
    draw      = CEPRIVATE_PLATFORM_GET_PROC_ADDRESS("draw");
    terminate = CEPRIVATE_PLATFORM_GET_PROC_ADDRESS("terminate");

    if (setup) setup();

    f64 previous = 0, current = 0;
    {
        ptimepoint_t timepoint = pget_tick(PSTD_HIGH_RESOLUTION_CLOCK);
        current = pget_time_seconds_d(timepoint);
		previous = current;
    }
    while (CEPRIVATE_GLOBAL.is_running) {
        CEPRIVATE_PLATFORM_POLL_EVENTS();

        ptimepoint_t timepoint = pget_tick(PSTD_HIGH_RESOLUTION_CLOCK);
        current = pget_time_seconds_d(timepoint);
		f64 elapsed_time  = current - previous;
		previous = current;
        if (update) update(elapsed_time);

        CEPRIVATE_PLATFORM_CLEAR();
        if (draw) draw();
        
        CEPRIVATE_PLATFORM_SWAP_BUFFERS();
    }
    
    if (terminate) terminate();
    ceShutdown();
}

void ceInit(void) {
    CEPRIVATE_GLOBAL = (ceApp){0};
    CEPRIVATE_GLOBAL.is_running = true;
    CEPRIVATE_INIT_PLATFORM();
    CEPRIVATE_PLATFORM_INIT_KEYS();
}

void ceShutdown(void) {
    if (CEPRIVATE_GLOBAL.has_app) {
        CEPRIVATE_SHUTDOWN_PLATFORM();

        if (CEPRIVATE_GLOBAL.image_buffer) {
            pfree(CEPRIVATE_GLOBAL.image_buffer);
            CEPRIVATE_GLOBAL.image_buffer = NULL;
        }
    }
}
// core -------------------------------------------------------------------------------------------
#include <math.h>

#if defined(CELERY_STB_IMAGE)
#define STBI_NO_SIMD
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

#if defined(CELERY_QOI)
#define QOI_IMPLEMENTATION
#include "qoi.h"
#endif

#if defined(CELERY_GIF)
#define MSF_GIF_IMPL
#include "msf_gif.h"
#endif

#if defined(CELERY_STB_IMAGE)
ceSprite ceLoadImageSTB(const char *filepath) {
    int width, height, num_bits;
   //  stbi_set_flip_vertically_on_load(true);
    u8 *buffer = stbi_load(filepath, &width, &height, &num_bits, 4);
    if (!buffer) return (ceSprite){.is_valid = false};
    return (ceSprite){true, width, height, (void*)buffer};
}
#endif

#if defined(CELERY_QOI)
ceSprite ceLoadImageQOI(const char *filepath) {
    qoi_desc desc;
    cePixel *data = qoi_read(filepath, &desc, 4);
    if (!data) return (ceSprite){.is_valid = false};
    return (ceSprite){true, desc.width, desc.height, data};
}

void ceSaveSpriteQOI(ceSprite *spr, const char *filepath) {
    if (!spr || !spr->is_valid) return;

    qoi_write(filepath, spr->data,  
        &(qoi_desc){spr->width, spr->height, 4, QOI_SRGB}
    );
}
#endif

ceSprite ceGetFrameAsSprite(void) {
    u32 width  = CEPRIVATE_GLOBAL.image_width;
    u32 height = CEPRIVATE_GLOBAL.image_height;
    cePixel *data = pallocate(sizeof(cePixel) * width*height);
    if (!data) return (ceSprite){false, 0, 0, 0};

    memcpy(data, CEPRIVATE_GLOBAL.image_buffer, sizeof(cePixel) * width*height);
    return (ceSprite){true, width, height, data};
}

ceSprite ceLoadImage(const char *filepath) {
    (void)filepath; abort();
}

void ceFreeSprite(ceSprite *spr) {
    if (!spr || !spr->is_valid) return;
    pfree(spr->data);
    spr->is_valid = false;
}

void ceSize(u32 width, u32 height) {
    if (CEPRIVATE_GLOBAL.has_app)
         CEPRIVATE_RESIZE_WINDOW(width, height);
    else CEPRIVATE_CREATE_WINDOW(width, height);
}

u32 ceWidth(void) {
    return CEPRIVATE_GLOBAL.image_width;
}

u32 ceHeight(void) {
    return CEPRIVATE_GLOBAL.image_height;
}

ceVec2 ceBounds(void) {
    return (ceVec2){.data={CEPRIVATE_GLOBAL.image_width, CEPRIVATE_GLOBAL.image_height}};
}

void ceScale(u32 scale) {
    CEPRIVATE_GLOBAL.scale = scale;
}

void ceSetTitle(const char *title) {
    CEPRIVATE_PLATFORM_TITLE(title);
}

void ceSetMode(ceMode mode) {
    CEPRIVATE_GLOBAL.mode = mode;
}

pbool_t ceHasCollided(void) {
    return CEPRIVATE_GLOBAL.collision_flag;
}

cePixel ceprivate_ColorLerp(cePixel v0, cePixel v1, f64 t) {
    s32 r0 = v0.r, r1 = v1.r;
    s32 g0 = v0.g, g1 = v1.g;
    s32 b0 = v0.b, b1 = v1.b;
    s32 a0 = v0.a, a1 = v1.a;

    s32 r2 = r0 + t * (r1 - r0);
    s32 g2 = g0 + t * (g1 - g0);
    s32 b2 = b0 + t * (b1 - b0);
    s32 a2 = a0 + t * (a1 - a0); 

    return (cePixel){
        .r= (u8)r2,
        .g= (u8)g2,
        .b= (u8)b2,
        .a= (u8)a2,
    };
}

void ceDraw(u32 x, u32 y, cePixel color) {
    CEPRIVATE_PLATFORM_DRAW(x, y, color);
}

void ceDrawSprite(ceSprite *spr, u32 x, u32 y) {
    if (!spr || !spr->is_valid) return;

    for (u32 img_y=0; img_y < spr->height; img_y++) {
        for (u32 img_x=0; img_x < spr->width; img_x++) {
            cePixel p = spr->data[img_x + img_y*spr->width];
            CEPRIVATE_PLATFORM_DRAW(x + img_x, y + img_y, p); 
        }
    }
}
void ceDrawPartialSprite(ceSprite *spr, u32 _xoff, u32 _yoff, u32 width, u32 height, u32 x, u32 y) 
{
    if (!spr || !spr->is_valid) return;
    if (width  > spr->width) width = spr->width;
    if (height > spr->height) height = spr->height;

    for (u32 img_y=0; img_y < height; img_y++) {
        for (u32 img_x=0; img_x < width; img_x++) {
            u32 _x = (img_x + _xoff);
            u32 _y = (img_y + _yoff);
            if (_x >= spr->width || _y >= spr->height) break;

            cePixel p = spr->data[_x + _y*spr->width];
            CEPRIVATE_PLATFORM_DRAW(x + img_x, y + img_y, p); 
        }
    }
}

void ceRectangle(u32 x, u32 y, u32 width, u32 height, cePixel color) {
    for (u64 rect_y=0; rect_y < height; rect_y++) {
        for (u64 rect_x=0; rect_x < width; rect_x++) {
            CEPRIVATE_PLATFORM_DRAW(x + rect_x, y + rect_y, color); 
        }
    }
}

void ceTriangle(u32 x0, u32 y0, u32 x1, u32 y1, u32 x2, u32 y2, cePixel color) {
    u32 tmp;
#define swap(a, b) tmp = (a); a = b; b = tmp //NOLINT
    if (y1 < y0) { swap(y0, y1); swap(x0, x1); }
    if (y2 < y0) { swap(y0, y2); swap(x0, x2); }
    if (y2 < y1) { swap(y1, y2); swap(x1, x2); }

    pbool_t swap = !(x1 < x0); 
    for (u32 line = y0; line < y1; line++) {
        s64 start_x = x0 + (x1 - (s64)x0) * (line - y0) / (y1 - y0);
        s64 end_x   = x0 + (x2 - (s64)x0) * (line - y0) / (y2 - y0);

        if (swap) { swap(start_x, end_x); }

        for (s32 x = start_x; x < (end_x + 0.5f); x++) {
            CEPRIVATE_PLATFORM_DRAW(x, line, color);
        }
    }

    for (u32 line = y1; line < y2; line++) {
        s64 start_x = x1 + (x2 - (s64)x1) * (line - y1) / (y2 - y1);
        s64 end_x   = x0 + (x2 - (s64)x0) * (line - y0) / (y2 - y0);

        if (swap) { swap(start_x, end_x); }

        for (s64 x = start_x; x < end_x; x++) {
            CEPRIVATE_PLATFORM_DRAW(x, line, color);
        }
    }

#undef swap
}

void ceTriangleShaded(ceShadedArea area) {
    ceVec2  p0 = area.p0, p1 = area.p1, p2 = area.p2;
    cePixel c0 = area.c0, c1 = area.c1, c2 = area.c2;

    ceVec2 vtmp;
    cePixel ctmp;

#define swapV(a, b) vtmp = (a); a = b; b = vtmp //NOLINT
#define swapC(a, b) ctmp = (a); a = b; b = ctmp //NOLINT
    if (p1.y < p0.y) { swapV(p0, p1); swapC(c0, c1); }
    if (p2.y < p0.y) { swapV(p0, p2); swapC(c0, c2); }
    if (p2.y < p1.y) { swapV(p1, p2); swapC(c1, c2); }

    pbool_t swap = !(p1.x < p0.x); 
    for (u32 line = p0.y; line < p1.y; line++) {
        f32 start_x = p0.x + (p1.x - p0.x) * (line - p0.y) / (p1.y - p0.y);
        f32 end_x   = p0.x + (p2.x - p0.x) * (line - p0.y) / (p2.y - p0.y);

        f32 straight_percentage = (line - p0.y)/(p2.y - p0.y);
        f32 bend_percentage     = (line - p0.y)/(p1.y - p0.y);
        cePixel straight_color = ceprivate_ColorLerp(c0, c2, straight_percentage);
        cePixel bend_color     = ceprivate_ColorLerp(c0, c1, bend_percentage);

        if (swap) {
            f32 tmp = start_x;
            start_x = end_x;
            end_x   = tmp;
        }

        for (s32 x = start_x; x < (end_x + 0.5f); x++) {
            cePixel out_color;
            if (end_x - start_x == 0.0f)
                 out_color = bend_color;
            else out_color = ceprivate_ColorLerp(bend_color, straight_color, 
                    (x - start_x) / (end_x - start_x));
            CEPRIVATE_PLATFORM_DRAW(x, line, out_color);
        }
    }

    for (u32 line = p1.y; line < p2.y; line++) {
        f64 start_x = p1.x + (p2.x - p1.x) * (line - p1.y) / (p2.y - p1.y);
        f64 end_x   = p0.x + (p2.x - p0.x) * (line - p0.y) / (p2.y - p0.y);

        f32 straight_percentage = (line - p0.y)/(p2.y - p0.y);
        f32 bend_percentage     = (line - p1.y)/(p2.y - p1.y);
        cePixel straight_color = ceprivate_ColorLerp(c0, c2, straight_percentage);
        cePixel bend_color     = ceprivate_ColorLerp(c0, c1, bend_percentage);

        if (swap) {
            f32 tmp = start_x;
            start_x = end_x;
            end_x   = tmp;
        }

        for (s64 x = start_x; x < end_x; x++) {
            cePixel out_color;
            if (end_x - start_x == 0.0f)
                 out_color = bend_color;
            else out_color = ceprivate_ColorLerp(bend_color, 
                    straight_color, (x - start_x) / (end_x - start_x));
            CEPRIVATE_PLATFORM_DRAW(x, line, out_color);
        }
    }

#undef swapV
#undef swapC
}

void ceEllipseShaded(u32 cx, u32 cy, f64 x_radius, f64 y_radius, cePixel c0, cePixel c1) {
    for (s64 y = -y_radius; y <=y_radius; y++) {
        for (s64 x = -x_radius; x <=x_radius; x++) {
            u64 lsqrd = x*x+y*y;
            if (lsqrd <= x_radius*x_radius && lsqrd <= y_radius*y_radius) {
                f64 px = x/x_radius;
                f64 py = y/y_radius;

                f64 percentage = px*px + py*py;
                CEPRIVATE_PLATFORM_DRAW(cx+x, cy+y, ceprivate_ColorLerp(c0, c1, percentage));
            }
        }
    }
}

void ceCircleShaded(u32 x, u32 y, f64 radius, cePixel center, cePixel edge) {
    ceEllipseShaded(x, y, radius, radius, center, edge);
}



void ceEllipse(u32 cx, u32 cy, f64 x_radius, f64 y_radius, cePixel color) {
    for (s64 y = -y_radius; y <=y_radius; y++) {
        for (s64 x = -x_radius; x <=x_radius; x++) {
            u64 lsqrd = x*x+y*y;
            if (lsqrd <= x_radius*x_radius && lsqrd <= y_radius*y_radius)
                CEPRIVATE_PLATFORM_DRAW(cx+x, cy+y, color);
        }
    }
}

void ceCircle(u32 x, u32 y, f64 radius, cePixel color) {
    ceEllipse(x, y, radius, radius, color);
}

void ceLine(u32 x0, u32 y0, u32 x1, u32 y1, cePixel color) {
    ceLineShaded(x0, y0, x1, y1, color, color);
}

void ceprivate_LineLowShaded(u32 x0, u32 y0, u32 x1, u32 y1, cePixel c0, cePixel c1) {
    s64 dx = x1 - x0;
    s64 dy = y1 - y0;
    f64 dist = sqrt((f64)dx*dx+(f64)dy*dy);
    if (dist == 0.0) dist = 1;

    s64 yi = 1;
    if (dy < 0) {
        yi = -1;
        dy = -dy;
    }
    s64 D = (2 * dy) - dx;
    s64 y = y0;

    f64 offset = 0;
    for (s64 x = x0; x != x1; x++) {
        cePixel color = ceprivate_ColorLerp(c0, c1, offset);
        CEPRIVATE_PLATFORM_DRAW(x, y, color);
        s64 _dx = x1 - x;
        s64 _dy = y1 - y;
        offset = 1.0 - sqrt((f64)(_dx*_dx+_dy*_dy))/dist;

        if (D > 0){
            y = y + yi;
            D = D + (2 * (dy - dx));
        } else D = D + 2*dy;
    }
}
void ceprivate_LineHighShaded(u32 x0, u32 y0, u32 x1, u32 y1, cePixel c0, cePixel c1) {
    s64 dx = x1 - x0;
    s64 dy = y1 - y0;
    f64 dist = sqrt((f64)dx*dx+(f64)dy*dy);
    if (dist == 0.0) dist = 1;

    s64 xi = 1;
    if (dx < 0){
        xi = -1;
        dx = -dx;
    }
    s64 D = (2 * dx) - dy;
    s64 x = x0;

    f64 offset = 0;
    for (s64 y = y0; y != y1; y++) {
        CEPRIVATE_PLATFORM_DRAW(x, y, ceprivate_ColorLerp(c0, c1, offset));
        f64 _dx = x1 - x;
        f64 _dy = y1 - y;
        offset = 1.0 - sqrt((f64)(_dx*_dx+_dy*_dy))/dist;

        if (D > 0) {
            x = x + xi;
            D = D + (2 * (dx - dy));
        } else D = D + 2*dx;
    }
}

void ceLineShaded(u32 x0, u32 y0, u32 x1, u32 y1, cePixel c0, cePixel c1) {
    if (x0 == x1) {
        s64 inc = y0 > y1 ? -1 : 1;
        f64 offset = 0;
        do {
            CEPRIVATE_PLATFORM_DRAW(x0, y0, ceprivate_ColorLerp(c0, c1, offset));
            y0 += inc;
            offset = (f64)y0/(y1?(f64)y1:1.0);
        } while(y0 <= y1);
        return;
    }

    if (y0 == y1) {
        s64 inc = x0 > x1 ? -1 : 1;
        f64 offset = 0;
        do {
            CEPRIVATE_PLATFORM_DRAW(x0, y0, ceprivate_ColorLerp(c0, c1, offset));
            x0 += inc;
            offset = (f64)x0/(x1?(f64)x1:1.0);
        } while(x0 <= x1);
        return;
    }

    if (llabs((s64)y1 - y0) < llabs((s64)x1 - x0)) {
        if (x0 > x1) ceprivate_LineLowShaded(x1, y1, x0, y0, c0, c1);
        else         ceprivate_LineLowShaded(x0, y0, x1, y1, c0, c1);
    } else {
        if (y0 > y1) ceprivate_LineHighShaded(x1, y1, x0, y0, c0, c1);
        else         ceprivate_LineHighShaded(x0, y0, x1, y1, c0, c1);
    }
}


#if defined(CELERY_GIF)
ceGifState ceBeginGIF(void) {
    ceGifState state;
    int result = msf_gif_begin(&state.state, 
            CEPRIVATE_GLOBAL.image_width, CEPRIVATE_GLOBAL.image_height);
    state.is_valid = result != 0;
    return state;
}

void ceRecordFrame(ceGifState *s) {
    if (!s || !s->is_valid) return;

    cePixel *buf = CEPRIVATE_GLOBAL.image_buffer;
    msf_gif_frame(&s->state, &buf->r, 5, 16, 0); 
}

void ceRecordFrameAdv(ceGifState *s, u32 centi_seconds_per_frame, u32 bit_depth) {
    if (!s || !s->is_valid) return;

    cePixel *buf = CEPRIVATE_GLOBAL.image_buffer;
    msf_gif_frame(&s->state, &buf->r, centi_seconds_per_frame, bit_depth, 0); 
}

void ceSaveGif(ceGifState *s, const char *filepath) {
    if (!s || !s->is_valid) return;

    MsfGifResult result = msf_gif_end(&s->state);
    if (result.data) {
        FILE * fp = fopen(filepath, "wb");
        fwrite(result.data, result.dataSize, 1, fp);
        fclose(fp);
    }
    msf_gif_free(result);
    s->is_valid = false;
}

void ceEndGif(ceGifState *s) {
    if (!s || !s->is_valid) return;

    MsfGifResult result = msf_gif_end(&s->state);
    msf_gif_free(result);
    s->is_valid = false;
}
#endif

ceInputState ceGetKey(ceKeyCode code) {
    if (code >= 'a' && code <= 'z') code = toupper(code);
    return CEPRIVATE_GLOBAL.keys[code];
}

ceInputState ceGetMouseButton(ceMouseButton button) {
    if (button >= CE_MOUSE_BUTTON_COUNT) return (ceInputState){0};
    return CEPRIVATE_GLOBAL.mouse.buttons[button];
}

ceMouse ceGetMouse(void) {
    return CEPRIVATE_GLOBAL.mouse;
}

ceVec2d ceGetMousePos(void) {
    return CEPRIVATE_GLOBAL.mouse.pos;
}

ceVec2d ceGetMouseWheel(void) {
    return CEPRIVATE_GLOBAL.mouse.wheel;
}

ceModifier ceGetModifiers(void) {
    return CEPRIVATE_GLOBAL.mods;
}
// win32 ------------------------------------------------------------------------------------------
#if defined(PSTD_WINDOWS)
#include <windowsx.h>

static ceApp CEPRIVATE_GLOBAL;
#define WIN32_GLOBAL (CEPRIVATE_GLOBAL.win32)


void ceprivate_win32_init(void) {
    WIN32_GLOBAL.module = GetModuleHandle(NULL);
    WNDCLASS wndclass = {
        .lpfnWndProc   = ceprivate_win32_winproc,
        .lpszClassName = TEXT("CELERY_WINDOW_CLASS"),
        .hInstance     = WIN32_GLOBAL.module,
    };
    if (!RegisterClass(&wndclass)) {
        return;
    }
}

void ceprivate_win32_init_keys(void) {
    extern void *pmemexpand(void *dst, const void *src, usize dstsize, usize srcsize);
    static const ceKeyCode unknown = CE_KEY_UNKNOWN;
    pmemexpand(CEPRIVATE_GLOBAL.keycodes,  &unknown, sizeof(CEPRIVATE_GLOBAL.keycodes),  sizeof(unknown));
    pmemexpand(CEPRIVATE_GLOBAL.scancodes, &unknown, sizeof(CEPRIVATE_GLOBAL.scancodes), sizeof(unknown));
    
    CEPRIVATE_GLOBAL.keycodes[0x00B] = CE_KEY_0;
    CEPRIVATE_GLOBAL.keycodes[0x002] = CE_KEY_1;
    CEPRIVATE_GLOBAL.keycodes[0x003] = CE_KEY_2;
    CEPRIVATE_GLOBAL.keycodes[0x004] = CE_KEY_3;
    CEPRIVATE_GLOBAL.keycodes[0x005] = CE_KEY_4;
    CEPRIVATE_GLOBAL.keycodes[0x006] = CE_KEY_5;
    CEPRIVATE_GLOBAL.keycodes[0x007] = CE_KEY_6;
    CEPRIVATE_GLOBAL.keycodes[0x008] = CE_KEY_7;
    CEPRIVATE_GLOBAL.keycodes[0x009] = CE_KEY_8;
    CEPRIVATE_GLOBAL.keycodes[0x00A] = CE_KEY_9;
    CEPRIVATE_GLOBAL.keycodes[0x01E] = CE_KEY_A;
    CEPRIVATE_GLOBAL.keycodes[0x030] = CE_KEY_B;
    CEPRIVATE_GLOBAL.keycodes[0x02E] = CE_KEY_C;
    CEPRIVATE_GLOBAL.keycodes[0x020] = CE_KEY_D;
    CEPRIVATE_GLOBAL.keycodes[0x012] = CE_KEY_E;
    CEPRIVATE_GLOBAL.keycodes[0x021] = CE_KEY_F;
    CEPRIVATE_GLOBAL.keycodes[0x022] = CE_KEY_G;
    CEPRIVATE_GLOBAL.keycodes[0x023] = CE_KEY_H;
    CEPRIVATE_GLOBAL.keycodes[0x017] = CE_KEY_I;
    CEPRIVATE_GLOBAL.keycodes[0x024] = CE_KEY_J;
    CEPRIVATE_GLOBAL.keycodes[0x025] = CE_KEY_K;
    CEPRIVATE_GLOBAL.keycodes[0x026] = CE_KEY_L;
    CEPRIVATE_GLOBAL.keycodes[0x032] = CE_KEY_M;
    CEPRIVATE_GLOBAL.keycodes[0x031] = CE_KEY_N;
    CEPRIVATE_GLOBAL.keycodes[0x018] = CE_KEY_O;
    CEPRIVATE_GLOBAL.keycodes[0x019] = CE_KEY_P;
    CEPRIVATE_GLOBAL.keycodes[0x010] = CE_KEY_Q;
    CEPRIVATE_GLOBAL.keycodes[0x013] = CE_KEY_R;
    CEPRIVATE_GLOBAL.keycodes[0x01F] = CE_KEY_S;
    CEPRIVATE_GLOBAL.keycodes[0x014] = CE_KEY_T;
    CEPRIVATE_GLOBAL.keycodes[0x016] = CE_KEY_U;
    CEPRIVATE_GLOBAL.keycodes[0x02F] = CE_KEY_V;
    CEPRIVATE_GLOBAL.keycodes[0x011] = CE_KEY_W;
    CEPRIVATE_GLOBAL.keycodes[0x02D] = CE_KEY_X;
    CEPRIVATE_GLOBAL.keycodes[0x015] = CE_KEY_Y;
    CEPRIVATE_GLOBAL.keycodes[0x02C] = CE_KEY_Z;

    CEPRIVATE_GLOBAL.keycodes[0x028] = CE_KEY_APOSTROPHE;
    CEPRIVATE_GLOBAL.keycodes[0x02B] = CE_KEY_BACKSLASH;
    CEPRIVATE_GLOBAL.keycodes[0x033] = CE_KEY_COMMA;
    CEPRIVATE_GLOBAL.keycodes[0x00D] = CE_KEY_EQUAL;
    CEPRIVATE_GLOBAL.keycodes[0x029] = CE_KEY_GRAVE_ACCENT;
    CEPRIVATE_GLOBAL.keycodes[0x01A] = CE_KEY_LEFT_BRACKET;
    CEPRIVATE_GLOBAL.keycodes[0x00C] = CE_KEY_MINUS;
    CEPRIVATE_GLOBAL.keycodes[0x034] = CE_KEY_PERIOD;
    CEPRIVATE_GLOBAL.keycodes[0x01B] = CE_KEY_RIGHT_BRACKET;
    CEPRIVATE_GLOBAL.keycodes[0x027] = CE_KEY_SEMICOLON;
    CEPRIVATE_GLOBAL.keycodes[0x035] = CE_KEY_SLASH;
    CEPRIVATE_GLOBAL.keycodes[0x056] = CE_KEY_WORLD_2;

    CEPRIVATE_GLOBAL.keycodes[0x00E] = CE_KEY_BACKSPACE;
    CEPRIVATE_GLOBAL.keycodes[0x153] = CE_KEY_DELETE;
    CEPRIVATE_GLOBAL.keycodes[0x14F] = CE_KEY_END;
    CEPRIVATE_GLOBAL.keycodes[0x01C] = CE_KEY_ENTER;
    CEPRIVATE_GLOBAL.keycodes[0x001] = CE_KEY_ESCAPE;
    CEPRIVATE_GLOBAL.keycodes[0x147] = CE_KEY_HOME;
    CEPRIVATE_GLOBAL.keycodes[0x152] = CE_KEY_INSERT;
    CEPRIVATE_GLOBAL.keycodes[0x15D] = CE_KEY_MENU;
    CEPRIVATE_GLOBAL.keycodes[0x151] = CE_KEY_PAGE_DOWN;
    CEPRIVATE_GLOBAL.keycodes[0x149] = CE_KEY_PAGE_UP;
    CEPRIVATE_GLOBAL.keycodes[0x045] = CE_KEY_PAUSE;
    CEPRIVATE_GLOBAL.keycodes[0x146] = CE_KEY_PAUSE;
    CEPRIVATE_GLOBAL.keycodes[0x039] = CE_KEY_SPACE;
    CEPRIVATE_GLOBAL.keycodes[0x00F] = CE_KEY_TAB;
    CEPRIVATE_GLOBAL.keycodes[0x03A] = CE_KEY_CAPS_LOCK;
    CEPRIVATE_GLOBAL.keycodes[0x145] = CE_KEY_NUM_LOCK;
    CEPRIVATE_GLOBAL.keycodes[0x046] = CE_KEY_SCROLL_LOCK;
    CEPRIVATE_GLOBAL.keycodes[0x03B] = CE_KEY_F1;
    CEPRIVATE_GLOBAL.keycodes[0x03C] = CE_KEY_F2;
    CEPRIVATE_GLOBAL.keycodes[0x03D] = CE_KEY_F3;
    CEPRIVATE_GLOBAL.keycodes[0x03E] = CE_KEY_F4;
    CEPRIVATE_GLOBAL.keycodes[0x03F] = CE_KEY_F5;
    CEPRIVATE_GLOBAL.keycodes[0x040] = CE_KEY_F6;
    CEPRIVATE_GLOBAL.keycodes[0x041] = CE_KEY_F7;
    CEPRIVATE_GLOBAL.keycodes[0x042] = CE_KEY_F8;
    CEPRIVATE_GLOBAL.keycodes[0x043] = CE_KEY_F9;
    CEPRIVATE_GLOBAL.keycodes[0x044] = CE_KEY_F10;
    CEPRIVATE_GLOBAL.keycodes[0x057] = CE_KEY_F11;
    CEPRIVATE_GLOBAL.keycodes[0x058] = CE_KEY_F12;
    CEPRIVATE_GLOBAL.keycodes[0x064] = CE_KEY_F13;
    CEPRIVATE_GLOBAL.keycodes[0x065] = CE_KEY_F14;
    CEPRIVATE_GLOBAL.keycodes[0x066] = CE_KEY_F15;
    CEPRIVATE_GLOBAL.keycodes[0x067] = CE_KEY_F16;
    CEPRIVATE_GLOBAL.keycodes[0x068] = CE_KEY_F17;
    CEPRIVATE_GLOBAL.keycodes[0x069] = CE_KEY_F18;
    CEPRIVATE_GLOBAL.keycodes[0x06A] = CE_KEY_F19;
    CEPRIVATE_GLOBAL.keycodes[0x06B] = CE_KEY_F20;
    CEPRIVATE_GLOBAL.keycodes[0x06C] = CE_KEY_F21;
    CEPRIVATE_GLOBAL.keycodes[0x06D] = CE_KEY_F22;
    CEPRIVATE_GLOBAL.keycodes[0x06E] = CE_KEY_F23;
    CEPRIVATE_GLOBAL.keycodes[0x076] = CE_KEY_F24;
    CEPRIVATE_GLOBAL.keycodes[0x038] = CE_KEY_LEFT_ALT;
    CEPRIVATE_GLOBAL.keycodes[0x01D] = CE_KEY_LEFT_CONTROL;
    CEPRIVATE_GLOBAL.keycodes[0x02A] = CE_KEY_LEFT_SHIFT;
    CEPRIVATE_GLOBAL.keycodes[0x15B] = CE_KEY_LEFT_SUPER;
    CEPRIVATE_GLOBAL.keycodes[0x137] = CE_KEY_PRINT_SCREEN;
    CEPRIVATE_GLOBAL.keycodes[0x138] = CE_KEY_RIGHT_ALT;
    CEPRIVATE_GLOBAL.keycodes[0x11D] = CE_KEY_RIGHT_CONTROL;
    CEPRIVATE_GLOBAL.keycodes[0x036] = CE_KEY_RIGHT_SHIFT;
    CEPRIVATE_GLOBAL.keycodes[0x15C] = CE_KEY_RIGHT_SUPER;
    CEPRIVATE_GLOBAL.keycodes[0x150] = CE_KEY_DOWN;
    CEPRIVATE_GLOBAL.keycodes[0x14B] = CE_KEY_LEFT;
    CEPRIVATE_GLOBAL.keycodes[0x14D] = CE_KEY_RIGHT;
    CEPRIVATE_GLOBAL.keycodes[0x148] = CE_KEY_UP;

    CEPRIVATE_GLOBAL.keycodes[0x052] = CE_KEY_KP_0;
    CEPRIVATE_GLOBAL.keycodes[0x04F] = CE_KEY_KP_1;
    CEPRIVATE_GLOBAL.keycodes[0x050] = CE_KEY_KP_2;
    CEPRIVATE_GLOBAL.keycodes[0x051] = CE_KEY_KP_3;
    CEPRIVATE_GLOBAL.keycodes[0x04B] = CE_KEY_KP_4;
    CEPRIVATE_GLOBAL.keycodes[0x04C] = CE_KEY_KP_5;
    CEPRIVATE_GLOBAL.keycodes[0x04D] = CE_KEY_KP_6;
    CEPRIVATE_GLOBAL.keycodes[0x047] = CE_KEY_KP_7;
    CEPRIVATE_GLOBAL.keycodes[0x048] = CE_KEY_KP_8;
    CEPRIVATE_GLOBAL.keycodes[0x049] = CE_KEY_KP_9;
    CEPRIVATE_GLOBAL.keycodes[0x04E] = CE_KEY_KP_ADD;
    CEPRIVATE_GLOBAL.keycodes[0x053] = CE_KEY_KP_DECIMAL;
    CEPRIVATE_GLOBAL.keycodes[0x135] = CE_KEY_KP_DIVIDE;
    CEPRIVATE_GLOBAL.keycodes[0x11C] = CE_KEY_KP_ENTER;
    CEPRIVATE_GLOBAL.keycodes[0x059] = CE_KEY_KP_EQUAL;
    CEPRIVATE_GLOBAL.keycodes[0x037] = CE_KEY_KP_MULTIPLY;
    CEPRIVATE_GLOBAL.keycodes[0x04A] = CE_KEY_KP_SUBTRACT;

    for (u32 scancode = 0; scancode < 512; scancode++) {
        if (CEPRIVATE_GLOBAL.keycodes[scancode] != -1)
            CEPRIVATE_GLOBAL.scancodes[CEPRIVATE_GLOBAL.keycodes[scancode]] = scancode; 
    }
}

void ceprivate_win32_shutdown(void) {
    if (WIN32_GLOBAL.id != ~0u) {
        glDeleteTextures(1, &WIN32_GLOBAL.id);
    }

    wglMakeCurrent(NULL,NULL);
    wglDeleteContext(WIN32_GLOBAL.gl);
    ReleaseDC(WIN32_GLOBAL.handle, WIN32_GLOBAL.dc);

    DestroyWindow(WIN32_GLOBAL.handle);

    UnregisterClass(TEXT("CELERY_WINDOW_CLASS"), WIN32_GLOBAL.module);
}


void ceprivate_win32_create_window(u32 width, u32 height) {
    DWORD style    = WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX|WS_POPUP|WS_CLIPSIBLINGS|WS_CLIPCHILDREN;
    DWORD style_ex = WS_EX_APPWINDOW;
    
    CEPRIVATE_GLOBAL.width  = width;
    CEPRIVATE_GLOBAL.height = height;
    RECT rect = { 0, 0, width, height };
    AdjustWindowRectEx(&rect, style, FALSE, style_ex);
    width  = rect.right - rect.left;
    height = rect.bottom - rect.top;

    HWND hwnd = CreateWindowEx(style_ex, TEXT("CELERY_WINDOW_CLASS"), 
            TEXT(""), style, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 
            NULL, NULL, WIN32_GLOBAL.module, NULL);
    ShowWindow(hwnd, SW_SHOW);

    CEPRIVATE_GLOBAL.has_app = true;
    WIN32_GLOBAL.handle = hwnd;

    HDC dc = GetDC(hwnd);
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR), 1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        PFD_MAIN_PLANE, 0, 0, 0, 0
    };


    int pf = ChoosePixelFormat(dc, &pfd);
    if (!pf) return;
    SetPixelFormat(dc, pf, &pfd);
    
    HGLRC glrc = wglCreateContext(dc);
    if (!glrc) {
        CEPRIVATE_GLOBAL.has_app = false;
        return;
    }
    wglMakeCurrent(dc, glrc);
    WIN32_GLOBAL.gl = glrc;
    WIN32_GLOBAL.dc = dc;
    
    // Remove Frame cap
    BOOL (WINAPI *wglSwapInterval)(int interval) = 
        (BOOL(WINAPI*)(int interval))wglGetProcAddress("wglSwapIntervalEXT");
    if (wglSwapInterval) wglSwapInterval(0);

    glEnable(GL_TEXTURE_2D); // Turn on texturing
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glViewport(0, 0, CEPRIVATE_GLOBAL.width, CEPRIVATE_GLOBAL.height);

    RECT area;
    GetClientRect(hwnd, &area);
    width  = area.right  - area.left;
    height = area.bottom - area.top;

    u32 scale = CEPRIVATE_GLOBAL.scale ? CEPRIVATE_GLOBAL.scale : 1;
    u32 surface_width  = width/scale;
    u32 surface_height = height/scale;
    cePixel *buffer = pzero_allocate(sizeof(cePixel) * surface_width * surface_height);
    u32 id = ceprivate_win32_create_surface(surface_width, surface_height, buffer);
    if (id == ~0u) {
        pprintf("could not create opengl surface!");
        CEPRIVATE_GLOBAL.has_app = false;
        return;
    }
    WIN32_GLOBAL.id = id;
    CEPRIVATE_GLOBAL.image_width  = surface_width;
    CEPRIVATE_GLOBAL.image_height = surface_height;
    CEPRIVATE_GLOBAL.image_buffer = buffer;
    ceprivate_win32_title("");
}

void ceprivate_win32_resize_window(u32 width, u32 height) {
    DWORD style    = WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX|WS_POPUP|WS_CLIPSIBLINGS|WS_CLIPCHILDREN;
    DWORD style_ex = WS_EX_APPWINDOW;
    
    CEPRIVATE_GLOBAL.width  = width;
    CEPRIVATE_GLOBAL.height = height;
    RECT rect = { 0, 0, width, height };
    AdjustWindowRectEx(&rect, style, FALSE, style_ex);
    width  = rect.right - rect.left;
    height = rect.bottom - rect.top;
    
    SetWindowPos(WIN32_GLOBAL.handle, HWND_TOP, 0, 0, width, height,
            SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOZORDER);
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glViewport(0, 0, width, height);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ceprivate_win32_swap_buffers(void) {
    if (!CEPRIVATE_GLOBAL.has_app) return;
    
    f64 width  = CEPRIVATE_GLOBAL.image_width;
    f64 height = CEPRIVATE_GLOBAL.image_height;
    void *data = CEPRIVATE_GLOBAL.image_buffer;
    glBindTexture(GL_TEXTURE_2D, WIN32_GLOBAL.id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( 1.0f, 1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( 1.0f,-1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f,-1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, 1.0f);
    glEnd();

    SwapBuffers(WIN32_GLOBAL.dc);
}

void ceprivate_win32_clear(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    CEPRIVATE_GLOBAL.collision_flag = false;
}

s32 ceprivate_win32_create_surface(u32 width, u32 height, void *buf) {
    u32 id;
    glGenTextures(1, &id);
    if (id == ~0u) return -1;

    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buf);
    return id;
}

void ceprivate_win32_update_surface(u32 x, u32 y, cePixel p) {
    if (!CEPRIVATE_GLOBAL.has_app) return;
    if (p.a == 0) return;

    u32 width  = CEPRIVATE_GLOBAL.image_width;
    u32 height = CEPRIVATE_GLOBAL.image_height;
    if (x >= width || y >= height) return;

    ceMode mode = CEPRIVATE_GLOBAL.mode;
    cePixel d = CEPRIVATE_GLOBAL.image_buffer[x + y * width];
    f64 a = p.a / 255.0;
    f64 c = 1.0 - a;
    f64 r = a * (f64)p.r + c * (f64)d.r;
    f64 g = a * (f64)p.g + c * (f64)d.g;
    f64 b = a * (f64)p.b + c * (f64)d.b;
    if (d.a >= CE_ENTITY_0 && mode >= CE_ENTITY_0)
         CEPRIVATE_GLOBAL.collision_flag = true;
    if (mode == CE_FOREGROUND) mode = d.a;

    CEPRIVATE_GLOBAL.image_buffer[x + y * width] = (cePixel){.r=r, .g=g, .b=b, .a=mode};
}

void ceprivate_win32_title(const char *str) {
    CEPRIVATE_GLOBAL.title = str;
#if defined(UNICODE)
    if (str) {
        usize length = strlen(str) + 1;
        wchar_t* buf = pallocate(length * sizeof(wchar_t));
        mbstowcs_s(&length, buf, length, str, _TRUNCATE);
        SetWindowText(WIN32_GLOBAL.handle, buf);
        free(buf);
    }
#else
    SetWindowText(WIN32_GLOBAL.handle, CEPRIVATE_GLOBAL.title);
#endif
}

void (*ceprivate_win32_get_proc_address(const char *str))() {
    return (void(*)())GetProcAddress(WIN32_GLOBAL.module, str);
}



LRESULT CALLBACK ceprivate_win32_winproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    ceApp *cel = &CEPRIVATE_GLOBAL;
    switch(msg) {
    case WM_DESTROY: 
        PostQuitMessage(0);
        cel->is_running = false;
        return 0;
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    case WM_XBUTTONDOWN:
    case WM_XBUTTONUP: {
            ceMouseButton button; int action; 
            /**/ if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONUP)
                 button = CE_MOUSE_LEFT;
            else if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONUP) //NOLINT
                 button = CE_MOUSE_RIGHT;
            else if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONUP) //NOLINT
                 button = CE_MOUSE_MIDDLE;
            else if (GET_XBUTTON_WPARAM(wparam) == XBUTTON1)//NOLINT
                 button = CE_MOUSE_4;
            else button = CE_MOUSE_5;//NOLINT

            if (msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN 
             || msg == WM_MBUTTONDOWN || msg == WM_XBUTTONDOWN) {
                action = 1;
            } else {
                action = 0;
            }
            
            if      (action == 1) cel->mouse.buttons[button].pressed  = true;
            else if (action == 0) cel->mouse.buttons[button].released = true;
            cel->mouse.pos = (ceVec2d){ 
                .x= GET_X_LPARAM(lparam), 
                .y= GET_Y_LPARAM(lparam) 
            };
            return 0;
        }
    case WM_MOUSEWHEEL: {
            cel->mouse.wheel.y = (SHORT) HIWORD(wparam) / (double) WHEEL_DELTA;
            return 0;
        }
    case WM_MOUSEHWHEEL: {
            cel->mouse.wheel.x = (SHORT) HIWORD(wparam) / (double) WHEEL_DELTA;
            return 0;
        }
    case WM_MOUSEMOVE: 
        cel->mouse.pos = (ceVec2d){ 
            .x= GET_X_LPARAM(lparam), 
            .y= GET_Y_LPARAM(lparam)
        }; 
        return 0;
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
    case WM_KEYUP:
    case WM_SYSKEYUP: {
            int action   = (HIWORD(lparam) & KF_UP) ? 0 : 1;
            unsigned int scancode = (HIWORD(lparam) & (KF_EXTENDED | 0xff));
            if (!scancode) {
                scancode = MapVirtualKeyW((UINT) wparam, MAPVK_VK_TO_VSC);
            }
            ceKeyCode key = cel->keycodes[scancode];
            if (action == 1 && !cel->keys[key].held) {
                cel->keys[key].pressed = true;
            }
            else if (action == 0) cel->keys[key].released = true;
            break;
        }
    default: break;
    }
    return DefWindowProc(hwnd, msg, wparam, lparam);
}

void ceprivate_win32_poll_events(void) {
    if (!CEPRIVATE_GLOBAL.has_app) return;

    MSG msg = {0};
    while (PeekMessage(&msg, WIN32_GLOBAL.handle, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    static ceInputState oldkeystate[512] = {0};
    static ceInputState oldmousestate[5] = {0};

    ceModifier mods = 0;
    if (GetKeyState(VK_SHIFT) & 0x8000)
        mods |= CE_MOD_SHIFT;
    if (GetKeyState(VK_CONTROL) & 0x8000)
        mods |= CE_MOD_CONTROL;
    if (GetKeyState(VK_MENU) & 0x8000)
        mods |= CE_MOD_ALT;
    if ((GetKeyState(VK_LWIN) | GetKeyState(VK_RWIN)) & 0x8000)
        mods |= CE_MOD_SUPER;
    if (GetKeyState(VK_CAPITAL) & 1)
        mods |= CE_MOD_CAPS_LOCK;
    if (GetKeyState(VK_NUMLOCK) & 1)
        mods |= CE_MOD_NUM_LOCK;
    CEPRIVATE_GLOBAL.mods = mods;

    ceInputState *keystate = CEPRIVATE_GLOBAL.keys;
    for (int i = 0; i < 512; i++) {
        if (keystate[i].pressed) {
            if (!oldkeystate[i].pressed) {
                oldkeystate[i] = keystate[i];
                keystate[i].released = false;
                keystate[i].pressed  = true;
                keystate[i].held     = true;
            }
            else {
                oldkeystate[i] = keystate[i];
                keystate[i].released = false;
                keystate[i].pressed  = false;
                keystate[i].held     = true;
            }
        }
        else if (keystate[i].released) {
            if (oldkeystate[i].released) {
                oldkeystate[i] = keystate[i];
                keystate[i].released = true;
                keystate[i].pressed  = false;
                keystate[i].held     = false;
            }
            else {
                oldkeystate[i] = keystate[i];
                keystate[i].released = false;
                keystate[i].pressed  = false;
                keystate[i].held     = false;
            }
        }
        else if (keystate[i].held) {
            oldkeystate[i] = keystate[i];
            keystate[i].released = false;
            keystate[i].pressed  = false;
        }
    }
    ceInputState *mousestate = CEPRIVATE_GLOBAL.mouse.buttons;
    for (int i = 0; i < 5; i++) {
        if (mousestate[i].pressed){
            if (oldmousestate[i].pressed) {
                oldmousestate[i] = mousestate[i];
                mousestate[i].released = false;
                mousestate[i].pressed  = true;
                mousestate[i].held     = true;
            }
            else {
                oldmousestate[i] = mousestate[i];
                mousestate[i].released = false;
                mousestate[i].pressed  = false;
                mousestate[i].held     = true;
            }
        }
        else if (mousestate[i].released) {
            if (oldmousestate[i].released) {
                oldmousestate[i] = mousestate[i];
                mousestate[i].released = true;
                mousestate[i].pressed  = false;
                mousestate[i].held     = false;
            }
            else {
                oldmousestate[i] = mousestate[i];
                mousestate[i].released = false;
                mousestate[i].pressed  = false;
                mousestate[i].held     = false;
            }
        }
        else if (mousestate[i].held) {
            oldmousestate[i] = mousestate[i];
            mousestate[i].released = false;
            mousestate[i].pressed  = false;
        }
    }
}
#undef WIN32_GLOBAL
#if defined(PSTD_MSVC)
#pragma warning(pop)
#endif

#endif
#endif

