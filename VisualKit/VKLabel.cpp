//
//  VKLabel.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 21/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "VKLabel.hpp"
#include "VK.hpp"

VKLabel::VKLabel()
{
    _type = VK_Label;
    //setOpaque(false);
    background = GXColors::White;
}

void VKLabel::paint( GXContext* context , const GXRect& bounds)
{
    context->setFontSize(20);
    context->setFontId( context->getFontManager().getFont( VKDefaults::DefaultFont) );
    context->setFillColor( GXColors::Black);// GXColorMake(0, 1., 0.35) );
    
    const GXPoint textPos = GXPointMake(5, 5);
    
    _text.setSize(bounds.size);
    context->setTextAlignement(GXTextAlign_LEFT | GXTextAlign_TOP);
    
    //_text.clearHitTests();
    //_text.addHitTest(_cursorPos);
    _text.draw(context, textPos);
    
}

bool VKLabel::serialize( GB::VariantMap& obj) const
{
    obj.insert(std::make_pair("Res", getContent()));
    
    return VKView::serialize(obj);
}
