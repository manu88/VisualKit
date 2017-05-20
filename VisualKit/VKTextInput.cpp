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
    
    /*
    _content = "I had a project where I needed to stuff the Linux keyboard with some keystrokes to control a web browser remotely. I couldn't believe how little information there was on the keyboard buffer and how much time it took me to figure it all out. I saw many posts with similar questions but very few with any real wo";
     */
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
