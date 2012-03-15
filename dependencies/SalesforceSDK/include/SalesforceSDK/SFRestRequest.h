//
//  SFRestRequest.h
//  SalesforceSDK
//
//  Created by Didier Prophete on 7/25/11.
//  Copyright 2011 Salesforce.com. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum SFRestMethod {
    SFRestMethodGET = 0,
    SFRestMethodPOST,
    SFRestMethodPUT,
    SFRestMethodDELETE,
    SFRestMethodHEAD,
    SFRestMethodPATCH,
} SFRestMethod;

/**
 */
@interface SFRestRequest : NSObject {
    SFRestMethod _method;
    NSString *_path;
    NSDictionary *_queryParams;
}

@property (nonatomic, assign) SFRestMethod method;
@property (nonatomic, retain) NSString *path;
@property (nonatomic, retain) NSDictionary *queryParams;

- (id)initWithMethod:(SFRestMethod)method path:(NSString *)path queryParams:(NSDictionary *)queryParams;

+ (id)requestWithMethod:(SFRestMethod)method path:(NSString *)path queryParams:(NSDictionary *)queryParams;

@end
