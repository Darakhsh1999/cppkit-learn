import os
import numpy as np
import pandas as pd
from perf_timer import Timer
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error


timer = Timer()

# Load train data
timer.start()
train_data = pd.read_csv(os.path.join("..","data","regression_data_train.csv"))
data_load_time = timer.stop()

y_train = train_data["target"]
X_train = train_data.drop(columns="target", axis=1)

# Load test data
test_data = pd.read_csv(os.path.join("..","data","regression_data_test.csv"))
y_test = test_data["target"]
X_test = test_data.drop(columns="target", axis=1)

# Fit model
timer.start()
model = LinearRegression()
model.fit(X_train, y_train)
fit_time = timer.stop()

# Predict on test data
timer.start()
y_pred = model.predict(X_test)
inference_time = timer.stop()

# Calculate score
mse = mean_squared_error(y_test,y_pred)

betas = np.array([model.intercept_]+list(model.coef_))

# Result logging
print(f"Data loading time: {1000*data_load_time:.4f} ms")
print(f"Fit time: {1000*fit_time:.4f} ms")
print(f"Inference time: {1000*inference_time:.4f} ms")
print(f"MSE = {mse:.3f}")
np.set_printoptions(suppress=True)
print(f"Coefficients {betas}")
print(f"y_pred = {y_pred[0]:.3f}")