
#include <string.h>

typedef unsigned char byte;
typedef unsigned short word;
typedef signed char sbyte;

byte __at (0x4800) vram[32][32];
byte __at (0x4800) vramflat[32*32];

struct {
  byte scroll;
  byte attrib;
} __at (0x5000) columns[32];

struct {
  byte xpos;
  byte code;
  byte color;
  byte ypos;
} __at (0x5040) sprites[8];

struct {
  signed char dx; // unused by h/w
  byte xpos;
  signed char dy; // unused by h/w
  byte ypos;
} __at (0x5060) missiles[8];

byte __at (0x5080) xram[128];

byte __at (0x6801) enable_irq;
byte __at (0x6804) enable_stars;
byte __at (0x6808) missile_width;
byte __at (0x6809) missile_offset;
byte __at (0x7000) watchdog;
byte __at (0x8100) input0;
byte __at (0x8101) input1;
byte __at (0x8102) input2;

#define LEFT1 !(input0 & 0x20)
#define RIGHT1 !(input0 & 0x10)
#define UP1 !(input0 & 0x1)
#define DOWN1 !(input2 & 0x40)
#define FIRE1 !(input0 & 0x8)
#define BOMB1 !(input0 & 0x2)
#define COIN1 !(input0 & 0x80)
#define COIN2 !(input0 & 0x40)
#define START1 !(input1 & 0x80)
#define START2 !(input1 & 0x40)

__sfr __at (0x1) ay8910_a_reg;
__sfr __at (0x2) ay8910_a_data;
__sfr __at (0x4) ay8910_b_reg;
__sfr __at (0x8) ay8910_b_data;

inline void set8910a(byte reg, byte data) {
  ay8910_a_reg = reg;
  ay8910_a_data = data;
}
inline void set8910b(byte reg, byte data) {
  ay8910_b_reg = reg;
  ay8910_b_data = data;
}

typedef enum {
  AY_PITCH_A_LO, AY_PITCH_A_HI,
  AY_PITCH_B_LO, AY_PITCH_B_HI,
  AY_PITCH_C_LO, AY_PITCH_C_HI,
  AY_NOISE_PERIOD,
  AY_ENABLE,
  AY_ENV_VOL_A,
  AY_ENV_VOL_B,
  AY_ENV_VOL_C,
  AY_ENV_PERI_LO, AY_ENV_PERI_HI,
  AY_ENV_SHAPE
} AY8910Register;

///

void main();

void start() {
__asm
	LD      SP,#0x4800
        EI
; copy initialized data to RAM
        LD    BC, #l__INITIALIZER+1
        LD    A, B
        LD    DE, #s__INITIALIZED
        LD    HL, #s__INITIALIZER
        LDIR
__endasm;
	main();
}

const char __at (0x4000) tilerom[0x1000] = {/*{w:16,h:16,remap:[3,0,1,2,4,5,6,7,8,9,10],brev:1,np:2,pofs:2048,count:64}*/
0xFE,0xFE,0xA2,0x92,0xFE,0xFE,0x0E,0x00,0x02,0x02,0xFE,0xFE,0x4E,0x02,0x00,0x00,0x66,0xF6,0x92,0x8A,0xCE,0x46,0x06,0x00,0xEE,0xFE,0x92,0x92,0xC6,0xC6,0x06,0x00,0x08,0xFE,0xFE,0x08,0x08,0x38,0x38,0x00,0x9E,0x9E,0x92,0x92,0xF6,0xF6,0x06,0x00,0xDE,0xDE,0x92,0x92,0xFE,0xFE,0x0E,0x00,0xC0,0xE0,0xB0,0x9E,0xCE,0xC0,0xC0,0x00,0xFE,0xFE,0x92,0x92,0xFE,0xFE,0x0E,0x00,0xFE,0xFE,0x92,0x92,0xF6,0xF6,0x06,0x00,0xFE,0xFE,0x90,0x90,0xFE,0xFE,0x0E,0x00,0x6C,0xFE,0x92,0x92,0xFE,0xFE,0x0E,0x00,0xC6,0xC6,0x82,0x82,0xFE,0xFE,0x0E,0x00,0x3E,0x7E,0xC2,0x82,0xFE,0xFE,0x0E,0x00,0xC6,0x82,0x92,0x92,0xFE,0xFE,0x0E,0x00,0x80,0x80,0x90,0x90,0xFE,0xFE,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0xFE,0x90,0x90,0xFE,0xFE,0x0E,0x00,0x6C,0xFE,0x92,0x92,0xFE,0xFE,0x0E,0x00,0xC6,0xC6,0x82,0x82,0xFE,0xFE,0x0E,0x00,0x3E,0x7E,0x82,0x82,0xFE,0xFE,0x0E,0x00,0xC6,0x82,0x92,0x92,0xFE,0xFE,0x0E,0x00,0x80,0x80,0x90,0x90,0xFE,0xFE,0x0E,0x00,0xDE,0xDE,0x92,0x82,0xFE,0xFE,0x0E,0x00,0xFE,0xFE,0x10,0x10,0xFE,0xFE,0x0E,0x00,0x00,0x82,0xFE,0xFE,0x8E,0x82,0x00,0x00,0x00,0x8E,0xFE,0xFE,0x82,0x06,0x06,0x00,0x82,0xC6,0x6C,0x38,0xFE,0xFE,0x0E,0x00,0x06,0x02,0x02,0x02,0xFE,0xFE,0x0E,0x00,0xFE,0xFE,0x62,0x30,0x60,0xFE,0xFE,0x00,0xFE,0xFE,0x38,0x70,0xFE,0xFE,0x0E,0x00,0xFE,0xFE,0x82,0x82,0xFE,0xFE,0x0E,0x00,
0xF0,0xF0,0x90,0x90,0xFE,0xFE,0x0E,0x00,0xFF,0xFE,0x86,0x82,0xFE,0xFE,0x0E,0x00,0x62,0xF6,0x9C,0x98,0xFE,0xFE,0x0E,0x00,0xDE,0xDE,0x92,0x92,0xF2,0xF6,0x06,0x00,0x00,0x80,0x80,0xFE,0xFE,0x8E,0x80,0x00,0xFE,0xFE,0x02,0x02,0xFE,0xFE,0x0E,0x00,0xF8,0xFC,0x06,0x06,0xFC,0xF8,0x70,0x00,0xFE,0xFE,0x0C,0x18,0x8C,0xFE,0xFE,0x00,0xC6,0xEE,0x38,0x38,0xEE,0xC6,0x06,0x00,0x00,0xC0,0xE0,0x3E,0x3E,0xEE,0xC0,0x00,0xC6,0xE2,0xB2,0x9A,0x8E,0xC6,0x06,0x00,0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0xFF,0x81,0x81,0x99,0x99,0x81,0x81,0xFF,0x00,0x00,0x40,0x20,0x30,0x48,0x08,0x08,0x20,0x24,0x18,0x08,0x07,0x00,0x00,0x00,0x08,0x48,0x30,0x20,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x80,0x80,0x78,0x7E,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x78,0x80,0x80,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x28,0x07,0x07,0x03,0x00,0x00,0x00,0x00,0x00,0x80,0xE0,0xF0,0x07,0x07,0x28,0x10,0x00,0x00,0x00,0x00,0xE0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x04,0x03,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x80,0xE0,0xE0,0x07,0x27,0x18,0x00,0x00,0x00,0x00,0x00,0xF0,0xF8,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x04,0x02,0x03,0x07,0x27,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xE0,0x3F,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xF0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x01,0x01,0x01,0x23,0x3F,0x07,0x00,0x00,0x00,0x00,0x80,0xC0,0xC0,0xE0,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x13,0x1F,0x07,0x03,0x00,0x00,0x80,0x80,0x80,0xC0,0xE0,0xF0,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xE0,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x10,0x09,0x0F,0x07,0x07,0x00,0x80,0x40,0x80,0x80,0xC0,0xC0,0xC0,0x03,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x08,0x04,0x03,0x03,0x03,0x00,0x00,0x10,0x08,0x10,0x60,0xE0,0xE0,0x03,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0xE0,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,
0x00,0x00,0x03,0x00,0x00,0x00,0xE7,0x20,0x00,0x00,0xFF,0x20,0x70,0x60,0x90,0x00,0xE7,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x90,0x60,0x70,0x20,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x0B,0x04,0x05,0x0F,0x00,0x00,0x00,0x00,0x80,0xE0,0xA0,0xB0,0x05,0x06,0x0B,0x10,0x00,0x00,0x00,0x00,0xA0,0x60,0xE0,0x00,0x00,0x00,0x00,0x00,0x10,0x08,0x05,0x21,0x10,0x08,0x41,0x1B,0x00,0x20,0x80,0x20,0x64,0x08,0x80,0x90,0x01,0x28,0x50,0x11,0x25,0x04,0x08,0x00,0x88,0x04,0x64,0x20,0x80,0x08,0x04,0x00,0x08,0x80,0xC1,0x02,0x14,0x00,0x40,0xC0,0x11,0x03,0x86,0x10,0x00,0x20,0x03,0x16,0x80,0x00,0x14,0x02,0x01,0xC0,0x84,0x04,0x00,0x20,0x00,0x10,0x83,0x01,0x30,0x18,0x00,0x00,0x00,0x10,0x04,0x26,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x40,0x00,0x30,0x00,0x26,0x04,0x10,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x80,0x80,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x02,0x04,0x08,0x11,0x29,0x00,0x00,0x00,0x00,0x00,0x20,0x14,0x00,0x04,0x00,0x00,0x81,0x01,0x01,0x08,0x00,0x01,0x81,0x00,0x00,0x43,0x2C,0x10,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0xD0,0x10,0x00,0x80,0x01,0x00,0x00,0x00,0x08,0x80,0x00,0x00,0x04,0x04,0x00,0x48,0x10,0x60,0x08,0x14,0x10,0x08,0x04,0x02,0x00,0x00,0x92,0x00,0x08,0x01,0x01,0x11,0xD0,0x0A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x05,0x03,0x00,0x00,0x00,0x00,0x00,0x98,0x00,0x00,0x00,0x01,0x80,0x00,0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0x40,0x80,0x02,0x00,0x01,0x82,0x24,0x18,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x02,0x04,0x01,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x20,0x07,0x10,0x86,0x92,0x0C,0x68,0x20,0x00,0x00,0x00,0x00,0x00,0xC0,0x61,0x12,0x00,0x00,0x08,0x08,0x20,0x00,0x20,0x00,0x02,0x00,0xD1,0x02,0x01,0x34,0x05,0x00,0xC0,0x20,0x20,0x20,0x20,0x40,0x00,0xE0,0x04,0x0C,0x02,0x01,0x00,0x00,0x00,0x00,0xC0,0x40,0x40,0x40,0x00,0x00,0x3C,0x02,0x01,0x06,0x08,0x08,0x00,0x00,0x00,0x00,0x72,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0A,0x08,0x00,0x00,0x44,0x00,0x20,0x10,0x10,0x20,0x00,0x00,0x08,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x04,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x01,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x02,0x02,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0xA0,0x00,0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x23,0x88,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x05,0x00,0x00,0xA8,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x02,0x42,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x38,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x11,0x01,0x00,0x00,0x00,0x00,0x08,0x18,0x00,0x85,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x80,0x00,0x00,0x00,0x40,0x00,0x40,0xC0,0x18,0x08,0x00,0x00,0x00,0x00,0x00,0x80,0x02,0x02,0x00,0x80,0x00,0x20,0x20,0x00,0x00,0x00,0x00,0x00,

0xFE,0xFE,0xA2,0x92,0xFE,0xFE,0x0E,0x00,0x02,0x02,0xFE,0xFE,0x4E,0x02,0x00,0x00,0x66,0xF6,0x92,0x8A,0xCE,0x46,0x06,0x00,0xEE,0xFE,0x92,0x92,0xC6,0xC6,0x06,0x00,0x08,0xFE,0xFE,0x08,0x08,0x38,0x38,0x00,0x9E,0x9E,0x92,0x92,0xF6,0xF6,0x06,0x00,0xDE,0xDE,0x92,0x92,0xFE,0xFE,0x0E,0x00,0xC0,0xE0,0xB0,0x9E,0xCE,0xC0,0xC0,0x00,0xFE,0xFE,0x92,0x92,0xFE,0xFE,0x0E,0x00,0xFE,0xFE,0x92,0x92,0xF6,0xF6,0x06,0x00,0xFE,0xFE,0x90,0x90,0xFE,0xFE,0x0E,0x00,0x6C,0xFE,0x92,0x92,0xFE,0xFE,0x0E,0x00,0xC6,0xC6,0x82,0x82,0xFE,0xFE,0x0E,0x00,0x3E,0x7E,0xC2,0x82,0xFE,0xFE,0x0E,0x00,0xC6,0x82,0x92,0x92,0xFE,0xFE,0x0E,0x00,0x80,0x80,0x90,0x90,0xFE,0xFE,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0xFE,0x90,0x90,0xFE,0xFE,0x0E,0x00,0x6C,0xFE,0x92,0x92,0xFE,0xFE,0x0E,0x00,0xC6,0xC6,0x82,0x82,0xFE,0xFE,0x0E,0x00,0x3E,0x7E,0x82,0x82,0xFE,0xFE,0x0E,0x00,0xC6,0x82,0x92,0x92,0xFE,0xFE,0x0E,0x00,0x80,0x80,0x90,0x90,0xFE,0xFE,0x0E,0x00,0xDE,0xDE,0x92,0x82,0xFE,0xFE,0x0E,0x00,0xFE,0xFE,0x10,0x10,0xFE,0xFE,0x0E,0x00,0x00,0x82,0xFE,0xFE,0x8E,0x82,0x00,0x00,0x00,0x8E,0xFE,0xFE,0x82,0x06,0x06,0x00,0x82,0xC6,0x6C,0x38,0xFE,0xFE,0x0E,0x00,0x06,0x02,0x02,0x02,0xFE,0xFE,0x0E,0x00,0xFE,0xFE,0x62,0x30,0x60,0xFE,0xFE,0x00,0xFE,0xFE,0x38,0x70,0xFE,0xFE,0x0E,0x00,0xFE,0xFE,0x82,0x82,0xFE,0xFE,0x0E,0x00,
0xF0,0xF0,0x90,0x90,0xFE,0xFE,0x0E,0x00,0xFF,0xFE,0x86,0x82,0xFE,0xFE,0x0E,0x00,0x62,0xF6,0x9C,0x98,0xFE,0xFE,0x0E,0x00,0xDE,0xDE,0x92,0x92,0xF2,0xF6,0x06,0x00,0x00,0x80,0x80,0xFE,0xFE,0x8E,0x80,0x00,0xFE,0xFE,0x02,0x02,0xFE,0xFE,0x0E,0x00,0xF8,0xFC,0x06,0x06,0xFC,0xF8,0x70,0x00,0xFE,0xFE,0x0C,0x18,0x8C,0xFE,0xFE,0x00,0xC6,0xEE,0x38,0x38,0xEE,0xC6,0x06,0x00,0x00,0xC0,0xE0,0x3E,0x3E,0xEE,0xC0,0x00,0xC6,0xE2,0xB2,0x9A,0x8E,0xC6,0x06,0x00,0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0xFF,0x81,0x81,0x99,0x99,0x81,0x81,0xFF,0x00,0x00,0x00,0x00,0x20,0x40,0x00,0x06,0x00,0x04,0x08,0x00,0x00,0x01,0x01,0x00,0x00,0x40,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x49,0x91,0x92,0x04,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x04,0x92,0x91,0x49,0x08,0x00,0x00,0x00,0x00,0x00,0x11,0x29,0x00,0x02,0x00,0x00,0x80,0x90,0x10,0x20,0x40,0x00,0x00,0x02,0x00,0x29,0x11,0x00,0x00,0x00,0x00,0x00,0x40,0x20,0x10,0x90,0x80,0x00,0x00,0x00,0x00,0x00,0x18,0x04,0x00,0x01,0x00,0x00,0x20,0x44,0x44,0x88,0x10,0x00,0x00,0x02,0x20,0x19,0x01,0x02,0x04,0x00,0x00,0x00,0x00,0x20,0x20,0x20,0x40,0x00,0x00,0x00,0x00,0x0C,0x04,0x00,0x00,0x01,0x20,0x00,0x00,0x00,0x20,0x40,0x84,0x08,0x10,0x32,0x00,0x04,0x08,0x10,0x01,0x00,0x00,0x00,0x00,0x00,0x40,0x80,0x00,0x00,0x00,0x00,0x03,0x01,0x00,0x00,0x20,0x30,0x02,0x00,0x00,0x10,0x10,0x22,0x84,0x18,0x00,0x00,0x04,0x19,0x01,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x10,0x18,0x02,0x00,0x00,0x00,0x80,0x90,0x10,0xA2,0x06,0x08,0x04,0x08,0x11,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x10,0x08,0x00,0x02,0x78,0x00,0x80,0x40,0x80,0x00,0x88,0x10,0x20,0x00,0x00,0x02,0x04,0x18,0x00,0x00,0x00,0x00,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x08,0x04,0x00,0x01,0x0C,0x00,0x00,0x10,0x08,0x10,0x00,0x40,0x18,0x30,0x02,0x04,0x18,0x00,0x00,0x00,0x00,0x06,0x20,0x10,0x0C,0x00,0x00,0x00,0x00,
0x00,0x07,0x00,0x01,0x10,0x31,0xDF,0xDF,0x00,0xFF,0xFC,0xFF,0xF4,0xE8,0xF8,0xF8,0xDF,0x31,0x10,0x01,0x00,0x07,0x00,0x00,0xF8,0xE8,0xF4,0xFF,0xFC,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x11,0x1C,0x08,0x00,0x00,0x00,0x00,0x80,0xB0,0x60,0x00,0x10,0x10,0x00,0x08,0x1C,0x11,0x01,0x00,0x00,0x00,0x10,0x00,0x00,0xB0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x04,0x14,0x00,0x00,0x00,0x00,0x40,0x10,0x90,0x20,0x00,0x38,0x00,0x14,0x04,0x12,0x00,0x00,0x00,0x00,0x00,0x20,0x90,0x10,0x40,0x00,0x00,0x00,0x00,0x00,0x03,0x08,0x31,0x14,0x08,0x00,0x00,0x80,0xE0,0x00,0x80,0x10,0x20,0x10,0x08,0x14,0x31,0x08,0x03,0x00,0x00,0x00,0x20,0x10,0x80,0x00,0xE0,0x80,0x00,0x00,0x00,0x01,0x0D,0x21,0x04,0x00,0x1C,0x00,0x00,0x00,0xA0,0x80,0x00,0x00,0x00,0x50,0x1C,0x00,0x04,0x21,0x0D,0x01,0x00,0x00,0x00,0x00,0x00,0x80,0xA0,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x78,0x00,0x02,0x06,0x10,0x01,0x4A,0x00,0x10,0x00,0xA0,0x02,0x14,0x10,0x08,0x00,0x00,0x80,0x01,0x1C,0x40,0x86,0x01,0x81,0x60,0x00,0x04,0x90,0x70,0x08,0x02,0x00,0x40,0x00,0x00,0x40,0x00,0x20,0x00,0x10,0x7C,0x81,0x01,0x01,0x04,0x00,0x08,0x80,0x20,0x04,0x01,0x40,0x04,0x48,0x11,0xA0,0x00,0x02,0x00,0x08,0x84,0x02,0x01,0x00,0x18,0x86,0x80,0x0C,0x11,0x18,0xDB,0x05,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x00,0x02,0x00,0x00,0x00,0x00,0x62,0x90,0x01,0x05,0x00,0x01,0x81,0x7C,0x01,0x40,0x00,0xC0,0x00,0x01,0x80,0x80,0x40,0x44,0x80,0x01,0x02,0x64,0x00,0x00,0x48,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x04,0x03,0x00,0x00,0x18,0x00,0x12,0x10,0x0A,0xC2,0x00,0x01,0x00,0x00,0x01,0x00,0x02,0x00,0x21,0x02,0x19,0x8E,0xA2,0x6C,0xE4,0x70,0x00,0x00,0x00,0x00,0x00,0x60,0xE3,0x02,0x60,0x00,0x14,0x20,0x08,0x80,0x00,0x00,0x0E,0x5A,0x5B,0x8A,0x45,0x35,0x04,0x02,0xE0,0x00,0x10,0x90,0x40,0x20,0x00,0x80,0x12,0x15,0x04,0x00,0x00,0x00,0x02,0x02,0xC0,0x60,0x20,0x60,0x20,0x18,0x3C,0x00,0x01,0x0E,0x0A,0x10,0x18,0x10,0x00,0x30,0x05,0x20,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x09,0x08,0x08,0x40,0x40,0x0C,0x10,0x20,0x20,0xD0,0x00,0x08,0x70,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x24,0x12,0x0A,0x00,0x10,
0x00,0x00,0x60,0x30,0x18,0x08,0x00,0x00,0x10,0x40,0x20,0x40,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x20,0x20,0x00,0x00,0x00,0x40,0x10,0x08,0x0D,0x10,0x00,0x00,0x00,0x00,0x06,0x10,0x00,0x00,0x00,0x05,0x08,0x02,0x44,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0xA0,0x10,0x88,0x04,0x00,0x00,0x00,0x00,0x00,0x06,0x04,0x00,0x00,0x00,0x08,0x08,0x04,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x00,0x08,0x12,0x24,0x08,0x50,0x00,0x40,0x00,0x00,0x70,0x04,0x00,0x01,0x0E,0x80,0xA8,0x00,0x80,0x20,0x40,0x60,0x00,0x80,0x08,0x00,0x08,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x02,0x00,0x00,0x88,0x00,0x40,0x00,0x39,0x04,0x02,0x00,0x00,0x00,0x00,0x00,0x40,0x60,0x38,0x01,0x08,0x04,0x02,0x00,0x30,0x30,0x18,0x04,0x00,0x01,0x00,0x0A,0x0C,0x04,0x02,0x02,0x04,0x70,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0xE0,0xE5,0x03,0x00,0x00,0x00,0x00,0x0C,0x18,0x40,0x80,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x3A,0x00,0x08,0x98,0x70,0x00,0x20,0x0E,0x0E,0x01,0x00,0x00,0x02,0x80,0x90,0x23,0x31,0xBD,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x02,0x80,0x87,0x08,0x10,0x20,0x00,0x00,0x00,0x04,0x01,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x02,0x80,0x00,0x00,0x00,0x40,0x00,0x40,0x10,0x64,0x84,0x00,0x00,0x00,0x00,0x00,0x10,0xC8,0xC1,0xC0,0x38,0x20,0x80,0x50,0x10,0x08,0x00,0x00,0x80,
};
const char __at (0x5000) palette[32] = {/*{pal:332,n:4}*/
  0x00,0xFF,0xFF,0xFF,0x00,0x16,0xC0,0x3F,
  0x00,0xD8,0x07,0x3F,0x00,0xC0,0xC4,0x07,
  0x00,0xC0,0xA0,0x07,0x00,0x00,0x00,0x07,
  0x00,0xF6,0x07,0xF0,0x00,0x76,0x07,0xC6,
};

#define LOCHAR 0x30
#define HICHAR 0xff

#define CHAR(ch) (ch-LOCHAR)

#define BLANK 0x10

void clrscr() {
  memset(vram, BLANK, sizeof(vram));
}

byte getchar(byte x, byte y) {
  return vram[29-x][y];
}

volatile byte video_framecount; // actual framecount

void _buffer() {
__asm
; padding to get to offset 0x66
  ld ix,#0
  ld ix,#0
  ld ix,#0
  nop
  nop
  nop
  nop
__endasm;
}

void rst_66() __interrupt {
  video_framecount++;
}

void reset_video_framecount() __critical {
  video_framecount = 0;
}


void putchar(byte x, byte y, byte ch) {
  vram[29-x][y] = ch;
}

void clrobjs() {
  byte i;
  memset(columns, 0, 0x100);
  for (i=0; i<8; i++)
    sprites[i].ypos = 64;
}

void putstring(byte x, byte y, const char* string) {
  while (*string) {
    putchar(x++, y, CHAR(*string++));
  }
}

void wait_for_frame() {
  byte initial_framecount = video_framecount;
  watchdog++;
  while (video_framecount == initial_framecount);
}
void DrawAddress(int offset)
{
  putchar(5,1,offset & 15);
  offset >>=4;
  putchar(4,1,offset & 15);
  offset >>=4;
  putchar(3,1,offset & 15);
  offset >>=4;
  putchar(2,1,offset & 15);
}
///

void main() {
  int i;
  int j;
  int offset;
  int counter=0;
  byte *p;
  byte * op;
  int scroll = 0;
  int oldscroll = 0;
  clrscr();
  clrobjs();
  enable_stars = 0xff;
  enable_irq = 0;
  p = vramflat +16*32 + 16;
  memset(vramflat, BLANK, 32*32);
  for(j=0;j<32;j++)
  {
    *(vramflat+j*32) = j%10;
  //  memset(vramflat+j*32,9-j%10, 32);
    columns[j].scroll =scroll;
    
  }
  enable_irq = 1;
  while (1) {
    wait_for_frame();
    putstring(0, 10, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    *p =BLANK;
    op =p;
    oldscroll = scroll;
    if (counter > 0) counter --;
    if (counter == 0)
    {
     if (UP1 ) p--;
     if (DOWN1 ) p++;
     if (LEFT1 ) p+=32;
     if (RIGHT1 ) p-=32;
     if (FIRE1 ) scroll+=1;
     if (BOMB1 ) scroll-=1;
      if (p<vramflat) p = p+32*32;
      if(p>vramflat+32*32) p =p-32*32;
      if(scroll <-15) scroll=-15;
      if(scroll >15) scroll=15;
    }
    if (p!=op || scroll != oldscroll) counter =8;
      for (i=0;i<32;i++)
      {
          columns[i].scroll =scroll;
      }
    for (i=0;i<8;i++)
    {
    missiles[i].xpos = 20+i*10;
    missiles[i].ypos = 20+i*10;
    }
  //memset(vramflat, BLANK, 32*32);
    *p =11*4;
    offset = p-vramflat;
    DrawAddress(offset);
//    sprites[0].ypos++;
    sprites[0].xpos = 24;
    sprites[0].ypos = 24;
    sprites[0].code = 1;
  }
}
