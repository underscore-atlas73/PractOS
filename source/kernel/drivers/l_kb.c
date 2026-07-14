#include <kernel/drivers/l_pic.h>
#include <kernel/drivers/l_kb.h>
#include <kernel/io.h>

#include <stdio.h>

void KB_handler(struct InterruptState* state) {
	uint8_t scancode = inb(PS2_DATA);

	if (!(scancode & 0x80)) {
		char ascii = XT_ASCII[scancode];
		if (ascii == 0) {
			switch(scancode) {
				case KB_XT_LSHIFT:
				case KB_XT_RSHIFT:
					KeyState.shift = true;
					break;
				case KB_XT_CAPSL:
					KeyState.caps_lock = !KeyState.caps_lock;
					break;
				case KB_XT_LCTRL:
					KeyState.ctrl = true;
					break;
				case KB_XT_LALT:
					KeyState.alt = true;
					break;
				case KB_XT_F1:
				case KB_XT_F2:
				case KB_XT_F3:
				case KB_XT_F4:
				case KB_XT_F5:
				case KB_XT_F6:
				case KB_XT_F7:
				case KB_XT_F8:
				case KB_XT_F9:
				case KB_XT_F10:
					*(((bool*)&KeyState) + scancode - 54) = true;
					break;
				case KB_XT_F11:
				case KB_XT_F12:
					*((bool*)&KeyState + scancode - 72) = true;
					break;
			}
		}

		if (ascii) {
			//printf("%c", ascii);
			goto end;
		}
	}
	{
		switch(scancode - 0x80) {
				case KB_XT_LSHIFT:
				case KB_XT_RSHIFT:
					KeyState.shift = false;
					break;
				case KB_XT_CAPSL:
					break;
				case KB_XT_LCTRL:
					KeyState.ctrl = false;
					break;
				case KB_XT_LALT:
					KeyState.alt = false;
					break;
				case KB_XT_F1:
				case KB_XT_F2:
				case KB_XT_F3:
				case KB_XT_F4:
				case KB_XT_F5:
				case KB_XT_F6:
				case KB_XT_F7:
				case KB_XT_F8:
				case KB_XT_F9:
				case KB_XT_F10:
					*(((bool*)&KeyState) + (scancode - 0x80) - 54) = false;
					break;
				case KB_XT_F11:
				case KB_XT_F12:
					*((bool*)&KeyState + (scancode - 0x80) - 72) = false;
					break;
		}
		goto end;
	}

	end:
	PIC_send_eoi(PIC_KB);
}

struct _KeyState KeyState = {0};

char XT_ASCII[89] = {
	[KB_XT_ESC	]	=	'\x1b',
	[KB_XT_ONE	]	=	'1',
	[KB_XT_TWO	]	=	'2',
	[KB_XT_THREE 	]	=	'3',
	[KB_XT_FOUR	]	=	'4',
	[KB_XT_FIVE	]	=	'5',
	[KB_XT_SIX	]	=	'6',
	[KB_XT_SEVEN	]	=	'7',
	[KB_XT_EIGHT 	]	=	'8',
	[KB_XT_NINE	]	=	'9',
	[KB_XT_ZERO	]	=	'0',
	[KB_XT_HYPH	]	=	'-',
	[KB_XT_EQU	]	=	'=',
	[KB_XT_BACK	]	=	'\b',
	[KB_XT_TAB	]	=	'\t',
	[KB_XT_Q	]	=	'q',
	[KB_XT_W	]	=	'w',
	[KB_XT_E	]	=	'e',
	[KB_XT_R	]	=	'r',
	[KB_XT_T	]	=	't',
	[KB_XT_Y	]	=	'y',
	[KB_XT_U	]	=	'u',
	[KB_XT_I	]	=	'i',
	[KB_XT_O	] 	=	'o',
	[KB_XT_P	]	=	'p',
	[KB_XT_LBR	]	=	'[',
	[KB_XT_RBR	]	=	']',
	[KB_XT_ENTER 	]	=	'\n',
	[KB_XT_LCTRL 	]	=	0,
	[KB_XT_A	]	=	'a',
	[KB_XT_S	]	=	's',
	[KB_XT_D	]	=	'd',
	[KB_XT_F	]	=	'f',
	[KB_XT_G	]	=	'g',
	[KB_XT_H	]	=	'h',
	[KB_XT_J	]	=	'j',
	[KB_XT_K	]	=	'k',
	[KB_XT_L	]	=	'l',
	[KB_XT_SEMI	]	=	';',
	[KB_XT_APOS	]	=	'\'',
	[KB_XT_BTICK 	]	=	'`',
	[KB_XT_LSHIFT	]	=	0,
	[KB_XT_BSLASH	] 	=	'\\',
	[KB_XT_Z	]	=	'z',
	[KB_XT_X	]	=	'x',
	[KB_XT_C	]	=	'c',
	[KB_XT_V	]	=	'v',
	[KB_XT_B	]	=	'b',
	[KB_XT_N	]	=	'n',
	[KB_XT_M	]	=	'm',
	[KB_XT_COMMA 	]	=	',',
	[KB_XT_PERIOD	]	=	'.',
	[KB_XT_FSLASH	]	=	'/',
	[KB_XT_RSHIFT	]	=	0,
	[KB_XT_KASTER	]	=	'*',
	[KB_XT_LALT	]	=	0,
	[KB_XT_SPACE 	]	=	' ',
	[KB_XT_CAPSL 	]	=	0,
	[KB_XT_F1	]	=	0,
	[KB_XT_F2	]	=	0,
	[KB_XT_F3	]	=	0,
	[KB_XT_F4	]	=	0,
	[KB_XT_F5	]	=	0,
	[KB_XT_F6	]	=	0,
	[KB_XT_F7 	]	=	0,
	[KB_XT_F8	]	=	0,
	[KB_XT_F9	]	=	0,
	[KB_XT_F10	]	=	0,
	[KB_XT_NUMLCK	]	=	0,
	[KB_XT_SCRLCK	]	=	0,
	[KB_XT_K7	]	=	'7',
	[KB_XT_K8	]	=	'8',
	[KB_XT_K9	]	=	'9',
	[KB_XT_KMINUS	]	=	'-',
	[KB_XT_K4	]	=	'4',
	[KB_XT_K5	]	=	'5',
	[KB_XT_K6	]	=	'6',
	[KB_XT_KPLUS 	]	=	'+',
	[KB_XT_K1	]	=	'1',
	[KB_XT_K2	]	=	'2',
	[KB_XT_K3	]	=	'3',
	[KB_XT_K0	]	=	'0',
	[KB_XT_KPERIO	]	=	'.',
	[KB_XT_F11	]	=	0,
	[KB_XT_F12	]	=	0
};
