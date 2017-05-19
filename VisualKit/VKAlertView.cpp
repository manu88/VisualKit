//
//  VKAlertView.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 19/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <assert.h>
#include "VK.hpp"
#include "VKAlertView.hpp"


VKAlertView::VKAlertView()
{
    setOpaque(false);
    setSize( GXSizeMake(400, 200) );
    //background = GXColorMake(0.0, 0.0, 0.0 , 0.1);
    
    bttonOk.setText("Ok");
    bttonCancel.setText("Cancel");
    
    bttonOk.setSize( GXSizeMake(60, 20) );
    bttonCancel.setSize( GXSizeMake(60, 20) );
    //= GXRectMake(10, 30, 60, 20);
    //bttonCancel.bounds = GXRectMake(70, 30, 60, 20);
    
    addChild( &bttonOk );
    addChild( &bttonCancel );

    bttonOk.onClic = std::bind(&VKAlertView::buttonClicked, this , std::placeholders::_1);
    bttonCancel.onClic = std::bind(&VKAlertView::buttonClicked, this , std::placeholders::_1);
    
}

void VKAlertView::buttonClicked( VKButton* button)
{
    removeFromParent();
}
void VKAlertView::paint( GXContext* context , const GXRect& bounds)
{
    bttonOk.setPos( GXPointMake(bounds.size.width/2 - 40, bounds.size.height - 40));
    bttonCancel.setPos( GXPointMake(bounds.size.width/2 + 40, bounds.size.height - 40));
    
    context->addRoundedRect(bounds, 5);
    context->setFillColor( GXColorMake(0.3, 0.3, 0.3 , 0.3));
    context->fill();
    
    context->addRoundedRect(GXRectMake(bounds.origin, bounds.size - GXSizeMake(4, 4)), 5);
    context->setFillColor( GXColorMake(0.7f , 0.7f , 0.7f));
    context->setStrokeColor(GXColors::White);
    context->fill();
    context->stroke();
    
    const GXFontHandle font =  context->getFontManager().getFont(VKDefaults::DefaultFont);// context->createFont( VKDefaults::DefaultFont );
    
    
    context->beginPath();
    context->setFontId( font );
    context->setTextSize( 20 );
    context->setTextAlignement( GXTextAlign_CENTER | GXTextAlign_MIDDLE );

    context->setFillColor(GXColors::White);
    context->addTextBox(GXPointMake( 0 ,15), bounds.size.width, _title );
    
}

bool VKAlertView::touchBegan( const GXTouch &t)
{
    return VKView::touchBegan(t);
}
bool VKAlertView::touchEnded( const GXTouch &t)
{
    return VKView::touchEnded(t);
}



