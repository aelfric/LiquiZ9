var end;
var audioOn = false;
var timeLimit = 0; // minutes
var firstAlert = 29.5;
var alertInterval = 0.166666;
var nextAlert = firstAlert;
var countDownThread;

function scheduleAudio() {
  audioOn = !audioOn;
  document.getElementById("audioControl").value = audioOn
    ? "turn audio alerts OFF"
    : "turn audio alerts ON";
}

function updateControls() {
  var d = new Date();
  var remaining = end - d.getTime();
  if (remaining < 0) clearInterval(countDownThread);

  if (audioOn && remaining <= nextAlert * 60000) {
    var audioAlertName =
      nextAlert >= firstAlert
        ? "alert25"
        : nextAlert >= firstAlert - alertInterval
        ? "alert20"
        : nextAlert >= firstAlert - alertInterval * 2
        ? "alert15"
        : nextAlert >= firstAlert - alertInterval * 3
        ? "alert10"
        : nextAlert >= firstAlert - alertInterval * 4
        ? "alert5"
        : nextAlert >= firstAlert - alertInterval * 5
        ? "alertover"
        : null;

    nextAlert -= alertInterval;
    if (audioAlertName != null) document.getElementById(audioAlertName).play();
  }
  var min = Math.floor(remaining / 60000);
  var seconds = Math.floor((remaining - min * 60000) / 1000);
  if (seconds < 10) seconds = "0" + seconds;
  var timeDisp = min + ":" + seconds;
  document.getElementById("topTime").innerText = timeDisp;
  document.getElementById("bottomTime").innerText = timeDisp;
}

function startTime(limit) {
  end = new Date().getTime() + limit * 60000;
  updateControls();
  countDownThread = setInterval(updateControls, 2000);
}

function checkAndSubmit() {
  var pledge = document.getElementById("pledge");
  console.log(name + ", " + pledge);
  var submission = [];
  var f = document.forms[0];
  for (var i = 0; i < f.elements.length; i++) {
    submission.push([f.elements[i].id, f.elements[i].value]);
  }
  var json = new XMLHttpRequest();
  json.open("post", "submitQuiz?quizId="+f.getAttribute("data-quizId"), true);
  json.setRequestHeader("Content-Type", "application/json");
  // Create a state change callback
  json.onreadystatechange = function () {
    if (json.readyState === 4 && json.status === 200) {
      // Print received data from server
      document.body.innerHTML = this.responseText;
    }
  };
  json.send(JSON.stringify(submission));
  //    document.forms[0].submit();
}

function selectMusic(v) {
  document.getElementById(v).play();
}

function protestRequest() {
  window.open(
    "protest-window.html",
    "Ratting",
    "width=550,height=500,left=150,top=200,toolbar=0,status=0"
  );
}

function loadJSON(callback) {
  var xobj = new XMLHttpRequest();
  xobj.overrideMimeType("application/json");
  xobj.open("GET", "getAnswers", true);
  xobj.onreadystatechange = function () {
    if (xobj.readyState === 4 && xobj.status === "200") {
      callback(xobj.responseText);
    }
  };
  xobj.send(null);
}

function getJSON(url, callback) {
  var xhr = new XMLHttpRequest();
  xhr.open("GET", url, true);
  xhr.responseType = "json";
  xhr.onload = function () {
    var status = xhr.status;
    if (status === 200) {
      callback(null, xhr.response);
    } else {
      callback(status, xhr.response);
    }
  };
  xhr.send();
}

function showResult() {
  const f = document.forms[0];
  const quizID = f.getAttribute("data-quizId")
  var answerSections = document.getElementsByClassName("answer");
  let i;
  for (i = 0; i < answerSections.length; i++) {
    answerSections[i].style.display = "block";
    // answerSections[i].style.color = "#ff0000";
  }

  var inputs = document.getElementsByTagName("input");
  for (i = 0; i < inputs.length; i++) {
    if (inputs[i].checked === true) {
      inputs[i].disabled = false;
    } else {
      inputs[i].readOnly = true;
      inputs[i].disabled = true;
    }
    if (inputs[i].type === "checkbox") {
      inputs[i].style.borderColor = "#ff0000";
    }
  }

  getJSON("getAnswers?qID="+encodeURI(quizID), function (
    err,
    data
  ) {
    if (err !== null) {
      alert("Something went wrong: " + err);
    } else {
      var answerObj = data;
      for(let i = 0; i<data.length; i++){
        let answerElement = document.getElementById("A" + data[i].id);
        answerElement.value = data[i].answers;
        //TODO this only works for text inputs and maybe select.  What does backend for checkbox and radio look like?
      }
      var questionAmount = Object.keys(answerObj).length;
      var sectionCurrent, sectionLast = answerObj[0]["id"].split("_")[1];
      var pointsTotal = 0;
      var pointsEarned = 0;

      for (var i = 0; i < questionAmount; i++) {
        var qID = "a" + answerObj[i]["id"];
        var answer = answerObj[i]["answers"];
        var options = document.getElementsByName(qID);
        sectionCurrent = answerObj[i]["id"].split("_")[1];

        if (sectionCurrent !== sectionLast) {
          var section = document.getElementById(sectionLast);
          section.innerHTML =
            "You earned: " +
            Math.ceil(100 * pointsEarned) / 100 +
            " points out of: " +
            Math.ceil(100 * pointsTotal) / 100 +
            " points.";

          pointsTotal = 0;
          pointsEarned = 0;
          sectionLast = sectionCurrent;
        }
        pointsTotal += answerObj[i]["pointsT"];
        pointsEarned += answerObj[i]["pointsE"];

        for (var j = 0; j < options.length; j++) {
          options[j].setAttribute("disabled", "true");
          if (answer.includes(options[j].value)) {
            if (options[j].type === "radio") {
              options[j].checked = true;
              options[j].disabled = false;
            } else if (options[j].type === "checkbox") {
              options[j].checked = true;
            } else {
              options[j].diabled = false;
              options[j].value = answer;
            }
          }
          options[j].value = answer;
        }
      }
    }
  });
}

(function () {
  let template = document.getElementById("quiz-content");
  let root = document.getElementById("root");
  let sections = template.content.querySelectorAll("div.section");
  for (let i = 0; i < sections.length; i++) {
    root.appendChild(sections[i].cloneNode(true));
  }

  const questions = document.querySelectorAll('.question');
  for(let i = 0; i < questions.length; i++) {
    let q = document.querySelectorAll('.question')[i]
    let a = q.cloneNode(true);
    a.className = "answer"
    let ids = a.querySelectorAll('*[id]');
    for(let j = 0; j < ids.length; j++){
      ids[j].id = "A" + ids[j].id;
      ids[j].name = "A" + ids[j].name;
    }
    q.appendChild(a);
  }
})();
