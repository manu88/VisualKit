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

VKWindow* _mainWin;
VKCursor* _cursor;

static void renderScreen( GXRenderer *render , Display* disp , GXContext *ctx)
{
    
    render->draw( ctx );
    DisplaySwap( disp );
    DisplayPollEvents( disp );
}


static void eventListener(void* disp , const GXEvent *evt)
{
    
    if(evt->type == GXEventTypeMouse)
    {
        const GXEventMouse* mouse = reinterpret_cast<const GXEventMouse*>(evt);
        _cursor->setPos( GXPointMake(mouse->x, mouse->y));
    }
            
    CLApplication::s_onGXEvent(disp , evt);
}

int main()
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
        
        
        
        // Calculate pixel ration for hi-dpi devices.
        pxRatio = (float)fbWidth / (float)winWidth;
        
        GXContext ctx;

        VKWindow mainWin;
        _mainWin = &mainWin;
        VKCursor cursor;
        _cursor = &cursor;
        CLApplication app;
        
        DisplaySetUserContext(&disp, &app);
        DisplaySetEventCallback(&disp, eventListener);
        
        mainWin.setWindowTitle("My APP");
        mainWin.id = 0;
        app._view = new CustomView();
        
        
        DisplayGetWindowSize( &disp, &winWidth, &winHeight);
        DisplayGetFramebufferSize(&disp, &fbWidth, &fbHeight);
        pxRatio = (float)fbWidth / (float)winWidth;
        
        
        mainWin.setBounds( GXRectMake(0, 0, winWidth, winHeight) );
        render.setRoot( &mainWin );
        
        app._view->setBounds( GXRectMake(0, 20, winWidth, winHeight - 20) );
        mainWin.addChild( app._view );
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

        /**/
        /*
        GB::Timer tT;
        tT.setInterval(2000);
        tT.setCallback([&](GB::Timer &timer)
        {
            if( app._view.hasParent())
            {
                assert(mainWin.removeChild( &app._view ));
                printf("Remove view \n");
            }
            else
            {
                assert(mainWin.addChild( &app._view ));
                printf("Add view \n");
            }
        });
        runL.addSource(tT);
        */
        
        runL.run();
    }
    
    DisplayRelease(&disp);
    
    return 0;
}
