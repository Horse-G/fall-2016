# Machine Learning

## Lecture 01, 2016-09-07
### Overview
#### Learning from data
Machine learning is the study of computational mechanisms that "learn" from data in order to make predictions and decisions.
#### Examples
1. ~Image classification~: Birdwatchers take pictures of birds, and want to organize photos by species. The *goal* would be to automatically recognize bird species in new photos.
2. ~Recommender system~: Netflix users watch moves and provide ratings. THe *goal* would be to predict the rating a user will provide on a movie not yet watched. The *real goal* is actually keep users as paying customers.
3. ~Machine translation~: Linguists provide translations of all English language books into French, sentence-by-sentence. THe *goal* would be automatically translate any English sentence into French.
4. ~Personalized medicine~: Physicians ateend to patients, prescribe treatments, and observe health outcomes. The *goal* would be to prescribe personalized treatment for patients that delivers the best possible health outcomes.

#### Basic setting
Given *data* (of labelled examples ~x,y~) where each input x is a description of an instance and each label y is an annotation relevant to the task, the *goal* is to "learn" a function of ~inputs -> actions~ from the data, such that for a new input x (without seeing its corresponding label y), the action f(x) is a "good" action.

Typically, for a *prediction problem*, we have ~Actions = Labels~ (we want the function to predict labels of new inputs).

#### Prediction problems
*goal* is to learn a prediction function that provides the labels of new inputs

                          new unlabelled example ->
past labelled examples -> learning algorithm -> learned predictor -> predicted label

#### Basic issues
1. What information should be recorded in the inputs, and how should they be represented?
2. What kinds of predictions functions should consider?
3. How should data be used to select a predictor?

#### Special case: binary classification
Using the image classification problem from above. If given two images, and you are only checking whether or not the birds or indigo buntings.

*THIS IS HARD*
1. Only have labels for 2 birds, which together comprise a miniscule fraction of the input space of all photographs of birds.
2. Relationship between the input x and correct label y may be complicated, possibly ambiguous/non-deterministic!
3. Can be many functions that perfectly match inputs to labels on (x,y). WHich should we pick?

#### Machine learning in context
Two realms of this problem solving:
*Intelligent systems*
The goal was to make robust systems with "human-like" behavior, but often hard-coded solutions were too complex/not robust.
- How do we learn from past experiences to perform well in the future?

*Algorithmic statistics*
The goal is to statistically analyze large, complex data sets. In the past there were small data sets with few degrees of freedom, and data collection and analysis was done by hand/eye. Now there are millions of data and variables, and they are collected through high volume automatic processes.
- How can we automate statistical analysis for modern application?

### Topics for the course
1. Non-parametric methods (nearest neighbors, decision trees)
2. Parametric methods (generative models, linear & non-linear models)
3. Reductions (boosting, multi-class -> binary)
4. Regression (least squares, Lasso)
5. Representation learning (mixture models, collaborative filtering)

#### Other topics
- distributed learning
- casual inference
- privacy and fairness
- semi-supervised learning
- online learning

### Pre-requisites
- linear algebra
- probability
- multivariate calculus
- basic algorithms and data structures
- Python or MATLAB programming ability

### Requirements
- complete assigned readings
- attend lecture, read slides
- 7 homeworks
- midterm & final

http://www.cs.columbia.edu/~djhsu/coms4771-f16/
