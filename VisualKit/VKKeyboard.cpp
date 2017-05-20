//
//  VKKeyboard.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 20/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "VKKeyboard.hpp"
#include "../../GX/include/GXKey.h"

static std::string toFrenchMac(int key ,int mods)
{
    const bool shift = mods & GXKeyMod_SHIFT;
    const bool alt = mods & GXKeyMod_ALT;
    switch (key)
    {
        case GXKey_SPACE:
            return " ";
        case GXKey_APOSTROPHE:
            return shift? "%" : "ù";
        case GXKey_COMMA:
            return shift? "." : ";";
        case GXKey_MINUS:
            return shift? "°" : ")";
        case GXKey_PERIOD:
            return shift? "/" : ":";
        case GXKey_SLASH:
            return shift? "+" : "=";
            
        case GXKey_0:
            return shift? "0" : "à";
        case GXKey_1:
            return shift? "1" : "&";
        case GXKey_2:
            return shift? "2" : "é";
        case GXKey_3:
            return shift? "3" : "\"";
        case GXKey_4:
            return shift? "4" : "'";
        case GXKey_5:
            return shift? "5" : "(";
        case GXKey_6:
            return shift? "6" : "§";
        case GXKey_7:
            return shift? "7" : "è";
        case GXKey_8:
            return shift? "8" : "!";
        case GXKey_9:
            return shift? "9" : "ç";
        case GXKey_SEMICOLON:
            return shift? "M" : "m";
        case GXKey_EQUAL:
            return shift? "_" : "-";
            
        case GXKey_A:
            return shift? "Q" : "q";
            
        case GXKey_B:
            return shift? "B" : "b";
        case GXKey_C:
            return shift? "C" : "c";
        case GXKey_D:
            return shift? "D" : "d";
        case GXKey_E:
            return shift? "E" : "e";
        case GXKey_F:
            return shift? "F" : "f";
        case GXKey_G:
            return shift? "G" : "g";
        case GXKey_H:
            return shift? "H" : "h";
        case GXKey_I:
            return shift? "I" : "i";
        case GXKey_J:
            return shift? "J" : "j";
        case GXKey_K:
            return shift? "K" : "k";
        case GXKey_L:
            return shift?( alt? "|" : "L" ): "l";
        case GXKey_M:
            return shift? "?" : ",";
        case GXKey_N:
            return shift? "N" : "n";
        case GXKey_O:
            return shift? "O" : "o";
        case GXKey_P:
            return shift? "P" : "p";
        case GXKey_Q:
            return shift? "A" : "a";
        case GXKey_R:
            return shift? "R" : "r";
        case GXKey_S:
            return shift? "S" : "s";
        case GXKey_T:
            return shift? "T" : "t";
        case GXKey_U:
            return shift? "U" : "u";
        case GXKey_V:
            return shift? "V" : "v";
        case GXKey_W:
            return shift? "Z" : "z";
        case GXKey_X:
            return shift? "X" : "x";
        case GXKey_Y:
            return shift? "Y" : "y";
        case GXKey_Z             :
            return shift? "W" : "w";
        case GXKey_LEFT_BRACKET  :
            return shift? "¨" : "^";
        case GXKey_BACKSLASH     :
            return shift? "£" : "`";
        case GXKey_RIGHT_BRACKET :
            return shift? "*" : "$";
        case GXKey_GRAVE_ACCENT  :
            return shift? ">" : "<";
        case GXKey_WORLD_1       :
            return shift? "#" : "@";
        case GXKey_WORLD_2:
            return "WORD2";
    }
    
    return "";
}

static std::string toFrenchPC(int key ,int mods)
{
    const bool shift = mods & GXKeyMod_SHIFT;
    const bool alt = mods & GXKeyMod_ALT;
    switch (key)
    {
        case GXKey_SPACE:
            return " ";
        case GXKey_APOSTROPHE:
            return shift? "%" : "ù";
        case GXKey_COMMA:
            return shift? "." : ";";
        case GXKey_MINUS:
            return shift? "°" : ")";
        case GXKey_PERIOD:
            return shift? "/" : ":";
        case GXKey_SLASH:
            return shift? "§" : "!";
            
        case GXKey_0:
            return alt? "@" :(shift? "0" : "à");
        case GXKey_1:
            return shift? "1" : "&";
        case GXKey_2:
            return alt? "~" :(shift? "2" : "é");
        case GXKey_3:
            return alt? "#" :(shift? "3" : "\"");
        case GXKey_4:
            return alt? "{" :(shift? "4" : "'");
        case GXKey_5:
            return alt? "[" :(shift? "5" : "(");
        case GXKey_6:
            return alt? "|" :(shift? "6" : "§");
        case GXKey_7:
            return alt? "`" :(shift? "7" : "è");
        case GXKey_8:
            return alt? "\\" :(shift? "8" : "!");
        case GXKey_9:
            return alt? "^" :(shift? "9" : "ç");
        case GXKey_SEMICOLON:
            return shift? "M" : "m";
        case GXKey_EQUAL:
            return alt? "}" :(shift? "+" : "=");
            
        case GXKey_A:
            return shift? "Q" : "q";
            
        case GXKey_B:
            return shift? "B" : "b";
        case GXKey_C:
            return shift? "C" : "c";
        case GXKey_D:
            return shift? "D" : "d";
        case GXKey_E:
            return shift? "E" : "e";
        case GXKey_F:
            return shift? "F" : "f";
        case GXKey_G:
            return shift? "G" : "g";
        case GXKey_H:
            return shift? "H" : "h";
        case GXKey_I:
            return shift? "I" : "i";
        case GXKey_J:
            return shift? "J" : "j";
        case GXKey_K:
            return shift? "K" : "k";
        case GXKey_L:
            return shift?( alt? "|" : "L" ): "l";
        case GXKey_M:
            return shift? "?" : ",";
        case GXKey_N:
            return shift? "N" : "n";
        case GXKey_O:
            return shift? "O" : "o";
        case GXKey_P:
            return shift? "P" : "p";
        case GXKey_Q:
            return shift? "A" : "a";
        case GXKey_R:
            return shift? "R" : "r";
        case GXKey_S:
            return shift? "S" : "s";
        case GXKey_T:
            return shift? "T" : "t";
        case GXKey_U:
            return shift? "U" : "u";
        case GXKey_V:
            return shift? "V" : "v";
        case GXKey_W:
            return shift? "Z" : "z";
        case GXKey_X:
            return shift? "X" : "x";
        case GXKey_Y:
            return shift? "Y" : "y";
        case GXKey_Z             :
            return shift? "W" : "w";
        case GXKey_LEFT_BRACKET  :
            return shift? "¨" : "^";
        case GXKey_BACKSLASH     :
            return shift? "μ" : "*";
        case GXKey_RIGHT_BRACKET :
            return shift? "£" : "$";
        case GXKey_GRAVE_ACCENT  :
            return shift? ">" : "<";
        case GXKey_WORLD_1       :
            return shift? ">" : "²";
        case GXKey_WORLD_2:
            return "WORD2";
    }
    
    return "";
}


std::string GXKey::toStr( VKKeyboardLayout layout /*= Default*/) const
{
    
    std::string s;
    
    if( layout == VKKeyboardLayout::Default)
    {
        int c = toascii(key) ;
        
        if(!( modifiers & GXKeyMod_SHIFT) )
        {
            c = tolower(c);
        }
        s = std::string(1, c);
    }
    else if( layout == VKKeyboardLayout::FrenchMac)
    {
        return toFrenchMac(key, modifiers);
    }
    else if( layout == VKKeyboardLayout::FrenchPC)
    {
        return toFrenchPC(key, modifiers);
    }
    return s;
}

bool GXKey::isCharacter() const
{
    return key >= GXKey_SPACE && key <= GXKey_WORLD_2;
}

bool VKKeyboardDelegate::keyPressed( const GXKey &)
{
    return false;
}
