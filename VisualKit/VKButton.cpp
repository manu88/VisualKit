//
//  VKButton.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 18/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "VKButton.hpp"


VKButton::VKButton()
{
    background = GXColorMake(1, 0, 0 );
    id = 3;
}

VKButton::~VKButton()
{
    
}

void VKButton::paint( GXContext* context , const GXRect& bounds)
{
    context->addRect(bounds);
    context->setStrokeColor( GXColors::Blue);
    context->setFillColor(GXColors::Green);
    context->fill();
    context->stroke();
    
    const GXFontHandle font = context->createFont("Roboto-Regular.ttf");
    
    context->setFontId( font );
    context->setTextSize( 20 );
    context->setTextAlignement( GXTextAlign_CENTER | GXTextAlign_MIDDLE );
    
    
    context->setFillColor(GXColors::Blue);
    
    
    context->addTextBox(GXPointMake( 10 ,20), 100, "Hello");
    
}
