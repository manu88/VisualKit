//
//  CustomView2.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 21/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "CustomView2.hpp"
#include "CLApplication.hpp"



void CustomView2::viewWillAppear()
{
    CLApplication::instance()->setName("View 2");
    
    background = GXColors::White;
    
    _returnBton.setText("Return");
    _returnBton.setBounds( GXRectMake(10, 10, 60, 20));
    addChild( &_returnBton );
    
    _returnBton.onClic = [](VKButton* bton)
    {
        printf("Return \n");
        CLApplication::instance()->dismissView();
    };
}
void CustomView2::viewDidDismiss()
{
    
}
