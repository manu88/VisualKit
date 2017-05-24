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
#include "ColorPickerView.hpp"
class BuilderToolBox;

class BuilderMainView : public VKView
{
public:
    BuilderMainView();
    
    void viewWillAppear() override;
    BuilderToolBox* _toolBox;
    ColorPickerView* _colorView;
    
    bool loadFile( const std::string &file);
    
    bool    createBase(VKView* v , const GB::VariantMap &desc);
    VKView* createButton( const GB::VariantMap &desc);
    VKView* createImage( const GB::VariantMap &desc);
    VKView* createLabel( const GB::VariantMap &desc);
    
    void addButton(VKSender* sender);
    void addLabel(VKSender* sender);
    void addImage(VKSender* sender);
    
    bool touchBegan( const GXTouch &t) override;
    bool touchMoved( const GXTouch &t) override;
    bool touchEnded( const GXTouch &t) override;
    
    
    bool keyPressed(  const GXKey &key ) override;
    
    void actionSave( VKSender* sender);
    void actionLoad( VKSender* sender);
    void textContentChanged( VKSender* sender);
    void widthContentChanged( VKSender* sender);
    void heightContentChanged( VKSender* sender);
    
    void itemSelectionChanged();
    
    VKView* _selected;
    
    
    VKLabel _label;
private:
    VKView* _movingV;
    
};

#endif /* BuilderMainView_hpp */
