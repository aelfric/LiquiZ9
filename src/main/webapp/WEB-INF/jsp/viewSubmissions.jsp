<%--
  Created by IntelliJ IDEA.
  User: ejone
  Date: 8/11/2020
  Time: 4:18 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<c:set var="context" value="${pageContext.request.contextPath}"/>
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>view quizzes</title>
    <link rel="stylesheet" type="text/css" href="${context}/css/page.css">
</head>
<body>
<form method="get" action="deleteSubmissions${quizId}">
    <input class="controls" type="submit" value="Return to teacher view" formaction="teacherView"/>
    <h1>${quizName}</h1>
    <input class="controls" type="submit" name="${quizId}" value="View as Spreadsheet" formaction="createSpreadsheetQuiz${quizId}"/>
    <input type="submit" value="Download Grade File" formaction="${context}/grades/${quizId}" formmethod="post" />
    <table border="1">
        <tr>
            <th>Delete</th>
            <th>Number</th>
            <th>Full Name</th>
            <th>User ID</th>
            <th>Grade</th>
            <th>Date Submitted</th>
        </tr>
            <c:forEach var="quizSubmission" items="${quizSubList}" varStatus="loop">
                <tr>
                    <td> <input type='checkbox' name='submission' value="${quizSubmission.getId()}"></td>
                    <td>${loop.count}</td>
                    <td>${quizSubmission.getFullName()}</td>
                    <td>${quizSubmission.getUserId()}</td>
                    <td>${quizSubmission.getGrade()}</td>
                    <td>${quizSubmission.getDateSubmitted()}</td>
                </tr>
            </c:forEach>
    </table>
    <input class='controls' type='submit' value='Delete Selected Quizzes'/>
</form>
</body>
</html>
