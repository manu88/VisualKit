//
//  CLApplication.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 18/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef CLApplication_hpp
#define CLApplication_hpp

#include <GBRunLoop.hpp>
#include "VKView.hpp"

class CLApplication
{
public:
    VKView _view;
    
    GB::RunLoop* _runLoop;
};

#endif /* CLApplication_hpp */
