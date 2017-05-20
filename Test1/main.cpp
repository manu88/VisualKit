//
//  main.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 18/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "CLApplication.hpp"
#include "AppDelegate.hpp"


int main(int argc , char* argv[])
{
    
    CLApplication app;
    AppDelegate appDelegate;
    
    app.setDelegate(&appDelegate);
    
    return app.main(argc, argv);
    
}
