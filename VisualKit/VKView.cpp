//
//  VKView.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 18/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "VKView.hpp"

VKView::VKView()
{
    background = GXColors::LightGray;
}

VKView::~VKView()
{
    
}

void VKView::paint( GXContext* context , const GXRect& bounds)
{
    context->beginPath();
    const GXFontHandle font = context->createFont("Roboto-Regular.ttf");
    
    context->setFontId( font );
    context->setTextSize( 20 );
    //context->setTextAlignement( GXTextAlign_CENTER | GXTextAlign_MIDDLE );
    
    context->setFillColor(GXColors::Black);
    context->addTextBox(GXPointMake(bounds.size.width /2, 20), 200, "Hello");
    
    
    context->addRect(GXRectMake(GXPointMake(100, 200), GXSizeMake(400, 300)));
    context->setStrokeColor( GXColors::Blue);
    context->setFillColor(GXColors::Green);
    context->fill();
    context->stroke();
    
}
