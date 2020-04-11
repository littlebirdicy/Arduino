#pragma once
#include "Arduino.h"
#ifndef _MUSIC_H_
#define _MUSIC_H_
#include "math.h"
class music
{
private:
    //这里是原调
    const float *voice[7] = {c, d, e, f, g, a, b};
    const float c[2] = {261.63, 523.31};
    const float d[2] = {293.66, 587.437};
    const float e[2] = {329.63, 659.421};
    const float f[2] = {349.23, 698.657};
    const float g[2] = {392, 784.27};
    const float a[2] = {440, 880.375};
    const float b[2] = {493.88, 988.256};

    int Mode = 1;   //设置默认调式为C调
    int Speed = 76; //默认每分钟76拍,4分音符为一拍
    float *Melody = nullptr;
    float *Rhythm = nullptr;
    int Size = 0;

public:
    music(int _mode, int _speed, int *_melody, float *_rhythm, int _size); //以_mode、_speed、_melody、_rhythm初始化对象，分别代表调式、速率、旋律、节奏
    ~music();
    float *melody(int *_melody);   //输入_melody为该调式下乐曲的简谱，升1用11表示，以此类推；空拍用0表示。返回一个数组，其中存储乐谱各个音对应的频率。
    float *rhythm(float *_rhythm); //输入_rhythm为melody音符对应的延时拍数，1表示一个4分音符，返回一个数组，其中存储乐谱各个音延续的时间。
    void playmusic(int _pin);      //封装函数，从引脚_pin播放音乐
};

music::music(int _mode, int _speed, int *_melody, float *_rhythm, int _size) //以_mode、_speed、_melody、_rhythm初始化对象，分别代表调式、速率、旋律、节奏
{
    this->Size = _size;
    this->Mode = _mode;
    this->Speed = _speed;
    this->Melody = melody(_melody);
    this->Rhythm = rhythm(_rhythm);
};

music::~music(){};

float *music::melody(int *_melody)
{
    float *Melody = nullptr; //存贮旋律数组
    Melody = new float[Size];
    for (int i = 0; i < Size; i++)
    {
        if (_melody[i] / 11 == 0)
        {
            Melody[i] = this->voice[_melody[i] - 1][0];
        }
        else
        {
            Melody[i] = this->voice[_melody[i] / 11 - 1][1];
        }
    }

    switch (this->Mode)
    {
    case 2:
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < Size; j++)
            {
                Melody[j] *= pow(2.0, 1.0 / 12);
            }
        }
        break;
    case 3:
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < Size; j++)
            {
                Melody[j] *= pow(2.0, 1.0 / 12);
            }
        }
        break;
    case 4:
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < Size; j++)
            {
                Melody[j] *= pow(2.0, 1.0 / 12);
            }
        }
        break;
    case 5:
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < Size; j++)
            {
                Melody[j] *= pow(2.0, 1.0 / 12);
            }
        }
        break;
    case 6:
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < Size; j++)
            {
                Melody[j] *= pow(2.0, 1.0 / 12);
            }
        }
        break;
    case 7:
        for (int i = 0; i < 11; i++)
        {
            for (int j = 0; j < Size; j++)
            {
                Melody[j] *= pow(2.0, 1.0 / 12);
            }
        }
        break;

    default:
        break;
    }
    return Melody;
}
float *music::rhythm(float *_rhythm)
{
    for (int i = 0; i < Size; i++)
    {
        _rhythm[i] = 1 / _rhythm[i];
    }
    
    float time_per_note = 60000.0 / float(this->Speed); //四分音符的时间
    float *Rhythm;                                      //存储每个音符的实际时间
    Rhythm = new float[Size];
    for (int i = 0; i < Size; i++)
    {
        Rhythm[i] = _rhythm[i] * time_per_note;
    }
    
    return Rhythm;
}
void music::playmusic(int _pin)
{
    for (int i = 0; i < this->Size; i++)
    {
        tone(_pin, Melody[i]);
        delay(Rhythm[i]);
    }
}

#endif
