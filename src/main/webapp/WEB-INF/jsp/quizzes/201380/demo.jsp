<%--
  Created by IntelliJ IDEA.
  User: ejone
  Date: 7/2/2020
  Time: 10:39 AM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>

<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <link rel="stylesheet" type="text/css" href="media/quiz.css" media="all">
    <title>
    demo
    </title>


    <script src='../../../../quiz.js'></script>
</head>
<body onload='startTime(30)'>



<form method="post" action="testQuiz">
    <div id='header' class='header'>
        <div style='background-color: #ccc;text-align: center;border-radius: 10px; width: 240px; float: left'>
            <img class='header' src='media/StevensLogo380x326.png'/>

        </div>
        <div style='margin-left: 250px'>
            <table>
                <tr><td class='headtext'>Demo Quiz</td><td></td></tr>
                <tr><td class='headtext'>Dov Kruger</td></tr>
                <tr><td class='headtext'>Email  Dov.Kruger@stevens.edu  if you have any questions!</td></tr>

                <h1>Absolute Path is:<%= request.getServletContext().getRealPath("/") %></h1>

                <div class='q' id='q1'>1. Multiple Choice Horizontal<span class='pts'> (10 points)</span>
                    <pre class='text'>
Which of the following is a mammal?<p hidden>9</p>
<input class='mc' name='q_1_1' type='radio' value=' fish'> fish	<input class='mc' name='q_1_1' type='radio' value=' bird'> bird	<input class='mc' name='q_1_1' type='radio' value=' cat'>cat<p hidden>10</p>
</pre>
                    <input type='button' class='protestButton' onClick='protestRequest()' value='Click to report a problem'><br><div id='1'></div></div>
                <div class='q' id='q2'>2. Multiple Choice Vertical<span class='pts'> (15 points)</span>
                    <pre class='text'>
Who is in the ECE Department?<p hidden>13</p>
<input class='mc' name='q_2_2' type='radio' value=' Kruger'> Kruger

<input class='mc' name='q_2_2' type='radio' value=' Thompson'> Thompson

<input class='mc' name='q_2_2' type='radio' value=' Sinnreich-Levi'> Sinnreich-Levi<p hidden>14</p>
</pre>
                    <input type='button' class='protestButton' onClick='protestRequest()' value='Click to report a problem'><br><div id='2'></div></div>
                <div class='q' id='q3'>3. Multiple Answer Horizontal<span class='pts'> (45 points)</span>
                    <pre class='text'>
Who is in the ECE Department?<p hidden>17</p>
<input class='ma' name='m_3_3' type='checkbox' value=' Kruger'> Kruger     <input class='ma' name='m_3_3' type='checkbox' value=' Thompson'> Thompson     <input class='ma' name='m_3_3' type='checkbox' value=' Sinnreich-Levi'> Sinnreich-Levi     <input class='ma' name='m_3_3' type='checkbox' value=' Favardin'> Favardin     <input class='ma' name='m_3_3' type='checkbox' value=' Song'> Song     <input class='ma' name='m_3_3' type='checkbox' value=' Lu'> Lu     <p hidden>18</p>
</pre>
                    <input type='button' class='protestButton' onClick='protestRequest()' value='Click to report a problem'><br><div id='3'></div></div>
                <div class='q' id='q4'>4. Multiple Answer Vertical<span class='pts'> (50 points)</span>
                    <pre class='text'>
Where is Stevens located?<p hidden>21</p>
<input class='ma' name='m_4_4' type='checkbox' value=' Hoboken'> Hoboken

<input class='ma' name='m_4_4' type='checkbox' value=' United States'> United States

<input class='ma' name='m_4_4' type='checkbox' value=' New York'> New York

<input class='ma' name='m_4_4' type='checkbox' value=' New Jersey'> New Jersey<p hidden>22</p>
</pre>
                    <input type='button' class='protestButton' onClick='protestRequest()' value='Click to report a problem'><br><div id='4'></div></div>
                <div class='q' id='q5'>5. Survey<span class='pts'> (50 points)</span>
                    <pre class='text'>
I like ice cream. <select class='' name='q_5_5'><option value=' '> </option>
<option value='strongly disagree'>strongly disagree</option>
<option value='disagree'>disagree</option>
<option value='no opinion'>no opinion</option>
<option value='agree'>agree</option>
<option value='strongly agree'>strongly agree</option>
</select><p hidden>25</p>
I like programming. <select class='' name='q_5_6'><option value=' '> </option>
<option value='strongly disagree'>strongly disagree</option>
<option value='disagree'>disagree</option>
<option value='no opinion'>no opinion</option>
<option value='agree'>agree</option>
<option value='strongly agree'>strongly agree</option>
</select><p hidden>26</p>
Stevens is a good school. <select class='' name='q_5_7'><option value=' '> </option>
<option value='strongly disagree'>strongly disagree</option>
<option value='disagree'>disagree</option>
<option value='no opinion'>no opinion</option>
<option value='agree'>agree</option>
<option value='strongly agree'>strongly agree</option>
</select><p hidden>27</p>
Teaching online is easy. <select class='' name='q_5_8'><option value=' '> </option>
<option value='strongly disagree'>strongly disagree</option>
<option value='disagree'>disagree</option>
<option value='no opinion'>no opinion</option>
<option value='agree'>agree</option>
<option value='strongly agree'>strongly agree</option>
</select><p hidden>28</p>
</pre>
                    <input type='button' class='protestButton' onClick='protestRequest()' value='Click to report a problem'><br><div id='5'></div></div>
                <div class='q' id='q6'>6. Basic Knowledge<span class='pts'> (10 points)</span>
                    <pre class='text'>
For example register r15 is the <input class='' name='Q_6_9' type='text' id='Q_6_9' size='3'/>, r14 is the <input class='' name='Q_6_10' type='text' id='Q_6_10' size='3'/>, and r13 is <input class='' name='Q_6_11' type='text' id='Q_6_11' size='3'/>.<p hidden>31</p>
We can say that register d1 and s2 <select class='' name='q_6_12'><option value='can be used independently'>can be used independently</option>
<option value='share the same bits'>share the same bits</option>
<option value='should never be used because they are reserved'>should never be used because they are reserved</option>
<option value='are not valid in the arm architecture'>are not valid in the arm architecture</option>
</select>.<p hidden>32</p>
</pre>
                    <input type='button' class='protestButton' onClick='protestRequest()' value='Click to report a problem'><br><div id='6'></div></div>
                <div class='q' id='q7'>7. Write a Function<span class='pts'> (10 points)</span>
                    <pre class='text'>
author: Andrew Desanti<p hidden>35</p>
In C++, write the function:<p hidden>36</p>
bool isLeap(int year);<p hidden>37</p>
that returns true if the year is a leap year and false if it is not.<p hidden>38</p>
A year is a leap year if it is divisible by 4 but not divisible by 100, OR<p hidden>39</p>
if it is divisible by 400. Recall that && is logical AND and || is logical OR.<p hidden>40</p>
Example: 1904 is a leap year (divisible by 4) 1900 is not (divisible by 100) but 2000 is a leap year (divisble by 400)<p hidden>41</p>
<textarea rows='10' cols='60' id='q_7_13' name='q_7_13'></textarea><p hidden>42</p>
</pre>
                    <input type='button' class='protestButton' onClick='protestRequest()' value='Click to report a problem'><br><div id='7'></div></div>
                <div class='q' id='q8'>8. gcd<span class='pts'> (10 points)</span>
                    <pre class='pcode'>

gcd(a,b)       // Complexity: <select class='' name='q_8_14'><option value=' '> </option>
<option value='O(n)'>O(n)</option>
<option value='O(n^2)'>O(n^2)</option>
<option value='O(n^3)'>O(n^3)</option>
<option value='O(n^4)'>O(n^4)</option>
<option value='O(log(n))'>O(log(n))</option>
<option value='O(√(n))'>O(√(n))</option>
<option value='O(2^n)'>O(2^n)</option>
<option value='O(3^n)'>O(3^n)</option>
<option value='O(10^n)'>O(10^n)</option>
<option value='O(n!)'>O(n!)</option>
<option value='O(n^n)'>O(n^n)</option>
<option value='O(1)'>O(1)</option>
<option value='O(n*log(n)'>O(n*log(n)</option>
<option value='O(n*√n)'>O(n*√n)</option>
</select><p hidden>45</p>
  if <input class='' name='q_8_15' type='text' id='q_8_15' size='6'/> = 0<p hidden>46</p>
    return a<p hidden>47</p>
  end<p hidden>48</p>
  return <input class='' name='q_8_16' type='text' id='q_8_16' size='6'/>(b, a mod b)<p hidden>49</p>
end <p hidden>50</p>
</pre>
                    <input type='button' class='protestButton' onClick='protestRequest()' value='Click to report a problem'><br><div id='8'></div></div>
                <div class='q' id='q9'>9. Basic Instructions<span class='pts'> (20 points)</span>
                    <pre class='pcode'>

After each of the following assembler instruction show the values in the registers<p hidden>53</p>
000102b4: mov  r0, #4    @r0=<input class='' name='Q_9_17' type='text' id='Q_9_17' size='8'/>   pc=<input class='' name='Q_9_18' type='text' id='Q_9_18' size='8'/><p hidden>54</p>
000102b8: sub  r0, #5    @r0=<input class='' name='Q_9_19' type='text' id='Q_9_19' size='8'/>   pc=<input class='' name='Q_9_20' type='text' id='Q_9_20' size='8'/><p hidden>55</p>
000102bc: adds r0, #1    @r0=<input class='' name='Q_9_21' type='text' id='Q_9_21' size='8'/>   V=<input class='' name='q_9_22' type='text' id='q_9_22' size='1'/> Z=<input class='' name='q_9_23' type='text' id='q_9_23' size='1'/> N=<input class='' name='q_9_24' type='text' id='q_9_24' size='1'/><p hidden>56</p>
000102bc: adds r0, #1    @r0=<input class='' name='Q_9_25' type='text' id='Q_9_25' size='8'/>   V=<input class='' name='q_9_26' type='text' id='q_9_26' size='1'/> Z=<input class='' name='q_9_27' type='text' id='q_9_27' size='1'/> N=<input class='' name='q_9_28' type='text' id='q_9_28' size='1'/><p hidden>57</p>
000102bc: subs r0, #1    @r0=<input class='' name='Q_9_29' type='text' id='Q_9_29' size='8'/>   V=<input class='' name='q_9_30' type='text' id='q_9_30' size='1'/> Z=<input class='' name='q_9_31' type='text' id='q_9_31' size='1'/> N=<input class='' name='q_9_32' type='text' id='q_9_32' size='1'/><p hidden>58</p>
</pre>
                    <input type='button' class='protestButton' onClick='protestRequest()' value='Click to report a problem'><br><div id='9'></div></div>
                <div class='q' id='q10'>10. Logic Gates<span class='pts'> (10 points)</span>
                    <pre class='pcode'>

<img src='media/imageQuestion.png'></img><p hidden>61</p>
<p hidden>62</p>
What kind of logic gate is this?<p hidden>63</p>
<input class='mc' name='q_10_33' type='radio' value=' OR'> OR	<input class='mc' name='q_10_33' type='radio' value=' NOR'> NOR	<input class='mc' name='q_10_33' type='radio' value=' AND'> AND	<input class='mc' name='q_10_33' type='radio' value=' XOR'> XOR	<p hidden>64</p>
</pre>
                    <input type='button' class='protestButton' onClick='protestRequest()' value='Click to report a problem'><br><div id='10'></div></div>
                <div class='q' id='q11'>11. Watch and React<span class='pts'> (20 points)</span>
                    <pre class='pcode'>

Watch the movie on the Tacoma Narrows Bridge.<p hidden>67</p>
Should engineers have known the bridge would collapse?<p hidden>68</p>
What caused the collapse?<p hidden>69</p>
<video controls width='320' height='240'><source src='media/TacomaNarrowsBridge.mp4' type='video/mp4'></video><p hidden>70</p>
<textarea rows='10' cols='60' id='q_11_34' name='q_11_34'>Type your essay here</textarea><p hidden>71</p>
</pre>
                    <input type='button' class='protestButton' onClick='protestRequest()' value='Click to report a problem'><br><div id='11'></div></div>
                <div class='q' id='q12'>12. Object Oriented Terminology<span class='pts'> (50 points)</span>
                    <pre class='text'>
A class is a <select class='' name='q_12_35'><option value=' '> </option>
<option value='parent'>parent</option>
<option value='child'>child</option>
<option value='object'>object</option>
<option value='class'>class</option>
<option value='message'>message</option>
<option value='method'>method</option>
<option value='encapsulation'>encapsulation</option>
<option value='instantiate'>instantiate</option>
<option value='instantiation'>instantiation</option>
<option value='instance of'>instance of</option>
<option value='abstract'>abstract</option>
<option value='interface'>interface</option>
<option value='concrete'>concrete</option>
<option value='generic'>generic</option>
<option value='kind of'>kind of</option>
</select> object.<p hidden>74</p>
An object is a <select class='' name='q_12_36'><option value=' '> </option>
<option value='parent'>parent</option>
<option value='child'>child</option>
<option value='object'>object</option>
<option value='class'>class</option>
<option value='message'>message</option>
<option value='method'>method</option>
<option value='encapsulation'>encapsulation</option>
<option value='instantiate'>instantiate</option>
<option value='instantiation'>instantiation</option>
<option value='instance of'>instance of</option>
<option value='abstract'>abstract</option>
<option value='interface'>interface</option>
<option value='concrete'>concrete</option>
<option value='generic'>generic</option>
<option value='kind of'>kind of</option>
</select> a class.<p hidden>75</p>
To create an object we <select class='' name='q_12_37'><option value=' '> </option>
<option value='parent'>parent</option>
<option value='child'>child</option>
<option value='object'>object</option>
<option value='class'>class</option>
<option value='message'>message</option>
<option value='method'>method</option>
<option value='encapsulation'>encapsulation</option>
<option value='instantiate'>instantiate</option>
<option value='instantiation'>instantiation</option>
<option value='instance of'>instance of</option>
<option value='abstract'>abstract</option>
<option value='interface'>interface</option>
<option value='concrete'>concrete</option>
<option value='generic'>generic</option>
<option value='kind of'>kind of</option>
</select> a class.<p hidden>76</p>
An object is an <select class='' name='q_12_38'><option value=' '> </option>
<option value='parent'>parent</option>
<option value='child'>child</option>
<option value='object'>object</option>
<option value='class'>class</option>
<option value='message'>message</option>
<option value='method'>method</option>
<option value='encapsulation'>encapsulation</option>
<option value='instantiate'>instantiate</option>
<option value='instantiation'>instantiation</option>
<option value='instance of'>instance of</option>
<option value='abstract'>abstract</option>
<option value='interface'>interface</option>
<option value='concrete'>concrete</option>
<option value='generic'>generic</option>
<option value='kind of'>kind of</option>
</select> of a class.<p hidden>77</p>
To hide the details of an object is called <select class='' name='q_12_39'><option value=' '> </option>
<option value='parent'>parent</option>
<option value='child'>child</option>
<option value='object'>object</option>
<option value='class'>class</option>
<option value='message'>message</option>
<option value='method'>method</option>
<option value='encapsulation'>encapsulation</option>
<option value='instantiate'>instantiate</option>
<option value='instantiation'>instantiation</option>
<option value='instance of'>instance of</option>
<option value='abstract'>abstract</option>
<option value='interface'>interface</option>
<option value='concrete'>concrete</option>
<option value='generic'>generic</option>
<option value='kind of'>kind of</option>
</select>.<p hidden>78</p>
</pre>
                    <input type='button' class='protestButton' onClick='protestRequest()' value='Click to report a problem'><br><div id='12'></div></div>

                <div class='controls'>
                    <div>Time Remaining</div>
                    <div id='bottomTime' class='time'></div>
                    <input class='controls' type='submit' value='Submit Quiz' onClick='showResult()'/>
                </div>
    </form>
</body>
</html>