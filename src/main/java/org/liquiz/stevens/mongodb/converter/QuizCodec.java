/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package org.liquiz.stevens.mongodb.converter;

import com.mongodb.MongoClient;
import org.bson.*;
import org.bson.codecs.Codec;
import org.bson.codecs.CollectibleCodec;
import org.bson.codecs.DecoderContext;
import org.bson.codecs.EncoderContext;
import org.bson.codecs.configuration.CodecRegistry;
import org.bson.types.ObjectId;
import org.liquiz.stevens.questions.Question;
import org.liquiz.stevens.quiz.Quiz;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

/**
 * Mongo decoder for Quiz.
 */
public class QuizCodec implements CollectibleCodec<Quiz> {

    private final CodecRegistry registry;
    private final Codec<Document> documentCodec;
    private final QuestionConverter QuestionConverter;

    /**
     * Default constructor.
     */
    public QuizCodec() {
        this.registry = MongoClient.getDefaultCodecRegistry();
        this.documentCodec = this.registry.get(Document.class);
        this.QuestionConverter = new QuestionConverter();
    }

    /**
     * Codec constructor.
     * @param codec The existing codec to use.
     */
    public QuizCodec(Codec<Document> codec) {
        this.registry = MongoClient.getDefaultCodecRegistry();
        this.documentCodec = codec;
        this.QuestionConverter = new QuestionConverter();
    }

    /**
     * Registry constructor.
     * @param registry The CodecRegistry to use.
     */
    public QuizCodec(CodecRegistry registry) {
        this.registry = registry;
        this.documentCodec = this.registry.get(Document.class);
        this.QuestionConverter = new QuestionConverter();
    }

    /**
     * Encode the passed Order into a Mongo/BSON document.
     * @param writer The writer to use for encoding.
     * @param quiz The Quiz to encode.
     * @param encoderContext The EncoderContext to use for encoding.
     */
    @Override
    public void encode(
                    BsonWriter writer,
                    Quiz quiz,
                    EncoderContext encoderContext
                ) {
        List<Document> questionDocumentList = new ArrayList<>();
        for(Map.Entry<String, Question> entry : quiz.getQuestionsMap().entrySet()){
            Question mapQ = entry.getValue();
            Document doc = new Document("id", mapQ.getId())
                                        .append("name", mapQ.getName())
                                        .append("gradeVal", mapQ.getGradeValue());
            doc = entry.getValue().getDocument(doc);
            questionDocumentList.add(doc);
        }
        Document document = new Document("_id", quiz.getId())
                .append("quizName", quiz.getQuizName())
                .append("classId", quiz.getCourseId())
                .append("className", quiz.getClassName())
                .append("answerFile", quiz.getAnswerFile())
                .append("numTries", quiz.getNumTries())
                .append("maxGrade", quiz.getMaxGrade())
                .append("showAnswersAfter", quiz.getAnswersRelease())
                .append("quizId", quiz.getQuizId())
                .append("content", quiz.getContent())
                .append("assignmentId", quiz.getAssignmentId())
                .append("questionsMap", questionDocumentList);


        documentCodec.encode(writer, document, encoderContext);
    }

    /**
     * Get the class that this Codec works with.
     * @return Returns the class that this Codec works with.
     */
    @Override
    public Class<Quiz> getEncoderClass() {
        return Quiz.class;
    }

    /**
     * Decodes a Mongo/BSON document into an Order.
     * @param reader The reader containing the Document.
     * @param decoderContext The DecoderContext to use for decoding.
     * @return Returns the decoded Order.
     */
    @Override
    public Quiz decode(BsonReader reader, DecoderContext decoderContext) {
        Document document = documentCodec.decode(reader, decoderContext);

        Quiz quiz = new Quiz(document.getObjectId("_id"), document.getInteger("numTries"),
                             document.getString("quizName"), document.getString("classId"), document.getString("className"),
                             document.getString("answerFile"), document.getDouble("maxGrade"), document.getDate("showAnswersAfter"),
                             document.getLong("quizId"),
            document.getString("content"),
            document.getInteger("assignmentId"));

        ArrayList<Document> docArr = (ArrayList) document.get("questionsMap");
        for (Document doc : docArr) {
            Question question = QuestionConverter.convert(doc);
            quiz.addQuestion(question);
        }

        return quiz;
    }

    /**
     * Generates a new ObjectId for the passed Order (if absent).
     * @param quiz The Quiz to work with.
     * @return Returns the passed Order with a new id added if there
     * was none.
     */
    @Override
    public Quiz generateIdIfAbsentFromDocument(Quiz quiz) {
        if (!documentHasId(quiz)) {
            quiz.setId(new ObjectId());
        }

        return quiz;
    }

    /**
     * Returns whether or not the passed Order has an id.
     * @param quiz The Quiz that you want to check for
     * the presence of an id.
     * @return Returns whether or not the passed Order has an id.
     */
    @Override
    public boolean documentHasId(Quiz quiz) {
        return (quiz.getId() != null);
    }

    /**
     * Gets the id of the passed Order.If there is no id, it will
 throw an IllegalStateException (RuntimeException).
     * @param quiz The Quiz whose id you want to get.
     * @return Returns the id of the passed Order as a BsonValue.
     */
    @Override
    public BsonValue getDocumentId(Quiz quiz) {
        if (!documentHasId(quiz)) {
            throw new IllegalStateException("The document does not contain an _id");
        }

        return new BsonString(quiz.getId().toHexString());
    }
}