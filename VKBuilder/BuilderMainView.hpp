//
//  VKBuilderMainView.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 21/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef BuilderMainView_hpp
#define BuilderMainView_hpp


#include "VKView.hpp"
#include "VKAction.hpp"
#include "VKImage.hpp"
#include "VKLabel.hpp"
#include "VKDropDown.hpp"
#include "VKSlider.hpp"
#include "ColorPickerView.hpp"
#include "VK.hpp"
class BuilderToolBox;

class BuilderMainView : public VKView 
{
public:
    BuilderMainView();
    
    void viewWillAppear() override;
    BuilderToolBox* _toolBox;
    ColorPickerView* _colorView;
    
    bool loadFile( const std::string &file);
    


    void addItemAction( VKSender* );
    void addButton();
    void addLabel();
    void addImage();
    void addTextInput();
    void addSlider();
    void addDropDown();
    void addCheckBox();
    bool addItem(VKView* v);
    
    bool touchBegan( const GXTouch &t) override;
    bool touchMoved( const GXTouch &t) override;
    bool touchEnded( const GXTouch &t) override;
    
    
    bool keyPressed(  const GXKey &key ) override;
    
    
    void colorEditEnded( const GXColor& col);
    void actionSave( VKSender* sender);
    void actionLoad( VKSender* sender);
    void textContentChanged( const std::string &content);
    
    void widthContentChanged( int val);
    void heightContentChanged( int val );
    void zPosChanged(int val);
    void setIdentifier( const std::string &id);
    
    void itemSelectionChanged();
    
    VKView* _selected;
    
    
    VKLabel _label;
private:
    VKView* _movingV;
    
};

#endif /* BuilderMainView_hpp */
