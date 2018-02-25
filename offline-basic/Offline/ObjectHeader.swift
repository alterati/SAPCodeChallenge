//  SAP Fiori for iOS Mentor
//  SAP Cloud Platform SDK for iOS Code Example
//  Object Header
//  Copyright © 2017 SAP SE or an SAP affiliate company. All rights reserved.


import SAPFiori

class ObjectHeader: UITableViewController {
    
    var objectHeader: FUIObjectHeader!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        tableView.register(FUIObjectTableViewCell.self, forCellReuseIdentifier: FUIObjectTableViewCell.reuseIdentifier)
        
        objectHeader = FUIObjectHeader()
        
        tableView.tableHeaderView = objectHeader
        tableView.rowHeight = UITableViewAutomaticDimension
        tableView.separatorStyle = .none
        
        if let objectHeader = tableView.tableHeaderView as? FUIObjectHeader {
            objectHeader.headlineText = "Inspect electric pump motor"
            objectHeader.subheadlineText = "Job 819701"
            objectHeader.tags = [FUITag(title: "Started"), FUITag(title:"PM01"), FUITag(title:"103-Repair")]
            objectHeader.bodyText = "1000-Hamburg\nMECHANIC"
            objectHeader.bodyLabel.numberOfLines = 2 // Set number of lines for this example
            objectHeader.footnoteText = "Due on 12/31/16"
            objectHeader.descriptionText = "Temperature sensor predicts overheating failure in 4 days. Urgent and needs attention!"
            objectHeader.statusText = "High"
            objectHeader.detailImage = UIImage() // TODO: Replace with your image
            objectHeader.substatusImage = UIImage() // TODO: Replace with your image
            // Image View as example for a detail content view
            let imageView = UIImageView(frame: CGRect(x: 0, y: 0, width: 800, height: 200))
            imageView.image = UIImage() // TODO: Replace with your image
            objectHeader.detailContentView = imageView
        }
    }
    
    // Table view data source
    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return 0
    }
    
    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        return UITableViewCell()
    }
}


