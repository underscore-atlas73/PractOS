#ifndef L_KB_H_
#define L_KB_H_

#include <kernel/drivers/l_pic.h>
#include <stdbool.h>
struct InterruptState;

#define PS2_COMMAND	0x64
#define PS2_DATA	0x60

enum KB_XT {
	KB_XT_ESC		=	0x01,
	KB_XT_ONE		= 	0x02,
	KB_XT_TWO		=	0x03,
	KB_XT_THREE		=	0x04,
	KB_XT_FOUR		=	0x05,
	KB_XT_FIVE		=	0x06,
	KB_XT_SIX		=	0x07,
	KB_XT_SEVEN		=	0x08,
	KB_XT_EIGHT		=	0x09,
	KB_XT_NINE		=	0x0A,
	KB_XT_ZERO		=	0x0B,
	KB_XT_HYPH		=	0x0C,
	KB_XT_EQU		=	0x0D,
	KB_XT_BACK		=	0x0E,
	KB_XT_TAB		=	0x0F,
	KB_XT_Q			=	0x10,
	KB_XT_W			=	0x11,
	KB_XT_E			=	0x12,
	KB_XT_R			=	0x13,
	KB_XT_T			=	0x14,
	KB_XT_Y			=	0x15,
	KB_XT_U			=	0x16,
	KB_XT_I			=	0x17,
	KB_XT_O			=	0x18,
	KB_XT_P			=	0x19,
	KB_XT_LBR		=	0x1A,
	KB_XT_RBR		=	0x1B,
	KB_XT_ENTER		=	0x1C,
	KB_XT_LCTRL		=	0x1D,
	KB_XT_A			=	0x1E,
	KB_XT_S			=	0x1F,
	KB_XT_D			=	0x20,
	KB_XT_F			=	0x21,
	KB_XT_G			=	0x22,
	KB_XT_H			=	0x23,
	KB_XT_J			=	0x24,
	KB_XT_K			=	0x25,
	KB_XT_L			=	0x26,
	KB_XT_SEMI		=	0x27,
	KB_XT_APOS		=	0x28,
	KB_XT_BTICK		=	0x29,
	KB_XT_LSHIFT		=	0x2A,
	KB_XT_BSLASH		=	0x2B,
	KB_XT_Z			=	0x2C,
	KB_XT_X			=	0x2D,
	KB_XT_C			=	0x2E,
	KB_XT_V			=	0x2F,
	KB_XT_B			=	0x30,
	KB_XT_N			=	0x31,
	KB_XT_M			=	0x32,
	KB_XT_COMMA		=	0x33,
	KB_XT_PERIOD		=	0x34,
	KB_XT_FSLASH		=	0x35,
	KB_XT_RSHIFT		=	0x36,
	KB_XT_KASTER		=	0x37,
	KB_XT_LALT		=	0x38,
	KB_XT_SPACE		=	0x39,
	KB_XT_CAPSL		=	0x3A,
	KB_XT_F1		=	0x3B,
	KB_XT_F2		=	0x3C,
	KB_XT_F3		=	0x3D,
	KB_XT_F4		=	0x3E,
	KB_XT_F5		=	0x3F,
	KB_XT_F6		=	0x40,
	KB_XT_F7		=	0x41,
	KB_XT_F8		=	0x42,
	KB_XT_F9		=	0x43,
	KB_XT_F10		=	0x44,
	KB_XT_NUMLCK		=	0x45,
	KB_XT_SCRLCK		=	0x46,
	KB_XT_K7		=	0x47,
	KB_XT_K8		=	0x48,
	KB_XT_K9		=	0x49,
	KB_XT_KMINUS		=	0x4A,
	KB_XT_K4		=	0x4B,
	KB_XT_K5		=	0x4C,
	KB_XT_K6		=	0x4D,
	KB_XT_KPLUS		=	0x4E,
	KB_XT_K1		=	0x4F,
	KB_XT_K2		=	0x50,
	KB_XT_K3		=	0x51,
	KB_XT_K0		=	0x52,
	KB_XT_KPERIO		=	0x53,
								// Gap?
	KB_XT_F11		=	0x57,
	KB_XT_F12		=	0x58
								// Very large gap; released start at 0x81
								// Extended begin with 0xE0 and start at 0x10; many gaps
};
extern char XT_ASCII[89];

struct _KeyState {
	bool shift;
	bool caps_lock;
	bool ctrl;
	bool alt;
	bool super;
	bool F1;
	bool F2;
	bool F3;
	bool F4;
	bool F5;
	bool F6;
	bool F7;
	bool F8;
	bool F9;
	bool F10;
	bool F11;
	bool F12;
	//bool numlock;
} __attribute__((__packed__));

extern struct _KeyState KeyState;

#endif // L_KB_H_
