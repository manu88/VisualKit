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

#include "VKKeyboard.hpp"

class CLApplication
{
public:
    CLApplication();
    VKView *_view;
    
    
    void setKeyboardResponder( VKKeyboardDelegate* resp) noexcept
    {
        _keyResponder = resp;
    }
    
    static GB::RunLoop* runLoop;
    
    static void s_onGXEvent(void* disp , const GXEvent *evt);
    
protected:
    
    void handleMouseEvent( const GXEventMouse* evt);
    void handleKeyEvent( const GXEventKey* evt);
    
    VKKeyboardDelegate *_keyResponder;
    
};

#endif /* CLApplication_hpp */
