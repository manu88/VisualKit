//
//  VKBuilderMainView.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 21/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <GBXMLDocument.hpp>
#include "VKStoryboard.hpp"
#include "BuilderMainView.hpp"
#include "BuilderToolBox.hpp"

BuilderMainView::BuilderMainView():
_selected(nullptr),
_movingV( nullptr )
{
    background = GXColorMake( 0.96f ,0.96f ,0.96f);
    
    _toolBox = new BuilderToolBox( this);
    _toolBox->setBounds(GXRectMake(700, 0, 300, 400));
    addChild(_toolBox);
    
    /*
    _label.setBounds(GXRectMake(300, 500, 200, 100));
    _label.setContent("Hello world!");
    addChild(&_label);
    */
    
    
    
}

void BuilderMainView::viewWillAppear()
{
    //loadFile("test.xml");
    
    _colorView = new ColorPickerView(this);
    
    _colorView->setBounds(GXRectMake(220, 220, 250, 200));
    _colorView->setZPos(50);
    addChild( _colorView );
}

bool BuilderMainView::loadFile( const std::string &file)
{
    
    for( GXLayer* c : getChildren())
    {
        if( c != _toolBox && c != _colorView)
        {
            removeChild(c);
        }
    }

    return VKStoryboard::createFromFile(this, file , nullptr /* no controller*/);
}



void BuilderMainView::actionLoad( VKSender* )
{
    loadFile("test.xml");
}

void BuilderMainView::actionSave( VKSender* )
{
    printf("Save\n");
    
    GB::XMLDocument doc;
    GB::VariantMap obj;
    
    if(serialize(obj))
    {
        doc.addValueForKey(obj, "rootView");
        
        if( doc.save("test.xml"))
        {
            printf("Serialization ok\n");
        }
        else
        {
            printf("Error saving XML\n");
        }
    }
}

void BuilderMainView::addItemAction( VKSender* sender )
{
    const VKDropDown* dp = dynamic_cast<const VKDropDown*>(sender);
    assert(dp);
    
    switch (dp->getSelectedIndex())
    {
        case 0:
            addButton();
            break;
            
        case 1:
            addLabel();
            break;
        case 2:
            addImage();
            break;
        case 3:
            addTextInput();
            break;
            
        case 4:
            addSlider();
            break;
            
        case 5:
            addDropDown();
            break;
        case 6:
            addCheckBox();
            break;
            
        default:
            break;
    }
}

void BuilderMainView::addButton()
{
    VKButton* item = new VKButton;
    
    addItem(item);
    
}

void BuilderMainView::addLabel()
{
    VKLabel* item = new VKLabel;
    
    addItem(item);
}

void BuilderMainView::addImage()
{
    VKImage* item = new VKImage;
    
    addItem(item);
}

void BuilderMainView::addTextInput()
{
    VKTextInput* item = new VKTextInput;
    
    addItem(item);
}

void BuilderMainView::addSlider()
{
    addItem( new VKSlider());
}

void BuilderMainView::addDropDown()
{
    addItem(new VKDropDown() );
}

void BuilderMainView::addCheckBox()
{
    addItem( new VKCheckBox() );
}

bool BuilderMainView::addItem(VKView* item)
{
    assert( item );
    
    item->setSize(GXSizeMake(90, 50));
    item->setCenter(getCenter());
    
    return addChild(item);
}

bool BuilderMainView::touchBegan( const GXTouch &t)
{   
    for( GXLayer *c : getChildren())
    {
        VKView* subV = dynamic_cast<VKView*>(c);
        if( subV == _toolBox || subV == _colorView)
            continue;
        
        if( subV && rectContainsPoint(subV->getBounds(), t.center))
        {
            _selected = subV;
            itemSelectionChanged();
            break;
        }
    }
    return VKView::touchBegan(t);
}

bool BuilderMainView::touchMoved( const GXTouch &t)
{
    if( _movingV || !VKView::touchMoved(t) )
    {
        if( !_movingV)
        {
            for (GXLayer* l : getChildren())
            {
                VKView* view  = dynamic_cast<VKView*>(l);
                
                if( view)
                {
                    if( rectContainsPoint(l->getBounds(), t.center))
                    {
                        _movingV = view;
                        
                    }
                }
            }
        }
        if( _movingV)
        {
            /*
            const GXPoint dif = t.center - _movingV->getPos();
            printf("Diff mouse %i %i\n" , dif.x , dif.y);
            _movingV->setPos(_movingV->getPos() - dif);
            */
            _movingV->setCenter(t.center);
        }

    }
    
    return _movingV;
}

bool BuilderMainView::touchEnded( const GXTouch &t)
{
    if( _movingV)
    {
        _movingV = nullptr;
        
    }
    
    return VKView::touchEnded(t);
}

void BuilderMainView::itemSelectionChanged()
{

    _colorView->setColor(_selected->background);
    _toolBox->updateSelected(_selected);
    /* */
    
    
}

void BuilderMainView::widthContentChanged( int val)
{
    if( _selected)
    {
        
        _selected->setSize(GXSizeMake( val, _selected->getSize().height) );
        
        _selected->setNeedsDisplay();
    }
}

void BuilderMainView::heightContentChanged( int val)
{
    if( _selected)
    {
        _selected->setSize(GXSizeMake( _selected->getSize().width, val ));
        _selected->setNeedsDisplay();
    }
}

void BuilderMainView::zPosChanged(int val)
{
    if( _selected)
    {
        _selected->setZPos(val);
    }
}

void BuilderMainView::textContentChanged(const std::string &content)
{
    printf("Content changed to '%s'\n" ,content.c_str());
    
    if( _selected)
    {
        
        if( VKButton* bt = dynamic_cast<VKButton*>(_selected) )
        {
            bt->setText( content );
            bt->setNeedsRedraw();
            
            return;
        }
        else if( VKImage* img = dynamic_cast<VKImage*>(_selected))
        {
            img->setFile( content );
            img->setNeedsRedraw();
        }
        else if( VKLabel* lbl = dynamic_cast<VKLabel*>(_selected))
        {
            lbl->setContent(content);
            lbl->setNeedsRedraw();
        }
        else if( VKDropDown* dp = dynamic_cast<VKDropDown*>(_selected))
        {
            VKContextMenu::Items items;
            
            std::istringstream f(content);
            
            std::string s;
            while (std::getline(f, s, ';'))
            {
                items.push_back(s);
            }
            
            dp->setItems(items);
            dp->setNeedsRedraw();
            }
    }
    
/*
    if( sender == &_toolBox->_text)
    {
 
    }
*/
}

void BuilderMainView::colorEditEnded( const GXColor& col)
{
    if( !_selected)
        return;
    
    _selected->background = col;
    _selected->setNeedsRedraw();
    //_selected->setNeedsRedraw();
}

void BuilderMainView::setIdentifier( const std::string &id)
{
    if( _selected)
    {
        _selected->identifier = id;
    }
}

bool BuilderMainView::keyPressed(  const GXKey &key )
{
    if( _selected && key.key == GXKey_UP)
    {

        _selected->setPos( _selected->getPos() - GXPointMake(0, 5));
        _selected->setNeedsDisplay();
    }
    else if( _selected && key.key == GXKey_DOWN)
    {
        
        _selected->setPos( _selected->getPos() + GXPointMake(0, 5));
        _selected->setNeedsDisplay();
    }
    else if( _selected && key.key == GXKey_LEFT)
    {
        
        _selected->setPos( _selected->getPos() - GXPointMake(5, 0));
        _selected->setNeedsDisplay();
    }
    else if( _selected && key.key == GXKey_RIGHT)
    {
        
        _selected->setPos( _selected->getPos() + GXPointMake(5, 0));
        _selected->setNeedsDisplay();
    }
    else if( _selected && key.key == GXKey_D)
    {

        
    }
    /*
    else if( _selected && key.key == GXKey_BACKSPACE)
    {
        removeChild(_selected);
        _selected = nullptr;
    }
    */
    
    return VKView::keyPressed(key);
}
