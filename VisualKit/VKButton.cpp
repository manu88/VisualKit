//
//  VKButton.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 18/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "VKButton.hpp"
#include "VK.hpp"

VKButton::VKButton()
{
    background = GXColorMake(1, 0, 0 );
    id = 3;
    
    setOpaque(false);
}

VKButton::~VKButton()
{
    
}

void VKButton::setText( const std::string &t) noexcept
{
    _text = t;
}

void VKButton::paint( GXContext* context , const GXRect& bounds)
{
    context->addRoundedRect(bounds , 5);
    context->setStrokeColor( GXColorMake(0.85f, 0.85f, 0.85f)); //[UIColor colorWithWhite:0.85f alpha:1.0f];
    context->setFillColor( GXColorMake(0.98f, 0.98f, 0.98f) ); //[UIColor colorWithWhite:0.98f alpha:1.0f];
    context->fill();
    context->stroke();
    
    const GXFontHandle font = context->createFont( VKDefaults::DefaultFont );
    
    context->setFontId( font );
    context->setTextSize( 20 );
    context->setTextAlignement( GXTextAlign_CENTER | GXTextAlign_MIDDLE );
    
    
    context->setFillColor(GXColors::Black);
    
    context->addTextBox(GXPointMake( 0 ,10), 60, _text );
    
}
