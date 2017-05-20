//
//  AppDelegate.hpp
//  GX
//
//  Created by Manuel Deneu on 20/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef AppDelegate_hpp
#define AppDelegate_hpp

#include "CLApplicationDelegate.hpp"
#include "CustomView.hpp"

class AppDelegate : public CLApplicationDelegate
{
public:
    
    
protected:
    void applicationWillLoad( CLApplication* app) override;
    void applicationDidLoad( CLApplication* app) override;
    void applicationWillStop( CLApplication* app) override;
    
    CustomView _view;
};

#endif /* AppDelegate_hpp */
