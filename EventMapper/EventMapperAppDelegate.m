//
//  EventMapperAppDelegate.m
//  EventMapper

#import "EventMapperAppDelegate.h"
#import "EventMapperViewController.h"
#import "MapViewController.h"

#import "SFOAuthCredentials.h"
#import "SFRestAPI.h"

@implementation EventMapperAppDelegate

static NSString *const remoteAccessConsumerKey = @"3MVG99OxTyEMCQ3hoszdSdiXWovJt19y1FOPFCdYF0qHnNFzVkJ4K6yLt3XqfcHR.xMSfuieSiPuyg1A8xyck";
static NSString *const OAuthRedirectURI = @"https://eventmapper.herokuapp.com/oauth";
static NSString *const OAuthLoginDomain = @"login.salesforce.com";

@synthesize window=_window;
@synthesize viewController=_viewController;
@synthesize coordinator=_coordinator;


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window.rootViewController = self.viewController;
    [self.window makeKeyAndVisible];
    return YES;
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    
    SFOAuthCredentials *credentials = [[[SFOAuthCredentials alloc] initWithIdentifier:remoteAccessConsumerKey] autorelease];
    credentials.domain = OAuthLoginDomain;
    credentials.redirectUri = OAuthRedirectURI;
    
    self.coordinator = [[[SFOAuthCoordinator alloc] initWithCredentials:credentials] autorelease];
    self.coordinator.delegate = self;
    [self.coordinator authenticate];
    
}


#pragma mark - SFOAuthCoordinatorDelegate

- (void)oauthCoordinator:(SFOAuthCoordinator *)coordinator willBeginAuthenticationWithView:(UIWebView *)view {
    NSLog(@"oauthCoordinator:willBeginAuthenticationWithView");
}

- (void)oauthCoordinator:(SFOAuthCoordinator *)coordinator didBeginAuthenticationWithView:(UIWebView *)view {
    NSLog(@"oauthCoordinator:didBeginAuthenticationWithView");
    [self.viewController.view addSubview:view];
}

- (void)oauthCoordinatorDidAuthenticate:(SFOAuthCoordinator *)coordinator {
    NSLog(@"oauthCoordinatorDidAuthenticate with sessionid: %@, userId: %@", coordinator.credentials.accessToken, coordinator.credentials.userId);
    [coordinator.view removeFromSuperview];
    [SFRestAPI APIWithCoordinator:self.coordinator];
    
    if ([self.viewController isKindOfClass:EventMapperViewController.class]) {
        self.viewController = [[[MapViewController alloc] initWithNibName:nil bundle:nil] autorelease];
        self.window.rootViewController = self.viewController;
    }
    
}

- (void)oauthCoordinator:(SFOAuthCoordinator *)coordinator didFailWithError:(NSError *)error {
    
    NSString *errorDescription = [error localizedDescription];
    NSLog(@"oauthCoordinator:didFailWithError: %@", errorDescription);
    NSRange textRange = [errorDescription rangeOfString:@"not+admin+approved"];
    
    if(textRange.location != NSNotFound) {
        
        NSLog(@"No Admin Approval");
        [self.coordinator stopAuthentication];
    
    } else {
        
        NSLog(@"Expired token");
        [self.coordinator revokeAuthentication];
        [coordinator.view removeFromSuperview];
        
        SFOAuthCredentials *credentials = [[[SFOAuthCredentials alloc] initWithIdentifier:remoteAccessConsumerKey] autorelease];
        credentials.domain = OAuthLoginDomain;
        credentials.redirectUri = OAuthRedirectURI;
        
        self.coordinator = [[[SFOAuthCoordinator alloc] initWithCredentials:credentials] autorelease];
        self.coordinator.delegate = self;
        [self.coordinator authenticate];
        
    }

}


- (void)applicationWillResignActive:(UIApplication *)application{}

- (void)applicationDidEnterBackground:(UIApplication *)application{}

- (void)applicationWillEnterForeground:(UIApplication *)application{}

- (void)applicationWillTerminate:(UIApplication *)application{}



- (void)dealloc
{
    [_window release];
    [_viewController release];
    [super dealloc];
}

@end
