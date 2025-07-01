#include "base64.h"
#include <iostream>
// #include<vector>
// #include<cstring>
// #include<iostream>
// #include<algorithm>
using namespace std;

const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
//base64包括 A～Z    a~z     1-10      +     /   =  26 + 26 + 10 + 1 + 1 = 64

bool is_base64(unsigned char c)
{
    return (isalnum(c) || (c == '+') || (c == '/'));
    //isalnum用于判断一个字符是否是字母或者数字
}

// 编码规则 https://blog.csdn.net/zhizhengguan/article/details/106020819
// 找出单个字符对应ASCII码值，每个八位，转换成每个六位的，不够则在最后面添加0   则 Hello 对应的Base64编码是： SGVsbG8=  5*8=40  (40 + 8)/6 = 8 注：不是40 + 2 = 42
std::string Base64Encode(unsigned char const *byte_to_encode, unsigned int byte_length)
{
    //计算时，以24为单位，所以编码后面出现了=或者==
    string ret;
    //每次从源字符串取出来三个用于编码
    int i = 0;
    unsigned char char_source_3[3];
    unsigned char char_target_4[4];
    while(byte_length--)
    {
        char_source_3[i++] = *(byte_to_encode++);
        if(i == 3)
        {
            // &操作  11100 & 01010 = 01000
            char_target_4[0] = (char_source_3[0] & 0xfc) >> 2;
            char_target_4[1] = ((char_source_3[0] & 0x03) << 4) + ((char_source_3[1] & 0xf0) >> 4);
            char_target_4[2] = ((char_source_3[1] & 0x0f) << 2) + ((char_source_3[2] & 0xc0) >> 6);
            char_target_4[3] = char_source_3[2] & 0x3f;

            for(int j = 0;j < 4; j++)
            {
                ret += base64_chars[char_target_4[j]];
            }
            std::cout << ret << std::endl;
            i = 0;
        }
    }
    std::cout << ret << std::endl;
    if(i)
    {
        for(int j = i;j < 3; j++)
        {
            char_source_3[j] = '\0'; //源字符串最后不够三个的时候填充0   i=1时，需要填充两个，i=2时，需要填充1个
        }
        char_target_4[0] = (char_source_3[0] & 0xfc) >> 2;
        char_target_4[1] = ((char_source_3[0] & 0x03) << 4) + ((char_source_3[1] & 0xf0) >> 4);
        char_target_4[2] = ((char_source_3[1] & 0x0f) << 2) + ((char_source_3[2] & 0xc0) >> 6);
        char_target_4[3] = char_source_3[2] & 0x3f;

        for(int j = 0; j < 4; j++)
        {
            if(j < (i + 1))
            {
                ret += base64_chars[char_target_4[j]];
            }
            else
            {
                ret += '=';
            }
        }

    }
    return ret;
}


// int main()
// {
//     const char *a = "adwaddaw";
//     int b = strlen(a);
//     std::cout<< Base64Encode(reinterpret_cast<unsigned char const *>(a),b) << std::endl;
// }
//g++ base64.cpp -o base64
//./bash64
