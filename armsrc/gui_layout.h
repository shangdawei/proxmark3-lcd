/**
 * \file gui_layout.h
 * Header: Graphical User Interace layout
 * 
 * LCD and GUI layout definitions
 * 
 * Mictronics yamppPod firmware
 * Copyright (C) 2008 by Michael Wolf
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */
#ifndef GUI_LAYOUT_H_
#define GUI_LAYOUT_H_

/**
 * RGB conversion macro
 * 
 */
#define RGB(r,g,b)  ((uint16_t)((uint16_t)(r>>3)<<11) | ((uint16_t)(g>>2)<<6) | ((uint16_t)(b>>3)))

/*
 * General GUI
 */
#define GUI_CLR_BG              RGB(255,255,255)    //!< GUI background color
#define GUI_CLR_TXT             RGB(0,0,0)          //!< GUI text color
#define GUI_CLR_MENU_BG         RGB(255,255,255)    //!< GUI menu background color    
#define GUI_CLR_MENU_TXT        RGB(0,0,0)          //!< GUI menu text color
#define GUI_CLR_MENU_SEL_BG     RGB(156,230,255)    //!< GUI menu selection background color    
#define GUI_CLR_MENU_SEL_TXT    RGB(255,255,255)    //!< GUI menu selection text color
#define GUI_CLR_BROWSE_BG       RGB(255,255,255)    //!< GUI browser background color
#define GUI_CLR_BROWSE_TXT      RGB(0,0,0)          //!< GUI browser text color
#define GUI_CLR_BROWSE_SEL_BG   RGB(156,230,255)    //!< GUI browser selection background color
#define GUI_CLR_BROWSE_SEL_TXT  RGB(255,255,255)    //!< GUI browser selection text color

#endif /*LCD_LAYOUT_H_*/
