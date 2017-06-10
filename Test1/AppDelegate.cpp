//
//  AppDelegate.cpp
//  GX
//
//  Created by Manuel Deneu on 20/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <iostream>
#include <assert.h>
#include "AppDelegate.hpp"

#include "CLApplication.hpp"

void AppDelegate::applicationWillLoad( CLApplication* app)
{
    assert( app );
    app->setName("MyApp");
    app->pushView( &_view );
    app->setKeyboardResponder( &_view );
}

void AppDelegate::applicationDidLoad( CLApplication* app)
{
    assert( app );
    printf("App did load\n");
}

void AppDelegate::applicationWillStop( CLApplication* app)
{
    assert( app );
    printf("App will stop\n");
}
