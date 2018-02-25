//  SAP Fiori for iOS Mentor
//  SAP Cloud Platform SDK for iOS Code Example
//  Marker Annotation View
//  Copyright © 2017 SAP SE or an SAP affiliate company. All rights reserved.


import SAPFiori
import MapKit

class MapViewController: UIViewController {
    
    @IBOutlet var mapView: MKMapView!
    var salesOrders: [MyPrefixSalesOrderHeader]?
    var customers: [MyPrefixCustomer]?
    
    // set the location to the SAP Headquarters: Dietmar-Hopp-Allee 16, 69190 Walldorf DE
    let location = CLLocationCoordinate2D(latitude: 49.293843, longitude: 8.641369)
    
    let latitudinalMeters = 1_000_000.0
    let longitudinalMeters = 1_000_000.0
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.loadLocations()
        
        // center map
        let coordinateRegion = MKCoordinateRegionMakeWithDistance(location, latitudinalMeters, longitudinalMeters)
        mapView.setRegion(coordinateRegion, animated: true)
    }
    
    private func loadLocations() {
        self.salesOrders?.forEach({ (salesOrder) in
            self.loadLocationForSalesOrder(salesOrder)
        })
    }
    
    private func loadLocationForSalesOrder(_ salesOrder: MyPrefixSalesOrderHeader) {
        let matchingCustomers = self.customers?.filter { $0.customerID == salesOrder.customerID }
        
        guard let customer = matchingCustomers?.first else { return }
        
        self.addAnnotationForCustomer(customer)
    }
    
    private func addAnnotationForCustomer(_ customer: MyPrefixCustomer) {
        if #available(iOS 11.0, *) {
            
            // the FUIMarkerAnnotationView is only available in iOS 11
            class FioriMarker: FUIMarkerAnnotationView {
                override var annotation: MKAnnotation? {
                    willSet {
                        markerTintColor = .preferredFioriColor(forStyle: .map1)
                        glyphImage = FUIIconLibrary.map.marker.venue.withRenderingMode(.alwaysTemplate)
                        displayPriority = .defaultHigh
                    }
                }
            }
            
            mapView.register(FioriMarker.self, forAnnotationViewWithReuseIdentifier: MKMapViewDefaultAnnotationViewReuseIdentifier)
        }
        
        let street = customer.street ?? ""
        let city = customer.city ?? ""
        let country = customer.country ?? ""
        let address = street + ", " + city + ", " + country // Sample: "1 Infinite Loop, CA, USA"
        
        let geocoder: CLGeocoder = CLGeocoder()
        geocoder.geocodeAddressString(address) { (placemarks, error) in
            guard let placemarks = placemarks else { return }
            
            if (placemarks.count > 0) {
                let topResult = placemarks.first!
                let placemark: MKPlacemark = MKPlacemark(placemark: topResult)
                
                self.mapView.addAnnotation(placemark)
                
                if let coordinate = placemark.location?.coordinate {
                    let annotation = MKPointAnnotation()
                    annotation.coordinate = CLLocationCoordinate2DMake(coordinate.latitude, coordinate.longitude)
                    annotation.title = customer.firstName ?? "Unknown customer"
                    self.mapView.addAnnotation(annotation)
                    
                    var region: MKCoordinateRegion = self.mapView.region
                    region.center.latitude = coordinate.latitude
                    region.center.longitude = coordinate.longitude
                    region.span = MKCoordinateSpanMake(0.5, 0.5)
                    self.mapView.setRegion(region, animated: true)
                }
            }
            
        }
        
        
    }
}


