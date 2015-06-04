enum KBRD_CTRL_STATS_MASK 
{
	KBRD_CTRL_STATS_MASK_OUT_BUF	=	1,			//00000001
	KBRD_CTRL_STATS_MASK_IN_BUF		=	2,			//00000010
	KBRD_CTRL_STATS_MASK_SYSTEM		=	4,			//00000100
	KBRD_CTRL_STATS_MASK_CMD_DATA	=	8,			//00001000
	KBRD_CTRL_STATS_MASK_LOCKED		=	0x10,		//00010000
	KBRD_CTRL_STATS_MASK_AUX_BUF	=	0x20,		//00100000
	KBRD_CTRL_STATS_MASK_TIMEOUT	=	0x40,		//01000000
	KBRD_CTRL_STATS_MASK_PARITY		=	0x80		//10000000
};

// keyboard encoder ------------------------------------------

enum KBRD_ENCODER_IO 
{
	KBRD_ENC_INPUT_BUF	=	0x60,
	KBRD_ENC_CMD_REG	=	0x60
};

enum KBRD_ENC_CMDS
 {
	KBRD_ENC_CMD_SET_LED				=	0xED,
	KBRD_ENC_CMD_ECHO					=	0xEE,
	KBRD_ENC_CMD_SCAN_CODE_SET			=	0xF0,
	KBRD_ENC_CMD_ID						=	0xF2,
	KBRD_ENC_CMD_AUTODELAY				=	0xF3,
	KBRD_ENC_CMD_ENABLE					=	0xF4,
	KBRD_ENC_CMD_RESETWAIT				=	0xF5,
	KBRD_ENC_CMD_RESETSCAN				=	0xF6,
	KBRD_ENC_CMD_ALL_AUTO				=	0xF7,
	KBRD_ENC_CMD_ALL_MAKEBREAK			=	0xF8,
	KBRD_ENC_CMD_ALL_MAKEONLY			=	0xF9,
	KBRD_ENC_CMD_ALL_MAKEBREAK_AUTO		=	0xFA,
	KBRD_ENC_CMD_SINGLE_AUTOREPEAT		=	0xFB,
	KBRD_ENC_CMD_SINGLE_MAKEBREAK		=	0xFC,
	KBRD_ENC_CMD_SINGLE_BREAKONLY		=	0xFD,
	KBRD_ENC_CMD_RESEND					=	0xFE,
	KBRD_ENC_CMD_RESET					=	0xFF
};

// keyboard controller ---------------------------------------

enum KBRD_CTRL_IO 
{
	KBRD_CTRL_STATS_REG	=	0x64,
	KBRD_CTRL_CMD_REG	=	0x64
};

enum KBRD_CTRL_CMDS 
{
	KBRD_CTRL_CMD_READ				=	0x20,
	KBRD_CTRL_CMD_WRITE				=	0x60,
	KBRD_CTRL_CMD_SELF_TEST			=	0xAA,
	KBRD_CTRL_CMD_INTERFACE_TEST	=	0xAB,
	KBRD_CTRL_CMD_DISABLE			=	0xAD,
	KBRD_CTRL_CMD_ENABLE			=	0xAE,
	KBRD_CTRL_CMD_READ_IN_PORT		=	0xC0,
	KBRD_CTRL_CMD_READ_OUT_PORT		=	0xD0,
	KBRD_CTRL_CMD_WRITE_OUT_PORT	=	0xD1,
	KBRD_CTRL_CMD_READ_TEST_INPUTS	=	0xE0,
	KBRD_CTRL_CMD_SYSTEM_RESET		=	0xFE,
	KBRD_CTRL_CMD_MOUSE_DISABLE		=	0xA7,
	KBRD_CTRL_CMD_MOUSE_ENABLE		=	0xA8,
	KBRD_CTRL_CMD_MOUSE_PORT_TEST	=	0xA9,
	KBRD_CTRL_CMD_MOUSE_WRITE		=	0xD4
};

	// send command
	kbrd_ctrl_send_cmd (KBRD_CTRL_CMD_SELF_TEST);

	// wait for output buffer to be full
// scan error codes ------------------------------------------

enum KBRD_ERROR 
{
	KBRD_ERR_BUF_OVERRUN			=	0,
	KBRD_ERR_ID_RET					=	0x83AB,
	KBRD_ERR_BAT					=	0xAA,	//note: can also be L. shift key make code
	KBRD_ERR_ECHO_RET				=	0xEE,
	KBRD_ERR_ACK					=	0xFA,
	KBRD_ERR_BAT_FAILED				=	0xFC,
	KBRD_ERR_DIAG_FAILED			=	0xFD,
	KBRD_ERR_RESEND_CMD				=	0xFE,
	KBRD_ERR_KEY					=	0xFF
};


//! original xt scan code set. Array index==make code
//! change what keys the scan code corrospond to if your scan code set is different
static int _kkybrd_scancode_std [] = {

	//! key			scancode
	KEY_UNKNOWN,	//0
	KEY_ESCAPE,		//1
	KEY_1,			//2
	KEY_2,			//3
	KEY_3,			//4
	KEY_4,			//5
	KEY_5,			//6
	KEY_6,			//7
	KEY_7,			//8
	KEY_8,			//9
	KEY_9,			//0xa
	KEY_0,			//0xb
	KEY_MINUS,		//0xc
	KEY_EQUAL,		//0xd
	KEY_BACKSPACE,	//0xe
	KEY_TAB,		//0xf
	KEY_Q,			//0x10
	KEY_W,			//0x11
	KEY_E,			//0x12
	KEY_R,			//0x13
	KEY_T,			//0x14
	KEY_Y,			//0x15
	KEY_U,			//0x16
	KEY_I,			//0x17
	KEY_O,			//0x18
	KEY_P,			//0x19
	KEY_LEFTBRACKET,//0x1a
	KEY_RIGHTBRACKET,//0x1b
	KEY_RETURN,		//0x1c
	KEY_LCTRL,		//0x1d
	KEY_A,			//0x1e
	KEY_S,			//0x1f
	KEY_D,			//0x20
	KEY_F,			//0x21
	KEY_G,			//0x22
	KEY_H,			//0x23
	KEY_J,			//0x24
	KEY_K,			//0x25
	KEY_L,			//0x26
	KEY_SEMICOLON,	//0x27
	KEY_QUOTE,		//0x28
	KEY_GRAVE,		//0x29
	KEY_LSHIFT,		//0x2a
	KEY_BACKSLASH,	//0x2b
	KEY_Z,			//0x2c
	KEY_X,			//0x2d
	KEY_C,			//0x2e
	KEY_V,			//0x2f
	KEY_B,			//0x30
	KEY_N,			//0x31
	KEY_M,			//0x32
	KEY_COMMA,		//0x33
	KEY_DOT,		//0x34
	KEY_SLASH,		//0x35
	KEY_RSHIFT,		//0x36
	KEY_KP_ASTERISK,//0x37
	KEY_RALT,		//0x38
	KEY_SPACE,		//0x39
	KEY_CAPSLOCK,	//0x3a
	KEY_F1,			//0x3b
	KEY_F2,			//0x3c
	KEY_F3,			//0x3d
	KEY_F4,			//0x3e
	KEY_F5,			//0x3f
	KEY_F6,			//0x40
	KEY_F7,			//0x41
	KEY_F8,			//0x42
	KEY_F9,			//0x43
	KEY_F10,		//0x44
	KEY_KP_NUMLOCK,	//0x45
	KEY_SCROLLLOCK,	//0x46
	KEY_HOME,		//0x47
	KEY_KP_8,		//0x48	//keypad up arrow
	KEY_PAGEUP,		//0x49
	KEY_KP_2,		//0x50	//keypad down arrow
	KEY_KP_3,		//0x51	//keypad page down
	KEY_KP_0,		//0x52	//keypad insert key
	KEY_KP_DECIMAL,	//0x53	//keypad delete key
	KEY_UNKNOWN,	//0x54
	KEY_UNKNOWN,	//0x55
	KEY_UNKNOWN,	//0x56
	KEY_F11,		//0x57
	KEY_F12			//0x58
};


static struct _locks 
{
	bool num, scroll, caps;
};

static struct _hold 
{
	bool shift, alt, ctrl;
};

//Key Buffer variables	
static KEYCODE key_buffer[KEY_BUFFER_SIZE];
static int buffer_current_key;
static int buffer_last_key;


static char _scancode;

// set if keyboard error
static int _kbrd_error = 0;

// set if the Basic Assurance Test (BAT) failed
static bool _kbrd_bat_res = false;

// set if diagnostics failed
static bool _kbrd_diag_res = false;

// set if system should resend last command
static bool _kbrd_resend_res = false;

// set if keyboard is disabled
static bool _kbrd_disable = false;



// sets leds
void kbrd_set_leds (bool num, bool caps, bool scroll) 
{
	uint8_t data = 0;

	// set or clear the bit
	data = (scroll) ? (data | 1) : data;
	data = (num) ? (data | 2) : (data & 1);
	data = (caps) ? (data | 4) : (data & 3);

	// send the command -- update keyboard LEDs
	kbrd_enc_send_cmd (KBRD_ENC_CMD_SET_LED);
	kbrd_enc_send_cmd (data);
}

// convert key to an ascii character
char kbrd_key_to_ascii (KEYCODE code)
 {
	uint8_t key = code;

	// check if key is an ascii character
	if (isascii (key)) {

		// if shift key is down or caps lock is on, make the key uppercase
		if (hold.shift ^^ lock.caps)
			if (key >= 'a' && key <= 'z')
				key -= 32;

		if (hold.shift && !lock.caps)
			if (key >= '0' && key <= '9')
				switch (key) {

					case '0':
						key = KEY_RIGHTPARENTHESIS;
						break;
					case '1':
						key = KEY_EXCLAMATION;
						break;
					case '2':
						key = KEY_AT;
						break;
					case '3':
						key = KEY_EXCLAMATION;
						break;
					case '4':
						key = KEY_HASH;
						break;
					case '5':
						key = KEY_PERCENT;
						break;
					case '6':
						key = KEY_CARRET;
						break;
					case '7':
						key = KEY_AMPERSAND;
						break;
					case '8':
						key = KEY_ASTERISK;
						break;
					case '9':
						key = KEY_LEFTPARENTHESIS;
						break;
				}
			else {

				switch (key) {
					case KEY_COMMA:
						key = KEY_LESS;
						break;

					case KEY_DOT:
						key = KEY_GREATER;
						break;

					case KEY_SLASH:
						key = KEY_QUESTION;
						break;

					case KEY_SEMICOLON:
						key = KEY_COLON;
						break;

					case KEY_QUOTE:
						key = KEY_QUOTEDOUBLE;
						break;

					case KEY_LEFTBRACKET :
						key = KEY_LEFTCURL;
						break;

					case KEY_RIGHTBRACKET :
						key = KEY_RIGHTCURL;
						break;

					case KEY_GRAVE:
						key = KEY_TILDE;
						break;

					case KEY_MINUS:
						key = KEY_UNDERSCORE;
						break;

					case KEY_PLUS:
						key = KEY_EQUAL;
						break;

					case KEY_BACKSLASH:
						key = KEY_BAR;
						break;
				}
			}
		return key;
	}
	// scan code is not a valid ascii char so no convertion is possible
	return 0;
}






int isascii(int c)
{
	return c >= 0 && c< 128;
}


// disables the keyboard
void kbrd_disable () 
{
	kbrd_ctrl_send_cmd (kbrd_CTRL_CMD_DISABLE);
	_kbrd_disable = true;
}

// enables the keyboard
void kbrd_enable () 
{
	kbrd_ctrl_send_cmd (kbrd_CTRL_CMD_ENABLE);
	_kbrd_disable = false;
}

// returns true if keyboard is disabled
bool kbrd_is_disabled () 
{
	return _kbrd_disable;
}

// reset the system
void kbrd_reset_system () 
{
	// writes 11111110 to the output port (sets reset system line low)
	kbrd_ctrl_send_cmd (KBRD_CTRL_CMD_WRITE_OUT_PORT);
	kbrd_enc_send_cmd (0xfe);
}

// prepares driver for use
void kbrd_install (int irq) 
{
	// Install our interrupt handler (irq 1 uses interrupt 33)
	setvect (irq, i86_kbrd_irq);

	// assume BAT test is good. If there is a problem, the IRQ handler where catch the error
	_kbrd_bat_res = true;
	_scancode = 0;

	// set lock keys and led lights
	lock.num = lock.scroll = lock.caps = false;
	kkbrd_set_leds (false, false, false);
	key_buffer_init();

	// shift, ctrl, and alt keys
	hold.shift = hold.alt = hold.ctrl = false;
}


//Key buffer functions
void key_buffer_init()
{
	buffer_current_key = -1;
	buffer_last_key = -1;
	for(int k = 0; k < KEY_BUFFER_SIZE; k++){
		key_buffer[k] = KEY_UNKNOWN;
	}
}

void key_buffer_add(KEYCODE key)
{
	if( !( (buffer_last_key+1) % KEY_BUFFER_SIZE == buffer_current_key) )
	{
		buffer_last_key = (++buffer_last_key) % KEY_BUFFER_SIZE;
		key_buffer[buffer_last_key] = key;
	}
}

void key_buffer_reset()
{
	key_buffer_init();
}


//Returns last element of the key buffer
KEYCODE kbrd_get_key () 
{
	if (buffer_last_key == buffer_current_key )
	{
		return KEY_UNKNOWN;
	}
	return key_buffer[++buffer_current_key];
}

KEYCODE kbrd_get_previous_key()
{
	return key_buffer[(buffer_current_key - 1) >= 0 ? (buffer_current_key-1) : KEY_BUFFER_SIZE -1 ];
}


// returns scroll lock state
bool	kbrd_get_scroll_lock () 
{
	return lock.scroll;
}

// returns num lock state
bool	kbrd_get_numlock () 
{
	return lock.num;
}

// returns caps lock state
bool	kbrd_get_capslock ()	
{
	return lock.caps;
}

// returns status of control key
bool	kbrd_get_ctrl ()	
{
	return hold.ctrl;
}

// returns status of alt key
bool	kbrd_get_alt () 
{
	return hold.alt;
}

// returns status of shift key
bool	kbrd_get_shift ()	
{
	return hold.shift;
}



// return last scan code
uint8_t kbrd_get_last_scan ()	
{
	return _scancode;
}


// read status from keyboard controller
uint8_t kbrd_ctrl_read_status () 
{
	return inportb (kbrd_CTRL_STATS_REG);
}

// send command byte to keyboard controller
void kbrd_ctrl_send_cmd (uint8_t cmd) 
{
	// wait for kbrd controller input buffer to be clear
	while (1)
		if ( (kbrd_ctrl_read_status () & kbrd_CTRL_STATS_MASK_IN_BUF) == 0)
			break;

	outportb (kbrd_CTRL_CMD_REG, cmd);
}

// read keyboard encoder buffer
uint8_t kbrd_enc_read_buf () 
{
	return inportb (kbrd_ENC_INPUT_BUF);
}

// send command byte to keyboard encoder
void kbrd_enc_send_cmd (uint8_t cmd) 
{
	// wait for kbrd controller input buffer to be clear
	while (1)
		if ( (kbrd_ctrl_read_status () & kbrd_CTRL_STATS_MASK_IN_BUF) == 0)
			break;

	// send command byte to kbrd encoder
	outportb (kbrd_ENC_CMD_REG, cmd);
}

//	keyboard interrupt handler
void i86_kbrd_irq () 
{
	static bool _extended = false;

	int code = 0;

	// read scan code only if the kbrd controller output buffer is full (scan code is in it)
	if (kbrd_ctrl_read_status () & kbrd_CTRL_STATS_MASK_OUT_BUF) {

		// read the scan code
		code = kbrd_enc_read_buf ();

		// is this an extended code? If so, set it and return
		if (code == 0xE0 || code == 0xE1){
			_extended = true;
		}
		else {

			// either the second byte of an extended scan code or a single byte scan code
			_extended = false;

			// test if this is a break code (Original XT Scan Code Set specific)
			if (code & 0x80) {	//test bit 7

				// covert the break code into its make code equivelant
				code -= 0x80;

				// grab the key
				int key = _kbrd_scancode_std [code];

				// test if a special key has been released & set it
				switch (key) {

					case KEY_LCTRL:
					case KEY_RCTRL:
						hold.ctrl = false;
						break;

					case KEY_LSHIFT:
					case KEY_RSHIFT:
						hold.shift = false;
						break;

					case KEY_LALT:
					case KEY_RALT:
						hold.alt = false;
						break;
				}
			}
			else {

				// this is a make code - set the scan code
				_scancode = code;

				// grab the key
				int key = _kbrd_scancode_std [code];

				// test if user is holding down any special keys & set it
				switch (key) {

					case KEY_LCTRL:
					case KEY_RCTRL:
						hold.ctrl = true;
						break;

					case KEY_LSHIFT:
					case KEY_RSHIFT:
						hold.shift = true;
						break;

					case KEY_LALT:
					case KEY_RALT:
						hold.alt = true;
						break;

					case KEY_CAPSLOCK:
						lock.caps = (lock.caps) ? false : true;
						kbrd_set_leds (lock.num, lock.caps, lock.scroll);
						break;

					case KEY_KP_NUMLOCK:
						lock.num = (lock.num) ? false : true;
						kbrd_set_leds (lock.num, lock.caps, lock.scroll);
						break;

					case KEY_SCROLLLOCK:
						lock.scroll = (lock.scroll) ? false : true;
						kbrd_set_leds (lock.num, lock.caps, lock.scroll);
						break;
					default key_buffer_add(key);
				}
			}
		}

		// watch for errors
		switch (code) {

			case KBRD_ERR_BAT_FAILED:
				_kbrd_bat_res = false;
				break;

			case KBRD_ERR_DIAG_FAILED:
				_kbrd_diag_res = false;
				break;

			case KBRD_ERR_RESEND_CMD:
				_kbrd_resend_res = true;
				break;
		}
	}
}