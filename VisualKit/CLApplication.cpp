//
//  CLApplication.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 18/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <assert.h>
#include "CLApplication.hpp"
#include "../../GX/include/Display.h"

/* static */void CLApplication::s_onGXEvent(void* disp , const GXEvent *evt)
{
    Display* display = static_cast< Display* >(disp);
    
    CLApplication* self = static_cast<CLApplication*>(DisplayGetUserContext( display));
    assert(self);
    
    switch (evt->type)
    {
        case GXEventTypeMouse:
        {
            const GXEventMouse* mouse = reinterpret_cast<const GXEventMouse*>(evt);
            
            const GXPoint center = GXPointMake( mouse->x , mouse->y );
            
            if( rectContainsPoint(self->_view.bounds, center))
            {
                const GXPoint realPoint = center - self->_view.bounds.origin;
                if( mouse->state == GXMouseStatePressed)
                {
                    self->_view.touchBegan( { realPoint , GXTouch::Phase::Began  });
                }
                else if( mouse->state == GXMouseStateReleased)
                {
                    self->_view.touchEnded( { realPoint , GXTouch::Phase::Ended  });
                }
            }
            
            
        }
            break;
        case GXEventTypeKey:
        {
            
        }
            break;
            
        default:
            assert(false);
            break;
    }
    
}
