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

/*static*/ GB::RunLoop* CLApplication::runLoop = nullptr;

CLApplication::CLApplication():
_view(nullptr),
_keyResponder(nullptr)
{
    
}


void CLApplication::handleMouseEvent( const GXEventMouse* mouse)
{
    const GXPoint center = GXPointMake( mouse->x , mouse->y );
    
    if( rectContainsPoint( _view->getBounds(), center))
    {
        const GXPoint realPoint = center - _view->getBounds().origin;
        
        if( mouse->state == GXMouseStatePressed)
        {
            _view->touchBegan( { realPoint , GXTouch::Phase::Began  });
        }
        else if( mouse->state == GXMouseStateReleased)
        {
            _view->touchEnded( { realPoint , GXTouch::Phase::Ended  });
        }
        else if( mouse->state == GXMouseStateMoving)
        {
            _view->touchMoved({ realPoint , GXTouch::Phase::Moved });
        }
    }

}

void CLApplication::handleKeyEvent( const GXEventKey* key)
{
    //printf("Got key %i \n" , key->code);
    if( _keyResponder)
    {
        if(key->action == GXKeyAction_Press)
        {
            _keyResponder->keyPressed( GXKey{key->code, key->mod});
        }
    }
}

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
            assert(mouse);
            self->handleMouseEvent(mouse);
        }
            break;
        case GXEventTypeKey:
        {
            const GXEventKey* key = reinterpret_cast<const GXEventKey*>(evt);
            assert(key);
            self->handleKeyEvent(key);
        }
            break;
            
        default:
            assert(false);
            break;
    }
    
}
