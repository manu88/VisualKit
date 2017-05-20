//
//  VKTextInput.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 19/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "VKTextInput.hpp"
#include "VK.hpp"

VKTextInput::VKTextInput()
{
    setOpaque(false);
    
    _block.setBounds(GXRectMake(10, 10, 5, 10));
    _block.background = GXColorMake(0, 1., 0.35);
    
    addChild(&_block);
}

void VKTextInput::paint( GXContext* context , const GXRect& bounds)
{
    context->addRoundedRect(bounds, 5);
    context->setFillColor(GXColors::White);
    context->setStrokeColor( GXColors::Black);
    context->fill();
    context->stroke();
    context->setFontSize(20);
    context->setFontId( context->getFontManager().getFont( VKDefaults::DefaultFont) );
    context->setFillColor( GXColorMake(0, 1., 0.35) );
    context->setTextAlignement(GXTextAlign_LEFT | GXTextAlign_TOP);
    context->addTextBox(GXPointMake(5, 10), bounds.size.width, _content);
    
}
