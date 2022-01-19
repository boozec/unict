<%-- 
    Document   : list
    Created on : Jan 19, 2022, 9:57:20 PM
    Author     : dcariotti
--%>

<%@page import="org.oorsprong.websamples.TCountryCodeAndName"%>
<%@page import="java.util.List"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Countries list</title>
    </head>
    <body>
        <h1>Countries list</h1>
        <% List<TCountryCodeAndName> languages = (List<TCountryCodeAndName>) request.getAttribute("countries"); %>
        <% for (TCountryCodeAndName language : languages) { %>
        <p><%= language.getSName()%> <a href="/CountryClient/SearchCapital?iso=<%= language.getSISOCode() %>">Search capital</a></p>
        <% } %>
        
    </body>
</html>
