<%-- 
    Document   : list
    Created on : Jan 19, 2022, 8:53:23 PM
    Author     : dcariotti
--%>

<%@page import="https.footballpool_dataaccess.ArrayOftStadiumInfo"%>
<%@page import="https.footballpool_dataaccess.TStadiumInfo"%>
<%@page import="java.util.List"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Stadium list</title>
    </head>
    <body>
        <h1>Stadium list</h1>
        <% List<TStadiumInfo> stadiums = (List<TStadiumInfo>) request.getAttribute("stadiumList"); %>
        <% for (TStadiumInfo stadium : stadiums) { %>
        <p><%= stadium.getSName() %></p>
        <% } %>
    </body>
</html>
