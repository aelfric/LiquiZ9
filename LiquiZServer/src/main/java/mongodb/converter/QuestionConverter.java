/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mongodb.converter;

import com.mongodb.BasicDBObjectBuilder;
import com.mongodb.DBObject;
import org.bson.types.ObjectId;
import java.util.Map;
import java.util.HashMap;
import java.util.List;
import java.util.TreeMap;
import org.bson.Document;
import questions.Question;
import questions.NumQuestion;
import questions.SimpleQuestion;
import questions.MultiAnsQuestion;

/**
 *
 * @author ejone
 */
public class QuestionConverter {
    
    /**
     *
     * @param q Question to be converted to document
     * @return Document that has been converted
     */
    public static Document convert(Question q) {
                
		Document doc = new Document("_id", q.getId())
                                .append("grade", q.getGrade())
                                .append("gradeVal", q.getGradeValue())
                                .append("name", q.getName());
                doc = q.getDocument(doc);
		return doc;
	}

    /**
     *
     * @param doc Document to convert to Question
     * @return Question that has been converted
     */
    public static Question convert(Document doc) {
                    String type;
                    type = (String)doc.get("name");
                    switch(type.charAt(0)){
                        case 'q':
                        case 'Q':
                        case 's': 
                        case 'S':
                          SimpleQuestion sqc = new SimpleQuestion(doc.getString("ans"), doc.getDouble("gradeVal"), doc.getString("name"), doc.getObjectId("_id"));
                          return sqc;
                        case 'N':
                        case 'n':
                          NumQuestion nq = new NumQuestion(doc.getDouble("low"), doc.getDouble("high"), doc.getDouble("gradeVal"), doc.getString("name"), doc.getObjectId("_id"));
                          return nq;
                        case 'M':
                        case 'm':
                          List<Document> ansList = (List<Document>) doc.get("answers");
                          String[] ansArr = new String[ansList.size()];
                          int index = 0;
                          for(Document docAns : ansList){
                            ansArr[index] = docAns.getString("ans");
                            index++;
                          }
                          MultiAnsQuestion mqc = new MultiAnsQuestion(ansArr, doc.getDouble("gradeVal"), doc.getBoolean("subWrongAns") , doc.getString("name"), doc.getObjectId("_id"));
                          return mqc;
                        default:
                          System.out.println("error adding question");     
                    }
            return null;
                    
	}
    
}
