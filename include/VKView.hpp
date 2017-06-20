//
//  VKView.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 18/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef VKView_hpp
#define VKView_hpp

#include <GBVariant.hpp>

#include "../../GX/include/GXLayer.hpp"
#include "VKTouch.hpp"
#include "VKKeyboard.hpp"

class VKWindow;

class VKView : public GXLayer , public VKTouchDelegate , public VKKeyboardDelegate
{
    friend class CLApplication;
    friend class VKWindow;
    
public:
    
    typedef enum
    {
        VK_View      = 0,
        VK_Button    = 1,
        VK_Image     = 2,
        VK_Label     = 3,
        VK_DropDown  = 4,
        VK_TextInput = 5,
    } Type;
    
    VKView();
    virtual ~VKView();
    
    void setFocus(bool focus) noexcept;
    bool hasFocus() const noexcept;
    
    virtual bool serialize( GB::VariantMap& obj) const;

    Type getType() const noexcept
    {
        return _type;
    }
    
    void setMinSize( const GXSize &) noexcept;
    const GXSize& getMinSize() const noexcept
    {
        return _minSize;
    }
    
    void setMaxSize( const GXSize &) noexcept;
    const GXSize& getMaxSize() const noexcept
    {
        return _maxSize;
    }
    
    void setBounds( const GXRect& b) noexcept override;
    
    /*
     This method will walk the views tree, so it can be time consumming...
     TODO : add hierarchy callback for parents changes so this pointer can be cached.
     */
    VKWindow* getWindow() const noexcept;
    
    
    
protected:

    virtual void paint( GXContext*  , const GXRect& ) override
    {} // Default GXLayer method does nothing
    
    
    // default to false
    virtual bool handleFocus();
    
    virtual void focusChanged();
    
    virtual bool touchBegan( const GXTouch &t) override;
    virtual bool touchEnded( const GXTouch &t) override;
    virtual bool touchMoved( const GXTouch &t) override;
    virtual bool onScroll( const GXScroll &) override;
    
    bool keyPressed(  const GXKey &key ) override;
    
    
    virtual void viewWillAppear();
    virtual void viewDidDismiss();
    
    
    Type _type;
    
private:
    
    bool _hasFocus;
    
    GXSize _minSize;
    GXSize _maxSize;
    

};

#endif /* VKView_hpp */
