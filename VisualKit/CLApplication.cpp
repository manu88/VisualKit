//
//  CLApplication.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 18/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <assert.h>
#include <GroundBase.hpp>

#include "CLApplication.hpp"
#include "CLApplicationDelegate.hpp"
#include "../../GX/include/Display.h"
#include "../../GX/include/GXLayer.hpp"
#include "../../GX/include/GXRenderer.hpp"

#include "VKCursor.hpp"
#include "VKWindow.hpp"

VKCursor* _cursor;

/*static*/ CLApplication* CLApplication::s_instance = nullptr;


CLApplication::CLApplication():
_view(nullptr),
_keyResponder(nullptr)
{
    
}

void CLApplication::setView( VKView* v) noexcept
{
    _view = v;
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
    if(evt->type == GXEventTypeMouse)
    {
        const GXEventMouse* mouse = reinterpret_cast<const GXEventMouse*>(evt);
        const GXPoint p =GXPointMake(mouse->x, mouse->y);
        if( _cursor->getPos() != p)
        {
            _cursor->setPos( p);
            _cursor->setNeedsDisplay();
        }
    }

    CLApplication* self = instance();
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

bool CLApplication::quit()
{
    return _runLoop.stop();
}

/* *** */


int CLApplication::main(int argc , char* argv[])
{
    GXRenderer render;
    
    Display disp;
    {
        
        
        /**/
        if( DisplayInit(&disp , 1280 , 750) == 0)
        {
            printf("Display init error \n");
            return -1;
        }
        
        int winWidth, winHeight;
        int fbWidth, fbHeight;
        float pxRatio;
        
        if (!disp._handle)
        {
            return -1;
        }
        
        DisplayMakeContextCurrent( &disp );
        
        DisplayGetWindowSize( &disp, &winWidth, &winHeight);
        DisplayGetFramebufferSize( &disp , &fbWidth, &fbHeight);
        
        
        if(DisplayGetType(&disp) == DisplayGLFW)
        {
            SetDefaultLayout( FrenchMac );
        }
        else if(DisplayGetType(&disp) == DisplayDispman)
        {
            SetDefaultLayout( FrenchPC );
        }
        
        // Calculate pixel ration for hi-dpi devices.
        pxRatio = (float)fbWidth / (float)winWidth;
        
        GXContext ctx;
        
        VKWindow mainWin;
        VKCursor cursor;
        _cursor = &cursor;
        
        
        DisplaySetEventCallback(&disp, CLApplication::s_onGXEvent);
        
        mainWin.setWindowTitle("My APP");
        mainWin.id = 0;
        
        _delegate->applicationWillLoad(this);
        
        
        
        
        DisplayGetWindowSize( &disp, &winWidth, &winHeight);
        DisplayGetFramebufferSize(&disp, &fbWidth, &fbHeight);
        pxRatio = (float)fbWidth / (float)winWidth;
        
        
        mainWin.setBounds( GXRectMake(0, 0, winWidth, winHeight) );
        render.setRoot( &mainWin );
        
        getCurrentView()->setBounds( GXRectMake(0, 20, winWidth, winHeight - 20) );
        mainWin.addChild( getCurrentView() );
        mainWin.addChild( &cursor);
        
        
        /**/
        
        GB::Timer t;
        t.setInterval(40);
        t.setCallback([&](GB::Timer &timer)
                      {
                          
                          if(render.draw( &ctx ))
                          {
                              DisplaySwap( &disp );
                          }
                          DisplayPollEvents( &disp );
                          
                          if( DisplayShouldClose( &disp ))
                          {
                              quit();
                          }
                      });
        
        _runLoop.addSource(t);
        
        
        _runLoop.dispatchAsync([this]()
        {
            _delegate->applicationDidLoad( this);
        });
        
        _runLoop.run();
    }
    
    DisplayRelease(&disp);
    
    return 0;
}
