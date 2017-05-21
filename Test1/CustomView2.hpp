//
//  CustomView2.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 21/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef CustomView2_hpp
#define CustomView2_hpp

#include "VKView.hpp"
#include "VKButton.hpp"
class CustomView2 : public VKView
{
public:
    

protected:
    void viewWillAppear() override;
    void viewDidDismiss() override;
    VKButton _returnBton;
};

#endif /* CustomView2_hpp */
