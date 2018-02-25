//  SAP Fiori for iOS Mentor
//  SAP Cloud Platform SDK for iOS Code Example
//  Timeline Cell
//  Copyright © 2017 SAP SE or an SAP affiliate company. All rights reserved.


import SAPFiori

class TimelineCell: UITableViewController {
    let cellReuseIdentifier = "FUITimelineCell"
    override func viewDidLoad() {
        super.viewDidLoad()
        tableView.register(FUITimelineCell.self, forCellReuseIdentifier: cellReuseIdentifier)
        tableView.estimatedRowHeight = 44
        tableView.rowHeight = UITableViewAutomaticDimension
        tableView.backgroundColor = UIColor.preferredFioriColor(forStyle: .backgroundBase)
        tableView.separatorStyle = .none
    }
    
    // Table delegates
    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return 1
    }
    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let timelineCell = tableView.dequeueReusableCell(withIdentifier: cellReuseIdentifier, for: indexPath) as! FUITimelineCell
        timelineCell.timelineWidth = CGFloat(95.0)
        timelineCell.headlineText = "Annual Relay Testing with the long text and lots of different tools and parts"
        timelineCell.subheadlineText = "819706"
        timelineCell.nodeImage = FUITimelineNode.open
        timelineCell.eventText =  "10:00 AM"
        timelineCell.eventImage =  UIImage() // TODO: Replace with your image
        timelineCell.statusImage = UIImage() // TODO: Replace with your image
        timelineCell.subStatusText =  "rainy"
        timelineCell.attributeText =  "1h 30 min"
        timelineCell.subAttributeText =  "8 min (2.4 min)"
        
        return timelineCell
        
    }
}


