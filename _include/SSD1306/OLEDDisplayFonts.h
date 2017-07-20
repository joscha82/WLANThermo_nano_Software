#ifndef OLEDDISPLAYFONTS_h
#define OLEDDISPLAYFONTS_h

// more Fonts: http://oleddisplay.squix.ch

const char ArialMT_Plain_10[] PROGMEM = {
  0x0A, // Width: 10
  0x0D, // Height: 13
  0x20, // First Char: 32
  0x5F, // Numbers of Chars: 95

  // Jump Table:
  0xFF, 0xFF, 0x00, 0x03,  // 32:65535
  0x00, 0x00, 0x04, 0x03,  // 33:0
  0x00, 0x04, 0x05, 0x04,  // 34:4
  0x00, 0x09, 0x09, 0x06,  // 35:9
  0x00, 0x12, 0x0A, 0x06,  // 36:18
  0x00, 0x1C, 0x10, 0x09,  // 37:28
  0x00, 0x2C, 0x0E, 0x07,  // 38:44
  0x00, 0x3A, 0x01, 0x02,  // 39:58
  0x00, 0x3B, 0x06, 0x03,  // 40:59
  0x00, 0x41, 0x06, 0x03,  // 41:65
  0x00, 0x47, 0x05, 0x04,  // 42:71
  0x00, 0x4C, 0x09, 0x06,  // 43:76
  0x00, 0x55, 0x04, 0x03,  // 44:85
  0x00, 0x59, 0x03, 0x03,  // 45:89
  0x00, 0x5C, 0x04, 0x03,  // 46:92
  0x00, 0x60, 0x05, 0x03,  // 47:96
  0x00, 0x65, 0x0A, 0x06,  // 48:101
  0x00, 0x6F, 0x08, 0x06,  // 49:111
  0x00, 0x77, 0x0A, 0x06,  // 50:119
  0x00, 0x81, 0x0A, 0x06,  // 51:129
  0x00, 0x8B, 0x0B, 0x06,  // 52:139
  0x00, 0x96, 0x0A, 0x06,  // 53:150
  0x00, 0xA0, 0x0A, 0x06,  // 54:160
  0x00, 0xAA, 0x09, 0x06,  // 55:170
  0x00, 0xB3, 0x0A, 0x06,  // 56:179
  0x00, 0xBD, 0x0A, 0x06,  // 57:189
  0x00, 0xC7, 0x04, 0x03,  // 58:199
  0x00, 0xCB, 0x04, 0x03,  // 59:203
  0x00, 0xCF, 0x0A, 0x06,  // 60:207
  0x00, 0xD9, 0x09, 0x06,  // 61:217
  0x00, 0xE2, 0x09, 0x06,  // 62:226
  0x00, 0xEB, 0x0B, 0x06,  // 63:235
  0x00, 0xF6, 0x14, 0x0A,  // 64:246
  0x01, 0x0A, 0x0E, 0x07,  // 65:266
  0x01, 0x18, 0x0C, 0x07,  // 66:280
  0x01, 0x24, 0x0C, 0x07,  // 67:292
  0x01, 0x30, 0x0B, 0x07,  // 68:304
  0x01, 0x3B, 0x0C, 0x07,  // 69:315
  0x01, 0x47, 0x09, 0x06,  // 70:327
  0x01, 0x50, 0x0D, 0x08,  // 71:336
  0x01, 0x5D, 0x0C, 0x07,  // 72:349
  0x01, 0x69, 0x04, 0x03,  // 73:361
  0x01, 0x6D, 0x08, 0x05,  // 74:365
  0x01, 0x75, 0x0E, 0x07,  // 75:373
  0x01, 0x83, 0x0C, 0x06,  // 76:387
  0x01, 0x8F, 0x10, 0x08,  // 77:399
  0x01, 0x9F, 0x0C, 0x07,  // 78:415
  0x01, 0xAB, 0x0E, 0x08,  // 79:427
  0x01, 0xB9, 0x0B, 0x07,  // 80:441
  0x01, 0xC4, 0x0E, 0x08,  // 81:452
  0x01, 0xD2, 0x0C, 0x07,  // 82:466
  0x01, 0xDE, 0x0C, 0x07,  // 83:478
  0x01, 0xEA, 0x0B, 0x06,  // 84:490
  0x01, 0xF5, 0x0C, 0x07,  // 85:501
  0x02, 0x01, 0x0D, 0x07,  // 86:513
  0x02, 0x0E, 0x11, 0x09,  // 87:526
  0x02, 0x1F, 0x0E, 0x07,  // 88:543
  0x02, 0x2D, 0x0D, 0x07,  // 89:557
  0x02, 0x3A, 0x0C, 0x06,  // 90:570
  0x02, 0x46, 0x06, 0x03,  // 91:582
  0x02, 0x4C, 0x06, 0x03,  // 92:588
  0x02, 0x52, 0x04, 0x03,  // 93:594
  0x02, 0x56, 0x09, 0x05,  // 94:598
  0x02, 0x5F, 0x0C, 0x06,  // 95:607
  0x02, 0x6B, 0x03, 0x03,  // 96:619
  0x02, 0x6E, 0x0A, 0x06,  // 97:622
  0x02, 0x78, 0x0A, 0x06,  // 98:632
  0x02, 0x82, 0x0A, 0x05,  // 99:642
  0x02, 0x8C, 0x0A, 0x06,  // 100:652
  0x02, 0x96, 0x0A, 0x06,  // 101:662
  0x02, 0xA0, 0x05, 0x03,  // 102:672
  0x02, 0xA5, 0x0A, 0x06,  // 103:677
  0x02, 0xAF, 0x0A, 0x06,  // 104:687
  0x02, 0xB9, 0x04, 0x02,  // 105:697
  0x02, 0xBD, 0x04, 0x02,  // 106:701
  0x02, 0xC1, 0x08, 0x05,  // 107:705
  0x02, 0xC9, 0x04, 0x02,  // 108:713
  0x02, 0xCD, 0x10, 0x08,  // 109:717
  0x02, 0xDD, 0x0A, 0x06,  // 110:733
  0x02, 0xE7, 0x0A, 0x06,  // 111:743
  0x02, 0xF1, 0x0A, 0x06,  // 112:753
  0x02, 0xFB, 0x0A, 0x06,  // 113:763
  0x03, 0x05, 0x05, 0x03,  // 114:773
  0x03, 0x0A, 0x08, 0x05,  // 115:778
  0x03, 0x12, 0x06, 0x03,  // 116:786
  0x03, 0x18, 0x0A, 0x06,  // 117:792
  0x03, 0x22, 0x09, 0x05,  // 118:802
  0x03, 0x2B, 0x0E, 0x07,  // 119:811
  0x03, 0x39, 0x0A, 0x05,  // 120:825
  0x03, 0x43, 0x09, 0x05,  // 121:835
  0x03, 0x4C, 0x0A, 0x05,  // 122:844
  0x03, 0x56, 0x06, 0x03,  // 123:854
  0x03, 0x5C, 0x04, 0x03,  // 124:860
  0x03, 0x60, 0x05, 0x03,  // 125:864
  0x03, 0x65, 0x09, 0x06,  // 126:869

  // Font Data:
  0x00,0x00,0xF8,0x02,  // 33
  0x38,0x00,0x00,0x00,0x38, // 34
  0xA0,0x03,0xE0,0x00,0xB8,0x03,0xE0,0x00,0xB8, // 35
  0x30,0x01,0x28,0x02,0xF8,0x07,0x48,0x02,0x90,0x01,  // 36
  0x00,0x00,0x30,0x00,0x48,0x00,0x30,0x03,0xC0,0x00,0xB0,0x01,0x48,0x02,0x80,0x01,  // 37
  0x80,0x01,0x50,0x02,0x68,0x02,0xA8,0x02,0x18,0x01,0x80,0x03,0x80,0x02,  // 38
  0x38, // 39
  0xE0,0x03,0x10,0x04,0x08,0x08,  // 40
  0x08,0x08,0x10,0x04,0xE0,0x03,  // 41
  0x28,0x00,0x18,0x00,0x28, // 42
  0x40,0x00,0x40,0x00,0xF0,0x01,0x40,0x00,0x40, // 43
  0x00,0x00,0x00,0x06,  // 44
  0x80,0x00,0x80, // 45
  0x00,0x00,0x00,0x02,  // 46
  0x00,0x03,0xE0,0x00,0x18, // 47
  0xF0,0x01,0x08,0x02,0x08,0x02,0x08,0x02,0xF0,0x01,  // 48
  0x00,0x00,0x20,0x00,0x10,0x00,0xF8,0x03,  // 49
  0x10,0x02,0x08,0x03,0x88,0x02,0x48,0x02,0x30,0x02,  // 50
  0x10,0x01,0x08,0x02,0x48,0x02,0x48,0x02,0xB0,0x01,  // 51
  0xC0,0x00,0xA0,0x00,0x90,0x00,0x88,0x00,0xF8,0x03,0x80, // 52
  0x60,0x01,0x38,0x02,0x28,0x02,0x28,0x02,0xC8,0x01,  // 53
  0xF0,0x01,0x28,0x02,0x28,0x02,0x28,0x02,0xD0,0x01,  // 54
  0x08,0x00,0x08,0x03,0xC8,0x00,0x38,0x00,0x08, // 55
  0xB0,0x01,0x48,0x02,0x48,0x02,0x48,0x02,0xB0,0x01,  // 56
  0x70,0x01,0x88,0x02,0x88,0x02,0x88,0x02,0xF0,0x01,  // 57
  0x00,0x00,0x20,0x02,  // 58
  0x00,0x00,0x20,0x06,  // 59
  0x00,0x00,0x40,0x00,0xA0,0x00,0xA0,0x00,0x10,0x01,  // 60
  0xA0,0x00,0xA0,0x00,0xA0,0x00,0xA0,0x00,0xA0, // 61
  0x00,0x00,0x10,0x01,0xA0,0x00,0xA0,0x00,0x40, // 62
  0x10,0x00,0x08,0x00,0x08,0x00,0xC8,0x02,0x48,0x00,0x30, // 63
  0x00,0x00,0xC0,0x03,0x30,0x04,0xD0,0x09,0x28,0x0A,0x28,0x0A,0xC8,0x0B,0x68,0x0A,0x10,0x05,0xE0,0x04,  // 64
  0x00,0x02,0xC0,0x01,0xB0,0x00,0x88,0x00,0xB0,0x00,0xC0,0x01,0x00,0x02,  // 65
  0x00,0x00,0xF8,0x03,0x48,0x02,0x48,0x02,0x48,0x02,0xF0,0x01,  // 66
  0x00,0x00,0xF0,0x01,0x08,0x02,0x08,0x02,0x08,0x02,0x10,0x01,  // 67
  0x00,0x00,0xF8,0x03,0x08,0x02,0x08,0x02,0x10,0x01,0xE0, // 68
  0x00,0x00,0xF8,0x03,0x48,0x02,0x48,0x02,0x48,0x02,0x48,0x02,  // 69
  0x00,0x00,0xF8,0x03,0x48,0x00,0x48,0x00,0x08, // 70
  0x00,0x00,0xE0,0x00,0x10,0x01,0x08,0x02,0x48,0x02,0x50,0x01,0xC0, // 71
  0x00,0x00,0xF8,0x03,0x40,0x00,0x40,0x00,0x40,0x00,0xF8,0x03,  // 72
  0x00,0x00,0xF8,0x03,  // 73
  0x00,0x03,0x00,0x02,0x00,0x02,0xF8,0x01,  // 74
  0x00,0x00,0xF8,0x03,0x80,0x00,0x60,0x00,0x90,0x00,0x08,0x01,0x00,0x02,  // 75
  0x00,0x00,0xF8,0x03,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02,  // 76
  0x00,0x00,0xF8,0x03,0x30,0x00,0xC0,0x01,0x00,0x02,0xC0,0x01,0x30,0x00,0xF8,0x03,  // 77
  0x00,0x00,0xF8,0x03,0x30,0x00,0x40,0x00,0x80,0x01,0xF8,0x03,  // 78
  0x00,0x00,0xF0,0x01,0x08,0x02,0x08,0x02,0x08,0x02,0x08,0x02,0xF0,0x01,  // 79
  0x00,0x00,0xF8,0x03,0x48,0x00,0x48,0x00,0x48,0x00,0x30, // 80
  0x00,0x00,0xF0,0x01,0x08,0x02,0x08,0x02,0x08,0x03,0x08,0x03,0xF0,0x02,  // 81
  0x00,0x00,0xF8,0x03,0x48,0x00,0x48,0x00,0xC8,0x00,0x30,0x03,  // 82
  0x00,0x00,0x30,0x01,0x48,0x02,0x48,0x02,0x48,0x02,0x90,0x01,  // 83
  0x00,0x00,0x08,0x00,0x08,0x00,0xF8,0x03,0x08,0x00,0x08, // 84
  0x00,0x00,0xF8,0x01,0x00,0x02,0x00,0x02,0x00,0x02,0xF8,0x01,  // 85
  0x08,0x00,0x70,0x00,0x80,0x01,0x00,0x02,0x80,0x01,0x70,0x00,0x08, // 86
  0x18,0x00,0xE0,0x01,0x00,0x02,0xF0,0x01,0x08,0x00,0xF0,0x01,0x00,0x02,0xE0,0x01,0x18, // 87
  0x00,0x02,0x08,0x01,0x90,0x00,0x60,0x00,0x90,0x00,0x08,0x01,0x00,0x02,  // 88
  0x08,0x00,0x10,0x00,0x20,0x00,0xC0,0x03,0x20,0x00,0x10,0x00,0x08, // 89
  0x08,0x03,0x88,0x02,0xC8,0x02,0x68,0x02,0x38,0x02,0x18,0x02,  // 90
  0x00,0x00,0xF8,0x0F,0x08,0x08,  // 91
  0x18,0x00,0xE0,0x00,0x00,0x03,  // 92
  0x08,0x08,0xF8,0x0F,  // 93
  0x40,0x00,0x30,0x00,0x08,0x00,0x30,0x00,0x40, // 94
  0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x08,  // 95
  0x08,0x00,0x10, // 96
  0x00,0x00,0x00,0x03,0xA0,0x02,0xA0,0x02,0xE0,0x03,  // 97
  0x00,0x00,0xF8,0x03,0x20,0x02,0x20,0x02,0xC0,0x01,  // 98
  0x00,0x00,0xC0,0x01,0x20,0x02,0x20,0x02,0x40,0x01,  // 99
  0x00,0x00,0xC0,0x01,0x20,0x02,0x20,0x02,0xF8,0x03,  // 100
  0x00,0x00,0xC0,0x01,0xA0,0x02,0xA0,0x02,0xC0,0x02,  // 101
  0x20,0x00,0xF0,0x03,0x28, // 102
  0x00,0x00,0xC0,0x05,0x20,0x0A,0x20,0x0A,0xE0,0x07,  // 103
  0x00,0x00,0xF8,0x03,0x20,0x00,0x20,0x00,0xC0,0x03,  // 104
  0x00,0x00,0xE8,0x03,  // 105
  0x00,0x08,0xE8,0x07,  // 106
  0xF8,0x03,0x80,0x00,0xC0,0x01,0x20,0x02,  // 107
  0x00,0x00,0xF8,0x03,  // 108
  0x00,0x00,0xE0,0x03,0x20,0x00,0x20,0x00,0xE0,0x03,0x20,0x00,0x20,0x00,0xC0,0x03,  // 109
  0x00,0x00,0xE0,0x03,0x20,0x00,0x20,0x00,0xC0,0x03,  // 110
  0x00,0x00,0xC0,0x01,0x20,0x02,0x20,0x02,0xC0,0x01,  // 111
  0x00,0x00,0xE0,0x0F,0x20,0x02,0x20,0x02,0xC0,0x01,  // 112
  0x00,0x00,0xC0,0x01,0x20,0x02,0x20,0x02,0xE0,0x0F,  // 113
  0x00,0x00,0xE0,0x03,0x20, // 114
  0x40,0x02,0xA0,0x02,0xA0,0x02,0x20,0x01,  // 115
  0x20,0x00,0xF8,0x03,0x20,0x02,  // 116
  0x00,0x00,0xE0,0x01,0x00,0x02,0x00,0x02,0xE0,0x03,  // 117
  0x20,0x00,0xC0,0x01,0x00,0x02,0xC0,0x01,0x20, // 118
  0xE0,0x01,0x00,0x02,0xC0,0x01,0x20,0x00,0xC0,0x01,0x00,0x02,0xE0,0x01,  // 119
  0x20,0x02,0x40,0x01,0x80,0x00,0x40,0x01,0x20,0x02,  // 120
  0x20,0x00,0xC0,0x09,0x00,0x06,0xC0,0x01,0x20, // 121
  0x20,0x02,0x20,0x03,0xA0,0x02,0x60,0x02,0x20,0x02,  // 122
  0x80,0x00,0x78,0x0F,0x08,0x08,  // 123
  0x00,0x00,0xF8,0x0F,  // 124
  0x08,0x08,0x78,0x0F,0x80, // 125
  0xC0,0x00,0x40,0x00,0xC0,0x00,0x80,0x00,0xC0 // 126
};

const char ArialMT_Plain_16[] PROGMEM = {
  0x10, // Width: 16
  0x13, // Height: 19
  0x20, // First Char: 32
  0x5F, // Numbers of Chars: 95

  // Jump Table:
  0xFF, 0xFF, 0x00, 0x04,  // 32:65535
  0x00, 0x00, 0x08, 0x04,  // 33:0
  0x00, 0x08, 0x0D, 0x06,  // 34:8
  0x00, 0x15, 0x1A, 0x09,  // 35:21
  0x00, 0x2F, 0x17, 0x09,  // 36:47
  0x00, 0x46, 0x26, 0x0E,  // 37:70
  0x00, 0x6C, 0x1D, 0x0B,  // 38:108
  0x00, 0x89, 0x04, 0x03,  // 39:137
  0x00, 0x8D, 0x0C, 0x05,  // 40:141
  0x00, 0x99, 0x0B, 0x05,  // 41:153
  0x00, 0xA4, 0x0D, 0x06,  // 42:164
  0x00, 0xB1, 0x17, 0x09,  // 43:177
  0x00, 0xC8, 0x09, 0x04,  // 44:200
  0x00, 0xD1, 0x0B, 0x05,  // 45:209
  0x00, 0xDC, 0x08, 0x04,  // 46:220
  0x00, 0xE4, 0x0A, 0x04,  // 47:228
  0x00, 0xEE, 0x17, 0x09,  // 48:238
  0x01, 0x05, 0x11, 0x09,  // 49:261
  0x01, 0x16, 0x17, 0x09,  // 50:278
  0x01, 0x2D, 0x17, 0x09,  // 51:301
  0x01, 0x44, 0x17, 0x09,  // 52:324
  0x01, 0x5B, 0x17, 0x09,  // 53:347
  0x01, 0x72, 0x17, 0x09,  // 54:370
  0x01, 0x89, 0x16, 0x09,  // 55:393
  0x01, 0x9F, 0x17, 0x09,  // 56:415
  0x01, 0xB6, 0x17, 0x09,  // 57:438
  0x01, 0xCD, 0x05, 0x04,  // 58:461
  0x01, 0xD2, 0x06, 0x04,  // 59:466
  0x01, 0xD8, 0x17, 0x09,  // 60:472
  0x01, 0xEF, 0x17, 0x09,  // 61:495
  0x02, 0x06, 0x17, 0x09,  // 62:518
  0x02, 0x1D, 0x16, 0x09,  // 63:541
  0x02, 0x33, 0x2F, 0x10,  // 64:563
  0x02, 0x62, 0x1D, 0x0B,  // 65:610
  0x02, 0x7F, 0x1D, 0x0B,  // 66:639
  0x02, 0x9C, 0x20, 0x0C,  // 67:668
  0x02, 0xBC, 0x20, 0x0C,  // 68:700
  0x02, 0xDC, 0x1D, 0x0B,  // 69:732
  0x02, 0xF9, 0x19, 0x0A,  // 70:761
  0x03, 0x12, 0x20, 0x0C,  // 71:786
  0x03, 0x32, 0x1D, 0x0C,  // 72:818
  0x03, 0x4F, 0x05, 0x04,  // 73:847
  0x03, 0x54, 0x14, 0x08,  // 74:852
  0x03, 0x68, 0x1D, 0x0B,  // 75:872
  0x03, 0x85, 0x17, 0x09,  // 76:901
  0x03, 0x9C, 0x23, 0x0D,  // 77:924
  0x03, 0xBF, 0x1D, 0x0C,  // 78:959
  0x03, 0xDC, 0x20, 0x0C,  // 79:988
  0x03, 0xFC, 0x1C, 0x0B,  // 80:1020
  0x04, 0x18, 0x20, 0x0C,  // 81:1048
  0x04, 0x38, 0x1D, 0x0C,  // 82:1080
  0x04, 0x55, 0x1D, 0x0B,  // 83:1109
  0x04, 0x72, 0x19, 0x0A,  // 84:1138
  0x04, 0x8B, 0x1D, 0x0C,  // 85:1163
  0x04, 0xA8, 0x1C, 0x0B,  // 86:1192
  0x04, 0xC4, 0x2B, 0x0F,  // 87:1220
  0x04, 0xEF, 0x20, 0x0B,  // 88:1263
  0x05, 0x0F, 0x19, 0x0B,  // 89:1295
  0x05, 0x28, 0x1A, 0x0A,  // 90:1320
  0x05, 0x42, 0x0C, 0x04,  // 91:1346
  0x05, 0x4E, 0x0B, 0x04,  // 92:1358
  0x05, 0x59, 0x09, 0x04,  // 93:1369
  0x05, 0x62, 0x14, 0x08,  // 94:1378
  0x05, 0x76, 0x1B, 0x09,  // 95:1398
  0x05, 0x91, 0x07, 0x05,  // 96:1425
  0x05, 0x98, 0x17, 0x09,  // 97:1432
  0x05, 0xAF, 0x17, 0x09,  // 98:1455
  0x05, 0xC6, 0x14, 0x08,  // 99:1478
  0x05, 0xDA, 0x17, 0x09,  // 100:1498
  0x05, 0xF1, 0x17, 0x09,  // 101:1521
  0x06, 0x08, 0x0A, 0x04,  // 102:1544
  0x06, 0x12, 0x17, 0x09,  // 103:1554
  0x06, 0x29, 0x14, 0x09,  // 104:1577
  0x06, 0x3D, 0x05, 0x04,  // 105:1597
  0x06, 0x42, 0x06, 0x04,  // 106:1602
  0x06, 0x48, 0x17, 0x08,  // 107:1608
  0x06, 0x5F, 0x05, 0x04,  // 108:1631
  0x06, 0x64, 0x23, 0x0D,  // 109:1636
  0x06, 0x87, 0x14, 0x09,  // 110:1671
  0x06, 0x9B, 0x17, 0x09,  // 111:1691
  0x06, 0xB2, 0x17, 0x09,  // 112:1714
  0x06, 0xC9, 0x18, 0x09,  // 113:1737
  0x06, 0xE1, 0x0D, 0x05,  // 114:1761
  0x06, 0xEE, 0x14, 0x08,  // 115:1774
  0x07, 0x02, 0x0B, 0x04,  // 116:1794
  0x07, 0x0D, 0x14, 0x09,  // 117:1805
  0x07, 0x21, 0x13, 0x08,  // 118:1825
  0x07, 0x34, 0x1F, 0x0C,  // 119:1844
  0x07, 0x53, 0x14, 0x08,  // 120:1875
  0x07, 0x67, 0x13, 0x08,  // 121:1895
  0x07, 0x7A, 0x14, 0x08,  // 122:1914
  0x07, 0x8E, 0x0F, 0x05,  // 123:1934
  0x07, 0x9D, 0x06, 0x04,  // 124:1949
  0x07, 0xA3, 0x0E, 0x05,  // 125:1955
  0x07, 0xB1, 0x17, 0x09,  // 126:1969
  
  // Font Data:
  0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x5F,  // 33
  0x00,0x00,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x78, // 34
  0x80,0x08,0x00,0x80,0x78,0x00,0xC0,0x0F,0x00,0xB8,0x08,0x00,0x80,0x08,0x00,0x80,0x78,0x00,0xC0,0x0F,0x00,0xB8,0x08,0x00,0x80,0x08,  // 35
  0x00,0x00,0x00,0xE0,0x10,0x00,0x10,0x21,0x00,0x08,0x41,0x00,0xFC,0xFF,0x00,0x08,0x42,0x00,0x10,0x22,0x00,0x20,0x1C, // 36
  0x00,0x00,0x00,0xF0,0x00,0x00,0x08,0x01,0x00,0x08,0x01,0x00,0x08,0x61,0x00,0xF0,0x18,0x00,0x00,0x06,0x00,0xC0,0x01,0x00,0x30,0x3C,0x00,0x08,0x42,0x00,0x00,0x42,0x00,0x00,0x42,0x00,0x00,0x3C,  // 37
  0x00,0x00,0x00,0x00,0x1C,0x00,0x70,0x22,0x00,0x88,0x41,0x00,0x08,0x43,0x00,0x88,0x44,0x00,0x70,0x28,0x00,0x00,0x10,0x00,0x00,0x28,0x00,0x00,0x44, // 38
  0x00,0x00,0x00,0x78,  // 39
  0x00,0x00,0x00,0x80,0x3F,0x00,0x70,0xC0,0x01,0x08,0x00,0x02,  // 40
  0x00,0x00,0x00,0x08,0x00,0x02,0x70,0xC0,0x01,0x80,0x3F, // 41
  0x10,0x00,0x00,0xD0,0x00,0x00,0x38,0x00,0x00,0xD0,0x00,0x00,0x10, // 42
  0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0xC0,0x1F,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x02, // 43
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x01, // 44
  0x00,0x08,0x00,0x00,0x08,0x00,0x00,0x08,0x00,0x00,0x08, // 45
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,  // 46
  0x00,0x60,0x00,0x00,0x1E,0x00,0xE0,0x01,0x00,0x18,  // 47
  0x00,0x00,0x00,0xE0,0x1F,0x00,0x10,0x20,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x10,0x20,0x00,0xE0,0x1F, // 48
  0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x20,0x00,0x00,0x10,0x00,0x00,0xF8,0x7F, // 49
  0x00,0x00,0x00,0x20,0x40,0x00,0x10,0x60,0x00,0x08,0x50,0x00,0x08,0x48,0x00,0x08,0x44,0x00,0x10,0x43,0x00,0xE0,0x40, // 50
  0x00,0x00,0x00,0x20,0x10,0x00,0x10,0x20,0x00,0x08,0x41,0x00,0x08,0x41,0x00,0x88,0x41,0x00,0xF0,0x22,0x00,0x00,0x1C, // 51
  0x00,0x0C,0x00,0x00,0x0A,0x00,0x00,0x09,0x00,0xC0,0x08,0x00,0x20,0x08,0x00,0x10,0x08,0x00,0xF8,0x7F,0x00,0x00,0x08, // 52
  0x00,0x00,0x00,0xC0,0x11,0x00,0xB8,0x20,0x00,0x88,0x40,0x00,0x88,0x40,0x00,0x88,0x40,0x00,0x08,0x21,0x00,0x08,0x1E, // 53
  0x00,0x00,0x00,0xE0,0x1F,0x00,0x10,0x21,0x00,0x88,0x40,0x00,0x88,0x40,0x00,0x88,0x40,0x00,0x10,0x21,0x00,0x20,0x1E, // 54
  0x00,0x00,0x00,0x08,0x00,0x00,0x08,0x00,0x00,0x08,0x78,0x00,0x08,0x07,0x00,0xC8,0x00,0x00,0x28,0x00,0x00,0x18,  // 55
  0x00,0x00,0x00,0x60,0x1C,0x00,0x90,0x22,0x00,0x08,0x41,0x00,0x08,0x41,0x00,0x08,0x41,0x00,0x90,0x22,0x00,0x60,0x1C, // 56
  0x00,0x00,0x00,0xE0,0x11,0x00,0x10,0x22,0x00,0x08,0x44,0x00,0x08,0x44,0x00,0x08,0x44,0x00,0x10,0x22,0x00,0xE0,0x1F, // 57
  0x00,0x00,0x00,0x40,0x40, // 58
  0x00,0x00,0x00,0x40,0xC0,0x01,  // 59
  0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x05,0x00,0x00,0x05,0x00,0x80,0x08,0x00,0x80,0x08,0x00,0x80,0x08,0x00,0x40,0x10, // 60
  0x00,0x00,0x00,0x80,0x08,0x00,0x80,0x08,0x00,0x80,0x08,0x00,0x80,0x08,0x00,0x80,0x08,0x00,0x80,0x08,0x00,0x80,0x08, // 61
  0x00,0x00,0x00,0x40,0x10,0x00,0x80,0x08,0x00,0x80,0x08,0x00,0x80,0x08,0x00,0x00,0x05,0x00,0x00,0x05,0x00,0x00,0x02, // 62
  0x00,0x00,0x00,0x60,0x00,0x00,0x10,0x00,0x00,0x08,0x00,0x00,0x08,0x5C,0x00,0x08,0x02,0x00,0x10,0x01,0x00,0xE0,  // 63
  0x00,0x00,0x00,0x00,0x3F,0x00,0xC0,0x40,0x00,0x20,0x80,0x00,0x10,0x1E,0x01,0x10,0x21,0x01,0x88,0x40,0x02,0x48,0x40,0x02,0x48,0x40,0x02,0x48,0x20,0x02,0x88,0x7C,0x02,0xC8,0x43,0x02,0x10,0x40,0x02,0x10,0x20,0x01,0x60,0x10,0x01,0x80,0x8F, // 64
  0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x1C,0x00,0x80,0x07,0x00,0x70,0x04,0x00,0x08,0x04,0x00,0x70,0x04,0x00,0x80,0x07,0x00,0x00,0x1C,0x00,0x00,0x60, // 65
  0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x41,0x00,0x08,0x41,0x00,0x08,0x41,0x00,0x08,0x41,0x00,0x08,0x41,0x00,0x08,0x41,0x00,0x90,0x22,0x00,0x60,0x1C, // 66
  0x00,0x00,0x00,0xC0,0x0F,0x00,0x20,0x10,0x00,0x10,0x20,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x10,0x20,0x00,0x20,0x10,  // 67
  0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x10,0x20,0x00,0x20,0x10,0x00,0xC0,0x0F,  // 68
  0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x41,0x00,0x08,0x41,0x00,0x08,0x41,0x00,0x08,0x41,0x00,0x08,0x41,0x00,0x08,0x41,0x00,0x08,0x41,0x00,0x08,0x40, // 69
  0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x02,0x00,0x08,0x02,0x00,0x08,0x02,0x00,0x08,0x02,0x00,0x08,0x02,0x00,0x08,0x02,0x00,0x08, // 70
  0x00,0x00,0x00,0xC0,0x0F,0x00,0x20,0x10,0x00,0x10,0x20,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x42,0x00,0x08,0x42,0x00,0x10,0x22,0x00,0x20,0x12,0x00,0x00,0x0E,  // 71
  0x00,0x00,0x00,0xF8,0x7F,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0xF8,0x7F, // 72
  0x00,0x00,0x00,0xF8,0x7F, // 73
  0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0xF8,0x3F,  // 74
  0x00,0x00,0x00,0xF8,0x7F,0x00,0x00,0x04,0x00,0x00,0x02,0x00,0x00,0x01,0x00,0x80,0x03,0x00,0x40,0x04,0x00,0x20,0x18,0x00,0x10,0x20,0x00,0x08,0x40, // 75
  0x00,0x00,0x00,0xF8,0x7F,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,0x40, // 76
  0x00,0x00,0x00,0xF8,0x7F,0x00,0x30,0x00,0x00,0xC0,0x00,0x00,0x00,0x03,0x00,0x00,0x1C,0x00,0x00,0x60,0x00,0x00,0x1C,0x00,0x00,0x03,0x00,0xC0,0x00,0x00,0x30,0x00,0x00,0xF8,0x7F, // 77
  0x00,0x00,0x00,0xF8,0x7F,0x00,0x10,0x00,0x00,0x60,0x00,0x00,0x80,0x00,0x00,0x00,0x03,0x00,0x00,0x04,0x00,0x00,0x18,0x00,0x00,0x20,0x00,0xF8,0x7F, // 78
  0x00,0x00,0x00,0xC0,0x0F,0x00,0x20,0x10,0x00,0x10,0x20,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x10,0x20,0x00,0x20,0x10,0x00,0xC0,0x0F,  // 79
  0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x02,0x00,0x08,0x02,0x00,0x08,0x02,0x00,0x08,0x02,0x00,0x08,0x02,0x00,0x08,0x02,0x00,0x10,0x01,0x00,0xE0,  // 80
  0x00,0x00,0x00,0xC0,0x0F,0x00,0x20,0x10,0x00,0x10,0x20,0x00,0x08,0x40,0x00,0x08,0x40,0x00,0x08,0x50,0x00,0x08,0x50,0x00,0x10,0x20,0x00,0x20,0x70,0x00,0xC0,0x4F,  // 81
  0x00,0x00,0x00,0xF8,0x7F,0x00,0x08,0x02,0x00,0x08,0x02,0x00,0x08,0x02,0x00,0x08,0x02,0x00,0x08,0x06,0x00,0x08,0x1A,0x00,0x10,0x21,0x00,0xE0,0x40, // 82
  0x00,0x00,0x00,0x60,0x10,0x00,0x90,0x20,0x00,0x08,0x41,0x00,0x08,0x41,0x00,0x08,0x41,0x00,0x08,0x42,0x00,0x08,0x42,0x00,0x10,0x22,0x00,0x20,0x1C, // 83
  0x08,0x00,0x00,0x08,0x00,0x00,0x08,0x00,0x00,0x08,0x00,0x00,0xF8,0x7F,0x00,0x08,0x00,0x00,0x08,0x00,0x00,0x08,0x00,0x00,0x08, // 84
  0x00,0x00,0x00,0xF8,0x1F,0x00,0x00,0x20,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,0x20,0x00,0xF8,0x1F, // 85
  0x00,0x00,0x00,0x18,0x00,0x00,0xE0,0x00,0x00,0x00,0x07,0x00,0x00,0x18,0x00,0x00,0x60,0x00,0x00,0x18,0x00,0x00,0x07,0x00,0xE0,0x00,0x00,0x18,  // 86
  0x18,0x00,0x00,0xE0,0x01,0x00,0x00,0x1E,0x00,0x00,0x60,0x00,0x00,0x1C,0x00,0x80,0x03,0x00,0x70,0x00,0x00,0x08,0x00,0x00,0x70,0x00,0x00,0x80,0x03,0x00,0x00,0x1C,0x00,0x00,0x60,0x00,0x00,0x1E,0x00,0xE0,0x01,0x00,0x18, // 87
  0x00,0x40,0x00,0x08,0x20,0x00,0x10,0x10,0x00,0x60,0x0C,0x00,0x80,0x02,0x00,0x00,0x01,0x00,0x80,0x02,0x00,0x60,0x0C,0x00,0x10,0x10,0x00,0x08,0x20,0x00,0x00,0x40,  // 88
  0x08,0x00,0x00,0x30,0x00,0x00,0x40,0x00,0x00,0x80,0x01,0x00,0x00,0x7E,0x00,0x80,0x01,0x00,0x40,0x00,0x00,0x30,0x00,0x00,0x08, // 89
  0x00,0x40,0x00,0x08,0x60,0x00,0x08,0x58,0x00,0x08,0x44,0x00,0x08,0x43,0x00,0x88,0x40,0x00,0x68,0x40,0x00,0x18,0x40,0x00,0x08,0x40,  // 90
  0x00,0x00,0x00,0xF8,0xFF,0x03,0x08,0x00,0x02,0x08,0x00,0x02,  // 91
  0x18,0x00,0x00,0xE0,0x01,0x00,0x00,0x1E,0x00,0x00,0x60, // 92
  0x08,0x00,0x02,0x08,0x00,0x02,0xF8,0xFF,0x03, // 93
  0x00,0x01,0x00,0xC0,0x00,0x00,0x30,0x00,0x00,0x08,0x00,0x00,0x30,0x00,0x00,0xC0,0x00,0x00,0x00,0x01,  // 94
  0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x02, // 95
  0x00,0x00,0x00,0x08,0x00,0x00,0x10, // 96
  0x00,0x00,0x00,0x00,0x39,0x00,0x80,0x44,0x00,0x40,0x44,0x00,0x40,0x44,0x00,0x40,0x42,0x00,0x40,0x22,0x00,0x80,0x7F, // 97
  0x00,0x00,0x00,0xF8,0x7F,0x00,0x80,0x20,0x00,0x40,0x40,0x00,0x40,0x40,0x00,0x40,0x40,0x00,0x80,0x20,0x00,0x00,0x1F, // 98
  0x00,0x00,0x00,0x00,0x1F,0x00,0x80,0x20,0x00,0x40,0x40,0x00,0x40,0x40,0x00,0x40,0x40,0x00,0x80,0x20,  // 99
  0x00,0x00,0x00,0x00,0x1F,0x00,0x80,0x20,0x00,0x40,0x40,0x00,0x40,0x40,0x00,0x40,0x40,0x00,0x80,0x20,0x00,0xF8,0x7F, // 100
  0x00,0x00,0x00,0x00,0x1F,0x00,0x80,0x24,0x00,0x40,0x44,0x00,0x40,0x44,0x00,0x40,0x44,0x00,0x80,0x24,0x00,0x00,0x17, // 101
  0x40,0x00,0x00,0xF0,0x7F,0x00,0x48,0x00,0x00,0x48,  // 102
  0x00,0x00,0x00,0x00,0x1F,0x01,0x80,0x20,0x02,0x40,0x40,0x02,0x40,0x40,0x02,0x40,0x40,0x02,0x80,0x20,0x01,0xC0,0xFF, // 103
  0x00,0x00,0x00,0xF8,0x7F,0x00,0x80,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,0x80,0x7F,  // 104
  0x00,0x00,0x00,0xC8,0x7F, // 105
  0x00,0x00,0x02,0xC8,0xFF,0x01,  // 106
  0x00,0x00,0x00,0xF8,0x7F,0x00,0x00,0x08,0x00,0x00,0x04,0x00,0x00,0x06,0x00,0x00,0x19,0x00,0x80,0x20,0x00,0x40,0x40, // 107
  0x00,0x00,0x00,0xF8,0x7F, // 108
  0x00,0x00,0x00,0xC0,0x7F,0x00,0x80,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,0x80,0x7F,0x00,0x80,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,0x80,0x7F, // 109
  0x00,0x00,0x00,0xC0,0x7F,0x00,0x80,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,0x80,0x7F,  // 110
  0x00,0x00,0x00,0x00,0x1F,0x00,0x80,0x20,0x00,0x40,0x40,0x00,0x40,0x40,0x00,0x40,0x40,0x00,0x80,0x20,0x00,0x00,0x1F, // 111
  0x00,0x00,0x00,0xC0,0xFF,0x03,0x80,0x20,0x00,0x40,0x40,0x00,0x40,0x40,0x00,0x40,0x40,0x00,0x80,0x20,0x00,0x00,0x1F, // 112
  0x00,0x00,0x00,0x00,0x1F,0x00,0x80,0x20,0x00,0x40,0x40,0x00,0x40,0x40,0x00,0x40,0x40,0x00,0x80,0x20,0x00,0xC0,0xFF,0x03,  // 113
  0x00,0x00,0x00,0xC0,0x7F,0x00,0x80,0x00,0x00,0x40,0x00,0x00,0x40, // 114
  0x00,0x00,0x00,0x80,0x23,0x00,0x40,0x44,0x00,0x40,0x44,0x00,0x40,0x44,0x00,0x40,0x44,0x00,0x80,0x38,  // 115
  0x40,0x00,0x00,0xF0,0x7F,0x00,0x40,0x40,0x00,0x40,0x40, // 116
  0x00,0x00,0x00,0xC0,0x3F,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,0x20,0x00,0xC0,0x7F,  // 117
  0xC0,0x00,0x00,0x00,0x03,0x00,0x00,0x1C,0x00,0x00,0x60,0x00,0x00,0x1C,0x00,0x00,0x03,0x00,0xC0, // 118
  0xC0,0x00,0x00,0x00,0x1F,0x00,0x00,0x60,0x00,0x00,0x1C,0x00,0x00,0x03,0x00,0xC0,0x00,0x00,0x00,0x03,0x00,0x00,0x1C,0x00,0x00,0x60,0x00,0x00,0x1F,0x00,0xC0, // 119
  0x40,0x40,0x00,0x80,0x20,0x00,0x00,0x1B,0x00,0x00,0x04,0x00,0x00,0x1B,0x00,0x80,0x20,0x00,0x40,0x40,  // 120
  0xC0,0x01,0x00,0x00,0x06,0x02,0x00,0x38,0x02,0x00,0xE0,0x01,0x00,0x38,0x00,0x00,0x07,0x00,0xC0, // 121
  0x40,0x40,0x00,0x40,0x60,0x00,0x40,0x58,0x00,0x40,0x44,0x00,0x40,0x43,0x00,0xC0,0x40,0x00,0x40,0x40,  // 122
  0x00,0x04,0x00,0x00,0x04,0x00,0xF0,0xFB,0x01,0x08,0x00,0x02,0x08,0x00,0x02, // 123
  0x00,0x00,0x00,0xF8,0xFF,0x03,  // 124
  0x08,0x00,0x02,0x08,0x00,0x02,0xF0,0xFB,0x01,0x00,0x04,0x00,0x00,0x04,  // 125
  0x00,0x02,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x01 // 126
};

const char Noto_Sans_8[] PROGMEM = {
	0x09, // Width: 9
	0x0C, // Height: 12
	0x20, // First Char: 32
    0x5F, // Numbers of Chars: 95

	// Jump Table:
	0xFF, 0xFF, 0x00, 0x02,  // 32:65535
	0x00, 0x00, 0x04, 0x03,  // 33:0
	0x00, 0x04, 0x05, 0x03,  // 34:4
	0x00, 0x09, 0x09, 0x05,  // 35:9
	0x00, 0x12, 0x09, 0x06,  // 36:18
	0x00, 0x1B, 0x0E, 0x08,  // 37:27
	0x00, 0x29, 0x0E, 0x07,  // 38:41
	0x00, 0x37, 0x01, 0x02,  // 39:55
	0x00, 0x38, 0x06, 0x03,  // 40:56
	0x00, 0x3E, 0x04, 0x03,  // 41:62
	0x00, 0x42, 0x07, 0x04,  // 42:66
	0x00, 0x49, 0x09, 0x05,  // 43:73
	0x00, 0x52, 0x02, 0x02,  // 44:82
	0x00, 0x54, 0x03, 0x03,  // 45:84
	0x00, 0x57, 0x04, 0x02,  // 46:87
	0x00, 0x5B, 0x05, 0x03,  // 47:91
	0x00, 0x60, 0x09, 0x06,  // 48:96
	0x00, 0x69, 0x06, 0x05,  // 49:105
	0x00, 0x6F, 0x0A, 0x06,  // 50:111
	0x00, 0x79, 0x07, 0x05,  // 51:121
	0x00, 0x80, 0x09, 0x05,  // 52:128
	0x00, 0x89, 0x07, 0x05,  // 53:137
	0x00, 0x90, 0x09, 0x06,  // 54:144
	0x00, 0x99, 0x07, 0x05,  // 55:153
	0x00, 0xA0, 0x09, 0x06,  // 56:160
	0x00, 0xA9, 0x09, 0x06,  // 57:169
	0x00, 0xB2, 0x04, 0x02,  // 58:178
	0x00, 0xB6, 0x04, 0x02,  // 59:182
	0x00, 0xBA, 0x09, 0x06,  // 60:186
	0x00, 0xC3, 0x07, 0x05,  // 61:195
	0x00, 0xCA, 0x09, 0x06,  // 62:202
	0x00, 0xD3, 0x05, 0x04,  // 63:211
	0x00, 0xD8, 0x0D, 0x08,  // 64:216
	0x00, 0xE5, 0x0A, 0x05,  // 65:229
	0x00, 0xEF, 0x09, 0x06,  // 66:239
	0x00, 0xF8, 0x0B, 0x06,  // 67:248
	0x01, 0x03, 0x0B, 0x07,  // 68:259
	0x01, 0x0E, 0x08, 0x05,  // 69:270
	0x01, 0x16, 0x07, 0x05,  // 70:278
	0x01, 0x1D, 0x0C, 0x07,  // 71:285
	0x01, 0x29, 0x0C, 0x07,  // 72:297
	0x01, 0x35, 0x06, 0x03,  // 73:309
	0x01, 0x3B, 0x04, 0x03,  // 74:315
	0x01, 0x3F, 0x0A, 0x05,  // 75:319
	0x01, 0x49, 0x0A, 0x05,  // 76:329
	0x01, 0x53, 0x0E, 0x08,  // 77:339
	0x01, 0x61, 0x0C, 0x07,  // 78:353
	0x01, 0x6D, 0x0B, 0x07,  // 79:365
	0x01, 0x78, 0x09, 0x06,  // 80:376
	0x01, 0x81, 0x0C, 0x07,  // 81:385
	0x01, 0x8D, 0x0A, 0x06,  // 82:397
	0x01, 0x97, 0x09, 0x06,  // 83:407
	0x01, 0xA0, 0x09, 0x05,  // 84:416
	0x01, 0xA9, 0x0B, 0x07,  // 85:425
	0x01, 0xB4, 0x09, 0x05,  // 86:436
	0x01, 0xBD, 0x0D, 0x07,  // 87:445
	0x01, 0xCA, 0x08, 0x05,  // 88:458
	0x01, 0xD2, 0x09, 0x05,  // 89:466
	0x01, 0xDB, 0x0A, 0x06,  // 90:475
	0x01, 0xE5, 0x06, 0x03,  // 91:485
	0x01, 0xEB, 0x06, 0x03,  // 92:491
	0x01, 0xF1, 0x04, 0x03,  // 93:497
	0x01, 0xF5, 0x07, 0x05,  // 94:501
	0x01, 0xFC, 0x08, 0x04,  // 95:508
	0x02, 0x04, 0x05, 0x05,  // 96:516
	0x02, 0x09, 0x0A, 0x06,  // 97:521
	0x02, 0x13, 0x09, 0x06,  // 98:531
	0x02, 0x1C, 0x08, 0x05,  // 99:540
	0x02, 0x24, 0x0A, 0x06,  // 100:548
	0x02, 0x2E, 0x0A, 0x06,  // 101:558
	0x02, 0x38, 0x05, 0x03,  // 102:568
	0x02, 0x3D, 0x0A, 0x06,  // 103:573
	0x02, 0x47, 0x0A, 0x06,  // 104:583
	0x02, 0x51, 0x04, 0x03,  // 105:593
	0x02, 0x55, 0x04, 0x03,  // 106:597
	0x02, 0x59, 0x08, 0x05,  // 107:601
	0x02, 0x61, 0x04, 0x03,  // 108:609
	0x02, 0x65, 0x10, 0x09,  // 109:613
	0x02, 0x75, 0x0A, 0x06,  // 110:629
	0x02, 0x7F, 0x09, 0x06,  // 111:639
	0x02, 0x88, 0x09, 0x06,  // 112:648
	0x02, 0x91, 0x0A, 0x06,  // 113:657
	0x02, 0x9B, 0x07, 0x04,  // 114:667
	0x02, 0xA2, 0x08, 0x05,  // 115:674
	0x02, 0xAA, 0x06, 0x03,  // 116:682
	0x02, 0xB0, 0x0A, 0x06,  // 117:688
	0x02, 0xBA, 0x07, 0x04,  // 118:698
	0x02, 0xC1, 0x0B, 0x06,  // 119:705
	0x02, 0xCC, 0x08, 0x04,  // 120:716
	0x02, 0xD4, 0x07, 0x04,  // 121:724
	0x02, 0xDB, 0x08, 0x05,  // 122:731
	0x02, 0xE3, 0x06, 0x03,  // 123:739
	0x02, 0xE9, 0x06, 0x05,  // 124:745
	0x02, 0xEF, 0x05, 0x03,  // 125:751
	0x02, 0xF4, 0x07, 0x05,  // 126:756

	// Font Data:
	0x00,0x00,0x3C,0x01,	// 33
	0x0C,0x00,0x00,0x00,0x0C,	// 34
	0x50,0x00,0xFC,0x01,0xD0,0x01,0x7C,0x00,0x50,	// 35
	0x00,0x00,0x98,0x00,0xFC,0x01,0xA8,0x00,0x48,	// 36
	0x00,0x00,0x7C,0x00,0xC4,0x01,0x78,0x00,0xFC,0x01,0x20,0x01,0xE0,0x01,	// 37
	0x00,0x00,0xDC,0x01,0x24,0x01,0x64,0x01,0x5C,0x01,0x80,0x00,0x40,0x01,	// 38
	0x0C,	// 39
	0x00,0x00,0xF8,0x01,0x04,0x02,	// 40
	0x0C,0x02,0xF0,0x01,	// 41
	0x08,0x00,0x28,0x00,0x34,0x00,0x08,	// 42
	0x20,0x00,0x20,0x00,0xF0,0x00,0x20,0x00,0x20,	// 43
	0x00,0x03,	// 44
	0x40,0x00,0x40,	// 45
	0x00,0x00,0x00,0x01,	// 46
	0x80,0x01,0x78,0x00,0x04,	// 47
	0x00,0x00,0xF8,0x00,0x04,0x01,0x04,0x01,0xF8,	// 48
	0x08,0x00,0x08,0x00,0xFC,0x01,	// 49
	0x00,0x00,0x88,0x01,0x44,0x01,0x24,0x01,0x18,0x01,	// 50
	0x00,0x01,0x24,0x01,0x24,0x01,0xDC,	// 51
	0xC0,0x00,0xB0,0x00,0x88,0x00,0xFC,0x01,0x80,	// 52
	0x3C,0x01,0x24,0x01,0x24,0x01,0xC0,	// 53
	0x00,0x00,0xF8,0x00,0x2C,0x01,0x24,0x01,0xE0,	// 54
	0x04,0x00,0x84,0x01,0x74,0x00,0x0C,	// 55
	0x00,0x00,0xDC,0x00,0x24,0x01,0x24,0x01,0xDC,	// 56
	0x00,0x00,0x38,0x00,0x44,0x01,0xC4,0x01,0xF8,	// 57
	0x00,0x00,0x10,0x01,	// 58
	0x00,0x02,0x10,0x01,	// 59
	0x00,0x00,0x20,0x00,0x60,0x00,0x90,0x00,0x90,	// 60
	0x50,0x00,0x50,0x00,0x50,0x00,0x50,	// 61
	0x00,0x00,0x90,0x00,0x90,0x00,0x60,0x00,0x20,	// 62
	0x44,0x01,0x24,0x00,0x1C,	// 63
	0x00,0x00,0xF0,0x01,0xE8,0x03,0x94,0x02,0x94,0x02,0xFC,0x02,0xF8,	// 64
	0x80,0x01,0x78,0x00,0x4C,0x00,0x70,0x00,0x80,0x01,	// 65
	0x00,0x00,0xFC,0x01,0x24,0x01,0x24,0x01,0xDC,	// 66
	0x00,0x00,0xF8,0x00,0x8C,0x01,0x04,0x01,0x04,0x01,0x04,	// 67
	0x00,0x00,0xFC,0x01,0x04,0x01,0x04,0x01,0x8C,0x01,0xF8,	// 68
	0x00,0x00,0xFC,0x01,0x24,0x01,0x24,0x01,	// 69
	0x00,0x00,0xFC,0x01,0x24,0x00,0x24,	// 70
	0x00,0x00,0xF8,0x00,0x8C,0x01,0x04,0x01,0x24,0x01,0xE4,0x01,	// 71
	0x00,0x00,0xFC,0x01,0x20,0x00,0x20,0x00,0x20,0x00,0xFC,0x01,	// 72
	0x04,0x01,0xFC,0x01,0x04,0x01,	// 73
	0x00,0x02,0xFC,0x03,	// 74
	0x00,0x00,0xFC,0x01,0x20,0x00,0x58,0x00,0x84,0x01,	// 75
	0x00,0x00,0xFC,0x01,0x00,0x01,0x00,0x01,0x00,0x01,	// 76
	0x00,0x00,0xFC,0x01,0x3C,0x00,0xC0,0x01,0xE0,0x00,0x1C,0x00,0xFC,0x01,	// 77
	0x00,0x00,0xFC,0x01,0x18,0x00,0x60,0x00,0x80,0x00,0xFC,0x01,	// 78
	0x00,0x00,0xF8,0x00,0x8C,0x01,0x04,0x01,0x8C,0x01,0xF8,	// 79
	0x00,0x00,0xFC,0x01,0x44,0x00,0x44,0x00,0x38,	// 80
	0x00,0x00,0xF8,0x00,0x8C,0x01,0x04,0x01,0x8C,0x03,0xF8,0x04,	// 81
	0x00,0x00,0xFC,0x01,0x24,0x00,0x64,0x00,0x98,0x01,	// 82
	0x00,0x00,0x18,0x01,0x24,0x01,0x24,0x01,0xC4,	// 83
	0x04,0x00,0x04,0x00,0xFC,0x01,0x04,0x00,0x04,	// 84
	0x00,0x00,0xFC,0x00,0x00,0x01,0x00,0x01,0x00,0x01,0xFC,	// 85
	0x1C,0x00,0x60,0x00,0x80,0x01,0x78,0x00,0x04,	// 86
	0x1C,0x00,0xE0,0x01,0xF0,0x00,0x0C,0x00,0x70,0x00,0xC0,0x01,0x3C,	// 87
	0x04,0x01,0xD8,0x00,0x70,0x00,0x8C,0x01,	// 88
	0x04,0x00,0x18,0x00,0xE0,0x01,0x18,0x00,0x04,	// 89
	0x00,0x00,0x84,0x01,0x64,0x01,0x14,0x01,0x0C,0x01,	// 90
	0x00,0x00,0xFC,0x03,0x04,0x02,	// 91
	0x0C,0x00,0xF0,0x00,0x00,0x01,	// 92
	0x04,0x02,0xFC,0x03,	// 93
	0x20,0x00,0x18,0x00,0x0C,0x00,0x30,	// 94
	0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x04,	// 95
	0x00,0x00,0x00,0x00,0x04,	// 96
	0x00,0x00,0xC0,0x01,0x50,0x01,0x50,0x01,0xF0,0x01,	// 97
	0x00,0x00,0xFC,0x01,0x10,0x01,0x10,0x01,0xE0,	// 98
	0x00,0x00,0xE0,0x00,0x10,0x01,0x10,0x01,	// 99
	0x00,0x00,0xE0,0x00,0x10,0x01,0x10,0x01,0xFC,0x01,	// 100
	0x00,0x00,0xE0,0x00,0x50,0x01,0x50,0x01,0x60,0x01,	// 101
	0x10,0x00,0xFC,0x01,0x14,	// 102
	0x00,0x00,0xE0,0x04,0x10,0x05,0x10,0x05,0xF0,0x07,	// 103
	0x00,0x00,0xFC,0x01,0x10,0x00,0x10,0x00,0xF0,0x01,	// 104
	0x04,0x00,0xF0,0x01,	// 105
	0x04,0x04,0xF0,0x07,	// 106
	0x00,0x00,0xFC,0x01,0x40,0x00,0xB0,0x01,	// 107
	0x00,0x00,0xFC,0x01,	// 108
	0x00,0x00,0xF0,0x01,0x10,0x00,0x10,0x00,0xF0,0x01,0x10,0x00,0x10,0x00,0xF0,0x01,	// 109
	0x00,0x00,0xF0,0x01,0x10,0x00,0x10,0x00,0xF0,0x01,	// 110
	0x00,0x00,0xE0,0x00,0x10,0x01,0x10,0x01,0xE0,	// 111
	0x00,0x00,0xF0,0x07,0x10,0x01,0x10,0x01,0xE0,	// 112
	0x00,0x00,0xE0,0x00,0x10,0x01,0x10,0x01,0xF0,0x07,	// 113
	0x00,0x00,0xF0,0x01,0x10,0x00,0x10,	// 114
	0x20,0x00,0x50,0x01,0x50,0x01,0x90,0x01,	// 115
	0x10,0x00,0xF8,0x01,0x10,0x01,	// 116
	0x00,0x00,0xF0,0x01,0x00,0x01,0x00,0x01,0xF0,0x01,	// 117
	0x30,0x00,0xC0,0x01,0xC0,0x01,0x30,	// 118
	0x70,0x00,0x80,0x01,0xE0,0x00,0xF0,0x00,0x80,0x01,0x70,	// 119
	0x10,0x01,0xA0,0x00,0xE0,0x00,0x10,0x01,	// 120
	0x30,0x04,0xC0,0x06,0xC0,0x01,0x30,	// 121
	0x00,0x00,0x90,0x01,0x50,0x01,0x30,0x01,	// 122
	0x40,0x00,0xBC,0x03,0x04,0x02,	// 123
	0x00,0x00,0x00,0x00,0xFC,0x07,	// 124
	0x04,0x02,0xBC,0x03,0x40,	// 125
	0x40,0x00,0x40,0x00,0x40,0x00,0x40	// 126
};


#endif 
