//
//  main.cpp
//  vatest
//
//  Created by systemp on 2018/07/08.
//  Copyright © 2018年 systemp. All rights reserved.
//

#include <iostream>

void vatest1(const char *format, ...);
void vatest2(int count, ...);

void formatString(const char* format, va_list list);

void vatest1(const char *format, ...)
{
    va_list list;
    
    // 第２引数は可変引数(...)の直前の引数
    va_start(list, format);
    
    // ... で渡したいところだが、できなさそう。
    // 受け取った先でva_startしてva_listととして処理するわけだから
    // この時点でva_listとして渡していても不都合はないのでは？
    vatest2(0,list);

    // printf的な使い方をしたい場合は、文字列かしてしまった渡すのも手としてはある。
    char string[256];
    vsprintf(string, format, list);
    printf("%s", string);
    
    // 正確に必要なメモリを算出し、メモリ確保して処理したい場合は以下関数参照.
    formatString(format, list);
    
    va_end(list);
    
    return;
}

void formatString(const char* format, va_list list)
{
    va_list list2;
    
    va_copy(list2, list); // list -> list2へ状態をコピー.
    
    const int len = vsnprintf(NULL, 0, format, list); // 必要なサイズを取得.
    char *buf = (char *)malloc((len + 1) * sizeof(char)); // NULL文字の分.
    vsnprintf(buf, len, format, list2); // list2を引数に渡す.
    // 何か処理する.
    printf("%s", buf);

    free(buf);
    va_end(list2);
    
    return;
}

// 可変引数にできるのは第２引数以降。よって、function(...)のような定義は出来ない。
void vatest2(int count, ...)
{
    va_list list;
    // 第２引数は可変引数(...)の直前の引数.
    va_start(list, count);
    // list使って何か処理する.
    va_end(list);

    return;
}

int main(int argc, const char * argv[]) {
    vatest1("%s:%ld\n", "abc", 1);
    return 0;
}
