<%
String email=(String)session.getAttribute("email");
if(email!=null){
    if(!email.equals("admin")){
        response.sendRedirect("adminLogin.jsp");
    }
}
else{
    response.sendRedirect("adminLogin.jsp");
}
%>


<html>
<head>
<title>Code Warrior</title>
<link rel="stylesheet" type="text/css" href="style.css">

</head>


<body>

    <jsp:include page="header.jsp"></jsp:include>        
    <jsp:include page="navigation.jsp"></jsp:include>  
      
    <div id="section">
        <h2>Add Question</h2>
     
      <%
        String status=request.getParameter("status");
        
        if(status!=null){
            if(status.equals("false")){%>
                <p style="color:red">Some error occurred!</p>
            <%}
            else if(status.equals("true")){%>
                <p style="color:red">Record added!</p>
            <%}
        }
        %>
           
        <form action="addQuestionDAO.jsp" name="login" onsubmit="return check()">
            <table cellpadding="10">
                       
                
                <tr>
                    <td><b>Question:</b></td>
                    <td><textarea rows="10" cols="100" name="question" required></textarea></td>
                </tr>
                
                <tr>
                    <td><b>A:</b></td>
                    <td><textarea rows="2" cols="50" name="a" required></textarea></td>
                </tr>

                <tr>
                    <td><b>B:</b></td>
                    <td><textarea rows="2" cols="50" name="b" required></textarea></td>
                </tr>

                <tr>
                    <td><b>C:</b></td>
                    <td><textarea rows="2" cols="50" name="c" required></textarea></td>
                </tr>

                <tr>
                    <td><b>D:</b></td>
                    <td><textarea rows="2" cols="50" name="d" required></textarea></td>
                </tr>
                
                <tr>
                <td><b>Answer:</b></td>
                <td>  <input type="radio" name="answer" value="A" required> A &nbsp;
                <input type="radio" name="answer" value="B"> B &nbsp;
                <input type="radio" name="answer" value="C"> C &nbsp;
                <input type="radio" name="answer" value="D"> D &nbsp;
                </td>
                </tr>

                <tr>
                <td><b>Set:</b></td>
                <td>  <input type="radio" name="set" value="1" required> 1 &nbsp;
                <input type="radio" name="set" value="2"> 2 &nbsp;
                <input type="radio" name="set" value="3"> 3
                </td>
                </tr>

                <tr>
                    <td colspan="2" align="center"><input type="submit" value="Add"/></td>
                </tr>
            </table>
        </form>        
    </div>
</body>

</html>