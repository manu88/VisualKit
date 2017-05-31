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


class VKView : public GXLayer , public VKTouchDelegate , public VKKeyboardDelegate
{
    friend class CLApplication;
    
public:
    typedef enum
    {
        VK_View   = 0,
        VK_Button = 1,
        VK_Image  = 2,
        VK_Label  = 3
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
    
protected:

    virtual void paint( GXContext* context , const GXRect& bounds) override
    {} // Default GXLayer method does nothing
    
    
    // default to false
    virtual bool handleFocus();
    
    virtual void focusChanged();
    
    bool touchBegan( const GXTouch &t) override;
    bool touchEnded( const GXTouch &t) override;
    bool touchMoved( const GXTouch &t) override;
    
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
