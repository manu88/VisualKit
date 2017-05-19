//
//  CustomView.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 19/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "CustomView.hpp"
#include "VK.hpp"
#include "VKButton.hpp"

CustomView::CustomView()
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
void CustomView::paint( GXContext* context , const GXRect& bounds)
{
    const GXFontHandle font = context->createFont(  VKDefaults::DefaultFont );
    
    context->setFontId( font );
    context->setTextSize( 20 );
    context->setTextAlignement( GXTextAlign_CENTER | GXTextAlign_MIDDLE );
    
    
    context->setFillColor(GXColors::Black);
    
    
    context->addTextBox(GXPointMake(bounds.size.width /2 , 20), 100, _test);
}

bool CustomView::touchBegan( const GXTouch &t)
{
    _test = std::to_string(t.center.x) + " " + std::to_string(t.center.y);
    setNeedsDisplay();
    
    return VKView::touchBegan(t);
}

bool CustomView::touchEnded( const GXTouch &t)
{
    return VKView::touchEnded(t);
}
