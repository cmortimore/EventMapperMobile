//
//  EventAnnotation.h
//  EventMapper


#import <Foundation/Foundation.h>
#import <MapKit/MapKit.h>


@interface EventAnnotation : NSObject<MKAnnotation> {
    CLLocationCoordinate2D coordinate;
}

@end
