//
//  SalesOrderViewController
//  Online
//
//  Copyright © 2016 SAP. All rights reserved.
//

import SAPFoundation
import UIKit
import SAPFiori

class SalesOrderViewController: UIViewController, URLSessionTaskDelegate, UITableViewDataSource, UITableViewDelegate {

    @IBAction func updateStatus(_ sender: Any) {
        do {
            try oDataModel!.updateSalesOrderHeader(status: "Close", currentSalesOrder: salesOrder)

        } catch  {
            let alert = UIAlertController(title: "Alert", message: "Updating the Status went south!", preferredStyle: .alert)
            alert.addAction(UIAlertAction(title: NSLocalizedString("OK", comment: "Default action"), style: .`default`, handler: { _ in
                NSLog("The \"OK\" alert occured.")
            }))
            self.present(alert, animated: true, completion: nil)
        }
    }
    @IBOutlet var SalesOrderTable: UITableView!
    private var salesOrder: MyPrefixSalesOrderHeader!

    private var products = [MyPrefixProduct]()
    private var oDataModel: ODataModel?
    var cellReuseIdentifier = "SalesOrderCell"
    func initialize(oDataModel: ODataModel) {
        self.oDataModel = oDataModel
    }

    /// delegate function from UIViewController
    override func viewDidLoad() {
        super.viewDidLoad()
        automaticallyAdjustsScrollViewInsets = false

        // Do any additional setup after loading the view
        oDataModel!.loadProdcutsForSalesOrder(salesOrder: salesOrder)  { resultProducts, error in

            if let tempProducts = resultProducts {
                self.products = tempProducts

            }
            OperationQueue.main.addOperation {
                self.SalesOrderTable.reloadData()

            }
        }
        if (salesOrder != nil) {
            let objectHeader = FUIObjectHeader()
            //        objectHeader.detailImageView.image = #imageLiteral(resourceName: "ProfilePic")
            
            objectHeader.headlineLabel.text = salesOrder.salesOrderID
            objectHeader.subheadlineLabel.text = "\(salesOrder.grossAmount!.toString()) \(salesOrder.currencyCode)"

            objectHeader.bodyLabel.text = salesOrder.lifeCycleStatusName
            objectHeader.descriptionLabel.text = "There is an issue but unfortunately we don't know it, just figure it out from the needed items..."
            
            objectHeader.statusLabel.text = "High"
            SalesOrderTable.tableHeaderView = objectHeader
            SalesOrderTable.register(FUIObjectTableViewCell.self, forCellReuseIdentifier: cellReuseIdentifier)
            SalesOrderTable.backgroundColor = UIColor.preferredFioriColor(forStyle: .backgroundBase)
            SalesOrderTable.separatorStyle = .none
            SalesOrderTable.estimatedRowHeight = 80
            SalesOrderTable.rowHeight = UITableViewAutomaticDimension
      }

    }


    /// Delegate function from UITableViewDataSource
    ///
    /// - Parameter tableView:
    /// - Returns: that this table only will have 1 section
    func numberOfSections(in _: UITableView) -> Int {
        return 1
    }

    /// Delegate function from UITableViewDataSource
    ///
    /// - Parameters:
    ///   - tableView:
    ///   - section:
    /// - Returns: returns the number of rows the table should have
    func tableView(_: UITableView, numberOfRowsInSection _: Int) -> Int {
        return products.count // your number of cell here
    }

    /// Delegate function from UITableViewDataSource
    ///
    /// - Parameters:
    ///   - tableView:
    ///   - indexPath:
    /// - Returns: fills the cells with the Sales order
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: cellReuseIdentifier, for: indexPath) as! FUIObjectTableViewCell
        let singleProduct = products[indexPath.row]
        cell.headlineText = singleProduct.categoryName
        cell.subheadlineText = singleProduct.name!;

        return cell
    }

    func tableView(_: UITableView, didSelectRowAt _: IndexPath) {
    }

    /// Handler to prepare the segue
    ///
    /// - Parameters:
    ///   - segue:
    ///   - sender:
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "showSalesOrderItem" {
            /// check email to implement this via sender
//            let selectedRow = sender as! UITableViewCell
//            let selectedIndexPath = SalesOrderTable.indexPath(for: selectedRow)!
//            let order: MyPrefixProduct = products[selectedIndexPath.row]
//            let itemViewControler = segue.destination as! SalesOrderItemViewController
//            itemViewControler.initialize(oDataModel: oDataModel!)
//            itemViewControler.loadSalesOrderItems(newItems: order)
        }
    }
    /// loads the current salesorderItem
    ///
    /// - Parameter newItems: the current salesorderItem
    public func loadSalesOrderItems(newItem: MyPrefixSalesOrderHeader) {
        salesOrder = newItem
    }
}
