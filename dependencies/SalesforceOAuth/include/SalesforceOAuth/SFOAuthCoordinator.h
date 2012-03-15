//
//  SFOAuthCoordinator.h
//  SalesforceOAuth
//
//  Created by Steve Holly on 17/06/2011.
//  Copyright 2011 Salesforce.com. All rights reserved.
//

#import <Security/Security.h>
#import <UIKit/UIKit.h>
#import "SFOAuthCredentials.h"


@class SFOAuthCoordinator;

/** SFOAuth default network timeout in seconds.
 */
extern const NSTimeInterval kSFOAuthDefaultTimeout;

/** This constant defines the SFOAuth framework error domain.
 
 Domain indicating an error occurred during OAuth authentication.
 */
extern NSString * const kSFOAuthErrorDomain;

/** 
 @enum SFOAuthErrorDomain related error codes
 Constants used by SFOAuthCoordinator to indicate errors in the SFOAuth domain
 */
// TODO additional error code documentation
enum {
    kSFOAuthErrorUnknown = 666,
    kSFOAuthErrorTimeout,
    kSFOAuthErrorMalformed,
    kSFOAuthErrorAccessDenied,              // end user denied authorization
    kSFOAuthErrorInvalidClientId,
    kSFOAuthErrorInvalidClientCredentials,  // client secret invalid
    kSFOAuthErrorInvalidGrant,              // expired access/refresh token, or, IP restricted or invalid login hours
    kSFOAuthErrorInvalidRequest,
    kSFOAuthErrorInactiveUser,
    kSFOAuthErrorInactiveOrg,
    kSFOAuthErrorRateLimitExceeded,
    kSFOAuthErrorUnsupportedResponseType
};

/** Protocol for objects intending to be a delegate for an OAuth coordinator.
 
 Implement this protocol to receive updates from an `SFOAuthCoordinator` instance.
 Use these methods to update your interface and refresh your application once a session restarts.

 @see SFOAuthCoordinator
 */
@protocol SFOAuthCoordinatorDelegate <NSObject>

/** Sent when authentication will begin.
 
 This method supplies the delegate with the UIWebView instance that will be used to
 conduct the OAuth login process.  You should present this view somewhere within your
 interface so the user can enter their credentials.
 
 @param coordinator The SFOAuthCoordinator instance processing this message
 @param view        The UIWebView instance that will be used to conduct the authentication workflow
 
 @see SFOAuthCoordinator
 */
- (void)oauthCoordinator:(SFOAuthCoordinator *)coordinator willBeginAuthenticationWithView:(UIWebView *)view;

/** Sent after authentication has begun and the view parameter is displaying the first page of authentication content.
 
 The delegate will receive this message when the first page of the authentication flow is visible in the view parameter.
 
 @warning the view parameter must be added to a superview upon completion of this method or an assert will fail
 
 @param coordinator The SFOAuthCoordinator instance processing this message
 @param view        The UIWebView instance that will be used to conduct the authentication workflow
 
 @see SFOAuthCoordinator
 */
- (void)oauthCoordinator:(SFOAuthCoordinator *)coordinator didBeginAuthenticationWithView:(UIWebView *)view;

/** Sent when authentication successfully completes.
 
 @param coordinator The SFOAuthCoordinator instance processing this message
 
 @see SFOAuthCoordinator
 */
- (void)oauthCoordinatorDidAuthenticate:(SFOAuthCoordinator *)coordinator;

/** Sent if authentication fails due to an error.
 
 @param coordinator The SFOAuthCoordinator instance processing this message
 @param error       The error message
 
 @see SFOAuthCoordinator
 */
- (void)oauthCoordinator:(SFOAuthCoordinator *)coordinator didFailWithError:(NSError *)error;

@end

/** The `SFOAuthCoordinator` class is the heart of the OAuth2 authentication process.
 
 This class manages a `UIWebView` instance and monitors it as it works its way
 through the various stages of the OAuth2 workflow. When authentication is complete,
 the coordinator instance extracts the necessary session information from the response
 and updates the `SFOAuthCredentials` object as necessary.
 
 @warning This class requires the following dependencies: 
 the Security framework and either the NSJSONSerialization iOS 5.0 SDK class 
 or the third party SBJsonParser class.
 */
@interface SFOAuthCoordinator : NSObject <UIWebViewDelegate> {
}

/** User credentials to use within the authentication process.
 
 @warning The behavior of this class is undefined if you attempt to set a new
 instance of `SFOAuthCredentials` to this property while the authentication process
 is underway.
 
 @see SFOAuthCredentials
 */
@property (nonatomic, retain) SFOAuthCredentials *credentials;

/** The delegate object for this coordinator. 

 The delegate is sent messages at different stages of the authentication process.
 
 @see SFOAuthCoordinatorDelegate
 */
@property (nonatomic, assign) id<SFOAuthCoordinatorDelegate> delegate;

/** Timout interval for OAuth requests.
 
 This value controls how long requests will wait for before timing out.
 */
@property (nonatomic, assign) NSTimeInterval timeout;

/** View in which full authentication (user agent flow) takes place.
 
 This is only guaranteed to be non-nil after one of the delegate methods returning a web view has been called.
 @see SFOAuthCoordinatorDelegate
 */
@property (nonatomic, readonly) UIWebView *view;

///---------------------------------------------------------------------------------------
/// @name Initialization
///---------------------------------------------------------------------------------------

/** Initializes a new OAuth coordinator with the supplied credentials.
 
 @warning The value of `credentials` must not be nil.
 
 @param credentials An instance of `SFOAuthCredentials` identifying the user to be authenticated.
 @return The initialized authentication coordinator.
 
 @see SFOAuthCredentials
 */
- (id)initWithCredentials:(SFOAuthCredentials *)credentials;

///---------------------------------------------------------------------------------------
/// @name Authentication control
///---------------------------------------------------------------------------------------

/** Begin the authentication process.
 */
- (void)authenticate;

/** Returns YES if the coordinator is in the process of authentication; NO otherwise.
 */
- (BOOL)isAuthenticating;

/** Stops the authentication process.
 */
- (void)stopAuthentication;

/** Revoke the authentication credentials.
 */
- (void)revokeAuthentication;

@end
