//
//  ColorPickerView.cpp
//  VisualKit
//
//  Created by Manuel Deneu on 23/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#include "ColorPickerView.hpp"


bool ColorPickerView::serialize( GB::VariantMap& obj) const
{
    return false;
}

void ColorPickerView::paint( GXContext* context , const GXRect& bounds)
{

    int i;
    float r0, r1, ax,ay, bx,by, cx,cy, aeps, r;
    float hue = 1.f;//sinf(t * 0.12f);
    GXPaint paint;
    

    //nvgSave(vg);

    /*	nvgBeginPath(vg);
        nvgRect(vg, x,y,w,h);
        nvgFillColor(vg, nvgRGBA(255,0,0,128));
        nvgFill(vg);*/
    float x = bounds.origin.x;
    float y = bounds.origin.y;
    float w = bounds.size.width;
    float h = bounds.size.height;
    cx = x + w*0.5f;
    cy = y + h*0.5f;
    r1 = (w < h ? w : h) * 0.5f - 5.0f;
    r0 = r1 - 20.0f;
    aeps = 0.5f / r1;	// half a pixel arc length in radians (2pi cancels out).

    for (i = 0; i < 6; i++) {
        float a0 = (float)i / 6.0f * M_PI * 2.0f - aeps;
        float a1 = (float)(i+1.0f) / 6.0f * M_PI * 2.0f + aeps;
        context->beginPath();
        
        context->addArc( cx,cy, r0, a0, a1, GXPaint::GX_CW);
        context->addArc( cx,cy, r1, a1, a0, GXPaint::GX_CCW);
        context->closePath();
        
        ax = cx + cosf(a0) * (r0+r1)*0.5f;
        ay = cy + sinf(a0) * (r0+r1)*0.5f;
        bx = cx + cosf(a1) * (r0+r1)*0.5f;
        by = cy + sinf(a1) * (r0+r1)*0.5f;
        paint = context->linearGradient( ax,ay, bx,by, GXColorMake(a0/(M_PI*2),1.0f,0.55f), GXColorMake(a1/(M_PI*2),1.0f,0.55f));
        
        /*
        paint = nvgLinearGradient(vg, ax,ay, bx,by, nvgHSLA(a0/(M_PI*2),1.0f,0.55f,255), nvgHSLA(a1/(M_PI*2),1.0f,0.55f,255));
         */
        context->setFillPainter(paint);
        //nvgFillPaint(vg, paint);
        //nvgFill(vg);
        context->fill();
    }
/*
    nvgBeginPath(vg);
    nvgCircle(vg, cx,cy, r0-0.5f);
    nvgCircle(vg, cx,cy, r1+0.5f);
    nvgStrokeColor(vg, nvgRGBA(0,0,0,64));
    nvgStrokeWidth(vg, 1.0f);
    nvgStroke(vg);
 */
}
