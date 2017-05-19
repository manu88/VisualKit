//
//  CustomView.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 19/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "CustomView.hpp"
#include "VK.hpp"
#include "CLApplication.hpp"

CustomView::CustomView():
input(STDIN_FILENO)
{
    background = GXColors::LightGray;
    
    
    bttonOk.setText("Show");
    bttonOk.setBounds( GXRectMake(10, 10, 60, 20));
    addChild( &bttonOk );

    bttonCancel.setText("Close");
    bttonCancel.setBounds(GXRectMake(80, 10, 60, 20));
    addChild( &bttonCancel );
    
    
    bttonOk.onClic = std::bind(&CustomView::buttonClicked, this , std::placeholders::_1);
    bttonCancel.onClic = std::bind(&CustomView::buttonClicked, this , std::placeholders::_1);
    
    
    alert = nullptr;
    
    
    input.notification = [this]( GBRunLoopSourceNotification notif )
    {
      if( notif == GBRunLoopSourceCanRead)
      {
          char buf[128];
          const GBSize r = input.read(buf, 128);
          if( r)
          {
              buf[r-1] = 0;
              printf("Read '%s'\n" , buf);
              _test = buf;
              setNeedsDisplay();
          }
          
      }
    };
    CLApplication::runLoop->addSource( input);
}

void CustomView::buttonClicked( VKButton* button)
{
    if( button == &bttonOk)
    {
        printf("OK\n");
        if( !alert)
        {
            alert = new VKAlertView();
            alert->setTitle("Hello");
            alert->setCenter( GXPointMake(getSize().width /2, getSize().height/2));
            addChild( alert);
        }
    }
    else if( button == &bttonCancel)
    {
        printf("Cancel\n");
        removeChild( alert );
        delete alert;
        alert = nullptr;
    }
}

void CustomView::paint( GXContext* context , const GXRect& bounds)
{

    
    
    const GXFontHandle font = context->getFontManager().getFont(VKDefaults::DefaultFont);// context->createFont(  VKDefaults::DefaultFont );
    
    context->setFontId( font );
    context->setTextSize( 20 );
    //context->setTextAlignement( GXTextAlign_CENTER | GXTextAlign_MIDDLE );
    
    
    context->setFillColor(GXColors::Black);
    
    
    context->addTextBox(GXPointMake(bounds.size.width /2 , 20), 100, _test);
    
    context->addCircle( _touchLoc, 5);
    context->setFillColor(GXColors::Red);
    context->fill();
}

bool CustomView::touchBegan( const GXTouch &t)
{
    _touchLoc = t.center;
    setNeedsDisplay();
    
    return VKView::touchBegan(t);
}

bool CustomView::touchEnded( const GXTouch &t)
{
    return VKView::touchEnded(t);
}
