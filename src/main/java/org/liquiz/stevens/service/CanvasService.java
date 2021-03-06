package org.liquiz.stevens.service;

import edu.ksu.canvas.CanvasApiFactory;
import edu.ksu.canvas.interfaces.AssignmentWriter;
import edu.ksu.canvas.interfaces.SubmissionWriter;
import edu.ksu.canvas.model.Progress;
import edu.ksu.canvas.model.assignment.Assignment;
import edu.ksu.canvas.oauth.OauthToken;
import edu.ksu.canvas.requestOptions.MultipleSubmissionsOptions;
import edu.ksu.lti.launch.exception.NoLtiSessionException;
import edu.ksu.lti.launch.model.LtiLaunchData;
import edu.ksu.lti.launch.model.LtiSession;
import edu.ksu.lti.launch.oauth.LtiLaunch;
import edu.ksu.lti.launch.service.LtiSessionService;
import org.apache.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;
import org.springframework.stereotype.Service;

import java.io.IOException;
import java.util.List;
import java.util.Optional;

//https://github.com/kstateome/lti-attendance/blob/374acac3aefbfe89fd148c5e353e19e422f03e1c/src/main/java/edu/ksu/canvas/attendance/services/CanvasApiWrapperService.java

@Component
@Scope(value = "session")
@Service
@Qualifier
public class CanvasService {

    private static Logger LOG = Logger.getLogger(CanvasService.class);

    @Autowired
    protected LtiLaunch ltiLaunch;

    @Autowired
    private LtiSessionService ltiSessionService;

    @Autowired
    private CanvasApiFactory canvasApiFactory;


    public void ensureApiTokenPresent() throws NoLtiSessionException {
        ltiLaunch.ensureApiTokenPresent();
    }

    public void validateOauthToken() throws IOException, NoLtiSessionException {
        ltiLaunch.validateOAuthToken();
    }

    public String getEid() throws NoLtiSessionException {
        LtiSession ltiSession = ltiSessionService.getLtiSession();
        return ltiSession.getEid();
    }

    public Optional<Progress> gradeMultipleSubmissionsBySection(OauthToken oauthToken, MultipleSubmissionsOptions submissionOptions) throws IOException {
        SubmissionWriter submissionWriter = canvasApiFactory.getWriter(SubmissionWriter.class, oauthToken);
        return submissionWriter.gradeMultipleSubmissionsBySection(submissionOptions);
    }

    public Optional<Progress> gradeMultipleSubmissionsByCourse(OauthToken oauthToken, MultipleSubmissionsOptions submissionOptions) throws IOException {
        SubmissionWriter submissionWriter = canvasApiFactory.getWriter(SubmissionWriter.class, oauthToken);
        return submissionWriter.gradeMultipleSubmissionsByCourse(submissionOptions);
    }

    public List<LtiLaunchData.InstitutionRole> getRoles() throws NoLtiSessionException {
        LtiSession ltiSession = ltiSessionService.getLtiSession();
        LtiLaunchData launchData = ltiSession.getLtiLaunchData();
        return launchData.getRolesList();
    }

    public Optional<Assignment> createAssignment(Assignment assignment,
                                                 OauthToken oauthToken) throws IOException, NoLtiSessionException {
        LtiSession ltiSession = ltiSessionService.getLtiSession();
        LtiLaunchData ltiLaunchData = ltiSession.getLtiLaunchData();
        String
            courseId =
            ltiLaunchData.getCustom_canvas_course_id();

        AssignmentWriter assignmentWriter =
            canvasApiFactory.getWriter(AssignmentWriter.class, oauthToken);
        return assignmentWriter.createAssignment(courseId, assignment);
    }
}
