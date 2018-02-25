//
//  TicketsViewController.swift
//  Offline
//
//  Created by Matteo Centro on 25/02/2018.
//  Copyright © 2018 SAP. All rights reserved.
//

import UIKit
import SAPFiori

class TicketsViewController: UIViewController, URLSessionTaskDelegate, UITableViewDataSource, UITableViewDelegate, ActivityIndicator {
    
    @IBOutlet weak var HomeTableView: UITableView!
    private var oDataModel: ODataModel?
    private var salesOrders = [MyPrefixSalesOrderHeader]()
    private var customers = [MyPrefixCustomer]()
    private var products = [MyPrefixProduct]()
    private var activityIndicator: UIActivityIndicatorView!
    private let refreshControl = UIRefreshControl()
    private var kpiHeader: FUIKPIHeader!
    private var kpiViewOpen: FUIKPIView?
    private var kpiViewPending: FUIKPIView?
    
    let objectCellId = "TicketCellID"
    
    func initialize(oDataModel: ODataModel) {
        self.oDataModel = oDataModel
    }
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        setupKPIView()
        activityIndicator = initActivityIndicator()
        activityIndicator.center = view.center
        view.addSubview(activityIndicator)
        
        showActivityIndicator(activityIndicator)
        
        oDataModel?.openOfflineStore { result in
            OperationQueue.main.addOperation {
                self.loadData()
            }
        }
        
        self.configureTableView()
    }
    
    private func configureTableView() {
        HomeTableView.backgroundColor = UIColor.preferredFioriColor(forStyle: .backgroundBase)
        HomeTableView.separatorStyle = .none
        HomeTableView.tableHeaderView = kpiHeader
        HomeTableView.estimatedRowHeight = 80
        HomeTableView.rowHeight = UITableViewAutomaticDimension
        HomeTableView.register(FUIObjectTableViewCell.self, forCellReuseIdentifier: objectCellId)
        
        HomeTableView.refreshControl = refreshControl
        refreshControl.addTarget(self, action: #selector(refreshOfflineData(_:)), for: .valueChanged)
        
        HomeTableView.dataSource = self
        HomeTableView.delegate = self
    }
    
    @objc private func refreshOfflineData(_ sender: Any) {
        // Fetch Weather Data
        self.oDataModel?.downloadOfflineStore{ error in
            
            OperationQueue.main.addOperation {
                self.loadData()
                self.refreshControl.endRefreshing()
            }
        }
    }
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    /// Delegate function from UITableViewDataSource
    ///
    /// - Parameter tableView:
    /// - Returns: that this table only will have 1 section
    func numberOfSections(in _: UITableView) -> Int {
        return 2
    }
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        if(section == 0){
            return salesOrders.count
            
        }
        return products.count
        
        
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: objectCellId, for: indexPath) as! FUIObjectTableViewCell
        
        let singleOrder = salesOrders[indexPath.row]
        
        cell.headlineText = singleOrder.salesOrderID
        cell.subheadlineText = (singleOrder.taxAmount?.toString())! + singleOrder.currencyCode!
        
        cell.accessoryType = .disclosureIndicator
        
        return cell
    }
    
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        performSegue(withIdentifier: "Tickets", sender: indexPath)
    }
    /// Handler to prepare the segue
    ///
    /// - Parameters:
    ///   - segue:
    ///   - sender:
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "Tickets" {
            let indexPath = sender as! IndexPath
            let order: MyPrefixSalesOrderHeader = salesOrders[indexPath.row]
            let sOviewControler = segue.destination as! SalesOrderViewController
            sOviewControler.initialize(oDataModel: oDataModel!)
            sOviewControler.loadSalesOrderItems(newItem: order)
            
        }
        
        if segue.identifier == "Map" {
            let mapViewController = segue.destination as! MapViewController
            mapViewController.salesOrders = self.salesOrders
            mapViewController.customers = self.customers
        }
    }
    
    
    private func loadData() {
        self.oDataModel!.loadSalesOpenOrders { resultSalesOrders, error in
            
            if error != nil {
                // handle error in future version
            }
            
            let kpiView1Metric = FUIKPIMetricItem(string: String(resultSalesOrders?.count ?? 0))
            self.kpiViewOpen?.items = [kpiView1Metric]
            
            if let tempSalesOrders = resultSalesOrders {
                self.salesOrders = tempSalesOrders
            }
            OperationQueue.main.addOperation {
                self.HomeTableView.reloadData()
            }
            self.hideActivityIndicator(self.activityIndicator)

        }
        self.oDataModel!.loadSalesClosedOrdersCount { (count, error) in
            let kpiView2Metric = FUIKPIMetricItem(string: String(count))
            self.kpiViewPending?.items = [kpiView2Metric]
        }
        self.oDataModel!.loadCustomers { (customers, error) in
            if error != nil {
                // handle error in future version
            }
            
            self.customers = customers!
        }
    }
    
    
    func setupKPIView() {
        let kpiView1 = FUIKPIView()
        let kpiView1Metric = FUIKPIMetricItem(string: "-")
        kpiView1.items = [kpiView1Metric]
        kpiView1.captionlabel.text = "Pending"
        self.kpiViewOpen = kpiView1
        
        let kpiView2 = FUIKPIView()
        let kpiView2Metric = FUIKPIMetricItem(string: "-")
        kpiView2.items = [kpiView2Metric]
        kpiView2.captionlabel.text = "Completed"
        kpiViewPending = kpiView2
        
        kpiHeader = FUIKPIHeader(items: [kpiView1, kpiView2])
    }
    
    
}
