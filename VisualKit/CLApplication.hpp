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

class CLApplicationDelegate;

class CLApplication
{
public:
    CLApplication();
    
    void setView( VKView* v) noexcept;
    VKView* getCurrentView() const noexcept
    {
        return _view;
    }
    
    void setDelegate( CLApplicationDelegate* delegate) noexcept
    {
        _delegate = delegate;
    }
    
    CLApplicationDelegate* getDelegate() const noexcept
    {
        return _delegate;
    }
    
    void setKeyboardResponder( VKKeyboardDelegate* resp) noexcept
    {
        _keyResponder = resp;
    }
    
    static GB::RunLoop* runLoop;
    
    int main(int argc , char* argv[]);
    
    static void s_onGXEvent(void* disp , const GXEvent *evt);
    
protected:
    
    void handleMouseEvent( const GXEventMouse* evt);
    void handleKeyEvent( const GXEventKey* evt);
    
    VKKeyboardDelegate *_keyResponder;
private:
    CLApplicationDelegate *_delegate;
    VKView *_view;
};

#endif /* CLApplication_hpp */
