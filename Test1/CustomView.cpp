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


#include "CustomView2.hpp"
CustomView::CustomView()
{
    background = GXColors::LightGray;
    
    
    bttonOk.setText("Show");
    bttonOk.setBounds( GXRectMake(10, 10, 60, 20));
    addChild( &bttonOk );

    bttonCancel.setText("Close");
    bttonCancel.setBounds(GXRectMake(80, 10, 60, 20));
    addChild( &bttonCancel );
    
    bttonNav.setText("Next");
    bttonNav.setBounds(GXRectMake(150, 10, 60, 20));
    addChild( &bttonNav );
    
    bttonNav.onClic = [](VKSender* sender)
    {
        CLApplication::instance()->pushView(new CustomView2());
    };
    
    bttonOk.onClic = std::bind(&CustomView::buttonClicked,  this , std::placeholders::_1);
    bttonCancel.onClic = std::bind(&CustomView::buttonClicked, this , std::placeholders::_1);
    
    
    alert = nullptr;
    
    textInput.setBounds(GXRectMake(20, 80, 400, 200));
    addChild( &textInput);
    
    textInput2.setBounds(GXRectMake(600, 80, 400, 200));
    addChild( &textInput2);

    

}


void CustomView::viewWillAppear()
{
    CLApplication::instance()->setName("View 1");
}
void CustomView::viewDidDismiss()
{
    
}

void CustomView::buttonClicked( VKSender* button)
{
    if( button == &bttonOk)
    {
        if( !alert)
        {
            alert = new VKAlertView();
            alert->setTitle("Hello");
            
            
            CLApplication::instance()->pushView(alert);
            alert->onReturn = [ this ]( VKAlertView* _alert , int code)
            {
                assert(_alert == alert);
                printf("Alert returned with code %i\n" , code);
                CLApplication::instance()->dismissView();
                delete alert;
                alert = nullptr;
            };
            //addChild( alert);
        }
    }
    else if( button == &bttonCancel)
    {
        CLApplication::instance()->quit();
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




bool CustomView::touchBegan( const GXTouch &t)
{    
    return VKView::touchBegan(t);
}
bool CustomView::touchMoved( const GXTouch &t)
{
    
    return VKView::touchMoved(t);
}

bool CustomView::touchEnded( const GXTouch &t)
{
    return VKView::touchEnded(t);
}
