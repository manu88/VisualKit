//
//  CLApplication.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 18/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <assert.h>
#include <chrono>
#include <iostream> // temp debug
#include <GroundBase.hpp>

#include "CLApplication.hpp"
#include "CLApplicationDelegate.hpp"

#include "../../GX/include/GXLayer.hpp"
#include "../../GX/include/GXRenderer.hpp"

static constexpr int CursorZPos = 200;


/*static*/ CLApplication* CLApplication::s_instance = nullptr;


CLApplication::CLApplication():
_keyResponder(nullptr),
_disp(nullptr),
_ctx(nullptr),
_delegate(nullptr),
_currentView(nullptr),
_fps(0.f)
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
    if( !v)
        return;
    

    
    if( _currentView)
    {
        v->setZPos(_currentView->getZPos()+1);
    }
    
    mainWin.dismissCurrentContextMenu();
    
    _currentView = v;
    _viewStack.push_back(v);
    
    _currentView->setBounds( GXRectMake(0, 20, mainWin.getSize().width, mainWin.getSize().height - 20) );
    _currentView->viewWillAppear();
    mainWin.addChild( _currentView );
    
    printf("pushView: %zi \n" , _viewStack.size());
    v->setNeedsRedraw();
    
    assert(v->getZPos() < _cursor.getZPos());
    

}

void CLApplication::dismissView() noexcept
{
    
    if( _viewStack.empty())
        return;
    
    VKView* last = _viewStack.back();
    _viewStack.pop_back();
    
    
    assert(!_viewStack.empty());
    
    mainWin.dismissCurrentContextMenu();
    
    _currentView = _viewStack.back();
    mainWin.removeChild(last);
    _currentView->viewWillAppear();
    last->viewDidDismiss();
    
    printf("dismissView: %zi \n", _viewStack.size());
    
    
    _currentView->setNeedsRedraw();
}

void CLApplication::setName( const std::string &n)
{
    if( _appName !=n)
    {
        _appName = n;
        mainWin.setWindowTitle( _appName );
        mainWin.setNeedsRedraw();
    }
    
}

const std::string& CLApplication::getName() const noexcept
{
    return _appName;
}

void CLApplication::handleScrollEvent( const GXEventScroll* evt)
{

    GXScroll scroll;
    scroll.movement = GXSizeMake( evt->x , evt->y);
    
    double x = -1;
    double y = -1;
    DisplayGetCursorPos(_disp, &x, &y);
    
    scroll.center = GXPointMake( x , y ) - _currentView->getPos();
    _currentView->onScroll( scroll);
    
}

void CLApplication::handleMouseEvent( const GXEventMouse* mouse)
{
    if( !_currentView)
        return ;
    static GXMouseState lastState = GXMouseStateReleased;
    static bool isPressMoving = 0;
    
    const GXPoint center = GXPointMake( mouse->x , mouse->y );
    

    if( rectContainsPoint( mainWin.getBounds(), center))
    {
        const GXPoint realPoint = center - mainWin.getBounds().origin;
        
        if( mouse->state == GXMouseStatePressed)
        {
            mainWin.touchBegan( { realPoint , GXTouch::Phase::Began  });
        }
        else if( mouse->state == GXMouseStateReleased)
        {
            mainWin.touchEnded( { realPoint , GXTouch::Phase::Ended  });
        }
        else if( mouse->state == GXMouseStateMoving)
        {
            if( isPressMoving)
            {
                mainWin.touchMoved({ realPoint , GXTouch::Phase::Moved });
            }
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
    if( _keyResponder)
    {
        if(key->action == GXKeyAction_Press)
        {
            _keyResponder->keyPressed( GXKey{key->code, key->mod});
        }
    }
}

/* static */void CLApplication::s_onGXEvent( const void* disp , const GXEvent *evt)
{
    

    CLApplication* self = instance();
    assert(self);
    
    const Display* display = reinterpret_cast<const Display*>(disp);
    assert(display);
    
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
        case GXEventTypeScroll:
        {
            const GXEventScroll* ev = reinterpret_cast<const GXEventScroll*>(evt);
            
            self->handleScrollEvent(ev);
            
        }
            break;
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
    
    _ctx = new GXContext();
    
    GXRenderer render;
    
    DisplaySetEventCallback( _disp, CLApplication::s_onGXEvent);

    DisplayGetWindowSize( _disp, &winWidth, &winHeight);
    DisplayGetFramebufferSize( _disp, &fbWidth, &fbHeight);

    _cursor.setZPos( CursorZPos );
    mainWin.addChild( &_cursor);
    
    mainWin.setBounds( GXRectMake(0, 0, winWidth, winHeight) );
    render.setRoot( &mainWin );
    
    render.initView(_ctx);
    
    _delegate->applicationWillLoad(this);

    GB::Timer t;
    t.setInterval(40);
    t.setCallback([&](GB::Timer &timer)
                  {
                      
                      DisplayPollEvents( _disp );
                      
                      if( DisplayShouldClose( _disp ))
                      {
                          quit();
                      }
                      
                      auto start = std::chrono::steady_clock::now();
                      
                      //DisplayClear(_disp);
                      const bool ret = render.draw( _ctx );
                      if(ret)
                      {
                          DisplaySwap( _disp );
                          auto end = std::chrono::steady_clock::now();
                          auto diff = end - start;
                          
                          if ( diff.count() != 0)
                          {
                              _fps = 1000.f / std::chrono::duration <double,std::milli> (diff).count();
                          }
                          //std::cout << std::chrono::duration <double,std::milli> (diff).count() << " ms" << std::endl;
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
