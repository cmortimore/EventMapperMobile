//
//  MapViewController.h
//  EventMapper
//
//  Created by Chuck Mortimore on 8/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MapKit/MapKit.h>

#import "SFRestAPI.h"


@interface MapViewController : UIViewController <MKMapViewDelegate, SFRestDelegate> {
    
    MKMapView *mapView;

}

@property(nonatomic, copy) MKMapView *mapView;

@end
