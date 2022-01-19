/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package it.dmi.exams.tsdwl;

import https.footballpool_dataaccess.TStadiumInfo;
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
@WebServlet(name = "StadiumInfo", urlPatterns = {"/StadiumInfo"})
public class StadiumInfo extends HttpServlet {
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
        RequestDispatcher view = request.getRequestDispatcher("search.html");
        
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
        TStadiumInfo stadium = this.stadiumInfo(request.getParameter("name"));
        
        response.setContentType("text/html;charset=UTF-8");
        try (PrintWriter out = response.getWriter()) {
            out.println("<html><head></head><body>");
            if (stadium.getSName().length() == 0) {
                out.println("<p>Stadium not found!</p>");
            } else {
                out.println("<p>Stadium info: </p>");
                out.println(stadium.getSName());
                out.println(stadium.getISeatsCapacity());
                out.println(stadium.getSCityName());
                out.println(stadium.getSGoogleMapsURL());
                out.println(stadium.getSWikipediaURL());
            }
            out.println("</body></html>");
        }
        
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

    private static TStadiumInfo stadiumInfo(java.lang.String sStadiumName) {
        https.footballpool_dataaccess.Info service = new https.footballpool_dataaccess.Info();
        https.footballpool_dataaccess.InfoSoapType port = service.getInfoSoap();
        return port.stadiumInfo(sStadiumName);
    }

}
