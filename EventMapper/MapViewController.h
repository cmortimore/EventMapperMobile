//
//  MapViewController.h
//  EventMapper

#import <UIKit/UIKit.h>
#import <MapKit/MapKit.h>

#import "SFRestAPI.h"


@interface MapViewController : UIViewController <MKMapViewDelegate, SFRestDelegate> {
    
    MKMapView *mapView;

}

@property(nonatomic, copy) MKMapView *mapView;

@end
