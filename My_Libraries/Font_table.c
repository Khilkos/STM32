#include "Font_table.h"

//========================================
const unsigned char FontTable[256][5]= {
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x00   0
	{ 0x02, 0x05, 0x02, 0x00, 0x00 },   //   0x01   1
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x02   2
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x03   3
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x04   4
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x05   5
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x06   6
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x07   7
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x08   8
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x09   9
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x0A  10
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x0B  11
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x0C  12
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x0D  13
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x0E  14
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x0F  15
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x10  16
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x11  17
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x12  18
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x13  19
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x14  20
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x15  21
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x16  22
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x17  23
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x18  24
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x19  25
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x1A  26
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x1B  27
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x1C  28
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x1D  29
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x1E  30
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x1F  31
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //   0x20  32
	{ 0x00, 0x00, 0x5F, 0x00, 0x00 },   // ! 0x21  33
	{ 0x00, 0x07, 0x00, 0x07, 0x00 },   // " 0x22  34
	{ 0x14, 0x7F, 0x14, 0x7F, 0x14 },   // # 0x23  35
	{ 0x24, 0x2A, 0x7F, 0x2A, 0x12 },   // $ 0x24  36
	{ 0x4C, 0x2C, 0x10, 0x68, 0x64 },   // % 0x25  37
	{ 0x36, 0x49, 0x55, 0x22, 0x50 },   // & 0x26  38
	{ 0x00, 0x05, 0x03, 0x00, 0x00 },   // ' 0x27  39
	{ 0x00, 0x1C, 0x22, 0x41, 0x00 },   // ( 0x28  40
	{ 0x00, 0x41, 0x22, 0x1C, 0x00 },   // ) 0x29  41
	{ 0x14, 0x08, 0x3E, 0x08, 0x14 },   // * 0x2A  42
	{ 0x08, 0x08, 0x3E, 0x08, 0x08 },   // + 0x2B  43
	{ 0x00, 0x00, 0x50, 0x30, 0x00 },   // , 0x2C  44
	{ 0x10, 0x10, 0x10, 0x10, 0x10 },   // - 0x2D  45
	{ 0x00, 0x60, 0x60, 0x00, 0x00 },   // . 0x2E  46
	{ 0x20, 0x10, 0x08, 0x04, 0x02 },   // / 0x2F  47
	{ 0x3E, 0x51, 0x49, 0x45, 0x3E },   // 0 0x30  48
	{ 0x00, 0x42, 0x7F, 0x40, 0x00 },   // 1 0x31  49
	{ 0x42, 0x61, 0x51, 0x49, 0x46 },   // 2 0x32  50
	{ 0x21, 0x41, 0x45, 0x4B, 0x31 },   // 3 0x33  51
	{ 0x18, 0x14, 0x12, 0x7F, 0x10 },   // 4 0x34  52
	{ 0x27, 0x45, 0x45, 0x45, 0x39 },   // 5 0x35  53
	{ 0x3C, 0x4A, 0x49, 0x49, 0x30 },   // 6 0x36  54
	{ 0x01, 0x71, 0x09, 0x05, 0x03 },   // 7 0x37  55
	{ 0x36, 0x49, 0x49, 0x49, 0x36 },   // 8 0x38  56
	{ 0x06, 0x49, 0x49, 0x29, 0x1E },   // 9 0x39  57
	{ 0x00, 0x36, 0x36, 0x00, 0x00 },   // : 0x3A  58
	{ 0x00, 0x56, 0x36, 0x00, 0x00 },   // ; 0x3B  59
	{ 0x08, 0x14, 0x22, 0x41, 0x00 },   // < 0x3C  60
	{ 0x14, 0x14, 0x14, 0x14, 0x14 },   // = 0x3D  61
	{ 0x00, 0x41, 0x22, 0x14, 0x08 },   // > 0x3E  62
	{ 0x02, 0x01, 0x51, 0x09, 0x06 },   // ? 0x3F  63
	{ 0x3C, 0x42, 0x5A, 0x56, 0x0C },   // @ 0x40  64
	{ 0x7E, 0x11, 0x11, 0x11, 0x7E },   // A 0x41  65
	{ 0x7F, 0x49, 0x49, 0x49, 0x36 },   // B 0x42  66
	{ 0x3E, 0x41, 0x41, 0x41, 0x22 },   // C 0x43  67
	{ 0x7F, 0x41, 0x41, 0x22, 0x1C },   // D 0x44  68
	{ 0x7F, 0x49, 0x49, 0x49, 0x41 },   // E 0x45  69
	{ 0x7F, 0x09, 0x09, 0x09, 0x01 },   // F 0x46  70
	{ 0x3E, 0x41, 0x49, 0x49, 0x7A },   // G 0x47  71
	{ 0x7F, 0x08, 0x08, 0x08, 0x7F },   // H 0x48  72
	{ 0x00, 0x41, 0x7F, 0x41, 0x00 },   // I 0x49  73
	{ 0x20, 0x40, 0x41, 0x3F, 0x01 },   // J 0x4A  74
	{ 0x7F, 0x08, 0x14, 0x22, 0x41 },   // K 0x4B  75
	{ 0x7F, 0x40, 0x40, 0x40, 0x40 },   // L 0x4C  76
	{ 0x7F, 0x02, 0x0C, 0x02, 0x7F },   // M 0x4D  77
	{ 0x7F, 0x04, 0x08, 0x10, 0x7F },   // N 0x4E  78
	{ 0x3E, 0x41, 0x41, 0x41, 0x3E },   // O 0x4F  79
	{ 0x7F, 0x09, 0x09, 0x09, 0x06 },   // P 0x50  80
	{ 0x3E, 0x41, 0x51, 0x21, 0x5E },   // Q 0x51  81
	{ 0x7F, 0x09, 0x19, 0x29, 0x46 },   // R 0x52  82
	{ 0x46, 0x49, 0x49, 0x49, 0x31 },   // S 0x53  83
	{ 0x01, 0x01, 0x7F, 0x01, 0x01 },   // T 0x54  84
	{ 0x3F, 0x40, 0x40, 0x40, 0x3F },   // U 0x55  85
	{ 0x1F, 0x20, 0x40, 0x20, 0x1F },   // V 0x56  86
	{ 0x3F, 0x40, 0x38, 0x40, 0x3F },   // W 0x57  87
	{ 0x63, 0x14, 0x08, 0x14, 0x63 },   // X 0x58  88
	{ 0x07, 0x08, 0x70, 0x08, 0x07 },   // Y 0x59  89
	{ 0x61, 0x51, 0x49, 0x45, 0x43 },   // Z 0x5A  90
	{ 0x00, 0x7F, 0x41, 0x41, 0x00 },   // [ 0x5B  91
	{ 0x02, 0x04, 0x08, 0x10, 0x20 },   // \ 0x5C  92
	{ 0x00, 0x41, 0x41, 0x7F, 0x00 },   // ] 0x5D  93
	{ 0x04, 0x02, 0x01, 0x02, 0x04 },   // ^ 0x5E  94
	{ 0x40, 0x40, 0x40, 0x40, 0x40 },   // _ 0x5F  95
	{ 0x00, 0x01, 0x02, 0x04, 0x00 },   // ` 0x60  96
	{ 0x20, 0x54, 0x54, 0x54, 0x78 },   // a 0x61  97
	{ 0x7F, 0x48, 0x44, 0x44, 0x38 },   // b 0x62  98
	{ 0x38, 0x44, 0x44, 0x44, 0x20 },   // c 0x63  99
	{ 0x38, 0x44, 0x44, 0x48, 0x7F },   // d 0x64 100
	{ 0x38, 0x54, 0x54, 0x54, 0x18 },   // e 0x65 101
	{ 0x08, 0x7E, 0x09, 0x01, 0x02 },   // f 0x66 102
	{ 0x18, 0x94, 0x94, 0x94, 0x7C },   // g 0x67 103
	{ 0x7F, 0x08, 0x04, 0x04, 0x78 },   // h 0x68 104
	{ 0x00, 0x44, 0x7D, 0x40, 0x00 },   // i 0x69 105
	{ 0x20, 0x40, 0x44, 0x3D, 0x00 },   // j 0x6A 106
	{ 0x7F, 0x10, 0x28, 0x44, 0x00 },   // k 0x6B 107
	{ 0x00, 0x41, 0x7F, 0x40, 0x00 },   // l 0x6C 108
	{ 0x7C, 0x04, 0x18, 0x04, 0x78 },   // m 0x6D 109
	{ 0x7C, 0x08, 0x04, 0x04, 0x78 },   // n 0x6E 110
	{ 0x38, 0x44, 0x44, 0x44, 0x38 },   // o 0x6F 111
	{ 0x7C, 0x14, 0x14, 0x14, 0x08 },   // p 0x70 112
	{ 0x08, 0x14, 0x14, 0x18, 0x7C },   // q 0x71 113
	{ 0x7C, 0x08, 0x04, 0x04, 0x08 },   // r 0x72 114
	{ 0x48, 0x54, 0x54, 0x54, 0x20 },   // s 0x73 115
	{ 0x04, 0x3F, 0x44, 0x40, 0x20 },   // t 0x74 116
	{ 0x3C, 0x40, 0x40, 0x20, 0x7C },   // u 0x75 117
	{ 0x1C, 0x20, 0x40, 0x20, 0x1C },   // v 0x76 118
	{ 0x3C, 0x40, 0x30, 0x40, 0x3C },   // w 0x77 119
	{ 0x44, 0x28, 0x10, 0x28, 0x44 },   // x 0x78 120
	{ 0x0C, 0x50, 0x50, 0x50, 0x3C },   // y 0x79 121
	{ 0x44, 0x64, 0x54, 0x4C, 0x44 },   // z 0x7A 122
	{ 0x00, 0x08, 0x36, 0x41, 0x00 },   // { 0x7B 123
	{ 0x00, 0x00, 0x7F, 0x00, 0x00 },   // | 0x7C 124
	{ 0x00, 0x41, 0x36, 0x08, 0x00 },   // } 0x7D 125
	{ 0x08, 0x04, 0x08, 0x10, 0x08 },   // ~ 0x7E 126
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   //  0x7F 127
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0x80 128
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0x81 129
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0x82 130
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0x83 131
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0x84 132
	{ 0x40, 0x00, 0x40, 0x00, 0x40 },   // � 0x85 133
	{ 0x04, 0x04, 0xFF, 0x04, 0x04 },   // � 0x86 134
	{ 0x24, 0x24, 0xFF, 0x24, 0x24 },   // � 0x87 135
	{ 0x28, 0x7C, 0xAA, 0xAA, 0x82 },   // � 0x88 136
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0x89 137
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0x8A 138
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0x8B 139
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0x8C 140
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0x8D 141
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0x8E 142
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0x8F 143
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0x90 144
	{ 0x00, 0x06, 0x05, 0x00, 0x00 },   // � 0x91 145
	{ 0x00, 0x00, 0x05, 0x03, 0x00 },   // � 0x92 146
	{ 0x06, 0x05, 0x00, 0x06, 0x05 },   // � 0x93 147
	{ 0x05, 0x03, 0x00, 0x05, 0x03 },   // � 0x94 148
	{ 0x18, 0x3C, 0x3C, 0x3C, 0x18 },   // � 0x95 149
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0x96 150
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0x97 151
	{ 0x78, 0x48, 0x48, 0x78, 0x00 },   // � 0x98 152
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0x99 153
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0x9A 154
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0x9B 155
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0x9C 156
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0x9D 157
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0x9E 158
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0x9F 159
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0xA0 160
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0xA1 161
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0xA2 162
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0xA3 163
	{ 0x22, 0x1C, 0x14, 0x1C, 0x22 },   // � 0xA4 164
	{ 0x7E, 0x02, 0x02, 0x02, 0x03 },   // � 0xA5 165
	{ 0x00, 0x00, 0xE7, 0x00, 0x00 },   // � 0xA6 166
	{ 0x4A, 0x95, 0xA5, 0xA9, 0x52 },   // � 0xA7 167
	{ 0x7C, 0x55, 0x54, 0x45, 0x44 },   // � 0xA8 168
	{ 0x00, 0x18, 0x24, 0x24, 0x00 },   // � 0xA9 169
	{ 0x3E, 0x49, 0x49, 0x41, 0x22 },   // � 0xAA 170
	{ 0x08, 0x14, 0x2A, 0x14, 0x22 },   // � 0xAB 171
	{ 0x04, 0x04, 0x04, 0x04, 0x0C },   // � 0xAC 172
	{ 0x00, 0x08, 0x08, 0x08, 0x00 },   // � 0xAD 173
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0xAE 174
	{ 0x00, 0x45, 0x7C, 0x45, 0x00 },   // � 0xAF 175
	{ 0x00, 0x04, 0x0A, 0x04, 0x00 },   // � 0xB0 176
	{ 0x44, 0x44, 0x5F, 0x44, 0x44 },   // � 0xB1 177
	{ 0x00, 0x41, 0x7F, 0x41, 0x00 },   // � 0xB2 178
	{ 0x00, 0x00, 0x7A, 0x00, 0x00 },   // � 0xB3 179
	{ 0x00, 0x78, 0x08, 0x0C, 0x00 },   // � 0xB4 180
	{ 0x00, 0xFC, 0x20, 0x3C, 0x20 },   // � 0xB5 181
	{ 0x0C, 0x1E, 0xFE, 0x02, 0xFE },   // � 0xB6 182
	{ 0x00, 0x18, 0x18, 0x00, 0x00 },   // � 0xB7 183
	{ 0x39, 0x54, 0x54, 0x49, 0x00 },   // � 0xB8 184
	{ 0x78, 0x10, 0x20, 0x7B, 0x03 },   // � 0xB9 185
	{ 0x38, 0x54, 0x54, 0x44, 0x00 },   // � 0xBA 186
	{ 0x22, 0x14, 0x2A, 0x14, 0x08 },   // � 0xBB 187
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0xBC 188
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0xBD 189
	{ 0x00, 0x00, 0x00, 0x00, 0x00 },   // � 0xBE 190
	{ 0x00, 0x54, 0x70, 0x44, 0x00 },   // � 0xBF 191
	{ 0x7C, 0x12, 0x11, 0x12, 0x7C },   // � 0xC0 192
	{ 0x7F, 0x49, 0x49, 0x49, 0x31 },   // � 0xC1 193
	{ 0x7F, 0x49, 0x49, 0x49, 0x36 },   // � 0xC2 194
	{ 0x7F, 0x01, 0x01, 0x01, 0x01 },   // � 0xC3 195
	{ 0x60, 0x3F, 0x21, 0x3F, 0x60 },   // � 0xC4 196
	{ 0x7F, 0x49, 0x49, 0x49, 0x41 },   // � 0xC5 197
	{ 0x77, 0x08, 0x7F, 0x08, 0x77 },   // � 0xC6 198
	{ 0x22, 0x41, 0x49, 0x49, 0x36 },   // � 0xC7 199
	{ 0x7F, 0x10, 0x08, 0x04, 0x7F },   // � 0xC8 200
	{ 0x7E, 0x10, 0x09, 0x04, 0x7E },   // � 0xC9 201
	{ 0x7F, 0x08, 0x14, 0x22, 0x41 },   // � 0xCA 202
	{ 0x40, 0x3E, 0x01, 0x01, 0x7F },   // � 0xCB 203
	{ 0x7F, 0x02, 0x0C, 0x02, 0x7F },   // � 0xCC 204
	{ 0x7F, 0x08, 0x08, 0x08, 0x7F },   // � 0xCD 205
	{ 0x3E, 0x41, 0x41, 0x41, 0x3E },   // � 0xCE 206
	{ 0x7F, 0x01, 0x01, 0x01, 0x7F },   // � 0xCF 207
	{ 0x7F, 0x09, 0x09, 0x09, 0x06 },   // � 0xD0 208
	{ 0x3E, 0x41, 0x41, 0x41, 0x22 },   // � 0xD1 209
	{ 0x01, 0x01, 0x7F, 0x01, 0x01 },   // � 0xD2 210
	{ 0x07, 0x48, 0x48, 0x48, 0x3F },   // � 0xD3 211
	{ 0x0E, 0x11, 0x7F, 0x11, 0x0E },   // � 0xD4 212
	{ 0x63, 0x14, 0x08, 0x14, 0x63 },   // � 0xD5 213
	{ 0x3F, 0x20, 0x20, 0x3F, 0x60 },   // � 0xD6 214
	{ 0x07, 0x08, 0x08, 0x08, 0x7F },   // � 0xD7 215
	{ 0x7F, 0x40, 0x7E, 0x40, 0x7F },   // � 0xD8 216
	{ 0x3F, 0x20, 0x3F, 0x20, 0x7F },   // � 0xD9 217
	{ 0x01, 0x7F, 0x48, 0x48, 0x30 },   // � 0xDA 218
	{ 0x7F, 0x48, 0x30, 0x00, 0x7F },   // � 0xDB 219
	{ 0x00, 0x7F, 0x48, 0x48, 0x30 },   // � 0xDC 220
	{ 0x22, 0x41, 0x49, 0x49, 0x3E },   // � 0xDD 221
	{ 0x7F, 0x08, 0x3E, 0x41, 0x3E },   // � 0xDE 222
	{ 0x46, 0x29, 0x19, 0x09, 0x7F },   // � 0xDF 223
	{ 0x20, 0x54, 0x54, 0x54, 0x78 },   // � 0xE0 224
	{ 0x3C, 0x4A, 0x4A, 0x4A, 0x31 },   // � 0xE1 225
	{ 0x7C, 0x54, 0x54, 0x54, 0x28 },   // � 0xE2 226
	{ 0x7C, 0x04, 0x04, 0x0C, 0x00 },   // � 0xE3 227
	{ 0x60, 0x3C, 0x24, 0x3C, 0x60 },   // � 0xE4 228
	{ 0x38, 0x54, 0x54, 0x54, 0x18 },   // � 0xE5 229
	{ 0x6C, 0x10, 0x7C, 0x10, 0x6C },   // � 0xE6 230
	{ 0x44, 0x54, 0x54, 0x54, 0x28 },   // � 0xE7 231
	{ 0x7C, 0x20, 0x10, 0x08, 0x7C },   // � 0xE8 232
	{ 0x7C, 0x21, 0x12, 0x09, 0x7C },   // � 0xE9 233
	{ 0x7C, 0x10, 0x28, 0x44, 0x00 },   // � 0xEA 234
	{ 0x40, 0x38, 0x04, 0x04, 0x7C },   // � 0xEB 235
	{ 0x7C, 0x08, 0x10, 0x08, 0x7C },   // � 0xEC 236
	{ 0x7C, 0x10, 0x10, 0x10, 0x7C },   // � 0xED 237
	{ 0x38, 0x44, 0x44, 0x44, 0x38 },   // � 0xEE 238
	{ 0x7C, 0x04, 0x04, 0x04, 0x7C },   // � 0xEF 239
	{ 0x7C, 0x14, 0x14, 0x14, 0x08 },   // � 0xF0 240
	{ 0x38, 0x44, 0x44, 0x44, 0x00 },   // � 0xF1 241
	{ 0x04, 0x04, 0x7C, 0x04, 0x04 },   // � 0xF2 242
	{ 0x0C, 0x50, 0x50, 0x50, 0x3C },   // � 0xF3 243
	{ 0x08, 0x14, 0x7C, 0x14, 0x08 },   // � 0xF4 244
	{ 0x44, 0x28, 0x10, 0x28, 0x44 },   // � 0xF5 245
	{ 0x3C, 0x20, 0x20, 0x3C, 0x60 },   // � 0xF6 246
	{ 0x0C, 0x10, 0x10, 0x10, 0x7C },   // � 0xF7 247
	{ 0x7C, 0x40, 0x7C, 0x40, 0x7C },   // � 0xF8 248
	{ 0x3C, 0x20, 0x3C, 0x20, 0x7C },   // � 0xF9 249
	{ 0x04, 0x7C, 0x50, 0x50, 0x20 },   // � 0xFA 250
	{ 0x7C, 0x50, 0x20, 0x00, 0x7C },   // � 0xFB 251
	{ 0x00, 0x7C, 0x50, 0x50, 0x20 },   // � 0xFC 252
	{ 0x28, 0x44, 0x54, 0x54, 0x38 },   // � 0xFD 253
	{ 0x7C, 0x10, 0x38, 0x44, 0x38 },   // � 0xFE 254
	{ 0x48, 0x54, 0x34, 0x14, 0x7C }    // � 0xFF 255
};


//========================================


const unsigned char D_0[8]={0b00001110,0b00010001,0b00010001,0b00010001,0b00010001,0b00010001,0b00010001,0b00001110};
const unsigned char D_1[8]={0b00000001,0b00000011,0b00000101,0b00000001,0b00000001,0b00000001,0b00000001,0b00000001};
const unsigned char D_2[8]={0b00001110,0b00010001,0b00000001,0b00000001,0b00000010,0b00000100,0b00001000,0b00011111};
const unsigned char D_3[8]={0b00001110,0b00010001,0b00000001,0b00000110,0b00000001,0b00000001,0b00010001,0b00001110};
const unsigned char D_4[8]={0b00000010,0b00000110,0b00001010,0b00001010,0b00010010,0b00011111,0b00000010,0b00000010};
const unsigned char D_5[8]={0b00011111,0b00010000,0b00010000,0b00011110,0b00000001,0b00000001,0b00010001,0b00001110};
const unsigned char D_6[8]={0b00001110,0b00010001,0b00010000,0b00011110,0b00010001,0b00010001,0b00010001,0b00001110};
const unsigned char D_7[8]={0b00011111,0b00000001,0b00000010,0b00000010,0b00000100,0b00000100,0b00001000,0b00001000};
const unsigned char D_8[8]={0b00001110,0b00010001,0b00010001,0b00001110,0b00010001,0b00010001,0b00010001,0b00001110};
const unsigned char D_9[8]={0b00001110,0b00010001,0b00010001,0b00010001,0b00001111,0b00000001,0b00010001,0b00001110};
	
//=========================================================================

	
	
