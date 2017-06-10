//
//  CustomView3.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 08/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "CustomView3.hpp"
#include "CLApplication.hpp"

void CustomView3::viewWillAppear()
{
    identifier = "CustomView3";
    
    CLApplication::instance()->setName("View 3");
    
    background = GXColors::White;
    
    _returnBton.setText("Return");
    _returnBton.setBounds( GXRectMake(10, 10, 60, 20));
    addChild( &_returnBton );
    
    _returnBton.onClic = [](VKSender*)
    {
        printf("Return \n");
        CLApplication::instance()->dismissView();
    };
}
void CustomView3::viewDidDismiss()
{
    
}
