//
//  EventAnnotation.m
//  EventMapper


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
