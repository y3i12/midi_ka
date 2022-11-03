/*
 * Copyright (c) 2016 Evan Kale
 * Email: EvanKale91@gmail.com
 * Website: www.ISeeDeadPixel.com
 *          www.evankale.blogspot.ca
 *
 * This file is part of ArduinoMidiPS2.
 *
 * ArduinoMidiPS2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// #include "MagicMusicKeyboard.h"

// //MIDI baud rate
// #define SERIAL_RATE 31250

// //PS2 pins
// #define KBD1_CLOCK 4  
// #define KBD1_DATA 5
// // #define KBD2_CLOCK 6
// // #define KBD2_DATA 7
// // #define KBD3_CLOCK 8
// // #define KBD3_DATA 9
// // #define KBD4_CLOCK 10
// // #define KBD4_DATA 11

// //First note offsets
// #define KBD1_OFFSET 21
// // #define KBD2_OFFSET 33
// // #define KBD3_OFFSET 45
// // #define KBD4_OFFSET 57

// MagicMusicKeyboard magicMusicKeyboard1(KBD1_CLOCK, KBD1_DATA, KBD1_OFFSET);
// // MagicMusicKeyboard magicMusicKeyboard2(KBD2_CLOCK, KBD2_DATA, KBD2_OFFSET);
// // MagicMusicKeyboard magicMusicKeyboard3(KBD3_CLOCK, KBD3_DATA, KBD3_OFFSET);
// // MagicMusicKeyboard magicMusicKeyboard4(KBD4_CLOCK, KBD4_DATA, KBD4_OFFSET);

// void setup()
// {
// 	Serial.begin(SERIAL_RATE);
// 	magicMusicKeyboard1.init();
// 	// magicMusicKeyboard2.init();
// 	// magicMusicKeyboard3.init();
// 	// magicMusicKeyboard4.init();
// }

// void loop()
// {
// 	magicMusicKeyboard1.update();
// 	// magicMusicKeyboard2.update();
// 	// magicMusicKeyboard3.update();
// 	// magicMusicKeyboard4.update();
// }


/* Advanced keyboard example test to serial port at 115200 with command setting

  PS2KeyAdvanced library example

  Advanced support PS2 Keyboard to get every key code byte from a PS2 Keyboard
  for testing purposes. Enables capture of all keys output to serial monitor.

  IMPORTANT WARNING

    If using a DUE or similar board with 3V3 I/O you MUST put a level translator
    like a Texas Instruments TXS0102 or FET circuit as the signals are
    Bi-directional (signals transmitted from both ends on same wire).

    Failure to do so may damage your Arduino Due or similar board.

  Test History
    September 2014 Uno and Mega 2560 September 2014 using Arduino V1.6.0
    January 2016   Uno, Mega 2560 and Due using Arduino 1.6.7 and Due Board
                    Manager V1.6.6

  This is for a LATIN style keyboard using Scan code set 2. See various
  websites on what different scan code sets use. Scan Code Set 2 is the
  default scan code set for PS2 keyboards on power up.

  Will support most keyboards even ones with multimedia keys or even 24 function keys.

  Also allows keys entered to send commands to keyboard as follows
    R = Reset       Send reset command to keyboard and get responses
    E = Echo        Send protocol ECHO command (0xEE) and get same back
    I = ReadID      Read the keyboard ID code ( should 2 bytes 0xAb 0x83)
    S = Scancode    Get current Scancode set in use on keyboard should be 2
    T = Typematic rate Set to slowest Rate and delay
    G = Current Lock Get the current lock status (num, scroll, caps)
    B = Break codes Toggle if receiving break codes is on or off
    N = No repeat   Ignore repeats of make codes for Shift, Ctrl, ALT, ALT-GR, GUI

  The circuit:
   * KBD Clock (PS2 pin 1) to an interrupt pin on Arduino ( this example pin 3 )
   * KBD Data (PS2 pin 5) to a data pin ( this example pin 4 )
   * +5V from Arduino to PS2 pin 4
   * GND from Arduino to PS2 pin 3

   The connector to mate with PS2 keyboard is a 6 pin Female Mini-Din connector
   PS2 Pins to signal
    1       KBD Data
    3       GND
    4       +5V
    5       KBD Clock

   Keyboard has 5V and GND connected see plenty of examples and
   photos around on Arduino site and other sites about the PS2 Connector.

 Interrupts

   Clock pin from PS2 keyboard MUST be connected to an interrupt
   pin, these vary with the different types of Arduino

  PS2KeyAdvanced requires both pins specified for begin( )

  keyboard.begin( data_pin, irq_pin );

  Valid irq pins:
     Arduino Uno:  2, 3
     Arduino Due:  All pins, except 13 (LED)
     Arduino Mega: 2, 3, 18, 19, 20, 21
     Teensy 2.0:   All pins, except 13 (LED)
     Teensy 2.0:   5, 6, 7, 8
     Teensy 1.0:   0, 1, 2, 3, 4, 6, 7, 16
     Teensy++ 2.0: 0, 1, 2, 3, 18, 19, 36, 37
     Teensy++ 1.0: 0, 1, 2, 3, 18, 19, 36, 37
     Sanguino:     2, 10, 11

  Read method Returns an UNSIGNED INT containing
        Make/Break status
        Caps status
        Shift, CTRL, ALT, ALT GR, GUI keys
        Flag for function key not a displayable/printable character
        8 bit key code

  Code Ranges (bottom byte of unsigned int)
        0       invalid/error
        1-1F    Functions (Caps, Shift, ALT, Enter, DEL... )
        1A-1F   Functions with ASCII control code
                    (DEL, BS, TAB, ESC, ENTER, SPACE)
        20-61   Printable characters noting
                    0-9 = 0x30 to 0x39 as ASCII
                    A to Z = 0x41 to 0x5A as upper case ASCII type codes
                    8B Extra European key
        61-A0   Function keys and other special keys (plus F2 and F1)
                    61-78 F1 to F24
                    79-8A Multimedia
                    8B NOT included
                    8C-8E ACPI power
                    91-A0 and F2 and F1 - Special multilingual
        A8-FF   Keyboard communications commands (note F2 and F1 are special
                codes for special multi-lingual keyboards)

    By using these ranges it is possible to perform detection of any key and do
    easy translation to ASCII/UTF-8 avoiding keys that do not have a valid code.

    Top Byte is 8 bits denoting as follows with defines for bit code

        Define name bit     description
        PS2_BREAK   15      1 = Break key code
                   (MSB)    0 = Make Key code
        PS2_SHIFT   14      1 = Shift key pressed as well (either side)
                            0 = NO shift key
        PS2_CTRL    13      1 = Ctrl key pressed as well (either side)
                            0 = NO Ctrl key
        PS2_CAPS    12      1 = Caps Lock ON
                            0 = Caps lock OFF
        PS2_ALT     11      1 = Left Alt key pressed as well
                            0 = NO Left Alt key
        PS2_ALT_GR  10      1 = Right Alt (Alt GR) key pressed as well
                            0 = NO Right Alt key
        PS2_GUI      9      1 = GUI key pressed as well (either)
                            0 = NO GUI key
        PS2_FUNCTION 8      1 = FUNCTION key non-printable character (plus space, tab, enter)
                            0 = standard character key

  Error Codes
     Most functions return 0 or 0xFFFF as error, other codes to note and
     handle appropriately
        0xAA   keyboard has reset and passed power up tests
               will happen if keyboard plugged in after code start
        0xFC   Keyboard General error or power up fail

  See PS2Keyboard.h file for returned definitions of Keys

  Note defines starting
            PS2_KEY_* are the codes this library returns
            PS2_*     remaining defines for use in higher levels

  To get the key as ASCII/UTF-8 single byte character conversion requires use
  of PS2KeyMap library AS WELL.

  Written by Paul Carpenter, PC Services <sales@pcserviceselectronics.co.uk>
*/

#include "PS2KeyAdvanced.h"

/* Keyboard constants  Change to suit your Arduino
   define pins used for data and clock from keyboard */
#define DATAPIN 4
#define IRQPIN  2

uint16_t c;
uint8_t breaks = 0;
uint8_t repeats = 0;
const char * gKeyNames[0xFF];

PS2KeyAdvanced keyboard;


void setup( )
{
  for (int i = 0; i< 0xff; ++i) {
    gKeyNames[i] = 0;
  }
  
  gKeyNames[PS2_LOCK_SCROLL] = "SCROLL";
  gKeyNames[PS2_LOCK_NUM] = "NUM";
  gKeyNames[PS2_LOCK_CAPS] = "CAPS";
  gKeyNames[PS2_LOCK_EXTRA] = "EXTRA";
  gKeyNames[PS2_KEY_NUM] = "NUM";
  gKeyNames[PS2_KEY_SCROLL] = "SCROLL";
  gKeyNames[PS2_KEY_CAPS] = "CAPS";
  gKeyNames[PS2_KEY_PRTSCR] = "PRTSCR";
  gKeyNames[PS2_KEY_PAUSE] = "PAUSE";
  gKeyNames[PS2_KEY_L_SHIFT] = "L_SHIFT";
  gKeyNames[PS2_KEY_R_SHIFT] = "R_SHIFT";
  gKeyNames[PS2_KEY_L_CTRL] = "L_CTRL";
  gKeyNames[PS2_KEY_R_CTRL] = "R_CTRL";
  gKeyNames[PS2_KEY_L_ALT] = "L_ALT";
  gKeyNames[PS2_KEY_R_ALT] = "R_ALT";
  gKeyNames[PS2_KEY_L_GUI] = "L_GUI";
  gKeyNames[PS2_KEY_R_GUI] = "R_GUI";
  gKeyNames[PS2_KEY_MENU] = "MENU";
  gKeyNames[PS2_KEY_BREAK] = "BREAK";
  gKeyNames[PS2_KEY_HOME] = "HOME";
  gKeyNames[PS2_KEY_END] = "END";
  gKeyNames[PS2_KEY_PGUP] = "PGUP";
  gKeyNames[PS2_KEY_PGDN] = "PGDN";
  gKeyNames[PS2_KEY_L_ARROW] = "L_ARROW";
  gKeyNames[PS2_KEY_R_ARROW] = "R_ARROW";
  gKeyNames[PS2_KEY_UP_ARROW] = "UP_ARROW";
  gKeyNames[PS2_KEY_DN_ARROW] = "DN_ARROW";
  gKeyNames[PS2_KEY_INSERT] = "INSERT";
  gKeyNames[PS2_KEY_DELETE] = "DELETE";
  gKeyNames[PS2_KEY_ESC] = "ESC";
  gKeyNames[PS2_KEY_BS] = "BS";
  gKeyNames[PS2_KEY_TAB] = "TAB";
  gKeyNames[PS2_KEY_ENTER] = "ENTER";
  gKeyNames[PS2_KEY_SPACE] = "SPACE";
  gKeyNames[PS2_KEY_KP0] = "KP0";
  gKeyNames[PS2_KEY_KP1] = "KP1";
  gKeyNames[PS2_KEY_KP2] = "KP2";
  gKeyNames[PS2_KEY_KP3] = "KP3";
  gKeyNames[PS2_KEY_KP4] = "KP4";
  gKeyNames[PS2_KEY_KP5] = "KP5";
  gKeyNames[PS2_KEY_KP6] = "KP6";
  gKeyNames[PS2_KEY_KP7] = "KP7";
  gKeyNames[PS2_KEY_KP8] = "KP8";
  gKeyNames[PS2_KEY_KP9] = "KP9";
  gKeyNames[PS2_KEY_KP_DOT] = "KP_DOT";
  gKeyNames[PS2_KEY_KP_ENTER] = "KP_ENTER";
  gKeyNames[PS2_KEY_KP_PLUS] = "KP_PLUS";
  gKeyNames[PS2_KEY_KP_MINUS] = "KP_MINUS";
  gKeyNames[PS2_KEY_KP_TIMES] = "KP_TIMES";
  gKeyNames[PS2_KEY_KP_DIV] = "KP_DIV";
  gKeyNames[PS2_KEY_0] = "0";
  gKeyNames[PS2_KEY_1] = "1";
  gKeyNames[PS2_KEY_2] = "2";
  gKeyNames[PS2_KEY_3] = "3";
  gKeyNames[PS2_KEY_4] = "4";
  gKeyNames[PS2_KEY_5] = "5";
  gKeyNames[PS2_KEY_6] = "6";
  gKeyNames[PS2_KEY_7] = "7";
  gKeyNames[PS2_KEY_8] = "8";
  gKeyNames[PS2_KEY_9] = "9";
  gKeyNames[PS2_KEY_APOS] = "APOS";
  gKeyNames[PS2_KEY_COMMA] = "COMMA";
  gKeyNames[PS2_KEY_MINUS] = "MINUS";
  gKeyNames[PS2_KEY_DOT] = "DOT";
  gKeyNames[PS2_KEY_DIV] = "DIV";
  gKeyNames[PS2_KEY_SINGLE] = "SINGLE";
  gKeyNames[PS2_KEY_A] = "A";
  gKeyNames[PS2_KEY_B] = "B";
  gKeyNames[PS2_KEY_C] = "C";
  gKeyNames[PS2_KEY_D] = "D";
  gKeyNames[PS2_KEY_E] = "E";
  gKeyNames[PS2_KEY_F] = "F";
  gKeyNames[PS2_KEY_G] = "G";
  gKeyNames[PS2_KEY_H] = "H";
  gKeyNames[PS2_KEY_I] = "I";
  gKeyNames[PS2_KEY_J] = "J";
  gKeyNames[PS2_KEY_K] = "K";
  gKeyNames[PS2_KEY_L] = "L";
  gKeyNames[PS2_KEY_M] = "M";
  gKeyNames[PS2_KEY_N] = "N";
  gKeyNames[PS2_KEY_O] = "O";
  gKeyNames[PS2_KEY_P] = "P";
  gKeyNames[PS2_KEY_Q] = "Q";
  gKeyNames[PS2_KEY_R] = "R";
  gKeyNames[PS2_KEY_S] = "S";
  gKeyNames[PS2_KEY_T] = "T";
  gKeyNames[PS2_KEY_U] = "U";
  gKeyNames[PS2_KEY_V] = "V";
  gKeyNames[PS2_KEY_W] = "W";
  gKeyNames[PS2_KEY_X] = "X";
  gKeyNames[PS2_KEY_Y] = "Y";
  gKeyNames[PS2_KEY_Z] = "Z";
  gKeyNames[PS2_KEY_SEMI] = "SEMI";
  gKeyNames[PS2_KEY_BACK] = "BACK";
  gKeyNames[PS2_KEY_OPEN_SQ] = "OPEN_SQ";
  gKeyNames[PS2_KEY_CLOSE_SQ] = "CLOSE_SQ";
  gKeyNames[PS2_KEY_EQUAL] = "EQUAL";
  gKeyNames[PS2_KEY_F1] = "F1";
  gKeyNames[PS2_KEY_F2] = "F2";
  gKeyNames[PS2_KEY_F3] = "F3";
  gKeyNames[PS2_KEY_F4] = "F4";
  gKeyNames[PS2_KEY_F5] = "F5";
  gKeyNames[PS2_KEY_F6] = "F6";
  gKeyNames[PS2_KEY_F7] = "F7";
  gKeyNames[PS2_KEY_F8] = "F8";
  gKeyNames[PS2_KEY_F9] = "F9";
  gKeyNames[PS2_KEY_F10] = "F10";
  gKeyNames[PS2_KEY_F11] = "F11";
  gKeyNames[PS2_KEY_F12] = "F12";

  Serial.begin( 115200 );
  Serial.println( "PS2 Advanced Key - Advanced Test:" );

  // Configure the keyboard library
  int status = keyboard.begin( DATAPIN, IRQPIN );

  if ( status < 0 ) 
  {
    Serial.println( "Keyboard Not Found" );
  }
  else if ( status > 0 )
  {
    Serial.print( "Invalid Code received of " );
    Serial.println( status, HEX );
  }
}


void loop( )
{
  if( keyboard.available( ) )
  {
    // read the next key
    c = keyboard.read( );
    //Serial.println( c , HEX );
    if( ( c & 0xFF ) > 0 )
    {
      if (gKeyNames[c & 0xFF]) 
      {
        Serial.print( "Key Press: " );
        Serial.println( gKeyNames[c & 0xFF] );
      }
    }
  
    /* now do something with keys entered results on serial monitor */
    // if( !( c & PS2_BREAK ) )  // only on make codes
    // {
    //   switch( c & 0xFF )
    //   {
    //   case PS2_KEY_R:
    //                 Serial.println( "Reset" );
    //                 keyboard.resetKey( );  // Reset keyboard
    //                 break;
    //   case PS2_KEY_S:
    //                 Serial.println( "Get Scancode set in use" );
    //                 keyboard.getScanCodeSet( );  // Get which scan code set
    //                 break;
    //   case PS2_KEY_G:
    //                 Serial.print( "Get current lock status = " );
    //                 c = keyboard.getLock( );  // Get current lock status
    //                 Serial.println( c, HEX );
    //                 break;
    //   case PS2_KEY_I:
    //                 Serial.println( "Read ID code" );
    //                 keyboard.readID( );  // Get which scan code set
    //                 break;
    //   case PS2_KEY_E:
    //                 Serial.println( "Echo" );
    //                 keyboard.echo( );
    //                 break;
    //   case PS2_KEY_T:
    //                 Serial.println( "Typematic Rate" );
    //                 keyboard.typematic( 31, 3);  // Get slowest
    //                 break;
    //   case PS2_KEY_B:
    //                 Serial.print( "No Break Codes " );
    //                 breaks ^= 1;;
    //                 Serial.println( breaks );
    //                 keyboard.setNoBreak( breaks );  // set break mode
    //                 break;
    //   case PS2_KEY_N:
    //                 Serial.print( "No Repeat Makes for CTRL... " );
    //                 repeats ^= 1;
    //                 Serial.println( repeats );
    //                 keyboard.setNoRepeat( repeats );  // Set repeat mode
    //                 break;
    //   }
    // }
  }
}
