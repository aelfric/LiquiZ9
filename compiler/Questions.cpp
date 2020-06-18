#include "Questions.hh"
#include "LiQuizCompiler.hh"
using namespace std;

inline const std::string &to_string(const std::string &s) { return s; }
inline std::string to_string(char c) {
  char s[2] = {c, '\0'};
  return std::string(s);
}

template <typename... Args>
void buildString(std::string &dest, const Args &... args) {
dest.clear();
int unpack[]{0, (dest += to_string(args), 0)...};
static_cast<void>(unpack);
}

QuestionType::~QuestionType() {}

void QuestionType::addAnswer(string &typeID, string &qID, const string &ans,
                             double points, ostream &answersFile, int &partNum,
                             int &questionNum) {
  partNum++;
  buildString(qID, typeID, "_", "q", questionNum, "_", partNum);
  answersFile << qID << "\t" << points << "\t" << ans << '\n';
  
}

static regex dSet("(:.*:)");

void MultipleChoiceHorizontal::getAnswer() {
  input = "";
  for (int i = 0; i < answer.length(); i++) {
    if (answer[i] == '*') {
      for (int j = i + 1; answer[j] != ',' && j < answer.length(); j++) {
        input += answer[j];
      }
      answer.erase(i, 1);
    }
  }
}

void MultipleChoiceHorizontal::getOptions() {
  replace = "";
  buildString(temp, "<input class='mc' name='", qID, "' type='radio' value='");
  for (int i = 0; i <= answer.length(); i++) {
    if (answer[i] == ',' || i == answer.length()) {
      replace += temp + option + "'>" + option + "\t";
      option = " ";
    } else {
      option += answer[i];
    }
  }
}

string MultipleChoiceHorizontal::print(const LiQuizCompiler *compiler,
                                       ostream &answersFile, int &partNum,
                                       int &questionNum, double &points) {
  input = "";
  answer = text;
  smatch m;

  if (regex_search(answer, m, dSet)) {
    answer = text.erase(0, 4);
    defName = "";
    for (int i = 0; answer[i] != ':'; i++) {
      defName += answer[i];
    }
    answer.erase(0, defName.length() + 1);
  } else {
    answer = text.erase(0, 4);
  }

  getAnswer();
  addAnswer(typeID, qID, input, points, answersFile, partNum, questionNum);
  getOptions();
  return replace;
}

void MultipleChoiceVertical::getAnswer() {
  input = "";
  for (int i = 0; i < answer.length(); i++) {
    if (answer[i] == '*') {
      for (int j = i + 1; answer[j] != ',' && j < answer.length(); j++) {
        input += answer[j];
      }
      answer.erase(i, 1);
    }
  }
}

void MultipleChoiceVertical::getOptions() {
  replace = "";
  buildString(temp, "<input class='mc' name='", qID, "' type='radio' value='");
  for (int i = 0; i <= answer.length(); i++) {
    if (answer[i] == ',' || i == answer.length()) {
      replace += temp + option + "'>" + option + "\n\n";
      option = " ";
    } else {
      option += answer[i];
    }
  }
  replace.erase(replace.length() - 1, 1);
  replace.erase(replace.length() - 1, 1);
}

string MultipleChoiceVertical::print(const LiQuizCompiler *compiler,
                                     ostream &answersFile, int &partNum,
                                     int &questionNum, double &points) {
  input = "";
  answer = text.erase(0, 4);
  getAnswer();
  addAnswer(typeID, qID, input, points, answersFile, partNum, questionNum);
  getOptions();
  return replace;
}

void MultipleAnswerHorizontal::getAnswer() {
  input = "";
  for (int i = 0; i < answer.length(); i++) {
    if (answer[i] == '*') {
      for (int j = i + 1; answer[j] != ',' && j < answer.length(); j++) {
        input += answer[j];
      }
      input += ",";
      answer.erase(i, 1);
    }
  }
  input.erase(input.length() - 1, 1);
}

void MultipleAnswerHorizontal::getOptions() {
  replace = "";
  buildString(temp, "<input class='ma' name='", qID,
              "' type='checkbox' value='");
  for (int i = 0; i <= answer.length(); i++) {
    if (answer[i] == ',' || i == answer.length()) {
      replace += temp + option + "'>" + option + "     ";
      option = " ";
    } else {
      option += answer[i];
    }
  }
}

string MultipleAnswerHorizontal::print(const LiQuizCompiler *compiler,
                                       ostream &answersFile, int &partNum,
                                       int &questionNum, double &points) {
  input = "";
  answer = text.erase(0, 4);
  getAnswer();
  addAnswer(typeID, qID, input, points, answersFile, partNum, questionNum);
  getOptions();
  return replace;
}

void MultipleAnswerVertical::getAnswer() {
  for (int i = 0; i < answer.length(); i++) {
    if (answer[i] == '*') {
      for (int j = i + 1; answer[j] != ',' && j < answer.length(); j++) {
        input += answer[j];
      }
      input += ",";
      answer.erase(i, 1);
    }
  }
  input.erase(input.length() - 1, 1);
}

void MultipleAnswerVertical::getOptions() {
  replace = "";
  buildString(temp, "<input class='ma' name='", qID,
              "' type='checkbox' value='");
  for (int i = 0; i <= answer.length(); i++) {
    if (answer[i] == ',' || i == answer.length()) {
      replace += temp + option + "'>" + option + "\n\n";
      option = " ";
    } else {
      option += answer[i];
    }
  }
  replace.erase(replace.length() - 1, 1);
  replace.erase(replace.length() - 1, 1);
}

string MultipleAnswerVertical::print(const LiQuizCompiler *compiler,
                                     ostream &answersFile, int &partNum,
                                     int &questionNum, double &points) {
  input = "";
  answer = text.erase(0, 4);
  getAnswer();
  addAnswer(typeID, qID, input, points, answersFile, partNum, questionNum);
  getOptions();
  return replace;
}

void FillIn::getFillInType(const char &type) {
  (fillTypes.find(type) != fillTypes.end()) ? typeID = type : typeID = "q";
}

string FillIn::print(const LiQuizCompiler *compiler, ostream &answersFile,
                     int &partNum, int &questionNum, double &points) {
  getFillInType(text[1]);

  //len = fillSize;

  if (typeID != "q") {
    answer = text.erase(0, 2);
  } else {
    answer = text.erase(0, 1);
  }

  if (answer[0] == '{') {
    for (int i = 1; answer[i] != '}'; i++) {
      size += answer[i];
    }

    len = stoi(size);
    answer.erase(0, size.length() + 3);
  } else {
    answer.erase(0, 1);
  }

  addAnswer(typeID, qID, answer, points, answersFile, partNum, questionNum);
  buildString(replace, "<input class='' name='", qID, "' type='text' id='", qID,
              "' size='", len, "'/>");
  size = "";
  answer = "";
  len = 6;
  typeID = "";
  return replace;
}

unordered_map<char, string> FillIn::fillTypes{
    {'Q', "case insensitive"},
    {'s', "space insensitive"},
    {'n', "numeric"},
    {'S', "space and case insensitive"}};

string TextQuestion::print(const LiQuizCompiler *compiler, ostream &answersFile,
                           int &partNum, int &questionNum, double &points) {
  addAnswer(typeID, qID, answer, points, answersFile, partNum, questionNum);
  text.erase(0, 4);
  buildString(replace, "<textarea rows='10' cols='60' id='", qID, "' name='",
              qID, "'>", text, "</textarea>");
  return replace;
}

void DropDown::getAnswer() {
  input = "";
  for (int i = 0; i < answer.length(); i++) {
    if (answer[i] == '*') {
      for (int j = i + 1; answer[j] != ',' && j < answer.length(); j++) {
        input += answer[j];
      }
      answer.erase(i, 1);
    }
  }
}

void DropDown::getOptions() {
  buildString(replace, "<select class='' name='", qID, "'>");
  for (int i = 0; i <= answer.length(); i++) {
    if (answer[i] == ',' || i == answer.length()) {
      replace += "<option value='" + option + "'>" + option + "</option>\n";
      option = "";
    } else {
      option += answer[i];
    }
  }
  replace += "</select>";
}

string DropDown::print(const LiQuizCompiler *compiler, ostream &answersFile,
                       int &partNum, int &questionNum, double &points) {
  input = "";
  answer = text.erase(0, 4);
  getAnswer();
  addAnswer(typeID, qID, input, points, answersFile, partNum, questionNum);
  getOptions();
  answer = "";
  return replace;
}

string Image::print(const LiQuizCompiler *, ostream &answersFile, int &partNum,
                    int &questionNum, double &points) {
  text.erase(0, 4);
  string temp = "media/" + text;
  buildString(replace, "<img src='", temp, "'></img>");
  return replace;
}

string Video::print(const LiQuizCompiler *, ostream &answersFile, int &partNum,
                    int &questionNum, double &points) {
  text.erase(0, 4);
  string temp = "media/" + text;
  buildString(replace, "<video controls width='320' height='240'><source src='",
              temp, "' type='video/mp4'></video>");
  return replace;
}

void Definition::getOptions() {
  buildString(replace, "<select class='' name='", qID, "'>");
  for (int i = 0; i <= defs.length(); i++) {
    if (defs[i] == ',' || i == defs.length()) {
      replace += "<option value='" + option + "'>" + option + "</option>\n";
      option = "";
    } else {
      option += defs[i];
    }
  }
  replace += "</select>";
}

string Definition::print(const LiQuizCompiler *compiler, ostream &answersFile,
                         int &partNum, int &questionNum, double &points) {
  answer = text.erase(0, 4);

  for (int i = 0; answer[i] != ':'; i++) {
    name += answer[i];
    count++;
  }

  compiler->findDefinitions(name, defs);
  answer = answer.erase(0, count + 1);

  addAnswer(typeID, qID, answer, points, answersFile, partNum, questionNum);
  getOptions();
  answer, name = "";
  count = 0;
  return replace;
}