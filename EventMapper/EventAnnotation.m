//
//  EventAnnotation.m
//  EventMapper
//
//  Created by Chuck Mortimore on 8/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "EventAnnotation.h"


@implementation EventAnnotation
@synthesize coordinate;

- (NSString *)subtitle{
	return nil;
}

- (NSString *)title{
	return nil;
}

-(id)initWithCoordinate:(CLLocationCoordinate2D) c{
	coordinate = c;
	return self;
}



@end
