//
//  VKButton.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 18/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "CLApplication.hpp"
#include "VKButton.hpp"
#include "VK.hpp"

VKButton::VKButton():
_triggerAction (false),
_state( Inactive )
{
    _type = VK_Button;
    
    background = GXColorMake(1, 0, 0 );
    id = 3;
    
    setOpaque(false);
    
    onClic = nullptr;
}

VKButton::~VKButton()
{
    
}

void VKButton::setText( const std::string &t) noexcept
{
    _text = t;
}

void VKButton::paint( GXContext* context , const GXRect& _bounds)
{
    context->beginPath();
    context->addRoundedRect( _bounds , 5);
    context->setStrokeColor( GXColorMake(0.85f, 0.85f, 0.85f));
    context->setFillColor( GXColorMake(0.98f, 0.98f, 0.98f) );
    context->fill();
    context->stroke();
    
    const GXFontHandle font =  context->getFontManager().getFont(VKDefaults::DefaultFont);// context->createFont( VKDefaults::DefaultFont );
    
    context->setFontId( font );
    context->setTextSize( 20 );
    context->setTextAlignement( GXTextAlign_CENTER | GXTextAlign_MIDDLE );
    
    
    context->setFillColor(GXColors::Black);
    
    context->addTextBox(GXPointMake( 0 ,10), _bounds.size.width, _text );
    
    if( _state == Highlighted)
    {

        context->addRoundedRect( _bounds , 5);
        
        GXColor c = GXColors::DarkGray;
        c.a = 0.5;
        context->setFillColor( c);
        
        context->fill();
    }
    
    
    if( _triggerAction)
    {
        _triggerAction = false;
        CLApplication::instance()->getRunLoop()->dispatchAsync([ this]()
                                              {
                                                  onClic(this);
                                              });
        
    }
}

bool VKButton::touchBegan( const GXTouch &t)
{
    
    _state = Highlighted;
    setNeedsDisplay();
    return true;
}
bool VKButton::touchEnded( const GXTouch &t)
{
    
    _state = Inactive;
    
    
    setNeedsDisplay();
    
    if( onClic)
    {
        onClic(this);
    }
    

    return  true;
}

bool VKButton::serialize( GB::VariantMap& obj) const
{
    obj.insert(std::make_pair("Text", getText()));
    return VKView::serialize(obj);
}
