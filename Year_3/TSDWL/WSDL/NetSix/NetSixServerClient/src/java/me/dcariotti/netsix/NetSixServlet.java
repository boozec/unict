/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package me.dcariotti.netsix;

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
@WebServlet(name = "NetSixServlet", urlPatterns = {"/NetSixServlet"})
public class NetSixServlet extends HttpServlet {

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
            out.println("<title>Servlet NetSixServlet</title>");            
            out.println("</head>");
            out.println("<body>");
            out.println("<h1>Servlet NetSixServlet at " + request.getContextPath() + "</h1>");
            out.println("</body>");
            out.println("</html>");
        }
    }

    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
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
        RequestDispatcher view = request.getRequestDispatcher("/search.html");
        
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
        response.setContentType("text/html");
        String serie_name = request.getParameter("name");
        String serie_episode = request.getParameter("episode");
        
        if (serie_name != "" && serie_episode != "") {
            boolean result = this.richiedi(serie_name, new Integer(serie_episode));
            PrintWriter out = response.getWriter();
           
            out.print("Episode number `");
            out.print(serie_episode);
            out.print("` of `");
            out.print(serie_name);
            out.print("` is ");
            
            if (result) {
                out.print("present");
            } else {
                out.print(" NOT present");
            }
            
            return;
        }
        
        try (PrintWriter out = response.getWriter()) {
            out.println("You must set both input names");
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

    private static boolean richiedi(java.lang.String name, int episode) {
        me.dcariotti.netsix.WsServ_Service service = new me.dcariotti.netsix.WsServ_Service();
        me.dcariotti.netsix.WsServ port = service.getWsServPort();
        return port.richiedi(name, episode);
    }

}
