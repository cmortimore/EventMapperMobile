//
//  MapViewController.m
//  EventMapper


#import "MapViewController.h"
#import "SFRestRequest.h"
#import "EventAnnotation.h"

@implementation MapViewController

@synthesize mapView;


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        SFRestRequest *request = [[SFRestAPI sharedInstance] requestForQuery:@"select id, name, Lat__c, Lon__c from Event__c"];
        [[SFRestAPI sharedInstance] send:request delegate:self];    
        
        mapView = [[MKMapView alloc] initWithFrame:self.view.bounds];
        mapView.delegate=self;

        [self.view insertSubview:mapView atIndex:0];
        
    }
    return self;
}




#pragma mark - SFRestDelegate

- (void)request:(SFRestRequest *)request didLoadResponse:(id)jsonResponse {
    
    
    
    CLLocationCoordinate2D coord = {latitude: 37.784188, longitude: -122.401455};
    MKCoordinateSpan span = {latitudeDelta: 0.0034, longitudeDelta: 0.0034};
    MKCoordinateRegion region = {coord, span};
    [mapView setRegion:region animated:TRUE];
    
    NSArray *records = [jsonResponse objectForKey:@"records"];
    for (id record in records) {
        NSString *name = [record objectForKey:@"Name"];
        NSString *lat = [record objectForKey:@"Lat__c"];
        NSString *lon = [record objectForKey:@"Lon__c"];
        NSLog(@"%@: (%@,%@)", name, lat, lon);
        

        CLLocationCoordinate2D point;
        point.latitude = [lat doubleValue];
        point.longitude = [lon doubleValue];
        
        EventAnnotation *eAnnotation = [[EventAnnotation alloc] initWithCoordinate:point];
        [mapView addAnnotation:eAnnotation];
        [eAnnotation release];
        
    }
    
    

}

- (void)request:(SFRestRequest*)request didFailLoadWithError:(NSError*)error {
    NSLog(@"Error from REST API: %@", [error description]);
}

- (void)requestDidCancelLoad:(SFRestRequest *)request {
    NSLog(@"Request was cancelled");    
}

- (void)requestDidTimeout:(SFRestRequest *)request {
    NSLog( @"Request timedout");        
}


- (MKAnnotationView *)mapView:(MKMapView *)mapView viewForAnnotation:(id <MKAnnotation>)annotation {
	
	MKPinAnnotationView *pin = [[[MKPinAnnotationView alloc] initWithAnnotation: annotation reuseIdentifier: nil] autorelease];
    pin.animatesDrop = YES;
    return pin;
    
}





- (void)dealloc
{
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    NSLog(@"it's a nice view");
    
    
    
    
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}









@end
