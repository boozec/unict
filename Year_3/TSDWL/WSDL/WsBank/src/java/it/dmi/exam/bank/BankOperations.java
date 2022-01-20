/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package it.dmi.exam.bank;

import javax.jws.WebService;
import javax.jws.WebMethod;
import javax.jws.WebParam;

/**
 *
 * @author dcariotti
 */
@WebService(serviceName = "BankOperations")
public class BankOperations {
    private double amount = 0.0;

    /**
     * Web service operation
     */
    @WebMethod(operationName = "deposit")
    public BankOperations deposit(@WebParam(name = "amount") final double amount) {
        this.amount += amount;
        
        return this;
    }

    /**
     * Web service operation
     */
    @WebMethod(operationName = "getAmount")
    public double getAmount() {
        return this.amount;
    }

    /**
     * Web service operation
     */
    @WebMethod(operationName = "get")
    public BankOperations get(@WebParam(name = "amount") final double amount) {
        this.amount -= amount;
        
        return this;
    }
    
}
