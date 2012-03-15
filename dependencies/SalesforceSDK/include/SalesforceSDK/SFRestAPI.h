//
//  SFRestAPI.h
//  salesforce
//
//  Created by Didier Prophete on 7/11/11.
//  Copyright 2011 Salesforce.com. All rights reserved.
//

#import <Foundation/Foundation.h>

/*
 * Domain used for errors reported by the rest API
 */
extern NSString* const kSFRestErrorDomain;

/*
 * Default API version (currently "v22.0")
 * You can override this by using setApiVersion:
 */
extern NSString* const kSFRestDefaultAPIVersion;

enum {
    kSFRestErrorGeneric = 0,
};

@class SFRestRequest;
@class SFOAuthCoordinator;
@class RKClient;

@protocol SFRestDelegate <NSObject>
@optional
/**
 * Sent when a request has finished loading
 */
- (void)request:(SFRestRequest *)request didLoadResponse:(id)jsonResponse;

/**
 * Sent when a request has failed due to an error
 */
- (void)request:(SFRestRequest *)request didFailLoadWithError:(NSError*)error;

/**
 * Sent to the delegate when a request was cancelled
 */
- (void)requestDidCancelLoad:(SFRestRequest *)request;

/**
 * Sent to the delegate when a request has timed out. This is sent when a
 * backgrounded request expired before completion.
 */
- (void)requestDidTimeout:(SFRestRequest *)request;
    
@end

/**
 Main clas used to issue REST requests to the standard Salesforce REST API.
 It should be initialized with `APIWithCoordinator:` after a successful
 oauth authentication with Salesforce.

 Sending a request is done using `send:delegate:`

 A request can be obtained in two different ways:

 - by calling the appropriate requestFor[...] method

 - by building the SFRestRequest manually
 */

@interface SFRestAPI : NSObject {
    SFOAuthCoordinator *_coordinator;
    RKClient *_client;
    NSString *_apiVersion;
}

@property (nonatomic, retain) SFOAuthCoordinator *coordinator;
@property (nonatomic, retain) RKClient *rkClient;

/**
 * api version used for all the calls. This could be "v21.0", "v22.0"...
 * The default value is kSFRestDefaultAPIVersion (currently "v22.0")
 */
@property (nonatomic, retain) NSString *apiVersion;

+ (SFRestAPI *)sharedInstance;

+ (id)APIWithCoordinator:(SFOAuthCoordinator *)coordinator;

/**
 * Send rest request to salesforce server and invokes appropriate delegate method
 * @param request the SFRestRequest to be sent
 * @param delegate the delegate object used when the response from the server comes back
 */
- (void)send:(SFRestRequest *)request delegate:(id<SFRestDelegate>)delegate;

/**
 * Lists summary information about each Salesforce.com version currently 
 * available, including the version, label, and a link to each version's
 * root.
 */
- (SFRestRequest *)requestForVersions;

/**
 * Lists available resources for the client's API version, including 
 * resource name and URI.
 */
- (SFRestRequest *)requestForResources;

/**
 * Lists the available objects and their metadata for your organization's 
 * data.
 */
- (SFRestRequest *)requestForDescribeGlobal;

/**
 * Describes the individual metadata for the specified object.
 * @param objectType object type; e.g. "Account"
 */
- (SFRestRequest *)requestForMetadataWithObjectType:(NSString *)objectType;

/**
 * Completely describes the individual metadata at all levels for the 
 * specified object.
 * @param objectType object type; e.g. "Account"
 */
- (SFRestRequest *)requestForDescribeWithObjectType:(NSString *)objectType;

/**
 * Retrieves field values for a record of the given type.
 * @param objectType object type; e.g. "Account"
 * @param objectId the record's object ID
 * @param fieldList comma-separated list of fields for which 
 *               to return values; e.g. "Name,Industry,TickerSymbol".
 *               pass nil to retrieve all the fields.
 */
- (SFRestRequest *)requestForRetrieveWithObjectType:(NSString *)objectType
                                           objectId:(NSString *)objectId 
                                          fieldList:(NSString *)fieldList;

/**
 * Creates a new record of the given type.
 * @param objectType object type; e.g. "Account"
 * @param fields an NSDictionary containing initial field names and values for 
 *               the record, e.g. {Name: "salesforce.com", TickerSymbol: 
 *               "CRM"}
 */
- (SFRestRequest *)requestForCreateWithObjectType:(NSString *)objectType 
                                           fields:(NSDictionary *)fields;

/**
 * Upsert - creates or updates record of the given type, based on the 
 * given external Id.
 * @param objectType object type; e.g. "Account"
 * @param externalIdField external ID field name; e.g. "accountMaster__c"
 * @param externalId the record's external ID value
 * @param fields an NSDictionaryan containing field names and values for 
 *               the record, e.g. {Name: "salesforce.com", TickerSymbol 
 *               "CRM"}
 */
- (SFRestRequest *)requestForUpsertWithObjectType:(NSString *)objectType
                                  externalIdField:(NSString *)externalIdField
                                       externalId:(NSString *)externalId
                                           fields:(NSDictionary *)fields;

/**
 * Updates field values on a record of the given type.
 * @param objectType object type; e.g. "Account"
 * @param objectId the record's object ID
 * @param fields an object containing initial field names and values for 
 *               the record, e.g. {Name: "salesforce.com", TickerSymbol 
 *               "CRM"}
 */
- (SFRestRequest *)requestForUpdateWithObjectType:(NSString *)objectType 
                                         objectId:(NSString *)objectId
                                           fields:(NSDictionary *)fields;

/**
 * Deletes a record of the given type.
 * @param objectType object type; e.g. "Account"
 * @param objectId the record's object ID
 */
- (SFRestRequest *)requestForDeleteWithObjectType:(NSString *)objectType 
                                         objectId:(NSString *)objectId;

/**
 * Executes the specified SOQL query.
 * @param soql a string containing the query to execute - e.g. "SELECT Id, 
 *             Name from Account ORDER BY Name LIMIT 20"
 */
- (SFRestRequest *)requestForQuery:(NSString *)soql;

/**
 * Executes the specified SOSL search.
 * @param sosl a string containing the search to execute - e.g. "FIND {needle}"
 */
- (SFRestRequest *)requestForSearch:(NSString *)sosl;

@end
