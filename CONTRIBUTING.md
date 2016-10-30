# Contributing to rLoop
rLoop is an open-source entry into SpaceX's [Hyperloop Pod Competition](http://www.spacex.com/hyperloop). You can become an official member of our team by filling out [this form.](https://docs.google.com/forms/d/e/1FAIpQLSfju0tH0LtEgnZkCslsqdfcByxXOJIGZL6Jv92yz8m2VieD0A/viewform)
We are a distributed team and communicate through Slack.


1. [Getting Involved](#getting-involved)
2. [Contribution Process](#contribution-process)
3. [Standards](#standards)
4. [Issue Reporting](#issue-reporting)
5. [Checklists](#checklists)


Note: This is the code development repository for the *rLoop pod systems* only. Before opening any issue or making a pull request, double check that you're in the right place.
* Code for the groundstation can be found [in that repository](https://github.com/rLoopTeam/eng-software-ground-station)
* For code meant for testing on the Hyperloop Development Kit, please see the [HDK repo](https://github.com/rLoopTeam/makers-hdk)


## Getting Involved


We're always looking for help identifying bugs, writing and reducing test cases, and improving documentation. There are quite a few features that are needed at this point. If you feel
like you can contribute, please check out the [code standards](https://github.com/rLoopTeam/eng-software-pod/blob/master/FIRMWARE/CODE_STANDARD/rloop_code_standard.txt), make a contribution, and we will be happy to consider it!


While we invite any and all to contribute to rLoop, most of the conversation and discussion takes place on our Slack Team. Planning is largely handled through JIRA. Please consider becoming a full member of the rLoop team
to stay up-to-date with the project!


Thank you.


## Contribution Process


rLoop uses git for software version control, and for branching and merging.


1. Write your contribution.
2. Make sure your contribution meets our [code standards.](https://github.com/rLoopTeam/eng-software-pod/blob/master/FIRMWARE/CODE_STANDARD/rloop_code_standard.txt)
3. Submit a pull request from your branch back to its parent feature branch. Include a check list, as described below. (Optionally, assign this to a specific member for review.)
4. Respond to any discussion. When the reviewer decides it's ready, they will merge the branch.


### Branching


Four basic types of branches are included in this repository.


1. Master Branch
2. Feature Branches
3. Developer Branches
4. Release Branches


Branches may be created during the course of development that may not fit neatly into the above categories. It is the responsibility of the developer who opens such branches to communicate
clearly their branch's purpose and procedures.


#### Master Branch


The role of the master branch is to represent the latest "production-ready" code. This should be working, bug-free code ready to be compiled and deployed to the pod. Source code on the master branch has undergone several
levels of peer review.


#### Feature Branches


Feature branches are used by developers to perform and record work on issues.

Feature branches need not necessarily be stable, even when pushed to the central repository. The practice of making incremental commits while working on an issue and pushing
these to the central repository is encouraged, to avoid lost work and to share work-in-progress. Small commits help isolate changes, which is useful when trying to debug defects.


Where possible, feature branches should be named according to their issue identifier. For example, branch logic_analyzer31 refers to issue 31.


Work on an issue may require the use of multiple branches. This can happen when a developer wants to try multiple solutions. Such branches should be appended with a character or descriptive term. Examples:
logic_analyzer31b or logic_analyzer31float.


#### Developer Branches


Developer branches are outside the scope of the above branches. They exists to try things out, or to maintain a branch of nice-to-haves that does not interfere with the review and integration process.
Developer branches may be pushed to the central repository as long as the branch creator is identifiable and the name of the branch does not conflict with the naming convention used in this repository.


#### Release Branches

Release branches are snapshots of the codebase that was run in the real world. We need to preserve the state of the code from our real-world tests so that any test data or bugs can be analyzed or replicated. Release branches are locked from continued development.


### Merging


When development is complete on an issue, the first step toward merging back into master is creating a Pull Request. The contributions should meet code, test, and commit message standards as described below.
Pull requests may be assigned to specific team members when appropriate.


Code review should take place using discussion features within the pull request. When the reviewer is satisfied, they should add a comment to the pull request and complete the merge.


## Standards


Contributions to rLoop are expected to have the following standards. Reviewers should use discretion when accepting changes.


### Code Standards


NOTE: We will migrate the contents of [this code standards file](https://github.com/rLoopTeam/eng-software-pod/blob/master/FIRMWARE/CODE_STANDARD/rloop_code_standard.txt) into this section at a later date.


### Commit Message Standards

##### A special note on JIRA integration:
rLoop uses [JIRA](http://jira.rloop.org/secure/RapidBoard.jspa?rapidView=19&projectKey=CTRL&view=detail) for team coordination and project managment. We have integrated GitHub with JIRA to streamline workflow communication. This enables us to quickly link issues to parent tasks without the need to update both services individually. Below is a quick overview on how to format your commit messages (called Smart Commits) so that everything stays in sync. The committer's email address must match their email address used in JIRA.

Please review [this video](https://youtu.be/hkLa2QR_pi8) for more in JIRA commits

Using Smart Commits allows you to:
* comment on issues
* record time tracking info against issues
* transition issues to any status defined in the JIRA project's workflow

Please visit [the Smart Commit documentation](https://confluence.atlassian.com/fisheye/using-smart-commits-298976812.html) for detailed information. **Reviewing this information is mandatory.**

The basic command line syntax for a Smart Commit message are:
* `<ignored text> <ISSUE_KEY> <ignored text> #<COMMAND> <optional COMMAND_ARGUMENTS>`
* ISSUE_KEY corresponds to a JIRA issue. For example: CTRL-41
* #command corresponds to one of three actions: comment, time, or transition
* optional COMMAND_ARGUMENTS can be comments, time records, etc. 

Smart Commit examples:
* CTRL-41 #comment unable to reproduce error
 * "unable to reproduce error" is a COMMAND_ARGUMENT and will also appear as a comment in JIRA attached to issue CTRL-41
* CTRL-41 #close reproduced error and fixed it!
 * this closes the issue in JIRA and appends the comment "reproduced the error and fixed it!" to the issue in JIRA
* CTRL-41 CTRL-45 CTRL-54 #resolve 
 * closes multiple issues without comment

Not all issues in GitHub will have an associated issue in JIRA. Take care to review the descriptions of issues to stay in compliance with our communication and collaboration guidelines. Smart Commits should also follow the standards for normal commits listed below.


Commit messages should:
* Contain a one-line subject, followed by one line of white space, followed by descriptive paragraphs.
* Contain a short reference to the feature or subsystem the commit effects, in square brackets, at the start of the subject line. Example: [bugfix] Logic Analyzer
* Contain a reference to a relevant issue number in the body of the commit.
  * This is important for traceability. You cannot tell what branch a commit was authored on easily.
  * May be omitted if the issue is obvious.
* Describe the change that was made.
* Provide sufficient information for a reviewer to understand the changes made and their relationship to the previous code.


Commit messages should not:
* Exceed 50 characters on the subject line.
* Exceed 72 characters in the body.
  * Exception: error messages may go over this character limit.
  
## Issue Reporting

Issues are meant to capture specific, actionable tasks. These include new feature requests, bugs, optimizations, etc. Be aware that issues are generated in two ways: the vast majority originate from the top down as planning sessions and analysis and design of the system. Others come from the bottom up as bug reports, questions, or requests by the community on GitHub.

Issues are organized into Milestones. Milestones collect and focus work on important or time-sensitive tasks. Milestones will almost always have a corresponding JIRA task - this is indicated by an issue tag such as "[CTRL-41]". Any issue, commit message, or milestone that has such a tag is linked to an issue in JIRA. Take care to read the [above notes on JIRA integration](#commit-message-standards) to understand the syntax used in comments and commits.


Issues should include:
* A short description of the issue or request.
* A longer-form description. Steps to reproduce the issue where applicable.
* When possible, a description of the impact of the issue.
* Tag the issue with a relevant label. Update tags as required.
* An assessment of the severity of the issue.
  * Trivial - minimal impact on functionality.
  * Critical - large scale loss of functionality of one or two subsystems.
  * Blocker - Harmful behavior, severely compromises entire project.

Issues are tracked at https://github.com/rLoopTeam/eng-software-pod/issues. Please remember to tag issues where possible.

## Checklists


The copy and paste the following checklists to  pull requests when the are filed (author) and when they are merged (reviewer).


### Author Checklist
```
- [] Changes address original issue.
- [] Changes coply with code standards.
- [] Build passes verification tests.
```



### Reviewer Checklist
```
- [] Changes appear to address issue.
- [] Code style and in-line documentation appropriate.
- [] Commit messages meet standards.
- [] Passes verification tests.
```








