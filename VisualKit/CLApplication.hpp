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
#include "../../GX/include/GXEvent.h"

class CLApplication
{
public:
    VKView *_view;
    
    static GB::RunLoop* runLoop;
    
    static void s_onGXEvent(void* disp , const GXEvent *evt);
    
protected:
    
};

#endif /* CLApplication_hpp */
