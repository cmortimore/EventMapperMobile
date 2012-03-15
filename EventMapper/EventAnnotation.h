//
//  EventAnnotation.h
//  EventMapper
//
//  Created by Chuck Mortimore on 8/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MapKit/MapKit.h>


@interface EventAnnotation : NSObject<MKAnnotation> {
    CLLocationCoordinate2D coordinate;
}

@end
