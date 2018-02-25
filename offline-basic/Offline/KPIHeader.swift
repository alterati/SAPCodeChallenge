//  SAP Fiori for iOS Mentor
//  SAP Cloud Platform SDK for iOS Code Example
//  KPI Header
//  Copyright © 2017 SAP SE or an SAP affiliate company. All rights reserved.


import SAPFiori

class KPIHeader: UITableViewController {
    
    var kpiHeader: FUIKPIHeader!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        initExampleData()
        
        tableView.estimatedRowHeight = 98
        tableView.rowHeight = UITableViewAutomaticDimension
        tableView.backgroundColor = UIColor.preferredFioriColor(forStyle: .backgroundBase)
        tableView.separatorStyle = .none
        tableView.tableHeaderView = kpiHeader
        tableView.delegate = self
        tableView.dataSource = self
    }
    
    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        // return 0 as we will display here in our example only the Header
        return 0
    }
    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        return UITableViewCell()
    }
    
    func initExampleData() {
        let kpiView1 = FUIKPIView()
        let kpiView1Metric = FUIKPIMetricItem(string: "2")
        kpiView1.items = [kpiView1Metric]
        kpiView1.captionlabel.text = "Customers Assisted"
        
        let kpiView2 = FUIKPIView()
        let kpiView2Metric = FUIKPIMetricItem(string: "5")
        kpiView2.items = [kpiView2Metric]
        kpiView2.captionlabel.text = "Still in Store Waiting For Checkout"
        
        let kpiView3 = FUIKPIView()
        let kpiView3Metric = FUIKPIMetricItem(string: "4")
        kpiView3.items = [kpiView3Metric]
        kpiView3.captionlabel.text = "Orders"
        
        let kpiView4 = FUIKPIView()
        let kpiView4Unit = FUIKPIUnitItem(string: "$")
        let kpiView4Metric = FUIKPIMetricItem(string: "294")
        kpiView4.items = [kpiView4Unit, kpiView4Metric]
        kpiView4.captionlabel.text = "Average Spend Per Calendar Year"
        kpiView4.captionlabel.numberOfLines = 2
        
        kpiHeader = FUIKPIHeader(items: [kpiView1, kpiView2, kpiView3, kpiView4])
    }
}


