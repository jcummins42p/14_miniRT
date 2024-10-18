/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   XK_defines.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:12:30 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/18 16:24:03 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XK_DEFINES_H
# define XK_DEFINES_H

# define XK_ESCAPE						  0xff1b

# define XK_KP_SPACE                      0xff80
# define XK_KP_TAB                        0xff89
# define XK_KP_ENTER                      0xff8d
# define XK_KP_F1                         0xff91
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
# define XK_KP_EQUAL                      0xffbd
# define XK_KP_MULTIPLY                   0xffaa
# define XK_KP_ADD                        0xffab
# define XK_KP_SEPARATOR                  0xffac
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
# define XK_KP_A                             97
# define XK_KP_D                            100
# define XK_KP_E                            101
# define XK_KP_F                            102
# define XK_KP_G                            103
# define XK_KP_Q                            113
# define XK_KP_R                            114
# define XK_KP_S                            115
# define XK_KP_T                            116
# define XK_KP_W                            119

# define XK_KP_SUBTRACT	0xffad
# define XK_KP_ADD		0xffab

# ifndef XK_LATIN1
#  define XK_LATIN1

#  define XK_SPACE                         0x0020
#  define XK_EXCLAM                        0x0021
#  define XK_QUOTEDBL                      0x0022
#  define XK_NUMBERSIGN                    0x0023
#  define XK_DOLLAR                        0x0024
#  define XK_PERCENT                       0x0025
#  define XK_AMPERSAND                     0x0026
#  define XK_APOSTROPHE                    0x0027
#  define XK_QUOTERIGHT                    0x0027
#  define XK_PARENLEFT                     0x0028
#  define XK_PARENRIGHT                    0x0029
#  define XK_ASTERISK                      0x002a
#  define XK_PLUS                          0x002b
#  define XK_COMMA                         0x002c
#  define XK_MINUS                         0x002d
#  define XK_PERIOD                        0x002e
#  define XK_SLASH                         0x002f
#  define XK_0                             0x0030
#  define XK_1                             0x0031
#  define XK_2                             0x0032
#  define XK_3                             0x0033
#  define XK_4                             0x0034
#  define XK_5                             0x0035
#  define XK_6                             0x0036
#  define XK_7                             0x0037
#  define XK_8                             0x0038
#  define XK_9                             0x0039
#  define XK_COLON                         0x003a
#  define XK_SEMICOLON                     0x003b
#  define XK_LESS                          0x003c
#  define XK_EQUAL                         0x003d
#  define XK_GREATER                       0x003e
#  define XK_QUESTION                      0x003f
#  define XK_AT                            0x0040
#  define XK_UA                             0x0041
#  define XK_UB                             0x0042
#  define XK_UC                             0x0043
#  define XK_UD                             0x0044
#  define XK_UE                             0x0045
#  define XK_UF                             0x0046
#  define XK_UG                             0x0047
#  define XK_UH                             0x0048
#  define XK_UI                             0x0049
#  define XK_UJ                             0x004a
#  define XK_UK                             0x004b
#  define XK_UL                             0x004c
#  define XK_UM                             0x004d
#  define XK_UN                             0x004e
#  define XK_UO                             0x004f
#  define XK_UP                             0x0050
#  define XK_UQ                             0x0051
#  define XK_UR                             0x0052
#  define XK_US                             0x0053
#  define XK_UT                             0x0054
#  define XK_UU                             0x0055
#  define XK_UV                             0x0056
#  define XK_UW                             0x0057
#  define XK_UX                             0x0058
#  define XK_UY                             0x0059
#  define XK_UZ                             0x005a
#  define XK_BRACKETLEFT                   0x005b
#  define XK_BACKSLASH                         45
#  define XK_BRACKETRIGHT                  0x005d
#  define XK_ASCIICIRCUM                   0x005e
#  define XK_UNDERSCORE                    0x005f
#  define XK_GRAVE                         0x0060
#  define XK_QUOTELEFT                     0x0060
#  define XK_A                             0x0061
#  define XK_B                             0x0062
#  define XK_C                             0x0063
#  define XK_D                             0x0064
#  define XK_E                             0x0065
#  define XK_F                             0x0066
#  define XK_G                             0x0067
#  define XK_H                             0x0068
#  define XK_I                             0x0069
#  define XK_J                             0x006a
#  define XK_K                             0x006b
#  define XK_L                             0x006c
#  define XK_M                             0x006d
#  define XK_N                             0x006e
#  define XK_O                             0x006f
#  define XK_P                             0x0070
#  define XK_Q                             0x0071
#  define XK_R                             0x0072
#  define XK_S                             0x0073
#  define XK_T                             0x0074
#  define XK_U                             0x0075
#  define XK_V                             0x0076
#  define XK_W                             0x0077
#  define XK_X                             120
#  define XK_Y                             0x0079
#  define XK_Z                             121
#  define XK_BRACELEFT                     0x007b
#  define XK_BAR                           0x007c
#  define XK_BRACERIGHT                    0x007d
#  define XK_ASCIITILDE                    0x007e

# endif

#endif
