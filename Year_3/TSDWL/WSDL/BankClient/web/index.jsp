<%-- 
    Document   : index
    Created on : Jan 20, 2022, 10:23:24 AM
    Author     : dcariotti
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Bank operations</title>
    </head>
    <body>
        <% double amount = (double) request.getAttribute("amount"); %>
        <h1>Your deposit is: <%= amount %></h1>
        <h1>Operations: </h1>
        <form method="post">
            <div>
                <label>Deposit money: </label>
                <input type="number" name="deposit">
            </div>
            <div>
                <label>Get money: </label>
                <input type="number" name="get">
            </div>
            <button type="submit">Go</button>
        </form>
    </body>
</html>
