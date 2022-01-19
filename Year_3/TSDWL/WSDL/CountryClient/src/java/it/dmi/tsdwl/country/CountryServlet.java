/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package it.dmi.tsdwl.country;

import java.io.IOException;
import java.util.List;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.oorsprong.websamples.ArrayOftCountryCodeAndName;
import org.oorsprong.websamples.TCountryCodeAndName;
/**
 *
 * @author dcariotti
 */
@WebServlet(name = "CountryServlet", urlPatterns = {"/CountryServlet"})
public class CountryServlet extends HttpServlet {
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
        List<TCountryCodeAndName> countries = this.listOfCountryNamesByName().getTCountryCodeAndName();
        
        request.setAttribute("countries", countries);
        
        RequestDispatcher view = request.getRequestDispatcher("list.jsp");
        
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
        
    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Short description";
    }// </editor-fold>

    private static ArrayOftCountryCodeAndName listOfCountryNamesByName() {
        org.oorsprong.websamples.CountryInfoService service = new org.oorsprong.websamples.CountryInfoService();
        org.oorsprong.websamples.CountryInfoServiceSoapType port = service.getCountryInfoServiceSoap();
        return port.listOfCountryNamesByName();
    }


}
