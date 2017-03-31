#ifndef __SYLLABLEUNIGRAM_H__
#define __SYLLABLEUNIGRAM_H__

#include <stdio.h>
#include <stdlib.h>

#define ASCII_NUM 128
#define HANGUL_HEIGHT 25
#define HANGUL_WIDTH 94

// ASCII 문자 빈도조사
void Ascii_frequency(int ch, int freq[]);
// 한글 빈도조사
void Hangul_frequency(int c1, int c2, int hfreq[HANGUL_HEIGHT][HANGUL_WIDTH]);
void Question_gram() ;
bool Ishangul(char c1) ;
void Frequency_research();
void Syllable_unigram() ;
void Syllable_onesearch();

#endif