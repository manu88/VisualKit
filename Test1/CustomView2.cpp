//
//  CustomView2.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 21/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "CustomView2.hpp"
#include "CustomView3.hpp"
#include "CLApplication.hpp"

CustomView2::CustomView2():_view3(nullptr)
{
    
}

void CustomView2::viewWillAppear()
{
    
    identifier = "CustomView2";
    
    CLApplication::instance()->setName("View 2");
    
    background = GXColors::White;
    
    _nextBton.setText("next");
    _nextBton.setBounds( GXRectMake(10, 10, 60, 20));
    addChild( &_nextBton );
    
    _returnBton.setText("Return");
    _returnBton.setBounds( GXRectMake(70, 10, 60, 20));
    addChild( &_returnBton );
    
    _returnBton.onClic = [](VKSender*)
    {
        printf("Return \n");
        CLApplication::instance()->dismissView();
    };
    
    _nextBton.onClic = [ this ](VKSender*)
    {
        if( !_view3)
        {
            _view3 = new CustomView3();
        }
        CLApplication::instance()->pushView(_view3);
    };
    
}
void CustomView2::viewDidDismiss()
{
    
}
