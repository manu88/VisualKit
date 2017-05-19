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
    setOpaque( true);
    setSize( GXSizeMake(10, 10));
    
}
void VKCursor::paint( GXContext* context , const GXRect& bounds)
{
    context->addCircle( GXPointMake( bounds.size.width/2 , bounds.size.height/2), 5);
    context->setFillColor(GXColors::Red);
    context->fill();
}
