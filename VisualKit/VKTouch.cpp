//
//  VKTouch.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 19/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "VKTouch.hpp"


bool VKTouchDelegate::touchBegan( const GXTouch &t)
{
    return false;
}

bool VKTouchDelegate::touchEnded( const GXTouch &t)
{
    return false;
}

bool VKTouchDelegate::touchMoved( const GXTouch &t)
{
    return false;
}

bool VKTouchDelegate::onScroll( const GXScroll &)
{
    return false;
}
