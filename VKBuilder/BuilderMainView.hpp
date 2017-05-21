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

class BuilderToolBox;

class BuilderMainView : public VKView
{
public:
    BuilderMainView();
    
    BuilderToolBox* _toolBox;
    
    void addButton(VKSender* sender);
    
    bool touchBegan( const GXTouch &t) override;
    /*
    bool touchEnded( const GXTouch &t) override;
    bool touchMoved( const GXTouch &t) override;
     */
    bool keyPressed(  const GXKey &key ) override;
    
    void textContentChanged( VKSender* sender);
    void widthContentChanged( VKSender* sender);
    void heightContentChanged( VKSender* sender);
    
    void itemSelectionChanged();
    
    VKView* _selected;
    
    VKImage _image;
private:
    
};

#endif /* BuilderMainView_hpp */
