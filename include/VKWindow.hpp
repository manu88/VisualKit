//
//  VKWindow.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 18/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef VKWindow_hpp
#define VKWindow_hpp

#include "../../GX/include/GXLayer.hpp"
#include "VKView.hpp"

class VKContextMenu;

class VKWindow : public VKView/* GXLayer*/
{
public:
    static constexpr const char* ClassName = "VKWindow";
    friend class CLApplication;
    VKWindow();
    virtual ~VKWindow();
    
    void setWindowTitle( const std::string &) noexcept;
    const std::string &getWindowTitle() const noexcept
    {
        return _winTitle;
    }
    
    bool dismissCurrentContextMenu();
    bool pushContextMenu( VKContextMenu* v);
    
protected:
    void paint( GXContext* context , const GXRect& bounds) override;
    
    bool touchBegan( const GXTouch &t) override;
    bool touchEnded( const GXTouch &t) override;
    bool touchMoved( const GXTouch &t) override;
private:
    
    std::string _winTitle;
    
    VKContextMenu* _currentContextMenu;
};

#endif /* VKWindow_hpp */
