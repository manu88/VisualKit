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

class VKStoryboard
{
    static VKView* createFromFile(const std::string &file);
};

#endif /* VKStoryboard_hpp */
