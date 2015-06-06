

enum KEYCODE {

// Alphanumeric keys ////////////////

	KEY_SPACE             = ' ',
	KEY_0                 = '0',
	KEY_1                 = '1',
	KEY_2                 = '2',
	KEY_3                 = '3',
	KEY_4                 = '4',
	KEY_5                 = '5',
	KEY_6                 = '6',
	KEY_7                 = '7',
	KEY_8                 = '8',
	KEY_9                 = '9',

	KEY_A                 = 'a',
	KEY_B                 = 'b',
	KEY_C                 = 'c',
	KEY_D                 = 'd',
	KEY_E                 = 'e',
	KEY_F                 = 'f',
	KEY_G                 = 'g',
	KEY_H                 = 'h',
	KEY_I                 = 'i',
	KEY_J                 = 'j',
	KEY_K                 = 'k',
	KEY_L                 = 'l',
	KEY_M                 = 'm',
	KEY_N                 = 'n',
	KEY_O                 = 'o',
	KEY_P                 = 'p',
	KEY_Q                 = 'q',
	KEY_R                 = 'r',
	KEY_S                 = 's',
	KEY_T                 = 't',
	KEY_U                 = 'u',
	KEY_V                 = 'v',
	KEY_W                 = 'w',
	KEY_X                 = 'x',
	KEY_Y                 = 'y',
	KEY_Z                 = 'z',

	KEY_RETURN            = '\r',
	KEY_ESCAPE            = 0x1001,
	KEY_BACKSPACE         = '\b',

// Arrow keys ////////////////////////

	KEY_UP                = 0x1100,
	KEY_DOWN              = 0x1101,
	KEY_LEFT              = 0x1102,
	KEY_RIGHT             = 0x1103,

// Function keys /////////////////////

	KEY_F1                = 0x1201,
	KEY_F2                = 0x1202,
	KEY_F3                = 0x1203,
	KEY_F4                = 0x1204,
	KEY_F5                = 0x1205,
	KEY_F6                = 0x1206,
	KEY_F7                = 0x1207,
	KEY_F8                = 0x1208,
	KEY_F9                = 0x1209,
	KEY_F10               = 0x120a,
	KEY_F11               = 0x120b,
	KEY_F12               = 0x120b,
	KEY_F13               = 0x120c,
	KEY_F14               = 0x120d,
	KEY_F15               = 0x120e,

	KEY_DOT               = '.',
	KEY_COMMA             = ',',
	KEY_COLON             = ':',
	KEY_SEMICOLON         = ';',
	KEY_SLASH             = '/',
	KEY_BACKSLASH         = '\\',
	KEY_PLUS              = '+',
	KEY_MINUS             = '-',
	KEY_ASTERISK          = '*',
	KEY_EXCLAMATION       = '!',
	KEY_QUESTION          = '?',
	KEY_QUOTEDOUBLE       = '\"',
	KEY_QUOTE             = '\'',
	KEY_EQUAL             = '=',
	KEY_HASH              = '#',
	KEY_PERCENT           = '%',
	KEY_AMPERSAND         = '&',
	KEY_UNDERSCORE        = '_',
	KEY_LEFTPARENTHESIS   = '(',
	KEY_RIGHTPARENTHESIS  = ')',
	KEY_LEFTBRACKET       = '[',
	KEY_RIGHTBRACKET      = ']',
	KEY_LEFTCURL          = '{',
	KEY_RIGHTCURL         = '}',
	KEY_DOLLAR            = '$',
	KEY_POUND             = '£',
	KEY_EURO              = '$',
	KEY_LESS              = '<',
	KEY_GREATER           = '>',
	KEY_BAR               = '|',
	KEY_GRAVE             = '`',
	KEY_TILDE             = '~',
	KEY_AT                = '@',
	KEY_CARRET            = '^',

// Numeric keypad //////////////////////

	KEY_KP_0              = '0',
	KEY_KP_1              = '1',
	KEY_KP_2              = '2',
	KEY_KP_3              = '3',
	KEY_KP_4              = '4',
	KEY_KP_5              = '5',
	KEY_KP_6              = '6',
	KEY_KP_7              = '7',
	KEY_KP_8              = '8',
	KEY_KP_9              = '9',
	KEY_KP_PLUS           = '+',
	KEY_KP_MINUS          = '-',
	KEY_KP_DECIMAL        = '.',
	KEY_KP_DIVIDE         = '/',
	KEY_KP_ASTERISK       = '*',
	KEY_KP_NUMLOCK        = 0x300f,
	KEY_KP_ENTER          = 0x3010,

	KEY_TAB               = 0x4000,
	KEY_CAPSLOCK          = 0x4001,

// Modify keys ////////////////////////////

	KEY_LSHIFT            = 0x4002,
	KEY_LCTRL             = 0x4003,
	KEY_LALT              = 0x4004,
	KEY_LWIN              = 0x4005,
	KEY_RSHIFT            = 0x4006,
	KEY_RCTRL             = 0x4007,
	KEY_RALT              = 0x4008,
	KEY_RWIN              = 0x4009,

	KEY_INSERT            = 0x400a,
	KEY_DELETE            = 0x400b,
	KEY_HOME              = 0x400c,
	KEY_END               = 0x400d,
	KEY_PAGEUP            = 0x400e,
	KEY_PAGEDOWN          = 0x400f,
	KEY_SCROLLLOCK        = 0x4010,
	KEY_PAUSE             = 0x4011,

	KEY_UNKNOWN,
	KEY_NUMKEYCODES
};



uint8_t kybrd_ctrl_read_status () {
 
	return (unit8_t)*KYBRD_CTRL_STATS_REG;
}


//! send command byte to keyboard controller
void kybrd_ctrl_send_cmd (uint8_t cmd) {
 
	//! wait for kkybrd controller input buffer to be clear
	while (1)
		if ( (kybrd_ctrl_read_status () & KYBRD_CTRL_STATS_MASK_IN_BUF) == 0)
			break;
 
	outportb (KYBRD_CTRL_CMD_REG, cmd);



	//! send command byte to keyboard controller
void kybrd_ctrl_send_cmd (uint8_t cmd) {
 
	//! wait for kkybrd controller input buffer to be clear
	while (1)
		if ( (kybrd_ctrl_read_status () & KYBRD_CTRL_STATS_MASK_IN_BUF) == 0)
			break;
 
	outportb (KYBRD_CTRL_CMD_REG, cmd);
}



//! read keyboard encoder buffer
uint8_t kybrd_enc_read_buf () {
 
	return inportb (KYBRD_ENC_INPUT_BUF);
}
 
//! send command byte to keyboard encoder
void kybrd_enc_send_cmd (uint8_t cmd) {
 
	//! wait for kkybrd controller input buffer to be clear
	while ((kybrd_ctrl_read_status () & KYBRD_CTRL_STATS_MASK_IN_BUF) != 0){

	}

	//! send command byte to kybrd encoder
	outportb (KYBRD_ENC_CMD_REG, cmd);
}





//! sets leds
void kkybrd_set_leds (bool num, bool caps, bool scroll) {
 
	uint8_t data = 0;
 
	//! set or clear the bit
	data = (scroll) ? (data | 1) : (data & 1);
	data = (num) ? (num | 2) : (num & 2);
	data = (caps) ? (num | 4) : (num & 4);
 
	//! send the command -- update keyboard Light Emetting Diods (LEDs)
	kybrd_enc_send_cmd (KYBRD_ENC_CMD_SET_LED);
	kybrd_enc_send_cmd (data);


//! run self test
bool kkybrd_self_test () {
 
	//! send command
	kybrd_ctrl_send_cmd (KYBRD_CTRL_CMD_SELF_TEST);
 
	//! wait for output buffer to be full
	while (1)
		if (kybrd_ctrl_read_status () & KYBRD_CTRL_STATS_MASK_OUT_BUF)
			break;
 
	//! if output buffer == 0x55, test passed
	return (kybrd_enc_read_buf () == 0x55) ? true : false;
}


//Command 0xAB - Interface Test


//! disables the keyboard
void kkybrd_disable () {
 
	kybrd_ctrl_send_cmd (KYBRD_CTRL_CMD_DISABLE);
	_kkybrd_disable = true;
}


//! enables the keyboard
void kkybrd_enable () {
 
	kybrd_ctrl_send_cmd (KYBRD_CTRL_CMD_ENABLE);
	_kkybrd_disable = false;
}


//! reset the system
void kkybrd_reset_system () {
 
	//! writes 11111110 to the output port (sets reset system line low)
	kybrd_ctrl_send_cmd (KYBRD_CTRL_CMD_WRITE_OUT_PORT);
	kybrd_enc_send_cmd (0xfe);
}



//! prepares driver for use
void kkybrd_install (int irq) {
 
	//! Install our interrupt handler (irq 1 uses interrupt 33)
	setvect (irq, i86_kybrd_irq);
 
	//! assume Basic Assurance test (BAT) test is good
	_kkybrd_bat_res = true;
	_scancode = 0;
 
	//! set lock keys and led lights
	_numlock = _scrolllock = _capslock = false;
	kkybrd_set_leds (false, false, false);
 
	//! shift, ctrl, and alt keys
	_shift = _alt = _ctrl = false;
}

/*****************************************************************************
*****************************************************************************/
void outportb(unsigned port, unsigned val)
{
 
__asm__ __volatile__("outb %b0,%w1"
:
: "a"(val), "d"(port));
 
}


/*****************************************************************************
*****************************************************************************/
unsigned inportb(unsigned short port)
{
 
unsigned char ret_val;
 
__asm__ __volatile__("inb %1,%0"
: "=a"(ret_val)
: "d"(port));
return ret_val;
 
}











