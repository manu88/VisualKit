//
//  VKWindow.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 18/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "VKWindow.hpp"
#include "VK.hpp"

VKWindow::VKWindow()
{
    background = GXColors::DarkGray;
    //setOpaque(false);
}

VKWindow::~VKWindow()
{
    
}

void VKWindow::setWindowTitle( const std::string &title) noexcept
{
    if( _winTitle != title)
    {
        _winTitle = title;
    }
}

void VKWindow::paint( GXContext* context , const GXRect& bounds)
{
    const GXFontHandle font = context->getFontManager().getFont(VKDefaults::DefaultFont);//context->createFont(  VKDefaults::DefaultFont );
    
    context->setFontId( font );
    context->setTextSize( 20 );
    context->setTextAlignement( GXTextAlign_CENTER | GXTextAlign_MIDDLE );
    
    
    context->setFillColor(GXColors::White);
    
    
    context->addTextBox(GXPointMake(bounds.size.width /2 , 10), 200, _winTitle );
}
