//
//  AppDelegate.cpp
//  GX
//
//  Created by Manuel Deneu on 20/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <iostream>
#include "AppDelegate.hpp"
#include "CustomView.hpp"
#include "CLApplication.hpp"

void AppDelegate::applicationWillLoad( CLApplication* app)
{
    CustomView* cView = new CustomView();
    app->setView( cView );
    app->setKeyboardResponder( cView );
}

void AppDelegate::applicationDidLoad( CLApplication* app)
{
    printf("App did load\n");
}

