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


class CustomView3;

class CustomView2 : public VKView
{
public:
    CustomView2();

protected:
    void viewWillAppear() override;
    void viewDidDismiss() override;
    
    VKButton _returnBton;
    VKButton _nextBton;
    CustomView3 *_view3;
};

#endif /* CustomView2_hpp */
