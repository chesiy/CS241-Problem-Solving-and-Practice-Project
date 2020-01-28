# Predict US Adult Income Using Logistical Regression
---------------------- 
## Brief Introduction
This is the course project for Problem Solving and Practice Course(CS241), which solves a classification task using logistical regression.  
The data set is 'US Adult Income' on Kaggle ('https://www.kaggle.com/johnolafenwa/us-census-data'), containing 48842 records.
## Data Preprocessing
1.Define and remove dirty data.  
2.Transfer some data into one-hot encoding.  
3.Normalize some data entries.
## Data Visualization
Design a small tool using FLTK which can generate bar charts, line charts, and so on.
## Logistical Regression
Complete a logistical regression algorithm with only C++ STL, and reach accuracy 78.43%, better than DummyClassifiers in Pythom. Here shows the pseudo code:  
`while iteration_time > 0`  
     `Y'=sigmoid(X*W); `  
     `for i in Y':`  
     `Loss=-Y[i]*log(Y'[i])-(1-Y[i])*log(1-Y'[i]); //count loss`  
     `dW=X^T*(Y'-Y);`  
      `W=W-dW*learning_rate;  //updata W using gradient descent`  
     `iteration_time--;`  
`end While`

     
