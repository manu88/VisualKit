//
//  CLApplication.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 18/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef CLApplication_hpp
#define CLApplication_hpp

#include <vector>
#include <GBRunLoop.hpp>
#include "VKView.hpp"
#include "../../GX/include/GXEvent.h"

#include "VKWindow.hpp"
#include "VKKeyboard.hpp"
#include "VKCursor.hpp"
#include "../../GX/include/Display.h"

class CLApplicationDelegate;

class CLApplication
{
public:
    ~CLApplication();
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
    
    void pushView( VKView* v) noexcept;
    VKView* getCurrentView() const noexcept
    {
        return _currentView;
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
    
    void setName( const std::string &n);
    const std::string &getName() const noexcept;
    
protected:
    
    void handleMouseEvent( const GXEventMouse* evt);
    void handleKeyEvent( const GXEventKey* evt);
    
    
private:
    CLApplication();
    
    static CLApplication* s_instance;
    
    static void s_onGXEvent(void* disp , const GXEvent *evt);
    
    
    std::string _appName;
    VKKeyboardDelegate *_keyResponder;
    Display *_disp;
    GXContext *_ctx;
    GB::RunLoop _runLoop;
    
    CLApplicationDelegate *_delegate;
    std::vector<VKView*> _viewStack;
    VKView* _currentView;
    VKCursor _cursor;
    
    VKWindow mainWin;
};

#endif /* CLApplication_hpp */
