//
//  VKView.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 18/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//
#include <assert.h>
#include "VKView.hpp"
#include "VK.hpp"
#include "VKButton.hpp"

VKView::VKView():
_hasFocus(false)
{

    
}

VKView::~VKView()
{
    
}

void VKView::setFocus(bool focus) noexcept
{
    _hasFocus = focus;
}
bool VKView::hasFocus() const noexcept
{
    return _hasFocus;
}

bool VKView::handleFocus()
{
    return false;
}

bool VKView::touchBegan( const GXTouch &t)
{
    for (GXLayer* l : getChildren())
    {
        VKView* del  = dynamic_cast<VKView*>(l);
        if( del)
        {
            if( rectContainsPoint(l->getBounds(), t.center))
            {
                del->setFocus(true);

                if(del->touchBegan({ t.center - l->getBounds().origin ,  GXTouch::Phase::Began }))
                {
                    //return true;
                }
            }
            else
            {
                del->setFocus(false);
            }
        }
        
        
    }
    
    
    
    return true;
}

bool VKView::touchEnded( const GXTouch &t)
{
    for (GXLayer* l : getChildren())
    {
        if( rectContainsPoint(l->getBounds(), t.center))
        {
            VKTouchDelegate* del  = dynamic_cast<VKTouchDelegate*>(l);
            
            if( del)
            {
                del->touchEnded({ t.center - l->getBounds().origin ,  GXTouch::Phase::Ended });
            }
        }
    }
    
    return true;
}
