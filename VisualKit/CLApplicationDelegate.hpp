//
//  CLApplicationDelegate.hpp
//  VisualKit
//
//  Created by Manuel Deneu on 20/05/2017.
//  Copyright © 2017 Unlimited Development. All rights reserved.
//

#ifndef CLApplicationDelegate_hpp
#define CLApplicationDelegate_hpp

class CLApplication;

class CLApplicationDelegate
{
    friend class CLApplication;
public:
    virtual ~CLApplicationDelegate();
protected:
    
    virtual void applicationWillLoad( CLApplication* app);
    virtual void applicationDidLoad( CLApplication* app);
    
    virtual void applicationWillStop( CLApplication* app);
private:
    
};

#endif /* CLApplicationDelegate_hpp */
