/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   XK_defines.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:12:30 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/18 13:55:03 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XK_DEFINES_H
# define XK_DEFINES_H

# define XK_Escape						  0xff1b

# define XK_KP_SPACE                      0xff80  /* Space */
# define XK_KP_TAB                        0xff89
# define XK_KP_ENTER                      0xff8d  /* Enter */
# define XK_KP_F1                         0xff91  /* PF1, KP_A, ... */
# define XK_KP_F2                         0xff92
# define XK_KP_F3                         0xff93
# define XK_KP_F4                         0xff94
# define XK_KP_HOME                       0xff95
# define XK_KP_LEFT                       0xff96
# define XK_KP_UP                         0xff97
# define XK_KP_RIGHT                      0xff98
# define XK_KP_DOWN                       0xff99
# define XK_KP_PRIOR                      0xff9a
# define XK_KP_PAGE_UP                    0xff9a
# define XK_KP_NEXT                       0xff9b
# define XK_KP_PAGE_DOWN                  0xff9b
# define XK_KP_END                        0xff9c
# define XK_KP_BEGIN                      0xff9d
# define XK_KP_INSERT                     0xff9e
# define XK_KP_DELETE                     0xff9f
# define XK_KP_EQUAL                      0xffbd  /* Equals */
# define XK_KP_MULTIPLY                   0xffaa
# define XK_KP_ADD                        0xffab
# define XK_KP_SEPARATOR                  0xffac  /* Separator, often comma */
# define XK_KP_SUBTRACT                   0xffad
# define XK_KP_DECIMAL                    0xffae
# define XK_KP_DIVIDE                     0xffaf

# define XK_KP_0                          65438
# define XK_KP_1                          65436
# define XK_KP_2                          65433
# define XK_KP_3                          65435
# define XK_KP_4                          65430
# define XK_KP_5                          65437
# define XK_KP_6                          65432
# define XK_KP_7                          65429
# define XK_KP_8                          65431
# define XK_KP_9                          65434
# define XK_KP_Q                             113
# define XK_KP_W                             119
# define XK_KP_E                             101
# define XK_KP_A                             97
# define XK_KP_S                             115
# define XK_KP_D                             100


# define XK_KP_SUBTRACT	0xffad
# define XK_KP_ADD		0xffab

# ifndef XK_LATIN1
#  define XK_LATIN1

#  define XK_SPACE                         0x0020  /* U+0020 SPACE */
#  define XK_EXCLAM                        0x0021  /* U+0021 EXCLAMATION MARK */
#  define XK_QUOTEDBL                      0x0022  /* U+0022 QUOTATION MARK */
#  define XK_NUMBERSIGN                    0x0023  /* U+0023 NUMBER SIGN */
#  define XK_DOLLAR                        0x0024  /* U+0024 DOLLAR SIGN */
#  define XK_PERCENT                       0x0025  /* U+0025 PERCENT SIGN */
#  define XK_AMPERSAND                     0x0026  /* U+0026 AMPERSAND */
#  define XK_APOSTROPHE                    0x0027  /* U+0027 APOSTROPHE */
#  define XK_QUOTERIGHT                    0x0027  /* deprecated */
#  define XK_PARENLEFT                     0x0028  /* U+0028 LEFT PARENTHESIS */
#  define XK_PARENRIGHT                    0x0029  /* U+0029 RIGHT PARENTHESIS */
#  define XK_ASTERISK                      0x002a  /* U+002A ASTERISK */
#  define XK_PLUS                          0x002b  /* U+002B PLUS SIGN */
#  define XK_COMMA                         0x002c  /* U+002C COMMA */
#  define XK_MINUS                         0x002d  /* U+002D HYPHEN-MINUS */
#  define XK_PERIOD                        0x002e  /* U+002E FULL STOP */
#  define XK_SLASH                         0x002f  /* U+002F SOLIDUS */
#  define XK_0                             0x0030  /* U+0030 DIGIT ZERO */
#  define XK_1                             0x0031  /* U+0031 DIGIT ONE */
#  define XK_2                             0x0032  /* U+0032 DIGIT TWO */
#  define XK_3                             0x0033  /* U+0033 DIGIT THREE */
#  define XK_4                             0x0034  /* U+0034 DIGIT FOUR */
#  define XK_5                             0x0035  /* U+0035 DIGIT FIVE */
#  define XK_6                             0x0036  /* U+0036 DIGIT SIX */
#  define XK_7                             0x0037  /* U+0037 DIGIT SEVEN */
#  define XK_8                             0x0038  /* U+0038 DIGIT EIGHT */
#  define XK_9                             0x0039  /* U+0039 DIGIT NINE */
#  define XK_COLON                         0x003a  /* U+003A COLON */
#  define XK_SEMICOLON                     0x003b  /* U+003B SEMICOLON */
#  define XK_LESS                          0x003c  /* U+003C LESS-THAN SIGN */
#  define XK_EQUAL                         0x003d  /* U+003D EQUALS SIGN */
#  define XK_GREATER                       0x003e  /* U+003E GREATER-THAN SIGN */
#  define XK_QUESTION                      0x003f  /* U+003F QUESTION MARK */
#  define XK_AT                            0x0040  /* U+0040 COMMERCIAL AT */
#  define XK_UA                             0x0041  /* U+0041 LATIN CAPITAL LETTER A */
#  define XK_UB                             0x0042  /* U+0042 LATIN CAPITAL LETTER B */
#  define XK_UC                             0x0043  /* U+0043 LATIN CAPITAL LETTER C */
#  define XK_UD                             0x0044  /* U+0044 LATIN CAPITAL LETTER D */
#  define XK_UE                             0x0045  /* U+0045 LATIN CAPITAL LETTER E */
#  define XK_UF                             0x0046  /* U+0046 LATIN CAPITAL LETTER F */
#  define XK_UG                             0x0047  /* U+0047 LATIN CAPITAL LETTER G */
#  define XK_UH                             0x0048  /* U+0048 LATIN CAPITAL LETTER H */
#  define XK_UI                             0x0049  /* U+0049 LATIN CAPITAL LETTER I */
#  define XK_UJ                             0x004a  /* U+004A LATIN CAPITAL LETTER J */
#  define XK_UK                             0x004b  /* U+004B LATIN CAPITAL LETTER K */
#  define XK_UL                             0x004c  /* U+004C LATIN CAPITAL LETTER L */
#  define XK_UM                             0x004d  /* U+004D LATIN CAPITAL LETTER M */
#  define XK_UN                             0x004e  /* U+004E LATIN CAPITAL LETTER N */
#  define XK_UO                             0x004f  /* U+004F LATIN CAPITAL LETTER O */
#  define XK_UP                             0x0050  /* U+0050 LATIN CAPITAL LETTER P */
#  define XK_UQ                             0x0051  /* U+0051 LATIN CAPITAL LETTER Q */
#  define XK_UR                             0x0052  /* U+0052 LATIN CAPITAL LETTER R */
#  define XK_US                             0x0053  /* U+0053 LATIN CAPITAL LETTER S */
#  define XK_UT                             0x0054  /* U+0054 LATIN CAPITAL LETTER T */
#  define XK_UU                             0x0055  /* U+0055 LATIN CAPITAL LETTER U */
#  define XK_UV                             0x0056  /* U+0056 LATIN CAPITAL LETTER V */
#  define XK_UW                             0x0057  /* U+0057 LATIN CAPITAL LETTER W */
#  define XK_UX                             0x0058  /* U+0058 LATIN CAPITAL LETTER X */
#  define XK_UY                             0x0059  /* U+0059 LATIN CAPITAL LETTER Y */
#  define XK_UZ                             0x005a  /* U+005A LATIN CAPITAL LETTER Z */
#  define XK_BRACKETLEFT                   0x005b  /* U+005B LEFT SQUARE BRACKET */
#  define XK_BACKSLASH                         45  /* U+005C REVERSE SOLIDUS */
#  define XK_BRACKETRIGHT                  0x005d  /* U+005D RIGHT SQUARE BRACKET */
#  define XK_ASCIICIRCUM                   0x005e  /* U+005E CIRCUMFLEX ACCENT */
#  define XK_UNDERSCORE                    0x005f  /* U+005F LOW LINE */
#  define XK_GRAVE                         0x0060  /* U+0060 GRAVE ACCENT */
#  define XK_QUOTELEFT                     0x0060  /* deprecated */
#  define XK_A                             0x0061  /* U+0061 LATIN SMALL LETTER A */
#  define XK_B                             0x0062  /* U+0062 LATIN SMALL LETTER B */
#  define XK_C                             0x0063  /* U+0063 LATIN SMALL LETTER C */
#  define XK_D                             0x0064  /* U+0064 LATIN SMALL LETTER D */
#  define XK_E                             0x0065  /* U+0065 LATIN SMALL LETTER E */
#  define XK_F                             0x0066  /* U+0066 LATIN SMALL LETTER F */
#  define XK_G                             0x0067  /* U+0067 LATIN SMALL LETTER G */
#  define XK_H                             0x0068  /* U+0068 LATIN SMALL LETTER H */
#  define XK_I                             0x0069  /* U+0069 LATIN SMALL LETTER I */
#  define XK_J                             0x006a  /* U+006A LATIN SMALL LETTER J */
#  define XK_K                             0x006b  /* U+006B LATIN SMALL LETTER K */
#  define XK_L                             0x006c  /* U+006C LATIN SMALL LETTER L */
#  define XK_M                             0x006d  /* U+006D LATIN SMALL LETTER M */
#  define XK_N                             0x006e  /* U+006E LATIN SMALL LETTER N */
#  define XK_O                             0x006f  /* U+006F LATIN SMALL LETTER O */
#  define XK_P                             0x0070  /* U+0070 LATIN SMALL LETTER P */
#  define XK_Q                             0x0071  /* U+0071 LATIN SMALL LETTER Q */
#  define XK_R                             0x0072  /* U+0072 LATIN SMALL LETTER R */
#  define XK_S                             0x0073  /* U+0073 LATIN SMALL LETTER S */
#  define XK_T                             0x0074  /* U+0074 LATIN SMALL LETTER T */
#  define XK_U                             0x0075  /* U+0075 LATIN SMALL LETTER U */
#  define XK_V                             0x0076  /* U+0076 LATIN SMALL LETTER V */
#  define XK_W                             0x0077  /* U+0077 LATIN SMALL LETTER W */
#  define XK_X                             120  /* U+0078 LATIN SMALL LETTER X */
#  define XK_Y                             0x0079  /* U+0079 LATIN SMALL LETTER Y */
#  define XK_Z                             121  /* U+007A LATIN SMALL LETTER Z */
#  define XK_BRACELEFT                     0x007b  /* U+007B LEFT CURLY BRACKET */
#  define XK_BAR                           0x007c  /* U+007C VERTICAL LINE */
#  define XK_BRACERIGHT                    0x007d  /* U+007D RIGHT CURLY BRACKET */
#  define XK_ASCIITILDE                    0x007e  /* U+007E TILDE */

# endif

#endif
