//
//  EventMapperAppDelegate.h
//  EventMapper


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
