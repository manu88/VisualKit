//
//  CustomView3.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 08/06/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef CustomView3_hpp
#define CustomView3_hpp

#include "VKView.hpp"
#include "VKButton.hpp"

class CustomView3 : public VKView
{
protected:
    void viewWillAppear() override;
    void viewDidDismiss() override;
    
    VKButton _returnBton;
    
};

#endif /* CustomView3_hpp */
