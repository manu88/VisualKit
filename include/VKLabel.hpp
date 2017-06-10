//
//  VKLabel.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 21/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef VKLabel_hpp
#define VKLabel_hpp

#include "VKView.hpp"
#include "../../GX/include/GXTextContainer.hpp"

class VKSimpleTextTrait
{
public:
    virtual ~VKSimpleTextTrait()
    {}
    
    
    void setTextSize( float size) noexcept
    {
        _fontSize = size;
    }
    float getTextSize() const noexcept
    {
        return _fontSize;
    }
    
    void setTextColor( const GXColor &c) noexcept
    {
        _textColor = c;
    }
    
    const GXColor &getTextColor() const noexcept
    {
        return _textColor;
    }
    
    void setTextFont( GXFontHandle font)
    {
        _font = font;
    }
    
    GXFontHandle getTextFont() const noexcept
    {
        return _font;
    }
    
    void setTextAlignement( GXTextAlign align) noexcept
    {
        _textAlign = align;
    }
    
    GXTextAlign getTextAlignement() const noexcept
    {
        return _textAlign;
    }
    
    void setFontHandle( GXFontHandle font ) noexcept
    {
        _font = font;
    }
    
    GXFontHandle getFontHandle() const noexcept
    {
        return _font;
    }
    
protected:
    VKSimpleTextTrait();
    
    
private:
    float        _fontSize;
    GXFontHandle _font;
    GXColor      _textColor;
    GXTextAlign  _textAlign;
};

class VKLabel : public VKView, public VKSimpleTextTrait
{
public:
    VKLabel();
    
    void setContent(const std::string &text) noexcept
    {
        _text.setContent( text);
    }
    
    const std::string &getContent() const noexcept
    {
        return _text.getContent();
    }

protected:
    void paint( GXContext* context , const GXRect& bounds) override;
    
    bool serialize( GB::VariantMap& obj) const override;
private:
    GXTextContainer _text;
    
    
    
};

#endif /* VKLabel_hpp */
