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

#include "../../GX/include/GXLayer.hpp"
#include "../../GX/include/GXRenderer.hpp"






/*static*/ CLApplication* CLApplication::s_instance = nullptr;


CLApplication::CLApplication():
_keyResponder(nullptr),
_disp(nullptr),
_ctx(nullptr),
_delegate(nullptr),
_currentView(nullptr)
{
    _disp = (Display*) malloc(sizeof(Display));
    if( DisplayInit(_disp , 1280 , 750) == 0)
    {
        printf("Display init error \n");
        
    }

}

CLApplication::~CLApplication()
{
    DisplayRelease(_disp);
    free(_disp);
    
    if( _ctx)
    {
        delete _ctx;
    }
}

void CLApplication::pushView( VKView* v) noexcept
{
    if( v)
    {
        if( _currentView)
        {
            v->setZPos(_currentView->getZPos()+1);
        }
        _currentView = v;
        _viewStack.push_back(v);
        
        _currentView->setBounds( GXRectMake(0, 20, mainWin.getSize().width, mainWin.getSize().height - 20) );
        _currentView->viewWillAppear();
        mainWin.addChild( _currentView );
        
        v->setNeedsDisplay();
        printf("pushView:\n");
            
        for (const GXLayer *c : mainWin.getChildren())
        {
            printf("Layer %i \n" , c->getZPos());
        }
    }
}

void CLApplication::dismissView() noexcept
{
    if( _viewStack.empty())
        return;
    
    VKView* last = _viewStack.back();
    _viewStack.pop_back();
    
    _currentView = _viewStack.back();
    mainWin.removeChild(last);
    _currentView->viewWillAppear();
    last->viewDidDismiss();
    
    printf("dismissView:\n");
    
    for (const GXLayer *c : mainWin.getChildren())
    {
        printf("Layer %i \n" , c->getZPos());
    }
}

void CLApplication::setName( const std::string &n)
{
    if( _appName !=n)
    {
        _appName = n;
        mainWin.setWindowTitle( _appName );
    }
    
}

const std::string& CLApplication::getName() const noexcept
{
    return _appName;
}

void CLApplication::handleMouseEvent( const GXEventMouse* mouse)
{
    static GXMouseState lastState = GXMouseStateReleased;
    static bool isPressMoving = 0;
    
    const GXPoint center = GXPointMake( mouse->x , mouse->y );
    
    if( rectContainsPoint( _currentView->getBounds(), center))
    {
        const GXPoint realPoint = center - _currentView->getBounds().origin;
        
        if( mouse->state == GXMouseStatePressed)
        {
            _currentView->touchBegan( { realPoint , GXTouch::Phase::Began  });
        }
        else if( mouse->state == GXMouseStateReleased)
        {
            _currentView->touchEnded( { realPoint , GXTouch::Phase::Ended  });
        }
        else if( mouse->state == GXMouseStateMoving)
        {
            if( isPressMoving)
                _currentView->touchMoved({ realPoint , GXTouch::Phase::Moved });
        }
    }
    
    if (lastState == GXMouseStatePressed && mouse->state == GXMouseStateMoving)
    {
        isPressMoving = true;
    }
    else if( lastState == GXMouseStateMoving && mouse->state == GXMouseStateReleased )
    {
        isPressMoving = false;
    }
    lastState = mouse->state;

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
    

    CLApplication* self = instance();
    assert(self);
    
    if(evt->type == GXEventTypeMouse)
    {
        const GXEventMouse* mouse = reinterpret_cast<const GXEventMouse*>(evt);
        const GXPoint p =GXPointMake(mouse->x, mouse->y);
        if( self->_cursor.getPos() != p)
        {
            self->_cursor.setPos( p);
            self->_cursor.setNeedsDisplay();
        }
    }
    
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

void CLApplication::quit()
{
    _runLoop.dispatchAsync([this]()
    {
        _delegate->applicationWillStop(this);
        return _runLoop.stop();
    });
}

/* *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** */


int CLApplication::main(int argc , char* argv[])
{
    assert(_delegate);
    
    int winWidth, winHeight;
    int fbWidth, fbHeight;
//    float pxRatio;
    
    if (!_disp->_handle)
    {
        return -1;
    }
    
    DisplayMakeContextCurrent( _disp );
    
    DisplayGetWindowSize( _disp, &winWidth, &winHeight);
    DisplayGetFramebufferSize( _disp , &fbWidth, &fbHeight);
    
    
    if(DisplayGetType( _disp) == DisplayGLFW)
    {
        SetDefaultLayout( FrenchMac );
    }
    else if(DisplayGetType( _disp) == DisplayDispman)
    {
        SetDefaultLayout( FrenchPC );
    }
    
    // Calculate pixel ration for hi-dpi devices.
//    pxRatio = (float)fbWidth / (float)winWidth;
    
    _ctx = new GXContext();
    
    GXRenderer render;
    
    

    DisplaySetEventCallback( _disp, CLApplication::s_onGXEvent);
    
    
    mainWin.id = 0;
    
    

    DisplayGetWindowSize( _disp, &winWidth, &winHeight);
    DisplayGetFramebufferSize( _disp, &fbWidth, &fbHeight);
//    pxRatio = (float)fbWidth / (float)winWidth;

    mainWin.setBounds( GXRectMake(0, 0, winWidth, winHeight) );
    render.setRoot( &mainWin );
    
    _delegate->applicationWillLoad(this);

    
    _cursor.setZPos(20);
    mainWin.addChild( &_cursor);

    GB::Timer t;
    t.setInterval(40);
    t.setCallback([&](GB::Timer &timer)
                  {
                      
                      if(render.draw( _ctx ))
                      {
                          DisplaySwap( _disp );
                      }
                      DisplayPollEvents( _disp );
                      
                      if( DisplayShouldClose( _disp ))
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

    return 0;
}
