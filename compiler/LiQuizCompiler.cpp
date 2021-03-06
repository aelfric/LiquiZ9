#include "LiQuizCompiler.hh"

#include <sstream>

#include "Questions.hh"

using namespace std;
using namespace nlohmann;

void LiQuizCompiler::findQuestionType(const string &type, double &points,
                                      string &delim, int pos, int len) {
  QuestionType *question = (questionTypes.find(type) != questionTypes.end())
                               ? questionTypes[type]
                               : defaultQuestionType;
  if (question != nullptr) {
    question->setText(delim);
    inputText = question->print(this, answers, partNum, questionNum, points);
    questionText.replace(pos, len, inputText);
  }
}

string LiQuizCompiler::removeExtension(const char fileName[]) {
  int i;
  for (i = 0; fileName[i] != '\0'; i++)
    ;
  for (; i >= 0 && fileName[i] != '.'; i--)
    ;
  return string(fileName, i + 1);
}

void LiQuizCompiler::findDefinitions(const string &name, string &defs) const {
  if (definitions.find(name) == definitions.end()) {
    cerr << "missing definition " << name << " on line " << questionLineNumber
         << endl;
  } else {
    defs = definitions.at(name);
  }
}

#if 0
/*
TODO: replace existing lookup of specInfo,
  styleSheet = specInfo.at("defaults").at("stylesheet");
  with code that checks if the symbol is actually there, prints an error message ie
  undefined symbol on line xxx

*/
static void expect(string& var, LiquiZCompiler* compiler, const json& specInfo, const char name[]) {

}

template<typename T>
static void lookup(T& var, LiquiZCompiler* compiler, const json& specInfo, const char name[], const char name2[]) {

}
#endif

LiQuizCompiler::LiQuizCompiler(const char liquizFileName[]) {
  questionText.reserve(1024);
  string baseFileName = removeExtension(liquizFileName);
  liquizFile.open("quizzes/" + baseFileName + "lq");
  html.open(baseFileName + "jsp");
  answers.open("quizzes/" + baseFileName + "ans");
  setLogLevel(3);    // set log level to show everything
  questionNum = 1; // start quiz on first question
  partNum = 0; // start section on first part
  questionCount = 0; // number of question inputs in the current question
  points = 0;
}

static json merge( const json &a, const json &b ) {
  json result = a.flatten();
  json tmp = b.flatten();
  for ( auto it = tmp.begin(); it != tmp.end(); ++it )
    result[it.key()] = it.value();
  return result.unflatten();
}

void LiQuizCompiler::includeQSpec(json* parentQuizSpec, const string& filename) {
  string specText;
  {
    ifstream specFile("spec/" + filename);
    string line;
    while (!specFile.eof()) {
      getline(specFile, line);
      specText += line;
      specText += '\n';
    }
  }

  json specInfo = json::parse(specText);

  if (logLevel >= 3) {
    cerr << "dumping qspec json before merge\n";
    for (auto i = specInfo.begin(); i != specInfo.end(); ++i)
      cerr << i.key() << "==>" << i.value() << '\n';
  }

  if (specInfo.find("parent") != specInfo.end()) {
    nlohmann::json parentQuizSpec;
    includeQSpec(&parentQuizSpec, specInfo.at("parent")); //TODO: merge specInfo on top of parentQuizSpec
    merge(parentQuizSpec, specInfo);
    specInfo = parentQuizSpec;
  }
  if (parentQuizSpec != nullptr) {// only the first level sets all the variables below
    *parentQuizSpec = specInfo;
    return;
  }
// specInfo should now contain the merged specification of all recursive files

  if (logLevel >= 3) {
    for (auto i = specInfo.begin(); i != specInfo.end(); ++i)
      cerr << i.key() << "==>" << i.value() << '\n';
  }

// TODO: check error on all these. If defaults does not exist, do nothing?
  imgFile = specInfo.at("defaults").at("img");
  styleSheet = specInfo.at("defaults").at("stylesheet");
  fillSize = specInfo.at("defaults").at("fillInTheBlankSize");
  timeLimit = specInfo.at("defaults").at("timeLimit");
  email = specInfo.at("email");
  author = specInfo.at("author");

  for (nlohmann::json::iterator it = specInfo.at("def").begin(); it != specInfo.at("def").end(); ++it) {
    string name = it.key();
    string defs;

    for (int i = 0; i < it.value().size(); i++) {
      string defVal = it.value()[i];
      defs += defVal;
      defs += ",";
    }
    defs.erase(defs.size()-1, 1);
    definitions[name] = defs;
    answers << "defs" << "\t" << name << "\t" << defs << "\n";
  }
}

void LiQuizCompiler::getJSONHeader() {
  string line;
  getline(liquizFile, line);
  nlohmann::json header = nlohmann::json::parse(line);
#if 0
  string specName;
  if (expect(specName, this, header, "quizspec")) {
    includeQSpec(specName)
  }
#endif
  if (header.find("quizspec") != header.end()) {
    string specName = header.at("quizspec");//TODO: pull error checking into separate function above
    includeQSpec(nullptr, specName);
  }
  quizName = header.at("name"); //TODO: error checking
}

void LiQuizCompiler::generateHeader() {
  getJSONHeader();
  html <<
R"(<%org.liquiz.stevens.login.Login.checkLogin();%>
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8"/>
  <link rel="stylesheet" type="text/css" href='css/)" <<
    styleSheet <<
R"('>
  <title>
    LiQuiz [)" <<
    quizName <<
R"(]
  </title>
  <script src='js/quiz.js'></script>
</head>
<body onload='startTime()" <<
  timeLimit << ")'>" <<
R"(
  <form method="get" action="gradquiz.jsp"></form>

  <!-- Header -->
  <div id='header' class='header'>
    <img class='logo' src='media/)" <<
  imgFile << "'/>" <<
R"(
    <div class='headerText'>
      <div class='quizTitle'>
        )" <<
  quizName <<
R"(
      </div>

      <div class='headerDetails'>
        <div class='headerRow'>
          )" <<
  author <<
R"(
        </div>
        <div class='headerRow'>
          Email  )" <<
           email << "  if you have any questions!" <<
R"(
        </div>
        <div class='headerRow'>
          <input id='pledge' type='checkbox' name='pledged' value='pledged'/>
          <label for='pledge'>I pledge my honor that I have abided by the Stevens Honor System</label>
        </div>
        <pre id='topTime'></pre>
      </div>
    </div>
    <div class='headerButtons'>
      <div class='controls'>
      <input type='button' value='Turn Audio On' onClick='scheduleAudio()'/>
    </div>
    <div class='controls'>
      <input  type='button' value='Submit Quiz' onClick='showResult()'/>
    </div>
  </div>
  </div>
)";
}

void LiQuizCompiler::setAnswer() {
  smatch m;
  answerText = questionText;
  int pos, end;
  while (regex_search(answerText, m, qID)) {
    pos = m.position();
    for (int i = m.position(); answerText[i] != '='; i++) {
      pos++;
    }
    answerText.insert(pos+2, "a");
  }
}

void LiQuizCompiler::makeQuestion(nlohmann::json &question) {
  string style = question.at("style");
  string preStart, preEnd;

  if (style == "pcode" || style == "code") {
    preStart = "<pre class='pcode'>";
    preEnd = "</pre>";
  } else {
    preStart = "<pre class='text'>";
    preEnd = "</pre>";
  }

  if (style != "def") {
    string temp = question.at("points");
    double totalPoints = std::stod(temp);
    string questionName = question.at("name");
    html << R"(
  <div class='section'>
    <div class='question' id='q)";
    html << questionNum << "'>";
    html << R"(
      <div>
        )";
    html << questionNum << "." << "\t" << questionName;
    html << R"(
        <span class='pts'>  )";
    html << "(" << totalPoints<< " points)</span><input type='button' class='protestButton' onClick='protestRequest()' value='Click to report a problem'>";
    html << R"(
      </div>
      )";
    html << preStart << endl;
    smatch m;
    double points = totalPoints / questionCount;

    while (regex_search(questionText, m, specials)) {
      string delim = m[2];

      int pos = questionText.find("<p hidden>", m.position());
      string end = "</p>";
      int endPos = questionText.find(end, m.position());
      string qLine;
      for (int i = pos + 10; i < endPos; i++) {
        qLine += questionText[i];
      }
      questionLineNumber = stoi(qLine);

      string type;
      if (delim[0] != 'f') {
        for (int i = 0; delim[i] != ':' && delim[i] != '{'; i++) {
          type += delim[i];
        }
      } else {
        type = delim[0];
      }
      findQuestionType(type, points, delim, m.position(), m.length());
    }
    questionText.erase(questionText.length()-1,1);
    setAnswer();
    html << questionText << preEnd;

    html << R"(
    </div>

    <div class='answer'>
      )";
    html << preStart;
    html << R"(
)";
    html << answerText <<  "<div id='" << questionNum << "'> </div>" << preEnd;
    html << R"(
    </div>
  </div>

  )";
    questionNum++;
  } else {
    string defs = question.at("values");
    string name = question.at("name");
    definitions[name] = defs;
    answers << "defs"
            << "\t" << name << "\t" << defs << '\n';
  }
}

void LiQuizCompiler::grabQuestions() {
  string line, qID, temp;
  smatch m;
  lineNumber = 1;
  while (getline(liquizFile, line), !liquizFile.eof()) {
    if (regex_search(
            line, m,
            questionStart)) {  // looking for the beginning of a question
      istringstream s(line);
      nlohmann::json question;  // gets the question header
      s >> question;
      lineNumber++;
      while (getline(liquizFile, line),
             !liquizFile.eof() &&
                 line != DELIM) {  // gets line within question section
        lineNumber++;
        questionText =
            questionText + line + "<p hidden>" + to_string(lineNumber) + "</p>";
        questionText += '\n';
      }
      lineNumber++;
      for (int i = 0; i < questionText.length(); i++) {
        if (questionText[i] == '$') {
          questionCount++;
        }
      }
      questionCount /= 2;
      makeQuestion(question);
      questionCount = 0;
      questionText = "";
    }
  }
}

void LiQuizCompiler::generateFooter() {
  html <<
      R"(
    <div class='footer'>
      <pre id='bottomTime'></pre>
      <input class='controls' type='button' value='Submit Quiz' onClick='showResult()'/>
    </div>
    </form>
</body>
</html>
      )";
}

void LiQuizCompiler::closeFile() {
  liquizFile.close();
  html.close();
  answers.close();
}

void LiQuizCompiler::generateQuiz() {
  generateHeader();
  grabQuestions();
  generateFooter();
  closeFile();
}

const regex LiQuizCompiler::questionStart("^\\{");
const regex LiQuizCompiler::specials(
    "\\$([a-z]*\\(|\\d+[cs]?\\{)?([^\\$]+)\\$");
const regex LiQuizCompiler::qID("name='[q||T||Q||m||s||n||S]_[0-9]*_[0-9]*'");

unordered_map<string, QuestionType *> LiQuizCompiler::questionTypes{
    {"mch", new MultipleChoiceHorizontal()},
    {"mcv", new MultipleChoiceVertical()},
    {"mah", new MultipleAnswerHorizontal()},
    {"mav", new MultipleAnswerVertical()},
    {"f", new FillIn()},
    {"tar", new TextQuestion()},
    {"def", new Definition()},
    {"dro", new DropDown()},
    {"img", new Image()},
    {"vid", new Video()},
    {"rnd", new RandomQuestion}};
