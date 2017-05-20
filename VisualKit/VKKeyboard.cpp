//
//  VKKeyboard.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 20/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "VKKeyboard.hpp"
#include "../../GX/include/GXKey.h"

std::string GXKey::toStr() const
{
    //printf("Modifiers : %i\n" , modifiers);
    
    
    int c = toascii(key) ;
    
    if(!( modifiers & GXKeyMod_SHIFT) )
    {
        c = tolower(c);
    }
    std::string s(1, c);
    
    
    
    return s;
}

bool VKKeyboardDelegate::keyPressed( const GXKey &)
{
    return false;
}
