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
        VKWindow mainWin;
        CLApplication app;
        
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
        
        DisplayGetWindowSize( &disp, &winWidth, &winHeight);
        DisplayGetFramebufferSize(&disp, &fbWidth, &fbHeight);
        pxRatio = (float)fbWidth / (float)winWidth;
        
        
        mainWin.bounds = GXRectMake(0, 0, winWidth, winHeight);
        render.setRoot( &mainWin );
        
        app._view.bounds = GXRectMake(0, 10, winWidth, winHeight - 40);
        mainWin.addChild(&app._view);

        GB::RunLoop runL;
        
        app._runLoop = &runL;
        /**/
        
        GB::Timer t;
        t.setInterval(40);
        t.setCallback([&](GB::Timer &timer)
                      {
                          /*
                           GLint defaultFBO = -1;
                           glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFBO);
                           assert(defaultFBO == 0);
                           */
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
