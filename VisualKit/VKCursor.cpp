//
//  VKCursor.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 19/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "VKCursor.hpp"



VKCursor::VKCursor()
{
    setOpaque( false);
    setSize( GXSizeMake(10, 20)); // 10 20
    
    setClassName( "VKCursor");
}
void VKCursor::paint( GXContext* context , const GXRect& bounds)
{
    
    context->addRect( bounds);
    /*
    context->setStrokeColor( GXColors::Green);
    context->stroke();
     */
    context->beginPath();
    context->moveTo(bounds.origin);                                                  //top arrow
    context->lineTo(GXPointMake(bounds.origin.x, 15*bounds.size.height/20));         // bottom left
    context->lineTo(GXPointMake(4*bounds.size.width/13, 12*bounds.size.height/20) ); //
    context->lineTo(GXPointMake(8*bounds.size.width/13, bounds.size.height) );       // bottom line left
    context->lineTo(GXPointMake(11*bounds.size.width/13, 11*bounds.size.height/12) );       // bottom line right
    context->lineTo(GXPointMake(8*bounds.size.width/13, 12*bounds.size.height/20) ); //
    context->lineTo(GXPointMake(11*bounds.size.width/12, 12*bounds.size.height/20));
    context->closePath();
    context->setFillColor( GXColors::Black);
    context->setStrokeColor(GXColors::White);
    context->setStrokeWidth(2);
    context->fill();
    context->stroke();
}
