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
#include "CLApplication.hpp"

#include "VKButton.hpp"



static void renderScreen( GXRenderer *render , Display* disp , GXContext *ctx)
{
    
    render->draw( ctx );
    DisplaySwap( disp );
    DisplayPollEvents( disp );
}


int main()
{
    GXRenderer render;
    
    Display disp;
    {
        
        
        /**/
        if( DisplayInit(&disp , 1000 , 800) == 0)
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
        
        //DisplaySetEventCallback(&disp, eventListener);
        
        // Calculate pixel ration for hi-dpi devices.
        pxRatio = (float)fbWidth / (float)winWidth;
        
        GXContext ctx;

        VKWindow mainWin;
        CLApplication app;
        
        mainWin.id = 0;
        app._view.id = 1;
        
        DisplayGetWindowSize( &disp, &winWidth, &winHeight);
        DisplayGetFramebufferSize(&disp, &fbWidth, &fbHeight);
        pxRatio = (float)fbWidth / (float)winWidth;
        
        
        mainWin.bounds = GXRectMake(0, 0, winWidth, winHeight);
        render.setRoot( &mainWin );
        
        app._view.bounds = GXRectMake(0, 10, winWidth, winHeight - 40);
        mainWin.addChild(&app._view);
        
        VKButton btton;
        btton.bounds = GXRectMake(10, 10, 200, 100);
        mainWin.addChild(  &btton);

        //render.setRoot( &btton );
        GB::RunLoop runL;
        
        app._runLoop = &runL;
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
