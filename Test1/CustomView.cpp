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
    
    textInput.setBounds(GXRectMake(20, 80, 400, 200));
    addChild( &textInput);
    
    /*
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
     */
}

void CustomView::buttonClicked( VKButton* button)
{
    if( button == &bttonOk)
    {
        if( !alert)
        {
            alert = new VKAlertView();
            alert->setTitle("Hello");
            alert->setCenter( GXPointMake(getSize().width /2, getSize().height/2));
            
            alert->onReturn = [ this ]( VKAlertView* _alert , int code)
            {
                assert(_alert == alert);
                printf("Alert returned with code %i\n" , code);
                _alert->removeFromParent();
                delete alert;
                alert = nullptr;
            };
            addChild( alert);
        }
    }
    else if( button == &bttonCancel)
    {
        CLApplication::runLoop->stop();
    }
}

void CustomView::paint( GXContext* context , const GXRect& bounds)
{

    const GXFontHandle font = context->getFontManager().getFont(VKDefaults::DefaultFont);// context->createFont(  VKDefaults::DefaultFont );
    
    context->setFontId( font );
    context->setTextSize( 20 );

    context->setFillColor(GXColors::Black);
    
    
    context->addTextBox(GXPointMake(bounds.size.width /2 , 20), 100, _test);
    
    
    
}

bool CustomView::keyPressed( const GXKey &key )
{
    std::string c = textInput.getContent();
    
    if( key.key == GXKey_BACKSPACE)
    {
        c.pop_back();
    }
    else if( key.key == GXKey_ENTER)
    {
        c.append("\n");
    }
    else
    {
        c.append( key.toStr() );
    }
    textInput.setContent(c);
    textInput.setNeedsDisplay();
    
    
    return true;
}

bool CustomView::touchBegan( const GXTouch &t)
{
    
    
    
    return VKView::touchBegan(t);
}
bool CustomView::touchMoved( const GXTouch &t)
{
    _touchLoc = t.center;
    setNeedsDisplay();
    return VKView::touchMoved(t);
}

bool CustomView::touchEnded( const GXTouch &t)
{
    return VKView::touchEnded(t);
}
