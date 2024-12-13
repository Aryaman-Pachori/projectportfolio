# Loan Default Risk Analysis

## Overview
This project focuses on predicting loan default risks using a Kaggle dataset. The goal is to build a machine learning model that predicts whether a borrower will default on a loan based on various financial and demographic factors. The analysis is done using Python in a Google Colab notebook.

## Dataset
The dataset used in this project is publicly available on Kaggle. It contains several features related to loan applicants, such as income, credit score, loan amount, and employment status. The target variable indicates whether the borrower defaulted on the loan.

### Key Features:
- **Loan Amount:** The total loan amount applied for.
- **Annual Income:** The borrower's annual income.
- **Credit Score:** The borrower's credit score.
- **Employment Status:** Whether the borrower is employed or not.
- **Loan Purpose:** The purpose of the loan.
- **Default Status:** Whether the borrower defaulted on the loan (target variable).

## Installation
To run the project in Google Colab, simply open the notebook in the provided repository. Ensure you have the necessary libraries installed by running the following command in the notebook:
```!pip install -r requirements.txt ```

## Requirements: 
- python 3.x
- pandas
- numpy
- scikit-learn
- matplotlib
- seaborn
- tensorflow
- kaggle (for dataset access) 

## Project Structure
``` loan-default-risk-analysis/
├── loan_default_analysis.ipynb  # Jupyter notebook for analysis and model training
├── requirements.txt             # List of dependencies
└── README.md                    # Project information
```

## Steps Involved

1. **Data Preprocessing:**
   - Load and inspect the dataset.
   - Handle missing values.
   - Encode categorical variables.

2. **Exploratory Data Analysis (EDA):**
   - Visualize distributions of key variables.
   - Analyze correlations between features and the target variable.

3. **Feature Engineering:**
   - Normalize numerical features.
   - Create new features, if necessary.

4. **Model Training:**
   - Split the data into training and testing sets.
   - Train multiple machine learning models (e.g., Logistic Regression, Random Forest, XGBoost).
   - Evaluate model performance using accuracy, precision, recall, and F1 score.

5. **Model Evaluation:**
   - Compare model performance on the test set.
   - Select the best-performing model.

## Usage

1. Open the `loan_default_analysis.ipynb` notebook in Google Colab or Jupyter Notebook.
2. Run the cells sequentially to perform the analysis, train models, and evaluate results.
3. Modify and experiment with the code to try different models or improve performance.

## Results

- The models provide accuracy, precision, recall, and F1 score metrics.
- Visualizations include feature importance, distribution of loan defaults, and confusion matrix.

## Conclusion

This project demonstrates how machine learning can be used to predict loan defaults, assisting financial institutions in making informed decisions. The analysis can be further enhanced by incorporating additional features, improving preprocessing steps, or trying more advanced algorithms.

## Acknowledgements

- The dataset is provided by Kaggle and can be accessed [here](https://www.kaggle.com/competitions/home-credit-default-risk/data).
- Thanks to the open-source community for the libraries and tools used in this project.
