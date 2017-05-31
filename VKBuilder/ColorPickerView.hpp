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
#include "VKTextInput.hpp"

class BuilderMainView;
class ColorPickerView : public VKView
{
public:
    ColorPickerView(BuilderMainView* mainView);
    void setColor( const GXColor &c);
    bool serialize( GB::VariantMap& obj) const override;
    
    

    
    BuilderMainView* _mainView;
    
protected:
    void colorEditEnded(VKSender*);
    
    void paint( GXContext* context , const GXRect& bounds) override;
    
    VKTextInput _red;
    VKTextInput _green;
    VKTextInput _blue;
    VKTextInput _alpha;
};

#endif /* ColorPickerView_hpp */
