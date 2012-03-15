//
//  EventMapperAppDelegate.h
//  EventMapper
//
//  Created by Chuck Mortimore on 8/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SFOAuthCoordinator.h"


@class EventMapperViewController;

@interface EventMapperAppDelegate : NSObject <UIApplicationDelegate, SFOAuthCoordinatorDelegate> {
    
    SFOAuthCoordinator *_coordinator;

}

@property (nonatomic, retain) IBOutlet UIWindow *window;

@property (nonatomic, retain) IBOutlet EventMapperViewController *viewController;

@property (nonatomic, retain) SFOAuthCoordinator *coordinator;     

@end
