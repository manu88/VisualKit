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
#include "VKStoryboard.hpp"

class BuilderMainView;
class ColorPickerView : public VKView , public VKStoryboardController
{
public:
    ColorPickerView(BuilderMainView* mainView);
    void setColor( const GXColor &c);
    bool serialize( GB::VariantMap& obj) const override;
    
    

    void onStoryboardAction(VKSender*) override;
    
    BuilderMainView* _mainView;
    
protected:
    void colorEditEnded(VKSender*);
    

    

};

#endif /* ColorPickerView_hpp */
