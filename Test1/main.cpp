//
//  main.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 18/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <iostream>
#include "../../GX/include/GXLayer.hpp"
#include "../../GX/include/GXRenderer.hpp"
#include "../../GX/include/Display.h"
#include <GroundBase.hpp>
#include "VKWindow.hpp"
#include "VKCursor.hpp"
#include "CLApplication.hpp"

#include "CustomView.hpp"
#include "AppDelegate.hpp"

VKWindow* _mainWin;
VKCursor* _cursor;

static void renderScreen( GXRenderer *render , Display* disp , GXContext *ctx)
{
    
    if(render->draw( ctx ))
    {
        DisplaySwap( disp );
    }
    DisplayPollEvents( disp );
}


static void eventListener(void* disp , const GXEvent *evt)
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
            
    CLApplication::s_onGXEvent(disp , evt);
}

int main(int argc , char* argv[])
{
    GXRenderer render;
    
    Display disp;
    {
        GB::RunLoop runL;
        CLApplication::runLoop = &runL;
        
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
        _mainWin = &mainWin;
        VKCursor cursor;
        _cursor = &cursor;
        CLApplication app;
        AppDelegate appDelegate;
        
        app.setDelegate(&appDelegate);
        
        DisplaySetUserContext(&disp, &app);
        DisplaySetEventCallback(&disp, eventListener);
        
        mainWin.setWindowTitle("My APP");
        mainWin.id = 0;
        CustomView* cView = new CustomView();
        app.setView( cView );
        app.setKeyboardResponder( cView );
        
        
        
        DisplayGetWindowSize( &disp, &winWidth, &winHeight);
        DisplayGetFramebufferSize(&disp, &fbWidth, &fbHeight);
        pxRatio = (float)fbWidth / (float)winWidth;
        
        
        mainWin.setBounds( GXRectMake(0, 0, winWidth, winHeight) );
        render.setRoot( &mainWin );
        
        app.getCurrentView()->setBounds( GXRectMake(0, 20, winWidth, winHeight - 20) );
        mainWin.addChild( app.getCurrentView() );
        mainWin.addChild( &cursor);
    
        
        /**/
        
        GB::Timer t;
        t.setInterval(40);
        t.setCallback([&](GB::Timer &timer)
                      {
                          renderScreen(&render , &disp , &ctx);
                          
                          if( DisplayShouldClose( &disp ))
                          {
                              runL.stop();
                          }
                      });
        
        runL.addSource(t);
        
        runL.run();
    }
    
    DisplayRelease(&disp);
    
    return 0;
}
