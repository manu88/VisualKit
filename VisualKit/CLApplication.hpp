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

class VKCursor;
class CLApplicationDelegate;

class CLApplication
{
public:
    
    static CLApplication* instance()
    {
        if( s_instance == nullptr)
        {
            s_instance = new CLApplication();
        }
        
        return s_instance;
    }
    static void releaseInstance()
    {
        delete s_instance;
        s_instance = nullptr;
    }
    
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
    
    void quit();
    
    GB::RunLoop* getRunLoop()
    {
        return &_runLoop;
    }
    
protected:
    
    void handleMouseEvent( const GXEventMouse* evt);
    void handleKeyEvent( const GXEventKey* evt);
    
    VKKeyboardDelegate *_keyResponder;
private:
    CLApplication();
    
    static CLApplication* s_instance;
    
    static void s_onGXEvent(void* disp , const GXEvent *evt);
    
    GB::RunLoop _runLoop;
    
    CLApplicationDelegate *_delegate;
    VKView *_view;
    VKCursor* _cursor;
};

#endif /* CLApplication_hpp */
