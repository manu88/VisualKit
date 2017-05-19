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

VKView::VKView()
{

    
}

VKView::~VKView()
{
    
}


bool VKView::touchBegan( const GXTouch &t)
{
    for (GXLayer* l : getChildren())
    {
        if( rectContainsPoint(l->bounds, t.center))
        {
            VKTouchDelegate* del  = dynamic_cast<VKTouchDelegate*>(l);
            
            if( del)
            {
                del->touchBegan({ t.center - bounds.origin ,  t.phase });
            }
            
        }
    }
    
    return true;
}

bool VKView::touchEnded( const GXTouch &t)
{
    for (GXLayer* l : getChildren())
    {
        if( rectContainsPoint(l->bounds, t.center))
        {
            VKTouchDelegate* del  = dynamic_cast<VKTouchDelegate*>(l);
            
            if( del)
            {
                del->touchEnded({ t.center - bounds.origin ,  t.phase });
            }   
        }
    }
    
    return true;
}
