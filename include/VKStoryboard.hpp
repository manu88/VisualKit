//
//  VKStoryboard.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 20/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef VKStoryboard_hpp
#define VKStoryboard_hpp

#include <string>
class VKView;
class VKSender;

class VKStoryboardController
{
public:
    virtual ~VKStoryboardController(){}
    
    virtual void onStoryboardAction(VKSender*) = 0;
    
protected:
    VKStoryboardController(){}
};

class VKStoryboard
{
public:
    static bool createFromFile(VKView* view , const std::string &file , VKStoryboardController* controller);
};

#endif /* VKStoryboard_hpp */
