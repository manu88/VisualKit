//
//  VKView.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 18/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//
#include <assert.h>
#include "VKView.hpp"
#include "VK.hpp"
#include "VKButton.hpp"

VKView::VKView()
{
    background = GXColors::LightGray;
    
    VKButton *bttonOk = new VKButton();
    bttonOk->setText("Ok");
    bttonOk->bounds = GXRectMake(10, 10, 60, 20);
    addChild( bttonOk );
    
    
    VKButton *bttonCancel = new VKButton();
    bttonCancel->setText("Cancel");
    bttonCancel->bounds = GXRectMake(80, 10, 60, 20);
    addChild( bttonCancel );
    
    
}

VKView::~VKView()
{
    
}

void VKView::paint( GXContext* context , const GXRect& bounds)
{
    const GXFontHandle font = context->createFont(  VKDefaults::DefaultFont );
    
    context->setFontId( font );
    context->setTextSize( 20 );
    context->setTextAlignement( GXTextAlign_CENTER | GXTextAlign_MIDDLE );
    
    
    context->setFillColor(GXColors::Black);
    

    context->addTextBox(GXPointMake(bounds.size.width /2 , 20), 100, _test);
}

bool VKView::touchBegan( const GXTouch &t)
{
    printf("Touch Began %i %i\n" , t.center.x , t.center.y);
    
    _test = std::to_string(t.center.x) + " " + std::to_string(t.center.y);
    setNeedsDisplay();
    
    for (GXLayer* l : getChildren())
    {
        if( rectContainsPoint(l->bounds, t.center))
        {
            printf("Touch in child\n");
        }
    }
    
    return true;
}

bool VKView::touchEnded( const GXTouch &t)
{
    printf("Touch Ended %i %i\n" , t.center.x , t.center.y);
    
    return true;
}
