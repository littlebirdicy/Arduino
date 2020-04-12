# 用来播放一些音乐

>使用前将文件夹复制到 /Arduino/libraries/ 目录下。

下面是使用模板：

```
#include "music.h"

int pin = my_pin;
int *my_melody; 
float *my_rhythm;
int my_size = sizeof(my_rhythm) / sizeof(*my_rhythm);
music my_music(tone, speed, my_melody, my_rhythm, my_size);

void setup()
{
    pinMode(my_pin, OUTPUT);
}

void loop()
{
    my_music.playmusic(my_pin);
}
```

其中`my_melody`是音乐的简谱，`my_rhythm`是对应音符的时长，这里以4分音符为一拍，为了方便，数组中1代表4分音符，2代表8分音符。
`my_size`是数组的大小，`tone`是调式，C调的`tone=1`，`speed`代表每分钟的拍数。

`my_music.playmusic(my_pin)`代表从my_pin引脚播放音乐。

## 最后贴一个极乐净土的应用代码

```
#include "music.h"

int pin = 9;
float my_rhythm[64] = {1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 2, 4, 4, 2, 2, 1, 1};
int my_melody[64] = {0, 0, 0, 3, 5, 6, 0, 0, 5, 6, 0, 0, 5, 6, 11, 5, 6, 3, 0, 3, 5, 6, 0, 0, 5, 6, 0, 0, 5, 6, 33, 11, 22, 6, 0, 3, 5, 6, 0, 0, 5, 6, 0, 0, 5, 6, 11, 5, 6, 3, 5, 1, 2, 3, 11, 6, 33, 22, 33, 22, 11, 22, 6, 0};
int my_size = sizeof(my_rhythm) / sizeof(*my_rhythm);

music mymusic(6, 110, my_melody, my_rhythm, my_size);

void setup()
{
    pinMode(pin, OUTPUT);
}

void loop()
{
    mymusic.playmusic(pin);
}
```

極楽浄土前奏的数组乐谱在music.txt里
