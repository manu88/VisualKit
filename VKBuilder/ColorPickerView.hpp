//
//  ColorPickerView.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 23/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef ColorPickerView_hpp
#define ColorPickerView_hpp

#include "VKView.hpp"

class ColorPickerView : public VKView
{
public:
    bool serialize( GB::VariantMap& obj) const override;
    
protected:
    void paint( GXContext* context , const GXRect& bounds) override;
};

#endif /* ColorPickerView_hpp */
