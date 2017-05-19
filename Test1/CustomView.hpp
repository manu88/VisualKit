//
//  CustomView.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 19/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef CustomView_hpp
#define CustomView_hpp


#include "VKView.hpp"

class CustomView : public VKView
{
public:
    CustomView();
protected:
    void paint( GXContext* context , const GXRect& bounds) override;
    
    bool touchBegan( const GXTouch &t) override;
    bool touchEnded( const GXTouch &t) override;
    
    std::string _test;
    
};


#endif /* CustomView_hpp */
