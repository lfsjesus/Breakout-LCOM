#ifndef __VBE
#define __VBE

#define VBE_768p_INDEX 0x105
#define VBE_480p_DC 0x110
#define VBE_600p_DC 0x115
#define VBE_1024p_DC 0x11A
#define VBE_864p_DC 0x14C

#define VBE_MODE_SET 0x4F02
#define VBE_LIENAR_FB BIT(14)

#define DIRECT_COLOR 0x06
#define INDEXED_COLOR 0x105

#define BIOS_SET_VIDEOMODE 0x00
#define BIOS_VIDEOCARD_SERV 0x10

#endif
