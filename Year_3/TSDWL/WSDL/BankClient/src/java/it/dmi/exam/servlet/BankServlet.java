/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package it.dmi.exam.servlet;

import it.dmi.exams.client.bank.BankOperations_Type;
import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 *
 * @author dcariotti
 */
@WebServlet(name = "BankServlet", urlPatterns = {"/BankServlet"})
public class BankServlet extends HttpServlet {

    /**
     * Processes requests for both HTTP <code>GET</code> and <code>POST</code>
     * methods.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        try (PrintWriter out = response.getWriter()) {
            /* TODO output your page here. You may use following sample code. */
            out.println("<!DOCTYPE html>");
            out.println("<html>");
            out.println("<head>");
            out.println("<title>Servlet BankServlet</title>");            
            out.println("</head>");
            out.println("<body>");
            out.println("<h1>Servlet BankServlet at " + request.getContextPath() + "</h1>");
            out.println("</body>");
            out.println("</html>");
        }
    }

    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        double amount = this.getAmount();
        request.setAttribute("amount", amount);
        RequestDispatcher view = request.getRequestDispatcher("index.jsp");
        view.forward(request, response);
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        double moneyToGet = 0.0;
        double moneyToDeposit = 0.0;
        
        String form_deposit = request.getParameter("deposit");
        String form_get = request.getParameter("get");
        
        if (form_deposit.length() > 0) {
            moneyToDeposit = Double.parseDouble(form_deposit);
        }
        
        if (form_get.length() > 0) {
            moneyToGet = Double.parseDouble(form_get);
        }
        
        PrintWriter out = response.getWriter();
        
        out.println("Deposit " + moneyToDeposit + "€");
        out.println("Get " + moneyToGet + "€");
        
        this.deposit(moneyToDeposit);
        this.get(moneyToGet);
    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Make bank operations";
    }

    private static BankOperations_Type deposit(double amount) {
        it.dmi.exams.client.bank.BankOperations_Service service = new it.dmi.exams.client.bank.BankOperations_Service();
        it.dmi.exams.client.bank.BankOperations port = service.getBankOperationsPort();
        return port.deposit(amount);
    }

    private static BankOperations_Type get(double amount) {
        it.dmi.exams.client.bank.BankOperations_Service service = new it.dmi.exams.client.bank.BankOperations_Service();
        it.dmi.exams.client.bank.BankOperations port = service.getBankOperationsPort();
        return port.get(amount);
    }

    private static double getAmount() {
        it.dmi.exams.client.bank.BankOperations_Service service = new it.dmi.exams.client.bank.BankOperations_Service();
        it.dmi.exams.client.bank.BankOperations port = service.getBankOperationsPort();
        return port.getAmount();
    }

}
